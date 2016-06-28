#include <stdio.h>
#include <string.h>

// you may ignore the following two lines
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main(int argc, char** argv) {
   int x[5];
   x[0] = 3; x[1] = 2; x[2] = 1; x[3] = 0;
   char *y = (char*) x;
   printf("%p", x);
   printf("\n this is a new line" );
   printf("%p", x+4);
   return 0;
}