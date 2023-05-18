#include <stdio.h>
#define TAM 100

typedef struct manager
{
    int mCode;
    char password[TAM];
    int contact;
    char username[TAM];
    struct manager* nextm;
}Manager;

//Manager sub-rotines
Manager* insertManager(Manager* begin, int mcod, char pass[], int cont, char mname[]);
Manager* readManagers();
int saveManager(Manager* begin);
int existManager(Manager* begin, int mcod);
Manager* removeManager(Manager* begin, int mcod);
void listManagers(Manager* begin);
void contactManager(Manager* begin);
int changeManager(Manager* begin, int mcod, char pass[], char newusername[], char newpass[]);