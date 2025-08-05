#include <string.h>
#include <stdio.h>

struct Bitmap {
	unsigned int file_size;
	unsigned int reserved;
	unsigned int offset;
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned int planes;
	unsigned int bits_per_pixel;
	unsigned int compression;
	unsigned int image_size;
	unsigned int x_pixels_per_meter;
	unsigned int y_pixels_per_meter;
	unsigned int colors_used;
	unsigned int important_colors_used;
};

int get_row_length(int width) {
	int check = (width * 3) % 4;
	if (check == 0) {
		return width * 3;
	} else {
		return (width * 3) + (4 - check);
	}
}

void print_file_info(struct Bitmap bitmap) {
	printf("File size: %d\n", bitmap.file_size);
	printf("Reserved: %d\n", bitmap.reserved);
	printf("Offset: %d\n", bitmap.offset);
	printf("Header size: %d\n", bitmap.header_size);
	printf("Width: %d\n", bitmap.width);
	printf("Height: %d\n", bitmap.height);
	printf("Planes: %d\n", bitmap.planes);
	printf("Bits per pixel: %d\n", bitmap.bits_per_pixel);
	printf("Compression: %d\n", bitmap.compression);
	printf("Image size: %d\n", bitmap.image_size);
	printf("x/m: %d\n", bitmap.x_pixels_per_meter);
	printf("y/m: %d\n", bitmap.y_pixels_per_meter);
	printf("Colors: %d\n", bitmap.colors_used);
	printf("IColors: %d\n", bitmap.important_colors_used);
}

void load_bitmap(char *filename) {
	FILE *fp = fopen(filename, "r");

	unsigned char file_type[2] = {};
	struct Bitmap bitmap;

	if (fp == NULL) {
		printf("File not found: %s\n", filename);
		return;
	}

	fread(file_type, 1, 2, fp);

	if (strcmp(file_type, "BM") == 0) {
		// Read file header:
		fread(&bitmap.file_size, 1, 4, fp);
		fread(&bitmap.reserved, 1, 4, fp);
		fread(&bitmap.offset, 1, 4, fp);
		// Read image header:
		fread(&bitmap.header_size, 1, 4, fp);
		fread(&bitmap.width, 1, 4, fp);
		fread(&bitmap.height, 1, 4, fp);
		fread(&bitmap.planes, 1, 2, fp);
		fread(&bitmap.bits_per_pixel, 1, 2, fp);
		fread(&bitmap.compression, 1, 4, fp);
		fread(&bitmap.image_size, 1, 4, fp);
		fread(&bitmap.x_pixels_per_meter, 1, 4, fp);
		fread(&bitmap.y_pixels_per_meter, 1, 4, fp);
		fread(&bitmap.colors_used, 1, 4, fp);
		fread(&bitmap.important_colors_used, 1, 4, fp);

		//print_file_info(bitmap);

		// Read image data - this should use malloc() instead of dynamic allocation
		unsigned char image[bitmap.image_size];
		unsigned int bytes = fread(&image, 1, bitmap.image_size, fp);
		printf("Read %d bytes.\n", bytes);

		int row_length = get_row_length(bitmap.width);

		//for (int y = 0; y < bitmap.height; y++) {
		//	for (int x = 0; x < row_length; x+=3) {
		//		printf("%x %x %x :: ", image[x], image[x+1], image[x+2]);
		//	} printf("\n");
		//}

		for (int y = bitmap.height - 1; y >= 0; y--) {
			for (int x = 0; x < bitmap.width * 3; x+=3) {
				char buffer[30] = {};
				unsigned int start = x + (y * row_length);
				unsigned int blue = image[start];
				unsigned int green = image[start + 1];
				unsigned int red = image[start + 2];
				//printf("%x: %x.%x.%x ", start, red, green, blue);
				snprintf(buffer, 30, "\033[48;2;%d;%d;%dm \033[0m", red, green, blue);
				printf("%s", buffer);
			}
			printf("\n");
		}
	}
	else {
		printf("Invalid file format: %s", file_type);
	}

	fclose(fp);
}

int main(int argc, char **argv) {
	
	if (argc > 1) {
		for (int a = 1; a < argc; a++) {
			if (strcmp(argv[a], "/?") == 0) {
				puts("Available flags:");
				puts("\t-f [filename]\tLoads the specified file and displays it.");
			}
			else if (strcmp(argv[a], "-f") == 0) {
				if (argc > a + 1) { a++; load_bitmap(argv[a]); }
			}
		}
	}

	return 0;
}
