#include <stdio.h>
int main() {

int shape,fill,size,zigzag,c = 0, r = 0,n=0;


for(;shape != 4;){ // checks if user has chosen to quit
printf("Enter Shape (1) Square (2) Triangle (3) ZigZag (4) Quit\n");
scanf("%d", &shape);

switch (shape) {

case 1: //Prints a square prompting for size and the option of filled or not
    printf("Enter size\n");
    scanf("%d", &size);
    printf("(0) Fill (1) No fill\n");
    scanf("%d", &fill);

    if (fill == 0){
        for (r=0; r<size; r++){ //filled square
                printf("\n");
                c=0;
        for (c=0; c<size; c++){
                printf("*");
            }
        }
        printf("\n");
    }
    else {
        for (c=0; c<size; c++){ //hollow square
                printf("*");
            }
        for (r=0; r<size-2; r++){
                printf("\n");
                printf("*");
                c=0;
            for (c=0; c<size-2;c++){
                printf(" ");
            }
                printf("*");

            }
            printf("\n");
            for (c=0; c<size; c++){
                printf("*");
            }
                printf("\n");
            }
                break;

case 2: //prints a triangle prompting for size and filled or not
    printf("Enter size\n");
    scanf("%d", &size);
    printf("(0) Fill (1) No fill\n");
    scanf("%d", &fill);

    if (fill == 0){ //filled triangle

        for (c=0; c<=size; c++){
        for (r=0; r<c; r++){
            printf("*");
            }
            printf("\n");
        }
    }
    else { //hollow triangle
        printf("*");
        for (r=2; r<=size; r++){
                printf("\n");
                printf("*");
                c=0;
            for (c=0; c<r-2;c++){
                printf(" ");
            }
                printf("*");

            }
            printf("\n");
            for (c=0; c<size; c++){
                printf("*");
            }
                printf("\n");
    }
        break;

case 3: //prints a zigzag prompting for size and repetitions
    printf("Enter size\n");
    scanf("%d", &size);
    printf("Enter number of zig zags\n");
    scanf("%d", &zigzag);
    for(n=0;n<zigzag;n++){
    for (r=1; r<=size; r++){
                printf("\n");
                c=0;
            for (c=0; c<r-1;c++){
                printf(" ");
            }
                printf("*");

            }
            for (r=size; r>=1; r--){ //inverse of above function to make zig zag pattern
                printf("\n");
                c=0;
            for (c=0; c<r-1;c++){
                printf(" ");
            }
                printf("*");

            }
    }
            printf("\n");
            break;

    }

        }

return 0;
}

