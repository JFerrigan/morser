/* SPDX-License-Identifier: MIT */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifndef VERSION
#define VERSION "dev"
#endif

static const char *letter_to_morse(char ch) {
    static const char *letters[] = {
        ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",
        ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",
        "...",  "-",    "..-",  "...-", ".--",  "-..-", "-.--", "--.."
    };
    static const char *digits[] = {
        "-----", ".----", "..---", "...--", "....-",
        ".....", "-....", "--...", "---..", "----."
    };

    if (isalpha((unsigned char) ch)) {
        return letters[toupper((unsigned char) ch) - 'A'];
    }

    if (isdigit((unsigned char) ch)) {
        return digits[ch - '0'];
    }

    return NULL;
}

static char morse_to_char(const char *code) {
    static const char *letters[] = {
        ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",
        ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",
        "...",  "-",    "..-",  "...-", ".--",  "-..-", "-.--", "--.."
    };
    static const char *digits[] = {
        "-----", ".----", "..---", "...--", "....-",
        ".....", "-....", "--...", "---..", "----."
    };

    for (size_t i = 0; i < sizeof(letters) / sizeof(letters[0]); i++) {
        if (strcmp(code, letters[i]) == 0) {
            return (char) ('A' + i);
        }
    }

    for (size_t i = 0; i < sizeof(digits) / sizeof(digits[0]); i++) {
        if (strcmp(code, digits[i]) == 0) {
            return (char) ('0' + i);
        }
    }

    return '?';
}

static void print_help(const char *program_name) {
    printf("Usage: %s [OPTION] <text>\n", program_name);
    printf("Encode text to Morse code by default.\n\n");
    printf("Options:\n");
    printf("  -d, --decode  Decode Morse code to text\n");
    printf("  -h, --help    Show this help message\n");
    printf("  -v, --version Show version information\n");
}

static void print_version(void) {
    printf("morser %s\n", VERSION);
}

static int append_text(char *output, size_t output_size, size_t *used, const char *format, ...) {
    va_list args;
    int written;

    if (*used >= output_size) {
        return -1;
    }

    va_start(args, format);
    written = vsnprintf(output + *used, output_size - *used, format, args);
    va_end(args);

    if (written < 0 || (size_t) written >= output_size - *used) {
        return -1;
    }

    *used += (size_t) written;
    return 0;
}

int morser_encode(const char *input, char *output, size_t output_size) {
    size_t used = 0;

    if (output_size == 0) {
        return -1;
    }

    for (size_t i = 0; input[i] != '\0'; i++) {
        const char *code;

        if (input[i] == ' ') {
            if (append_text(output, output_size, &used, "/ ") != 0) {
                return -1;
            }
            continue;
        }

        code = letter_to_morse(input[i]);
        if (append_text(output, output_size, &used, "%s ", code != NULL ? code : "?") != 0) {
            return -1;
        }
    }

    if (used > 0) {
        output[used - 1] = '\0';
    } else {
        output[0] = '\0';
    }

    return 0;
}

int morser_decode(const char *input, char *output, size_t output_size) {
    char token[16];
    size_t token_len = 0;
    size_t used = 0;

    if (output_size == 0) {
        return -1;
    }

    for (size_t i = 0;; i++) {
        char ch = input[i];

        if (ch == '.' || ch == '-') {
            if (token_len + 1 < sizeof(token)) {
                token[token_len++] = ch;
            } else {
                if (append_text(output, output_size, &used, "?") != 0) {
                    return -1;
                }
                token_len = 0;
                while (input[i + 1] == '.' || input[i + 1] == '-') {
                    i++;
                }
            }
            continue;
        }

        if (token_len > 0) {
            token[token_len] = '\0';
            if (append_text(output, output_size, &used, "%c", morse_to_char(token)) != 0) {
                return -1;
            }
            token_len = 0;
        }

        if (ch == '/') {
            if (append_text(output, output_size, &used, " ") != 0) {
                return -1;
            }
        } else if (ch == '\0') {
            break;
        }
    }

    output[used] = '\0';
    return 0;
}

int main(int argc, char *argv[]) {
    char output[4096];
    const char *input;
    int decode = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [OPTION] <text>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        print_version();
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decode") == 0) {
        decode = 1;
        if (argc < 3) {
            fprintf(stderr, "Usage: %s --decode <morse>\n", argv[0]);
            return 1;
        }
        input = argv[2];
    } else {
        input = argv[1];
    }

    if (decode) {
        if (morser_decode(input, output, sizeof(output)) != 0) {
            fprintf(stderr, "Output too large to decode\n");
            return 1;
        }
    } else {
        if (morser_encode(input, output, sizeof(output)) != 0) {
            fprintf(stderr, "Output too large to encode\n");
            return 1;
        }
    }

    printf("%s\n", output);
    return 0;
}
