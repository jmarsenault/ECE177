#include <stdio.h> 	// allows use of printf and scanf functions

int main() {
	int a;
	int b;
	int c;
	double x1;
	double x2;

	printf("Please enter the value of a.\n");

	scanf("%d", &a);

	printf("Please enter the value of b.\n");

	scanf("%d", &b);

	printf("Please enter the value of c.\n");

	scanf("%d", &c);

	x1 = (((b * -1) + sqrt(b * b - 4 * a * c)) / (2 * a));
	x2 = (((b * -1) - sqrt(b * b - 4 * a * c)) / (2 * a));

	printf("The first value of x is %lf.\n", x1);
	printf("The second value of x is %lf.", x2);

	return 0;
}		// End main()
