#include <stdio.h>

int main(void) {
    //Problem: Display a range for a table from n and n^2, for integers ranging from 1-10.

    int i, factorialnumber = 1, n = 12, max_width = 12, min_width = 2;

    printf("TABLE OF FACTORIALS\n");

    for (i = 1; i <= n; i++) {
        factorialnumber *= i;
        printf("%*d", min_width ,i);
        printf("%*d\n", max_width, factorialnumber);
    }
    return 0;
}
