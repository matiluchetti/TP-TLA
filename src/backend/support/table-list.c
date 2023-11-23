#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table-list.h"
#include "../support/logger.h"

Table * initTableList() {
    Table *list = (Table *)malloc(sizeof(Table));
    if (!list) {
        LogErrorRaw("Error: No se pudo asignar memoria para la lista de caracteres.\n");
        exit(EXIT_FAILURE);
    }

    list->team = NULL;
    return list;
}

// bool listFind(Table *list, const char *data) {
//     Node *current = list->head;
//     while (current != NULL) {
//         if (strcmp(current->data, data) == 0) {
//             return true;
//         }
//         current = current->next;
//     }

//     return false;
// }

void listInsert(Table *list, const char *player) {
    Node * newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        LogErrorRaw("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(EXIT_FAILURE);
    }
    newNode->player = strdup(player);
    newNode->next = list->team;
    list->team = newNode; 
}

// void listDelete(CharList *list, const char *data) {
//     Node *current = list->head;
//     Node *prev = NULL;

//     while (current != NULL) {
//         if (strcmp(current->data, data) == 0) {
//             if (prev == NULL) {
//                 list->head = current->next;
//             } else {
//                 prev->next = current->next;
//             }

//             free(current->data);
//             free(current);
//             return;
//         }

//         prev = current;
//         current = current->next;
//     }
// }

void freeTableList(Table *list) {
    Node *current = list->team;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        if (temp->player != NULL) free(temp->player);
        free(temp);
    }

    free(list);
}


 int countList(Table * list){
    int count = 0;
    Node * current = list->team;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        count++;
    }
    return count;
 }

 char * indexList(Table * list, int idx){
    Node * current = list-> team;
    for(int i=0;i<idx;i++){
        Node *temp = current;
        current = current->next;
    }
    return current->player;
 }

// // haceme una funcion que me imprima la lista

// void printList(Table *list) {
//     Node *current = list->head;
//     while (current != NULL) {
//         current = current->next;
//     }
// }
