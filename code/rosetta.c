#include <stdio.h>

void rosetta(char *text) {
	
	printf(" IDX  Dec  Hex  Oct       Bin  C\n");
	printf("====  ===  ===  ===  ========  =\n");
	
	int index = 0;
	
	while (*text != '\0') {
		printf("[%2u]  %3u  %3x  %3o  ", index, *text, *text, *text);
		// Print the binary representation of the character
		for (int b = 7; b >= 0; b--) {
			int bit = (*text >> b) & 0b00000001;
			printf("%u", bit);
		}
		printf("  %c\n", *text);
		text++;
		index++;
		if (index > 20) { break; }
	}

	printf("\n");
}