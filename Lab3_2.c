#include <stdio.h>
int main() {

    char c;
    unsigned char uc;

printf("%d\t%u\n", (short)45, (unsigned short)45);

printf("%d\t%u\n", (short)150, (unsigned short)150);

printf("%d\t%u\n", (short)-150, (unsigned short)-150);

printf("%d\t%u\n", (short)300, (unsigned short)300);

printf("%d\t%u\n", (short)-1, (unsigned short)-1);

printf("%d\t%u\n", (short)65535, (unsigned short)65535);


c = 45;
printf("%d\t%d\t%u\n",45, (short)c, (unsigned short)c);

c = 150;
printf("%d\t%d\t%u\n",150, (short)c, (unsigned short)c);

c = -150;
printf("%d\t%d\t%u\n",-150, (short)c, (unsigned short)c);

c = 300;
printf("%d\t%d\t%u\n",300, (short)c, (unsigned short)c);

c = -1;
printf("%d\t%d\t%u\n",-1, (short)c, (unsigned short)c);

c = 65535;
printf("%d\t%d\t%u\n",65535, (short)c, (unsigned short)c);

uc = 45;
printf("%d\t%d\t%u\n",45, (short)uc, (unsigned short)uc);

uc = 150;
printf("%d\t%d\t%u\n",150, (short)uc, (unsigned short)uc);

uc = -150;
printf("%d\t%d\t%u\n",-150, (short)uc, (unsigned short)uc);

uc = 300;
printf("%d\t%d\t%u\n",300, (short)uc, (unsigned short)uc);

uc = -1;
printf("%d\t%d\t%u\n",-1, (short)uc, (unsigned short)uc);

uc = 65535;
printf("%d\t%d\t%u\n",65535, (short)uc, (unsigned short)uc);

return 0;

}
