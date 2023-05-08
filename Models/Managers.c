/**
 * @file Managers.c
 * @author your name (you@domain.com)
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
 * @brief Done
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
            fprintf(fp, "%d;%s;%d;%s\n", aux->gCode, aux->password, aux->contact, aux->username);
            aux = aux->nextm;
        }
        fclose(fp);
        return 1;
    }
    else 
    {
        printf("Falha na abertura do ficheiro");
        return(0);
    }
}

/**
 * @brief Done
 * 
 * @param begin 
 */
void listManagers(Manager* begin)
{
    while (begin != NULL) 
    {
        printf("%d -> %s -> %d -> %s\n", begin->gCode, begin->password, begin->contact, begin->username);
        begin = begin->nextm;
    }
}
 /**
  * @brief Done
  * 
  * @return Manager* 
  */
Manager* readManagers()
{
    FILE* fp;
    int gcod, cont;
    char mname[50], pass[50];

    Manager* aux = NULL;
    fp = fopen("Text_Files/managers.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^;\n];%d;%[^\n]\n", &gcod, pass, &cont, mname);
        aux = insertManager(aux, gcod, pass, cont, mname);
        }
        fclose(fp);
    }
    return(aux);
}

/**
 * @brief Done
 * 
 * @param begin 
 * @param gcod 
 * @param pass 
 * @param cont 
 * @param mname 
 * @return Manager* 
 */
Manager* insertManager(Manager* begin, int gcod, char pass[], int cont, char mname[])
{
    if (!existManager(begin, gcod))
    {
        Manager* newManager = malloc(sizeof(struct manager));
        if (newManager != NULL)
        {
            newManager->gCode = gcod;
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
 * @brief Done
 * 
 * @param begin 
 * @param gcod 
 * @return int 
 */
int existManager(Manager* begin, int gcod)
{
    while (begin != NULL)
    {
        if (begin->gCode == gcod) return(1);
        {
            begin = begin->nextm;
        }
    }   
    return 0;
}

/**
 * @brief Done
 * 
 * @param begin 
 * @param gcod 
 * @return Manager* 
 */
Manager* removeManager(Manager* begin, int gcod)
{
    Manager *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->gCode == gcod)
    {
        aux = actual->nextm;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->gCode!=gcod))
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
 * @brief Done
 * 
 * @param begin 
 */
void contactManager(Manager* begin)
{
    while (begin != NULL)
    {
        printf("%d;%s;\n",begin->contact, begin->username);
        begin = begin->nextm;
    }
}

/**
 * @brief Done
 * 
 * @param begin 
 * @param gcod 
 * @param pass 
 * @param newusername 
 * @param newpass 
 * @return int 
 */
int changeManager(Manager* begin, int gcod, char pass[], char newusername[], char newpass[])
{
    Manager* actual =begin;
    while(actual != NULL)
    {
        if(actual->gCode == gcod && actual->password == pass)
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