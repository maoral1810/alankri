#include "serverManager.h"
#include "serverNet.h"

int main(void)
{
    Server* server = CreateServer();
    
    ServerRun(server);
    return 0;

    
        

}