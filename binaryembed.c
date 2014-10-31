/*
 *  binaryembed.c
 *  Neil // 2008-06-09
 */

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** argv) {
	if (argc < 1) {
		printf("Usage: %s <input>", argv[0]);
		return(1);
	}
	
	fprintf(stderr, "Input: %s\n", argv[1]);
	
	FILE* input = fopen(argv[1], "rb");
	if (input == NULL) {
		fprintf(stderr, "Input failed.\n");
		return(2);
	}
	if ( feof(input) ) {
		fprintf(stderr, "Input empty.\n");
		return(3);
	}
	
	long length = 0;
	char* data = malloc(sizeof(char));
	
	printf("//-----------------------------BINARYEMBED CODE BEGIN-----------------------------\n");
	printf("char data[] = \"");
	
	while ( 1 ) {
		fread(data, 1, 1, input);
		if (feof(input)) { // If last read failed, break out of loop.
			break;
		}
		//printf("%d, %d: %c = %x\n", i++, ftell(input), *data, *data);
		printf("\\x%x", *data);
		length += 1;
	}
	
	printf("\";\n");
    printf("long length = %ld;\n", length);
	printf("FILE* output = fopen(\"%s\", \"wb\");\n", argv[1]);
	printf("fwrite(data, 1, length, output);\n");
	printf("//------------------------------BINARYEMBED CODE END------------------------------\n");
	
	return(0);
}
