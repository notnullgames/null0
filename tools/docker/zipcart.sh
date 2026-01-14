#!/bin/bash

# this will build a cart (zip) from some files, respecting .cartignore

# Check if all required arguments are provided
if [ -z "${1}" ] || [ -z "${2}" ] || [ -z "${3}" ]; then
    echo "Usage: $0 CART_NAME DIR_IN DIR_OUT"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    echo "  DIR_IN     Input directory to package as cart"
    echo "  DIR_OUT    Output directory for the cart file"
    echo ""
    echo "Optional:"
    echo "  .cartignore  Place this file in DIR_IN to exclude files (gitignore syntax)"
    exit 1
fi

CART_NAME="${1}"
DIR_IN="${2}"
DIR_OUT="${3}"

# Function to check if a file matches any ignore pattern
matches_pattern() {
    local file="$1"
    local pattern="$2"
    
    # Remove leading slash from pattern
    pattern="${pattern#/}"
    
    # Convert gitignore pattern to bash glob
    # Handle ** wildcard
    pattern="${pattern//\*\*/.*}"
    # Handle directory patterns
    [[ "$pattern" == */ ]] && pattern="${pattern}*"
    
    # Check if file matches pattern (anywhere in path or at root)
    [[ "$file" == $pattern || "$file" == */$pattern ]]
}

should_ignore() {
    local file="$1"
    local ignore_file="$2"
    
    while IFS= read -r pattern; do
        # Skip empty lines and comments
        [[ -z "$pattern" || "$pattern" =~ ^[[:space:]]*# ]] && continue
        
        # Trim whitespace
        pattern=$(echo "$pattern" | xargs)
        
        # Handle negation patterns (!)
        if [[ "$pattern" == !* ]]; then
            pattern="${pattern#!}"
            matches_pattern "$file" "$pattern" && return 1  # Don't ignore
        else
            matches_pattern "$file" "$pattern" && return 0  # Ignore
        fi
    done < "$ignore_file"
    
    return 1  # Don't ignore by default
}

cd "${DIR_IN}"

# Build list of files
FILES=()
while IFS= read -r -d '' file; do
    # Remove leading ./
    file="${file#./}"
    
    # Skip .cartignore itself
    [[ "$file" == ".cartignore" ]] && continue

    # mac makes these dumb files
    [[ "$file" == ".DS_Store" ]] && continue
    
    # Check if should ignore
    if [ -f .cartignore ]; then
        should_ignore "$file" .cartignore || FILES+=("$file")
    else
        FILES+=("$file")
    fi
done < <(find . -type f -print0)

# Create zip only if there are files
if [ ${#FILES[@]} -eq 0 ]; then
    echo "No files to zip (all files excluded or directory empty)"
    exit 0
else
    echo "Adding ${FILES[@]}"
    zip "${DIR_OUT}/${CART_NAME}.null0" "${FILES[@]}"
fi
