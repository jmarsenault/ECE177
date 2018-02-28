#include <stdio.h>
int main() {

int h,m,s,i,value,t,mask,x;


do {
printf("Enter hours, min, sec:");
scanf("%d %d %d",&h,&m,&s);


for(t = 0; t < 3; t++){
        printf("\n");
    if(t == 0) {
        value = h;

        if(value < 0 || value >12){
            printf("ERROR: %d\n",value);
            value = -1;
        }
    }
    if(t == 1) {
        value = m;

        if(value < 0 || value >=60){
            printf("ERROR: %d\n",value);
            value = -1;
        }
    }
    if(t == 2) {
        value = s;

        if(value < 0 || value >=60){
            printf("ERROR: %d\n",value);
            value = -1;
        }
    }
if(value != -1){
for (i = 0; i <= 1; i++){
        if (i == 0) {
            x = value / 10;
        }
        if (i == 1){
            x = value % 10;
        }
for(mask = 0x8; mask > 0; mask>>=1){


        if (x & mask){
	printf("*");
    }
    else {
        printf("_");
        }
                }
                printf("\n");

            }
        }

    }
 printf("\n\n\n");
}
while(h!=0||m!=0||s!=0);
return 0;
}

