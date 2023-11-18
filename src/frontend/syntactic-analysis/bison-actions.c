#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-actions.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogErrorRaw("[ERROR] Mensaje: '%s', debido a '", string);
	for (int i = 0; i < yyleng; ++i) {
		switch (yytext[i]) {
			case '\n':
				LogErrorRaw("\\n");
			default:
				LogErrorRaw("%c", yytext[i]);
		}
	}
	LogErrorRaw("' (length = %d, linea %d).\n\n", yyleng, yylineno);
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
// int ProgramGrammarAction(const int value) {
// 	LogDebug("[Bison] ProgramGrammarAction(%d)", value);
// 	/*
// 	* "state" es una variable global que almacena el estado del compilador,
// 	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
// 	* es utilizada en la función "main".
// 	*/
// 	state.succeed = true;
// 	/*
// 	* Por otro lado, "result" contiene el resultado de aplicar el análisis
// 	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
// 	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
// 	* la expresión se computa on-the-fly, y es la razón por la cual esta
// 	* variable es un simple entero, en lugar de un nodo.
// 	*/
// 	state.result = value;
// 	return value;
// }

struct ProgramNode * ProgramGrammarAction(struct InfoNode * info){
	struct ProgramNode * initial = (struct ProgramNode *) calloc(1, sizeof(struct ProgramNode));
	initial->info = info;
	state.succeed = true;
	state.result = 15;
	state.program = initial;
	return initial;
}


int Return0(){
	return 0;
}

struct SportNode * SportGrammarAction(SportType selected_sport, struct ProbabilityNode * probabilities, struct MatchNode *match){
	struct SportNode * sport = (struct SportNode *) calloc(1, sizeof(struct SportNode));
	sport->sport = selected_sport;
	sport->probabilities = probabilities;
	sport->match = match;
	return sport;
}

struct ProbabilityNode * OddsGrammarAction(char * odds){
	struct ProbabilityNode * probabilities = (struct ProbabilityNode *) calloc(1, sizeof(struct ProbabilityNode));
	probabilities->type = PROBABILITY;
	if(sscanf(odds, "%2d-%2d-%2d", &probabilities->t1_odds, &probabilities->tie_odds, &probabilities->t2_odds) != 3){
		LogError("Error al parsear las probabilidades");
	}
	return probabilities;
}
struct ProbabilityNode * NoOddsGrammarAction(){
	struct ProbabilityNode * probabilities = (struct ProbabilityNode *) calloc(1, sizeof(struct ProbabilityNode));
	probabilities->type = NO_PROBABILITY;
	return probabilities;
}

struct MatchNode * MatchGrammarAction(struct TeamNode * team1, struct TeamNode * team2){
	struct MatchNode * match = (struct MatchNode *) calloc(1, sizeof(struct MatchNode));
	match->team1 = team1;
	match->team2 = team2;
	return match;
}

struct TeamNode * TeamGrammarAction(char * name, FormationNumberType formation, struct PlayerNode * players){
	struct TeamNode * team = (struct TeamNode *) calloc(1, sizeof(struct TeamNode));
	team->teamName = name;
	team->players = players;
	team->formation = formation;
	addTeam(name);
	return team;
}

struct TeamNameNode * TeamNameGrammarAction(char * name){
	struct TeamNameNode * teamName = (struct TeamNameNode *) calloc(1, sizeof(struct TeamNameNode));
	teamName->teamName = name;
	return teamName;
}

struct FormationNode * FormationGrammarAction(char * formation){
	struct FormationNode * formationNode = (struct FormationNode *) calloc(1, sizeof(struct FormationNode));
	int defenders, midfielders, forwards;
	int a = sscanf(formation, "%d-%d-%d", defenders, midfielders, forwards);
	if ( a == 3 ){
		if(defenders + midfielders + forwards == 10){
			formationNode->formation = FORMATION_11;
		}
		else if(defenders + midfielders + forwards == 7){
			formationNode->formation = FORMATION_8;
		}
		else if(defenders + midfielders + forwards == 4){
			formationNode->formation = FORMATION_5;
		}
		else if(defenders + midfielders + forwards == 2){
			formationNode->formation = FORMATION_3;
		}
	}
	else if ( a == 2 ){
		if (defenders + midfielders == 4) {
			formationNode->formation = FORMATION_5;
		}
		else if (defenders + midfielders == 3){
			formationNode->formation = FORMATION_3;
		}
	} 
	else{
		LogError("Error al parsear la formacion");
	}
	formationNode->formation = formation;
	return formationNode;
}

struct PlayerNode * PlayerGrammarAction(char * name, struct PlayerNode * nextPlayer){
	struct PlayerNode * player = (struct PlayerNode *) calloc(1, sizeof(struct PlayerNode));
	player->playerName = name;
	player->nextPlayer = nextPlayer;
	addPlayer(name);	
	return player;
}
struct PlayerNode * LastPlayerGrammarAction(char * name){
	struct PlayerNode * player = (struct PlayerNode *) calloc(1, sizeof(struct PlayerNode));
	player->playerName = name;
	player->nextPlayer = NULL;
	addPlayer(name);
	return player;
}