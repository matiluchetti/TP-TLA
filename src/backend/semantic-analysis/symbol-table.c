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

    symbolTable->teams = CList_init(sizeof(teams_t));
    symbolTable->size = 0;

}

symbol_t * getSymbolTable(){
    return symbolTable;
}

void addPlayer(char * playerName){
    player_t player;
    strcpy(player.name, playerName);
    teams_t * team = (teams_t *)CList_At_(symbolTable->teams, symbolTable->size - 1);
    if(team->players == NULL || team->players->count == 0){
        team->players = CList_init(sizeof(player_t));
    }
    symbolTable->teams->add(team->players, &player);
}

void addTeam(char * teamName){
    if(symbolTable->size <= 2){
        teams_t team;
        strcpy(team.name, teamName);
        symbolTable->teams->add(symbolTable->teams, &team);
        symbolTable->size++;
    }
    else{
        printf("Can't add any more teams\n");
    }
}


void symbolTableFree(){
    if(symbolTable == NULL){
        printf("Symbol table already freed\n");
        return;
    }
    if (symbolTable->teams != NULL && symbolTable->size > 0) {
        teams_t *firstTeam = (teams_t *)CList_At_(symbolTable->teams, 0);
        if (firstTeam != NULL && firstTeam->players != NULL) {
            firstTeam->players->free(firstTeam->players);
        }
    }

    if (symbolTable->teams != NULL && symbolTable->size > 1) {
        teams_t *secondTeam = (teams_t *)CList_At_(symbolTable->teams, 1);
        if (secondTeam != NULL && secondTeam->players != NULL) {
            secondTeam->players->free(secondTeam->players);
        }
    }
    symbolTable->teams->free(symbolTable->teams);
    free(symbolTable);
    symbolTable = NULL;
}