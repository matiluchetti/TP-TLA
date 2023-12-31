#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../support/table-list.h"

// lista de jugadores
//lista de subs
//lista de formaciones
// resultado
// fecha
// team name
// cantidad de jugadores

typedef struct symbol_t{
    //listas
    struct Table * team1;
    struct Table * team2;
    int size;
}symbol_t;


typedef struct player_t{
    char name[100];
}player_t;

//inicia la tabla de simbolos
void symbolTableInit();

void addTeam();

void addPlayer(char * playerName);

symbol_t * getSymbolTable();

void symbolTableFree();


#endif