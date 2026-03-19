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

int main(int argc, char *argv[]) {
    const char *input;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return 1;
    }

    input = argv[1];

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
    return 0;
}
