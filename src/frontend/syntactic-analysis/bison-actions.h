#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../../backend/semantic-analysis/symbol-table.h"
#include "../../backend/support/clist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.

// // Expresión.
// int AdditionExpressionGrammarAction(const int leftValue, const int rightValue);
// int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue);
// int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue);
// int DivisionExpressionGrammarAction(const int leftValue, const int rightValue);
// int FactorExpressionGrammarAction(const int value);

// // Factores.
// int ExpressionFactorGrammarAction(const int value);
// int ConstantFactorGrammarAction(const int value);

// // Constantes.
// int IntegerConstantGrammarAction(const int value);

/**
 * Implementación de "bison-actions.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/

ProgramNode * ProgramGrammarAction(SportNode * sport);
int Return0();
SportNode * SportGrammarAction(SportType sport,  ProbabilityNode * probabilities,  MatchNode *match);
ProbabilityNode * OddsGrammarAction(char *odds);
ProbabilityNode * NoOddsGrammarAction();
MatchNode * MatchGrammarAction( TeamNode * team1,  TeamNode * team2);
TeamNode * TeamGrammarAction(TeamNameNode * name, FormationNode * formation, PlayerNode * players);
TeamNameNode * TeamNameGrammarAction(char * name);
FormationNode * FormationGrammarAction(char * formation);
PlayerNode * PlayerGrammarAction(char * name,  PlayerNode * nextPlayer);
PlayerNode * LastPlayerGrammarAction(char * name);

#endif
