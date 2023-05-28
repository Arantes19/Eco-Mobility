/**
 * @file manager.h
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#define TAM 250

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
int changeManager(Manager* begin, int mcod, char pass[], char newusername[], char newpass[]);