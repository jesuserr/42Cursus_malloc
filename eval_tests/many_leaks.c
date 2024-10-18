//#include "../srcs/malloc.h"
#include <stdlib.h>

void* unoptimized_malloc(size_t size) {
    return malloc(size);
}

int main(void) {
    for (size_t i = 0; i < 1024; ++i)
    {
        unoptimized_malloc(128);
        unoptimized_malloc(1024);
        unoptimized_malloc(4096);
    }
    //show_alloc_mem();
}
// gcc -o many_leaks many_leaks.c -L. -lft_malloc && ./run.sh ./many_leaks
// gcc -o many_leaks many_leaks.c -L. -lft_malloc && ./run.sh valgrind ./many_leaks 

// it should appear 5,373,952 bytes in 3,072 blocks
// (128 * 1024) + (1024 * 1024) + (1024 * 4096) = 5,373,952