#include "hashmap.h"
#include "chatMan.h"
 #include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#define ID_LEN 333
#define FILE_OF_PID "./PID.txt" /* the mulicast main write the getpid to there */
#define TRUE 1
#define FALSE 0

#define MAGIC 0xBEEFBEEF
#define MAGICDEAD 0xDEADBEEF
#define MAX_GROUPS 300
#define MAX_LENGTH 500

/* ---------------------------------------------------------------------- */

struct ChatMan
{
    size_t m_magic;
    HashMap *m_groupsPIDs; /* group IP is key and value id PIDs (send and recieve getpid )  */
    List* m_myGroups;      /* IP of group */
};

typedef struct PIDs
{
    char m_PID1[ID_LEN]; /* send */
    char m_PID2[ID_LEN]; /* recieve */
}PIDs;

/* ------------------------help functions-------------------------------- */
static size_t ChatFunction(const void *_string);
static int ChatIsEqual(const void *_name1, const void *_name2);
static int ChatActionFunc(const void *_key, void *_value, void *_context);/* kill all chats  */
static void PidsDes(void* _pids);
static void CharPtrDes(void* _str);

    /* ----------------------------------------------------------------------- */
ChatMan *ChatManCreate()
{
    ChatMan *chat;
    chat = (ChatMan *)malloc(sizeof(ChatMan));
    if (NULL == chat)
    {
        return NULL;
    }

    chat->m_groupsPIDs = HashMapCreate(MAX_GROUPS, ChatFunction, ChatIsEqual);
    chat->m_myGroups = ListCreate();
    chat->m_magic = MAGIC;

    return chat;
}
/* ----------------------------------------------------------------------- */

void ChatManOpenChat(ChatMan *_chatMan, char *_ipAdd, int _port, char *_userName)
{
    FILE *fp=NULL;
    char read1[ID_LEN];
    char read2[ID_LEN];
    int len = ID_LEN;
    char command[MAX_LENGTH];
    PIDs *newTwopids;
    if(!(_chatMan)|| !(_ipAdd)|| ( _port<1025) || !(_userName) ) 
    {
        perror("invalid arguments");
        return;

    }

    newTwopids=(PIDs *)malloc(sizeof(PIDs)*1);

    ListPushHead(_chatMan->m_myGroups, _ipAdd); /* List of group ip ... */

    sprintf(command, "gnome-terminal --geometry=100x40+100-200 sh --command \"./wr.out %s %d %s %s\"", _ipAdd, _port, FILE_OF_PID, _userName);
    system(command);
    while(fp==NULL)
    {
        fp = fopen(FILE_OF_PID, "r+");

    }
  

    rewind(fp);            /* sets the file position to the beginning of the file of the given stream. */
    fgets(read1, len, fp); /* read from file the the id */
    fclose(fp);
    
    sprintf(command, "gnome-terminal --geometry=100x30+100-200  sh --command \"./re.out %s %d %s %s\"", _ipAdd, _port, FILE_OF_PID, _userName);
    system(command);
    fp=NULL;
     while(fp==NULL)
    {
        fp = fopen(FILE_OF_PID, "r+");

    }
    rewind(fp);
    fgets(read2, len, fp); /* read from file the the id */
    fclose(fp);

    strcpy(newTwopids->m_PID1, read1); /* two windows of one group */
    strcpy(newTwopids->m_PID2, read2);

    HashMapInsert(_chatMan->m_groupsPIDs, (void *)_ipAdd, (void *)newTwopids); /* group ip and group two pid to close if client want to close  */
}



ChatRes ChatManCloseChat(ChatMan *_chatMan, const char *_groupName, char *_ipAdd)
{
    PIDs* pIdToClose = malloc(sizeof(PIDs));
    char* ip;
    if ((_chatMan == NULL) || (_chatMan->m_magic != MAGIC)||(_ipAdd == NULL))
    {
        return CHATM_NOT_INIT_ERR;
    }

   if(MAP_SUCCESS == HashMapFind(_chatMan->m_groupsPIDs,(void*)_ipAdd,(void**)&pIdToClose))
   {
        HashMapRemove(_chatMan->m_groupsPIDs,(void *)_ipAdd,(void*)ip,(void **)&pIdToClose);

        kill((pid_t)atoi(pIdToClose->m_PID1), SIGKILL);
        kill((pid_t)atoi(pIdToClose->m_PID2), SIGKILL);
        free(pIdToClose);
        return CHATM_OK;
   }

	return CHATM_NOT_EXIST_IP;
}

/* ----------------------------------------- */

ChatRes ChatManCloseAll(ChatMan *_chatMan)
{

    if ((_chatMan == NULL) || (_chatMan->m_magic != MAGIC))
    {
        return CHATM_NOT_INIT_ERR;
    }
    HashMapForEach(_chatMan->m_groupsPIDs, ChatActionFunc, (void *)_chatMan);
    return CHATM_OK;
}

/* ----------------------------------------- */

List* ChatManGetMyListOfGroups(ChatMan *_chatMan)
{
    if ((!_chatMan) ||(_chatMan->m_magic != MAGIC))
    {
        return NULL;
    }
    return _chatMan->m_myGroups;
}



/* ----------------------------------------- */

void ChatManDestroy(ChatMan *_chatMan)
{
    if((!_chatMan) || (_chatMan->m_magic != MAGIC))
    {
        return;
    }

    HashMapDestroy(&(_chatMan->m_groupsPIDs),CharPtrDes,PidsDes);
    ListDestroy(&_chatMan->m_myGroups, NULL);

    _chatMan->m_magic = MAGICDEAD;

    free(_chatMan);
}

/* ---------------------------help functions----------------------------- */
static size_t ChatFunction(const void *_string)
{
    int counter = 0;
    int i = 0;

    while (i < strlen(_string))
    {
        counter += (((char*)_string)[i] + '0');
        i++;
    }
    return counter;
}

static int ChatIsEqual(const void *_name1, const void *_name2)
{
    return strcmp((char *)_name1, (char *)_name2) == 0;
}

static int ChatActionFunc(const void *_key, void *_value, void *_context) /* kill all chats  */
{

    int fir, sec;
    fir = atoi(((PIDs *)_value)->m_PID1);
    sec = atoi(((PIDs *)_value)->m_PID2);
    kill((pid_t)fir, SIGKILL);
    kill((pid_t)sec, SIGKILL);
    return 1;
}

static void PidsDes(void* _pids)
{
    free(((PIDs*)_pids));
}

static void CharPtrDes(void* _str)
{
    free(((char*)_str));
}



/* -------------------------------------------------------------------------- */


