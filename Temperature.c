#include <stdio.h> 	// allows use of printf and scanf functions

int main() {
	float c;
	float f;

	printf("Please enter the temperature in degrees Fahrenheit\n");

	scanf("%f", &f);

	c = (f - 32.0) * (5.0 / 9.0);

	printf("The temperature is %f degrees Celsius", c);

	return 0;
}		// End main()
