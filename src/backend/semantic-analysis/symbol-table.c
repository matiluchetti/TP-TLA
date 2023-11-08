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

    symbolTable->players = CList_init(sizeof(player_t));
}

symbol_t * getSymbolTable(){
    return symbolTable;
}

void addPlayer(char * playerName){
    player_t player;
    strcpy(player.name, playerName);
    symbolTable->players->add(symbolTable->players, &player);
}



void symbolTableFree(){
    if(symbolTable == NULL){
        printf("Symbol table already freed\n");
        return;
    }

    symbolTable->players->free(symbolTable->players);
    free(symbolTable);
    symbolTable = NULL;
}