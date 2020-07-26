#include <stdio.h>  /* printf */
#include <string.h> /* strcpy */

typedef union grade  
{
    int g;
    char cg[2];
    char str[9];
}grade;

typedef struct Student
{
    int id;
    union grade ged;
    int education;
}Student;

int main(void)
{
    Student maor;
    char strGrade[] = "excelant";
    maor.ged.g = 100;
    
    printf("grade  = %d\n", maor.ged.g);

    strcpy(maor.ged.str ,strGrade);

    printf("grade  = %s\n", maor.ged.str);

    strcpy(maor.ged.cg ,"A");

    printf("grade  = %s\n", maor.ged.cg);





    return 0;
}

