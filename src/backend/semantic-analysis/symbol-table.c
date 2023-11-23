#include "symbol-table.h"


symbol_t *symbolTable = NULL;


void symbolTableInit(){
    if(symbolTable != NULL){
        printf("Symbol table already initialized\n");
        return;
    }

    symbolTable = malloc(sizeof(symbol_t));

    if (symbolTable == NULL) {
        printf("Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    symbolTable->team1 = initTableList();
    symbolTable->team2 = initTableList();
    symbolTable->size = 1;

}

symbol_t * getSymbolTable(){
    return symbolTable;
}

void addPlayer(char * playerName){
    if(symbolTable->size == 1){
        listInsert(symbolTable->team1, playerName);
    }
    else{
        listInsert(symbolTable->team2, playerName);
    }
}

void addTeam(){
    if(symbolTable->size == 1){
        symbolTable->size++;
    }
    else if(symbolTable->size !=2){
        printf("Can't add any more teams\n");
    }
}


void symbolTableFree(){
    if(symbolTable == NULL){
        printf("Symbol table already freed\n");
        return;
    }
    freeTableList(symbolTable->team1);
    freeTableList(symbolTable->team2);
    free(symbolTable);
    symbolTable = NULL;
}