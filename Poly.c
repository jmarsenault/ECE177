#include <stdio.h> 	// allows use of printf and scanf functions

int main() {
	int x;
	int y;

	printf("Please enter the value of x.\n");

	scanf("%d", &x);

	y = x * x * x + 5 * x * x+ 10 * x + 15;

	printf("The value of y is %d.", y);

	return 0;
}		// End main()
