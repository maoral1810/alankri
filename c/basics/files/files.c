#include <stdio.h>  /* FILE, */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy, strcmp */
#include "colors.h"
#include "files.h"
#include "Errors.h"

typedef struct Node Node;
typedef struct WordContainer WordContainer;

#define MAX_BYTES 100
#define ASSCI_SIZE 256
#define NUMBER_OF_LETTERS 26
#define RESIZE_FACTOR 2
#define MAGIC_NUM 0xFFAAFFAA

typedef struct Person
{
    char name[30];
    int id;
    int age;
    int education;
} Person;

struct Node
{
    char m_data[100];
    unsigned int ouccrance;
    Node *m_left;
    Node *m_right;
    Node *m_father;
};

struct WordContainer
{
    Node *root;
    size_t magicNumber;
};

static Err CountLines(FILE *_fd, size_t *_counter);
static Err CountBytesFromEnd(FILE *_fd, size_t lineFromEnd,
                             long *_counter, long _fileSize);
static Err CountBytesInFile(FILE *_fd, long *_counter);
static Err CountOccurence(FILE *_fd, char *_word, size_t *_counter);

static Node *CreateNode(char *_data, Node *perant);
static WordContainer *CreateTree();
static void DestroyTree(WordContainer *_tree);
static void DestroyNode(Node *_node);
static Err InsertNode(Node *_root, char *_toInsert);
void PrintTree(Node *_currentNode);

Err Last(char *_fileName, size_t _lineNum)
{
    FILE *fd = NULL;
    Err status = ERR_OK;
    size_t numOfLines = 0;
    long countBytes = 0;
    long fileSize = 0;
    long pos = 0;
    char c = 0;
    char *str = 0;
		
	if(_fileName == NULL)
	{
		return ERR_NOT_INISILIZE;
	}
	
    fd = fopen(_fileName, "r");

    if (fd == NULL)
    {
        return ERR_OPEN_FILE;
    }

    status = CountBytesInFile(fd, &fileSize);
    
    if (status != ERR_OK)
    {
        return status;
    }

    status = CountBytesFromEnd(fd, _lineNum, &countBytes, fileSize);

    if (status != ERR_OK)
    {
        return status;
    }

    fseek(fd, countBytes + 1, SEEK_END);
    pos = fileSize - countBytes;

    str = (char *)malloc(sizeof(char) * (fileSize - pos));

    if (str == NULL)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    fgets(str, (fileSize - pos), fd);
    
    while (!feof(fd))
    {
        printf("%s", str);
        fgets(str, (fileSize - pos), fd);
    }

    putchar('\n');

    free(str);
    fclose(fd);

    return ERR_OK;
}

Err OcurrenceInFile(char *_fileName, size_t *_occurance)
{
    FILE *fd = NULL;
    FILE *cmpFD = NULL;
    char fileNameBuffer[MAX_BYTES] = "";
    char word[MAX_BYTES] = "";
    char toCompere[MAX_BYTES] = "";
    Err status = ERR_OK;
	
	if(_fileName == NULL || _occurance == NULL)
	{
		return ERR_NOT_INISILIZE;
	}
	
    fd = fopen(_fileName, "r");

    if (fd == NULL)
    {
        return ERR_OPEN_FILE;
    }

    fscanf(fd, "%s %s", fileNameBuffer, word);
    fclose(fd);

    cmpFD = fopen(fileNameBuffer, "r");

    if (cmpFD == NULL)
    {
        return ERR_OPEN_FILE;
    }

    status = CountOccurence(cmpFD, word, _occurance);
	fclose(cmpFD);

    return status;
}

