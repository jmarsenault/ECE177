#include <stdio.h> 	// allows use of printf and scanf functions
#include <math.h>

int main() {
	double	s;
	int s0;
	int v0;
	double a = 32.2;
	int t = 0;

	printf("Please enter the initial position.\n");

	scanf("%d", &s0);

	printf("Please enter the initial velocity.\n");

	scanf("%d", &v0);

	for (t=0; t<= 100; t+=5) {

	s = (s0 + v0 * t - 0.5 * a * t * t);

	printf("The position is %lf feet ", s);
	printf("at %d seconds\n", t);

	}

	return 0;
}		// End main()
