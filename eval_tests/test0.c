#include <stdlib.h>

int      main(void)
{
    int   i;
    char  *addr;

    i = 0; 
    while (i < 1024) 
    {
        i++;
    } 
    return (0); 
}

// gcc -o test0 test0.c && /usr/bin/time -v ./test0 0.00
// gcc -o test0 test0.c && ./run.sh /usr/bin/time -v ./test0