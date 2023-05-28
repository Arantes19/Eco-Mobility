/**
 * @file Managers.c
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Header_Files/manager.h"

/**
 * @brief Saves manager data in managers.txt file
 * 
 * @param begin 
 * @return int 
 */
int saveManager(Manager* begin)
{
    FILE* fp;
    fp = fopen("Text_Files/managers.txt", "w");
    if (fp!=NULL)
    {
        Manager* aux = begin;
        while (aux !=NULL)
        {
            fprintf(fp, "%d;%s;%d;%s\n", aux->mCode, aux->password, aux->contact, aux->username);
            aux = aux->nextm;
        }
        fclose(fp);
        return 1;
    }
    else 
    {
        printf("Error opening the file");
        return(0);
    }
}

/**
 * @brief lists all the manager data from the linked list
 * 
 * @param begin 
 */
void listManagers(Manager* begin)
{
    while (begin != NULL) 
    {
        printf("%d -> %s -> %d -> %s\n", begin->mCode, begin->password, begin->contact, begin->username);
        begin = begin->nextm;
    }
}
 /**
  * @brief Reads all the data of managers from the managers.txt file
  * 
  * @return Manager* 
  */
Manager* readManagers()
{
    FILE* fp;
    int mcod, cont;
    char mname[50], pass[50];

    Manager* aux = NULL;
    fp = fopen("Text_Files/managers.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^;\n];%d;%[^\n]\n", &mcod, pass, &cont, mname);
        aux = insertManager(aux, mcod, pass, cont, mname);
        }
        fclose(fp);
    }
    return(aux);
}

/**
 * @brief Insert a new manager in linked list
 * 
 * @param begin 
 * @param mcod 
 * @param pass 
 * @param cont 
 * @param mname 
 * @return Manager* 
 */
Manager* insertManager(Manager* begin, int mcod, char pass[], int cont, char mname[])
{
    if (!existManager(begin, mcod))
    {
        Manager* newManager = malloc(sizeof(struct manager));
        if (newManager != NULL)
        {
            newManager->mCode = mcod;
            strcpy(newManager->password, pass);
            newManager->contact = cont;
            strcpy(newManager->username, mname);
            newManager->nextm = begin;
            begin = newManager;
        } 
    }
    return(begin);
}

/**
 * @brief Verify is a given manager's code already exists
 * 
 * @param begin 
 * @param mcod 
 * @return int 
 */
int existManager(Manager* begin, int mcod)
{
    while (begin != NULL)
    {
        if (begin->mCode == mcod) return(1);
        {
            begin = begin->nextm;
        }
    }   
    return 0;
}

/**
 * @brief Removes a manager from the linked list given his code
 * 
 * @param begin 
 * @param mcod 
 * @return Manager* 
 */
Manager* removeManager(Manager* begin, int mcod)
{
    Manager *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->mCode == mcod)
    {
        aux = actual->nextm;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->mCode!=mcod))
        {
            previous = actual;
            actual = actual->nextm;
        }
        if (actual == NULL) return(begin);
        else
        {
            previous->nextm = actual->nextm;
            free(actual);
            return(begin);
        }
    }  
}

/**
 * @brief Change the current password from a manager given his code
 * 
 * @param begin 
 * @param mcod 
 * @param pass 
 * @param newusername 
 * @param newpass 
 * @return int 
 */
int changeManager(Manager* begin, int mcod, char pass[], char newusername[], char newpass[])
{
    Manager* actual =begin;
    while(actual != NULL)
    {
        if(actual->mCode == mcod && actual->password == pass)
        {
            strcpy(actual->username, newusername);
            strcpy(actual->password, newpass);
            printf("Manager info updated sucessfully\n");
            return 1;
        }
        actual = actual->nextm;
    }
    return 0;
}
