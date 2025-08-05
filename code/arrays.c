#include <stdio.h>

// Arrays are like pointers, except they also allocate memory for all their elements.  Arrays
// will decay into pointers when passed as parameters or used in functions:
//		int arr[5];
//		int *ptr = arr;			// 'arr' decays to 'int*'
//		int val = *(arr + 2);	// 'arr' decays to 'int*'
// Arrays do not decay in certain instances, such as when passed to sizeof()

typedef struct person {
	char *name;
	int age;
} Person;

void print_array() {
	int nums[5] = {1, 2, 3, 4, 5};
	
	puts("Print array data using array indexing:");
	for (int i = 0; i < 5; i++) {
		printf("Array item %d has value %d at address %p\n", i, nums[i], &nums[i]);
	}
	printf("\n");
	
	puts("Print array data using pointer arithmetic:");
	for (int i = 0; i < 5; i++) {
		printf("Array item %d has value %d at address %p\n", i, *(nums + i), nums + i);
	}
}

void print_struct_array() {
	Person people[2] = {{"Phillip", 25}, {"Achmed", 46}};

	puts("Print struct array data using array indexing:");
	for (int i = 0; i < 2; i++) {
		printf("%s is %d years old.\n", people[i].name, people[i].age);
	}

	printf("\n");

	puts("Print struct array data using pointer arithmetic:");
	for (int i = 0; i < 2; i++) {
		printf("%s is %d years old.\n", (people + i)->name, (people + i)->age);
	}
}

int main() {
	print_array();
	printf("\n");
	print_struct_array();
}