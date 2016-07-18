#include<stdio.h>

int main()
{
	char * end;
    int result = strtol("0x065", &end,16);
    printf("%d\n", result);
    //printf("%s", end[0]);
    printf("%d\n", end[0] == '\0' );
    return 0;

}