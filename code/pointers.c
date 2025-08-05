#include <stdio.h>

int main()
{
    int i = 7;		// i = simple integer
	int j = 5;		// j = simple integer
    int *p = &i;	// p = pointer to integer i
    int **d = &p;	// d = pointer to pointer p

	printf("int i = 7;\n");
    printf(">> i (%d) is stored at address %p\n\n", i, &i);

	printf("int *p = &i;\n");
	printf(">> The value of p is the address of i:\n");
    printf(">> p (%p) == &i (%p) and is stored at %p\n\n", p, &i, &p);

	printf("int **d = &p;\n");
	printf(">> The value of d is the address of p:\n");
    printf(">> d (%p) == &p (%p) and is stored at %p\n\n", d, &p, &d);

	printf(">> Dereferencing d gives us p, which holds the address of i:\n");
    printf(">> *d (%p) == p (%p) == &i (%p)\n\n", *d, p, &i);
    
	printf(">> Double dereferencing d gives us the value of i:\n");
	printf(">> **d (%d) == *p (%d) == i (%d)\n\n", **d, *p, i);

	**d = 3;
	printf("**d = 3;\n");
	printf(">> The value of i is now %d\n\n", i);

	*d = &j;
	printf("*d = &j;\n");
	printf(">> Double dereferencing d now gives us the value of j:\n");
	printf(">> **d (%d) == *p (%d) == j (%d)\n\n", **d, *p, j);

    return 0;
}
