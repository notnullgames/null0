#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "quickjs.h"

// Function to read file contents
static char* read_file(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return NULL;
    }
    
    struct stat st;
    if (fstat(fd, &st) < 0) {
        close(fd);
        fprintf(stderr, "Error: Cannot stat file '%s'\n", filename);
        return NULL;
    }
    
    size_t size = st.st_size;
    char* buffer = malloc(size + 1);
    if (!buffer) {
        close(fd);
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    ssize_t bytes_read = read(fd, buffer, size);
    close(fd);
    
    if (bytes_read != size) {
        free(buffer);
        fprintf(stderr, "Error: Failed to read complete file\n");
        return NULL;
    }
    
    buffer[size] = '\0';
    return buffer;
}

// Game engine API bindings - replace these with your actual engine functions
static JSValue js_log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc > 0) {
        const char *str = JS_ToCString(ctx, argv[0]);
        if (str) {
            printf("JS: %s\n", str);
            JS_FreeCString(ctx, str);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_get_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    // Return current time in milliseconds (mock implementation)
    return JS_NewFloat64(ctx, 1000.0); // Replace with actual time function
}

// Set up game engine bindings
static void setup_game_bindings(JSContext *ctx) {
    JSValue global = JS_GetGlobalObject(ctx);
    
    // Create a 'game' object
    JSValue game_obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, global, "game", game_obj);
    
    // Add console.log function
    JSValue console_obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_log, "log", 1));
    JS_SetPropertyStr(ctx, global, "console", console_obj);
    
    // Add game functions
    JS_SetPropertyStr(ctx, game_obj, "getTime", JS_NewCFunction(ctx, js_get_time, "getTime", 0));
    
    // Add more game engine functions here as needed
    // Example: JS_SetPropertyStr(ctx, game_obj, "drawSprite", JS_NewCFunction(ctx, js_draw_sprite, "drawSprite", 4));
    
    JS_FreeValue(ctx, global);
}

// Execute JavaScript and handle errors
static int execute_js(JSContext *ctx, const char *code, const char *filename) {
    JSValue result = JS_Eval(ctx, code, strlen(code), filename, JS_EVAL_TYPE_GLOBAL);
    
    if (JS_IsException(result)) {
        JSValue exception = JS_GetException(ctx);
        const char *error_str = JS_ToCString(ctx, exception);
        fprintf(stderr, "JavaScript Error: %s\n", error_str ? error_str : "Unknown error");
        JS_FreeCString(ctx, error_str);
        JS_FreeValue(ctx, exception);
        JS_FreeValue(ctx, result);
        return -1;
    }
    
    JS_FreeValue(ctx, result);
    return 0;
}

// Call a JavaScript function if it exists
static void call_js_function(JSContext *ctx, const char *func_name) {
    JSValue global = JS_GetGlobalObject(ctx);
    JSValue func = JS_GetPropertyStr(ctx, global, func_name);
    
    if (JS_IsFunction(ctx, func)) {
        JSValue result = JS_Call(ctx, func, global, 0, NULL);
        if (JS_IsException(result)) {
            JSValue exception = JS_GetException(ctx);
            const char *error_str = JS_ToCString(ctx, exception);
            fprintf(stderr, "Error calling %s: %s\n", func_name, error_str ? error_str : "Unknown error");
            JS_FreeCString(ctx, error_str);
            JS_FreeValue(ctx, exception);
        }
        JS_FreeValue(ctx, result);
    }
    
    JS_FreeValue(ctx, func);
    JS_FreeValue(ctx, global);
}

int main(int argc, char **argv) {
    // Initialize QuickJS runtime
    JSRuntime *rt = JS_NewRuntime();
    if (!rt) {
        fprintf(stderr, "Error: Failed to create QuickJS runtime\n");
        return 1;
    }
    
    JSContext *ctx = JS_NewContext(rt);
    if (!ctx) {
        fprintf(stderr, "Error: Failed to create QuickJS context\n");
        JS_FreeRuntime(rt);
        return 1;
    }
    
    // Set up game engine API bindings
    setup_game_bindings(ctx);
    
    // Load and execute main.js
    char *js_code = read_file("main.js");
    if (!js_code) {
        fprintf(stderr, "Error: Failed to load main.js\n");
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    
    printf("Loading main.js...\n");
    if (execute_js(ctx, js_code, "main.js") < 0) {
        free(js_code);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    
    free(js_code);
    
    // Main loop - call JavaScript update function if it exists
    printf("Starting main loop...\n");
    for (int i = 0; i < 60; i++) { // Run for 60 frames as example
        // Execute any pending JavaScript jobs (for async/await support)
        JSContext *ctx1;
        int ret = JS_ExecutePendingJob(rt, &ctx1);
        if (ret < 0) {
            if (ctx1) {
                JSValue exception = JS_GetException(ctx1);
                const char *error_str = JS_ToCString(ctx1, exception);
                fprintf(stderr, "Async error: %s\n", error_str ? error_str : "Unknown error");
                JS_FreeCString(ctx1, error_str);
                JS_FreeValue(ctx1, exception);
            }
        }
        
        // Call JavaScript update function
        call_js_function(ctx, "update");
        
        // Simulate frame delay
        usleep(16667); // ~60 FPS
    }
    
    // Call cleanup function if it exists
    call_js_function(ctx, "cleanup");
    
    printf("Shutting down...\n");
    
    // Cleanup
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    
    return 0;
}
