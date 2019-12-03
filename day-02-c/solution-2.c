#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t parse_input(
	size_t* code, char* src, size_t src_length
) {
	size_t cursor = 0;
	size_t code_cursor = 0;
	while (cursor < src_length) {
		if (isdigit(src[cursor])) {
			char buf[16];
			size_t i = 0;
			while (
				cursor < src_length &&
				isdigit(src[cursor])
			) {
				buf[i++] = src[cursor++];
			}
			buf[i] = '\0';
			size_t l = strtol(buf, NULL, 10);
			code[code_cursor++] = l;
		} else if (
			src[cursor] == ',' ||
			src[cursor] == '\n'
		) {
			cursor++;
		} else {
			printf("\nUnexpected char %c\n", src[cursor]);
			abort();
		}
	}
	return code_cursor;
}

void dump_code(size_t* code, size_t code_length) {
	for (int i = 0; i < code_length; i++) {
		printf("%zu ", code[i]);
		if (i > 0 && (i+1) % 4 == 0) { printf("\n"); }
	}
	printf("\n");
}

bool run_code(size_t* code, size_t code_length) {
	size_t cursor = 0;
	while (cursor < code_length) {
		switch (code[cursor]) {
		case 1: { // ADD
			size_t a = code[code[cursor + 1]];
			size_t b = code[code[cursor + 2]];
			code[code[cursor + 3]] = a + b;
			cursor += 4;
		} break;
		case 2: { // MULTIPLY
			size_t a = code[code[cursor + 1]];
			size_t b = code[code[cursor + 2]];
			code[code[cursor + 3]] = a * b;
			cursor += 4;
		} break;
		case 99: // HALT
			return true;
		default: // Invalid machine state
			return false;
		}
	}
	assert(false);
}

int main() {
	// Reserve space for code
	size_t code[512];

	// Parse input
	char src[513];
	src[512] = '\0';
	size_t src_length = fread(
		src, sizeof(char), 512, stdin
	);
	size_t code_length = parse_input(code, src, src_length);

	size_t code_copy[512];
	for (int noun = 0; noun <= 99; noun++) {
		for (int verb = 0; verb <= 99; verb++) {
			memcpy(code_copy, code, sizeof(size_t) * code_length);
			code_copy[1] = noun;
			code_copy[2] = verb;
			bool ok = run_code(code_copy, code_length);
			if (ok && code_copy[0] == 19690720) {
				printf("noun=%d, verb=%d, 100*noun+verb=%d\n", noun, verb, 100*noun+verb);
				return 0;
			}
		}
	}

	printf("No acceptable input found\n");
	return 1;
}
