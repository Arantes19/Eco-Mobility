#include <stdio.h>
#define TAM 100

typedef struct manager
{
    int gCode;
    char password[TAM];
    int contact;
    char username[TAM];
    struct manager* nextm;
}Manager;

//Manager sub-rotines
Manager* insertManager(Manager* begin, int gcod, char pass[], int cont, char mname[]);
Manager* readManagers();
int saveManager(Manager* begin);
int existManager(Manager* begin, int gcod);
Manager* removeManager(Manager* begin, int gcod);
void listManagers(Manager* begin);
