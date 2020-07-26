
#include <stdio.h> /* printf */

int main(int argc , char *argv[])
{
    if(argc != 3)
    {
        printf("arguments errors");
        return 0;
    }

    printf("%d\n", (atoi(argv[1]) * atoi(argv[2])));
    return 0;
}