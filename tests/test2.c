#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
    void *newMemory = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (newMemory == NULL)
    {
        perror("mmap:");
        return -1;
    }
    printf("Newly allocated memory %p\n", newMemory);
    int *myNewArray = (int *)newMemory;
    myNewArray[100] = 2;
    myNewArray[101] = 3;
    myNewArray[103] = 4;
    printf("%d,%d,%d\n", myNewArray[100], myNewArray[101], myNewArray[103]);
    return 0;
}
