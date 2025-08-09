#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
      #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
      #define NOMINMAX
    #endif
    #include <windows.h>
    #include <io.h>
    #define PATH_SEPARATOR '\\'
    #define access _access
    #define F_OK 0
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#elif defined(__linux__)
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    #include <sys/sysctl.h>
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#else
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#endif

/**
 * Get the full path to the current executable
 * Returns malloc'd string that must be freed, or NULL on error
 */
char* get_executable_path() {
    char* path = NULL;
    
#ifdef _WIN32
    DWORD size = MAX_PATH;
    path = malloc(size);
    if (!path) return NULL;
    
    DWORD result = GetModuleFileNameA(NULL, path, size);
    if (result == 0 || result == size) {
        // Path was truncated or error occurred, try with larger buffer
        free(path);
        size = 32768; // Large buffer for long paths
        path = malloc(size);
        if (!path) return NULL;
        
        result = GetModuleFileNameA(NULL, path, size);
        if (result == 0 || result == size) {
            free(path);
            return NULL;
        }
    }
    
#elif defined(__APPLE__)
    uint32_t size = 0;
    _NSGetExecutablePath(NULL, &size); // Get required size
    
    path = malloc(size);
    if (!path) return NULL;
    
    if (_NSGetExecutablePath(path, &size) != 0) {
        free(path);
        return NULL;
    }
    
    // Resolve any symlinks
    char* resolved = realpath(path, NULL);
    if (resolved) {
        free(path);
        path = resolved;
    }
    
#elif defined(__linux__)
    // Try readlink on /proc/self/exe
    size_t size = 1024;
    path = malloc(size);
    if (!path) return NULL;
    
    ssize_t len = readlink("/proc/self/exe", path, size - 1);
    while (len == size - 1) {
        // Buffer might be too small, try larger
        size *= 2;
        char* new_path = realloc(path, size);
        if (!new_path) {
            free(path);
            return NULL;
        }
        path = new_path;
        len = readlink("/proc/self/exe", path, size - 1);
    }
    
    if (len == -1) {
        free(path);
        return NULL;
    }
    
    path[len] = '\0';
    
#elif defined(__FreeBSD__)
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
    size_t size = 0;
    
    // Get required size
    if (sysctl(mib, 4, NULL, &size, NULL, 0) != 0) {
        return NULL;
    }
    
    path = malloc(size);
    if (!path) return NULL;
    
    if (sysctl(mib, 4, path, &size, NULL, 0) != 0) {
        free(path);
        return NULL;
    }
    
#elif defined(__NetBSD__)
    int mib[4] = {CTL_KERN, KERN_PROC_ARGS, -1, KERN_PROC_PATHNAME};
    size_t size = 0;
    
    if (sysctl(mib, 4, NULL, &size, NULL, 0) != 0) {
        return NULL;
    }
    
    path = malloc(size);
    if (!path) return NULL;
    
    if (sysctl(mib, 4, path, &size, NULL, 0) != 0) {
        free(path);
        return NULL;
    }
    
#else
    // Fallback: try /proc/self/exe (Linux-style)
    size_t size = 1024;
    path = malloc(size);
    if (!path) return NULL;
    
    ssize_t len = readlink("/proc/self/exe", path, size - 1);
    if (len == -1) {
        free(path);
        return NULL;
    }
    
    path[len] = '\0';
#endif
    
    return path;
}

/**
 * Get the directory containing the executable
 * Returns malloc'd string that must be freed, or NULL on error
 */
char* get_executable_directory() {
    char* exe_path = get_executable_path();
    if (!exe_path) return NULL;
    
    // Find the last path separator
    char* last_sep = strrchr(exe_path, PATH_SEPARATOR);
    if (!last_sep) {
        free(exe_path);
        // No separator found, assume current directory
        char* current_dir = malloc(2);
        if (current_dir) {
            strcpy(current_dir, ".");
        }
        return current_dir;
    }
    
    // Truncate at the last separator
    *last_sep = '\0';
    
    return exe_path;
}

/**
 * Check if a file exists next to the executable
 * Returns 1 if file exists, 0 if not, -1 on error
 */
char* file_exists_next_to_executable(const char* filename) {
    if (!filename) return NULL;
    
    char* exe_dir = get_executable_directory();
    if (!exe_dir) return NULL;
    
    // Calculate required buffer size
    size_t dir_len = strlen(exe_dir);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + 1 + file_len + 1; // dir + separator + filename + null
    
    char* full_path = malloc(total_len);
    if (!full_path) {
        free(exe_dir);
        return NULL;
    }
    
    // Build the full path
    snprintf(full_path, total_len, "%s%c%s", exe_dir, PATH_SEPARATOR, filename);
    
    // Check if file exists
    int result = (access(full_path, F_OK) == 0) ? 1 : 0;
    
    free(exe_dir);
    if (result == 0) {
        free(full_path);
        return NULL;
    }
    return full_path;
}