Err PrintDiffrence(char *_fileName1, char *_fileName2)
{
    FILE *fd1 = NULL;
    FILE *fd2 = NULL;
    Err status = ERR_OK;

    char str1[MAX_BYTES] = "";
    char str2[MAX_BYTES] = "";

    if (_fileName1 == NULL || _fileName2 == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    fd1 = fopen(_fileName1, "r");
    if (fd1 == NULL)
    {
        return ERR_OPEN_FILE;
    }

    fd2 = fopen(_fileName2, "r");
    if (fd2 == NULL)
    {
        fclose(fd1);
        return ERR_OPEN_FILE;
    }

    fgets(str1, MAX_BYTES, fd1);
    fgets(str2, MAX_BYTES, fd2);
    
    while (!feof(fd1) || !feof(fd2))
    {
        if (strcmp(str1, str2))
        {
            printf("lines diifrent!!\nline 1:%s\nline 2:%s\n", str1, str2);
        }
        
        fgets(str1, MAX_BYTES, fd1);
        fgets(str2, MAX_BYTES, fd2);
    }
	/* TODO PRINT THE REST OF THE FILE */
    fclose(fd1);
    fclose(fd2);

    return status;
}

Err WritePersonsToFileAndRead(char *_filename)
{
    Person arr[5] = {{"maor", 222111333, 30, 5}, {"soso", 333111220, 35, 3}, {"dudu", 666666666, 12, 1}, {"ori", 999111333, 59, 2}, {"momo", 76789870, 99, 8}};

    Person ReadFreomFile[5] = {0};
    FILE *fd = NULL;
    size_t writeBytes = 0;
    size_t readBytes = 0;

    if (_filename == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    fd = fopen(_filename, "w+");

    if (fd == NULL)
    {
        return ERR_OPEN_FILE;
    }

    writeBytes = fwrite(arr, sizeof(Person), 5, fd);

    fseek(fd, 0, SEEK_SET);

    readBytes = fread(ReadFreomFile, sizeof(Person), 5, fd);

    if(writeBytes != readBytes)
    {
        return ERR_READ_AND_WRITE;
    }

    printf("write = %lu\t read = %lu\t\n", writeBytes, readBytes);

    fclose(fd);

    return ERR_OK;
}

Err SkipSpaces(char *_readFile)
{
    FILE *fdRead = NULL;
    FILE *fdWrite = NULL;
    char str[MAX_BYTES] = "";

    if(_readFile == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    fdRead = fopen(_readFile, "r");
    if (fdRead == NULL)
    {
        return ERR_OPEN_FILE;
    }

    fdWrite = fopen("ResFile", "w");

    if (fdWrite == NULL)
    {
        fclose(fdRead);
        return ERR_OPEN_FILE;
    }

    fscanf(fdRead, "%s", str);
    
    while (!feof(fdRead))
    {
        fprintf(fdWrite, "%s", str);
        fscanf(fdRead, "%s", str);
    }

    fclose(fdWrite);
    fclose(fdRead);

    return ERR_OK;
}

Err CountLettersInFile(char *_FileName)
{
    size_t assciHistogram[ASSCI_SIZE] = {0};
    FILE *fd = NULL;
    size_t i = 0;
    char ch = 0;

    if (_FileName == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    fd = fopen(_FileName, "r");

    if (fd == NULL)
    {
        return ERR_OPEN_FILE;
    }
	
	ch = fgetc(fd);

    while (!feof(fd))
    {
        ++assciHistogram[ch];
        ch = fgetc(fd);
    }

    for (i = 'a'; i < 'z'; ++i)
    {
        printf("%c:\t%ld\n", (char)i, assciHistogram[i]);
    }

    for (i = 'A'; i < 'Z'; ++i)
    {
        printf("%c:\t%ld\n", (char)i, assciHistogram[i]);
    }

    return ERR_OK;
}
/* --------------------------------------------------------------------------*/
Err WordFrequency(char *_filename)
{
    WordContainer *tree = NULL;
    FILE *fd = NULL;
    Err status = ERR_OK;
    char str[MAX_BYTES] = {0};
    
    if (_filename == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    tree = CreateTree();
    if(NULL == tree)
    {
        return ERR_ALLOCTAION_FAILED;
    }

    fd = fopen(_filename, "r");
    if (fd == NULL)
    {
        return ERR_OPEN_FILE;
    }

    fscanf(fd, "%s", str);
    printf("%s\n",str);
    strcpy(tree->root->m_data, str);
    
    while (!feof(fd) && status == ERR_OK)
    {
        fscanf(fd, "%s", str);
       
        status = InsertNode(tree->root, str);
    }

    PrintTree(tree->root);
    DestroyTree(tree);

    return status;

}
/* ---------------------- static functions --------------------*/
static Node *CreateNode(char *_data, Node *perant)
{
    Node *node = NULL;

    if(NULL == _data)
    {
        return NULL;
    }

    node = (Node *)malloc(sizeof(Node));

    if(NULL == node)
    {
        return NULL;
    }

    strcpy(node->m_data, _data);
    node->ouccrance = 1;
    node->m_father = perant;
    node->m_left = NULL;
    node->m_right = NULL;

    return node;
}

static WordContainer *CreateTree()
{
    WordContainer *tree = (WordContainer *)malloc(sizeof (WordContainer));

    if(NULL == tree)
    {
        return NULL;
    }

    tree->root = CreateNode("", NULL);
    
    if(NULL == tree->root)
    {
        free(tree);
        return NULL;
    }

    tree->magicNumber = MAGIC_NUM;

    return tree;
}

static void DestroyTree(WordContainer *_tree)
{
    if(NULL == _tree || _tree->magicNumber != MAGIC_NUM)
    {
        return;
    }
    
    DestroyNode(_tree->root);
    
    _tree->magicNumber = 0; 
    free(_tree);
}

static void DestroyNode(Node *_node)
{
    if(_node == NULL)
    {
        return;
    }

    DestroyNode(_node->m_left);
    DestroyNode(_node->m_right);

    free(_node);
}

static Err InsertNode(Node *_root, char *_toInsert)
{
    Node *current = _root;
    int strCmpREs = 0;
    Node *saveFather = _root;

    if(NULL == _root || NULL == _toInsert)
    {
        return ERR_NOT_INISILIZE;
    }

    strCmpREs = strcmp(current->m_data, _toInsert);
    while (current != NULL)
    {
        strCmpREs = strcmp(current->m_data, _toInsert);
        saveFather = current;

        if(strCmpREs == 0)
        {
            ++current->ouccrance;
            return ERR_OK; 
        }
        
        else if(strCmpREs > 0) /* go left */
        {
            current = current->m_left;
        }
        
        else
        {
            current = current->m_right;
        }
    }

    current = CreateNode(_toInsert, saveFather);
    current->m_father = saveFather;
    
    if(strCmpREs > 0)
    {
        current->m_father->m_left = current; 
    }
    else
    {
        current->m_father->m_right = current;
    }

    return ERR_OK;
}

void PrintTree(Node *_currentNode)
{
    if(NULL == _currentNode)
    {
        return;
    }

    PrintTree(_currentNode->m_left);
    PrintTree(_currentNode->m_right);

    printf(BOLDGREY"%s "RESET" apear "BOLDRED"%d "RESET "times\n",
           _currentNode->m_data, _currentNode->ouccrance);
} 

static Err CountBytesFromEnd(FILE *_fd, size_t lineFromEnd,
                             long *_counter, long _fileSize)
{
    long countBytes = 0;
    size_t numOfLines = 0;
    char c = 0;

    if (_fd == NULL || _counter == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    while (numOfLines != lineFromEnd)
    {
        if (countBytes < -_fileSize)
        {
            *_counter = countBytes;
            return ERR_OK;
        }

        fseek(_fd, countBytes - 1, SEEK_END);

        c = fgetc(_fd);

        if (c == '\n')
        {
            numOfLines += 1;
        }

        --countBytes;
    }

    *_counter = countBytes;

    return ERR_OK;
}

static Err CountBytesInFile(FILE *_fd, long *_counter)
{
    if (_fd == NULL || _counter == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    fseek(_fd, -1, SEEK_END);
    *_counter = ftell(_fd);

    return ERR_OK;
}

static Err CountOccurence(FILE *_fd, char *_word, size_t *_counter)
{
    char toCompere[MAX_BYTES] = "";

    if (_fd == NULL || _word == NULL || _counter == NULL)
    {
        return ERR_NOT_INISILIZE;
    }

    fscanf(_fd, "%s", toCompere);

    while (!feof(_fd))
    {
        if (!strcmp(_word, toCompere))
        {
            ++*_counter;
        }
        
        fscanf(_fd, "%s", toCompere);
    }

    return ERR_OK;
}

static Err CountLines(FILE *_fd, size_t *_counter)
{
    size_t numOfLines = 1;
    int i = 0;
    char c = 0;

    if (_fd == NULL || _counter == NULL)
    {
        return ERR_FILE_NULL;
    }

    for (c = fgetc(_fd); c != EOF; c = fgetc(_fd))
    {
        if (c == '\n')
        {
            numOfLines += 1;
        }
    }

    *_counter = numOfLines;
}


