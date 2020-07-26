#include <pthread.h>    /* pthraedCreate */
#include <stdio.h>      /* printf */

#define NUM_OF_THREADS 10

void *PrintFunc(void *_tid)
{
    void *retval;
    printf("%lu ->",*(size_t *)_tid);
    pthread_exit(retval);
    return retval;
} 

int main (void)
{
    pthread_t threads[NUM_OF_THREADS];
    size_t i;
    
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (0 != pthread_create(&threads[i], NULL, PrintFunc, &i))
        {
            printf("failed to create thread \n");
        }

        pthread_join(threads[i], NULL);
    }
    
}