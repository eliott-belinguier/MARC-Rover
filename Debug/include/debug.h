#ifndef _DEBUG_H_
#define _DEBUG_H_

/**
 * @file debug.h
 * @brief Debugging macros for conditional compilation of debug statements.
 *
 * This header defines macros for conditional debugging. If the `DEBUG` macro is defined,
 * debug print macros will output to standard output or a specified file descriptor.
 * Otherwise, they will be compiled out, resulting in no additional runtime cost.
 */

#ifdef DEBUG

#include <stdio.h> // Standard I/O for printf
/**
 * @def DEBUG_PRINTF(format, ...)
 * @brief Prints formatted output to standard output if DEBUG is defined.
 *
 * This macro behaves like `printf`, but only compiles when `DEBUG` is defined.
 * When debugging is enabled, this can be used to output debug information to
 * the console. Otherwise, it will not output anything.
 *
 * @param format A C string that contains the text to be written, with
 * optional format specifiers.
 * @param ... Additional arguments, depending on the format specifiers.
 */
#define DEBUG_PRINTF(format, ...) printf(format, ##__VA_ARGS__)

/**
 * @def DEBUG_DPRINTF(fd, format, ...)
 * @brief Prints formatted output to a specified file descriptor if DEBUG is defined.
 *
 * This macro behaves like `dprintf`, printing to a file descriptor passed as the
 * first argument, but only compiles when `DEBUG` is defined.
 *
 * @param fd The file descriptor where the output should be written.
 * @param format A C string that contains the text to be written, with
 * optional format specifiers.
 * @param ... Additional arguments, depending on the format specifiers.
 */
#define DEBUG_DPRINTF(fd, format, ...) dprintf(fd, format, ##__VA_ARGS__)

/**
 * @def DEBUG_INST(...)
 * @brief Executes code within a block only if DEBUG is defined.
 *
 * This macro allows you to execute a block of code conditionally based on whether
 * `DEBUG` is defined. If `DEBUG` is not defined, the block will be ignored at compile time.
 *
 * @param ... The block of code to execute if DEBUG is defined.
 */
#define DEBUG_INST(...) {__VA_ARGS__}

#else

/**
 * @def DEBUG_PRINTF(format, ...)
 * @brief Does nothing when DEBUG is not defined.
 *
 * This macro is a no-op when `DEBUG` is not defined, so any debug output
 * is omitted from the compiled binary.
 *
 * @param format Ignored.
 * @param ... Ignored.
 */
#define DEBUG_PRINTF(format, ...) ((void) 0)

/**
 * @def DEBUG_DPRINTF(fd, format, ...)
 * @brief Does nothing when DEBUG is not defined.
 *
 * This macro is a no-op when `DEBUG` is not defined, so any output to file
 * descriptors is omitted from the compiled binary.
 *
 * @param fd Ignored.
 * @param format Ignored.
 * @param ... Ignored.
 */
#define DEBUG_DPRINTF(fd, format, ...) ((void) 0)

/**
 * @def DEBUG_INST(...)
 * @brief Does nothing when DEBUG is not defined.
 *
 * This macro is a no-op when `DEBUG` is not defined, so any code within its block
 * is omitted from the compiled binary.
 *
 * @param ... Ignored.
 */
#define DEBUG_INST(...) ((void) 0)

#endif
#endif
