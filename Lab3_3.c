#include <stdio.h>
int main() {
9i 
int Year = 2019;

int A, B, C, D, E, F, G, H, I, K, L, M, N, P;

//Calculate the date Easter falls on depending on the year.

A = Year % 19;

B = Year / 100;

C = Year % 100;

D = B / 4;

E = B % 4;

F = (B + 8) / 25;

G = (B - F + 1) / 3;

H = (19 * A + B - D - G + 15) % 30;

I = C / 4;

K = C % 4;

L = (32 + 2 * E + 2 * I - H - K) % 7;

M = (A + 11 * H + 22 * L) / 451;

N = (H + L - 7 * M + 114) / 31;

P = (H + L - 7 * M + 114) % 31;

int Month = N; //initializes Month to the value of N.

int Day = P + 1; //initializes Day to the value of P + 1.

//displays the date of Easter depending on the year.

printf("Date of Easter in %d is %d/%d", Year, Month, Day);

return 0;

}
