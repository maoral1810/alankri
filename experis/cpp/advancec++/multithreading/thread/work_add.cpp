#include <pthread.h>
#include <semaphore.h>
#include "work_add.hpp"

extern pthread_mutex_t g_lock; 
extern sem_t g_semaphore; 
namespace experis{

void WorkAdd::Run() {

/*     sem_wait(&g_semaphore); */
    pthread_mutex_lock(&g_lock);

    ++(*m_gNum);
    
    pthread_mutex_unlock(&g_lock);
/*     sem_post(&g_semaphore); */
}

}//namesapce experis