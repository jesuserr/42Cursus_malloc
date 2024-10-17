#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
        i++;
    }
    return (0);
}
// gcc -o test1 test1.c && /usr/bin/time -v ./test1 0.00
// gcc -o test1 test1.c && ./run.sh /usr/bin/time -v ./test1