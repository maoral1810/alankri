#include <stddef.h> /* size_t */
#define IP_LENGTH 17

#define CHAT_NAME_LENGTH 32

struct Chat
{
    char m_groupName[CHAT_NAME_LENGTH];
    char m_groupIP[IP_LENGTH];
    int m_port
    size_t m_NumOfClients;
};