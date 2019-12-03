#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
			printf("Unexpected char %c\n", src[cursor]);
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

void run_code(size_t* code, size_t code_length) {
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
			return;
		default:
			printf("Invalid machine state reached.\n");
			dump_code(code, code_length);
			exit(1);
		}
	}
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
	
	// Initialize to 1202 program alarm state
	code[1] = 12;
	code[2] = 2;
	run_code(code, code_length);
	printf("%zu\n", code[0]);
}
