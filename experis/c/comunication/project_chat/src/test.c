#include <stdio.h>
#include <clientManager.h>
#include "ChatProtocol.h"


int main(int argc, char const *argv[])
{
    ClientManager* clientManager = ClientManagerCreate("127.0.0.1","1989");
    if(NULL == clientManager)
    {
        return 0;
    }

    ClientManagerRun(clientManager);
    return 0;
}

