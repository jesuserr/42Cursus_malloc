#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char *str = (char *)malloc(100);
    strcpy(str, "Hola");    
    printf("%s\n",str);
    free(str);
    return(0);
}