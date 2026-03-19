#include <ctype.h>
#include <stdio.h>
#include <string.h>

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
}

static void encode_text(const char *input) {
    for (size_t i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ') {
            printf("/ ");
            continue;
        }

        const char *morse = letter_to_morse(input[i]);
        if (morse != NULL) {
            printf("%s ", morse);
        } else {
            printf("? ");
        }
    }

    printf("\n");
}

static void decode_text(const char *input) {
    char token[16];
    size_t token_len = 0;

    for (size_t i = 0;; i++) {
        char ch = input[i];

        if (ch == '.' || ch == '-') {
            if (token_len + 1 < sizeof(token)) {
                token[token_len++] = ch;
            } else {
                printf("? ");
                token_len = 0;
                while (input[i + 1] == '.' || input[i + 1] == '-') {
                    i++;
                }
            }
            continue;
        }

        if (token_len > 0) {
            token[token_len] = '\0';
            putchar(morse_to_char(token));
            token_len = 0;
        }

        if (ch == '/') {
            putchar(' ');
        } else if (ch == '\0') {
            break;
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
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
        decode_text(input);
    } else {
        encode_text(input);
    }

    return 0;
}
