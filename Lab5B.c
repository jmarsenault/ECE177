#include <stdio.h>
int main() {

int h,m,s,i,value,t;

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
                for(i = 0; i < 6; i++){
                    printf("%s", value & 0x20 ? "*":"_");
                    value = value<<1;
                }
            }

        }
        printf("\n\n");
    }

while(h!=0||m!=0||s!=0);

return 0;
}
