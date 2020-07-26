#ifndef __CHAT_MAN_H__
#define __CHAT_MAN_H__

#include "list.h"


typedef struct ChatMan ChatMan;

typedef enum ChatRes
{
  CHATM_OK,
  CHATM_NOT_INIT_ERR,
  CHATM_ALLOC_FAIL_ERR,
  CHATM_NOT_EXIST_IP
}ChatRes;

/**
 * @brief create chat namager that manage multicast chat 
 * @return ChatMan* : pointer to the chat manager
 */
ChatMan* ChatManCreate();


/**
 * @brief destroy chat manager 
 * @param  ChatMan* _cahtMan: chat manager to destroy
 */
void ChatManDestroy(ChatMan* _chatMan);

/**
 * @brief open windows of multicast chat 
 * @param char* _userName:  username of the user that want to open the chat 
 * @param char* _ipAdd:  multicast IP address Chat add
 *
 */
void ChatManOpenChat(ChatMan *_chatMan, char *_ipAdd, int _port, char *_userName);

/**
 * @brief: close Open chat window
 * @param ChatMan* _chatMan :pointer to the chat manager
 * @param constChat* _groupName: the name of the wanted group chat
 * @return ChatRes CHATM_OK if success CHATM_NOT_INIT_ERR if inputed ChatMan invalid 
 */
ChatRes ChatManCloseChat(ChatMan* _chatMan, const char* _groupName, char* _ipAdd);

/**
 * @brief close all open chats
 * @param ChatMan* _chatMan :pointer to the chat manager
 * @return ChatRes CHATM_OK if success CHATM_NOT_INIT_ERR if inputed ChatMan invalid 
 */
ChatRes ChatManCloseAll(ChatMan* _chatMan);

/**
 * @brief return a list of avaliable groups
 * @param ChatMan* _chatMan :pointer to the chat manager
 * @return List* list of Group Names 
 */
List* ChatManGetMyListOfGroups(ChatMan* _chatMan);


#endif /* __CHAT_MAN_H__ */