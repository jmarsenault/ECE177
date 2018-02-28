#include <stdio.h>
int main() {

int h,m,s,i,value,t,x;

    do {
    printf("Enter hours, min, sec:");
    scanf("%d %d %d",&h,&m,&s);

        for(t = 0; t < 3; t++){
            printf("\n");
            if(t == 0) {
                value = h;

                if(value < 0 || value >12){
                    printf("ERROR: %d\n",value);
                    t++;
                }
            }
            if(t == 1) {
                value = m;

                if(value < 0 || value >=60){
                    printf("ERROR: %d\n",value);
                    t++;
                }
            }
            if(t == 2) {
                value = s;

                if(value < 0 || value >=60){
                    printf("ERROR: %d\n",value);
                    t++;
                }
            }
            if (t < 3){
                x = value / 10;
                for(i = 0; i < 4; i++){
                    printf("%s", ((x & 0x08)==0x08)? "*":"_");
                    x = x<<1;
                }
                printf("\n");

                x = value % 10;
                for(i = 0; i < 4; i++){
                    printf("%s", ((x & 0x08)==0x08) ? "*":"_");
                    x = x<<1;
                }
            }

        }
        printf("\n\n");
    }

while(h!=0||m!=0||s!=0);

return 0;
}
