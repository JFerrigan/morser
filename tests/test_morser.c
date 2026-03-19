/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <string.h>

#define main morser_program_main
#include "../morser.c"
#undef main

static int assert_string_equal(const char *label, const char *actual, const char *expected) {
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "%s failed: expected \"%s\", got \"%s\"\n", label, expected, actual);
        return 1;
    }
    return 0;
}

int main(void) {
    char output[256];

    if (morser_encode("SOS 123", output, sizeof(output)) != 0) {
        fprintf(stderr, "encode returned error\n");
        return 1;
    }
    if (assert_string_equal("encode SOS 123", output, "... --- ... / .---- ..--- ...--") != 0) {
        return 1;
    }

    if (morser_decode("... --- ... / .---- ..--- ...--", output, sizeof(output)) != 0) {
        fprintf(stderr, "decode returned error\n");
        return 1;
    }
    if (assert_string_equal("decode SOS 123", output, "SOS 123") != 0) {
        return 1;
    }

    if (morser_encode("a!", output, sizeof(output)) != 0) {
        fprintf(stderr, "encode unsupported returned error\n");
        return 1;
    }
    if (assert_string_equal("encode unsupported", output, ".- ?") != 0) {
        return 1;
    }

    if (morser_decode("... --- ...   .-", output, sizeof(output)) != 0) {
        fprintf(stderr, "decode spacing returned error\n");
        return 1;
    }
    if (assert_string_equal("decode spacing", output, "SOSA") != 0) {
        return 1;
    }

    if (morser_decode("................", output, sizeof(output)) != 0) {
        fprintf(stderr, "decode long token returned error\n");
        return 1;
    }
    if (assert_string_equal("decode long token", output, "?") != 0) {
        return 1;
    }

    if (morser_encode("ABC", output, 4) == 0) {
        fprintf(stderr, "encode small buffer should fail\n");
        return 1;
    }

    if (morser_decode("... --- ...", output, 2) == 0) {
        fprintf(stderr, "decode small buffer should fail\n");
        return 1;
    }

    return 0;
}
