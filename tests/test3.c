#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"

int main()
{
    char *str;
    str = ft_strdup("Hola");
    ft_printf("%s\n",str);
    free(str);
    return(0);
}

// gcc test3.c ../libft/libft.a && ./a.out