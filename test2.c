//#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "srcs/malloc.h"

void    print(char *s)
{
    write(1, s, strlen(s));
}

int     main(void)
{
    int   i;
    char  *addr;

    i = 0;
    while (i < 1024) 
    {
        addr = (char*)malloc(1024);
        if (addr == NULL)
        {
            print("Failed to allocate memory\n");
            return (1);
        }
        addr[0] = 42;
        free(addr); 
        i++; 
    }
    return (0);
}


//gcc -c test2.c -o test2.o
//gcc -o test2 test2.o -lft_malloc -L.
//LD_PRELOAD=./libft_malloc.so LD_LIBRARY_PATH=. cat test2.c

// ldd test2
