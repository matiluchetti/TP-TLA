#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../../backend/semantic-analysis/symbol-table.h"


/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
 int ProgramGrammarAction(const int value);

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

struct ProgramNode * ProgramGrammarAction(struct InfoNode * info);
int Return0();
struct SportNode * SportGrammarAction(SportType sport, struct ProbabilityNode * probabilities, struct MatchNode *match);
struct ProbabilityNode * OddsGrammarAction(char *odds);
struct ProbabilityNode * NoOddsGrammarAction();
struct MatchNode * MatchGrammarAction(struct TeamNode * team1, struct TeamNode * team2);
struct TeamNode * TeamGrammarAction(char * name, FormationNumberType formation, int players);
struct TeamNameNode * TeamNameGrammarAction(char * name);
struct FormationNode * FormationGrammarAction(char * formation);
struct PlayerNode * PlayerGrammarAction(char * name, struct PlayerNode * nextPlayer);
struct PlayerNode * LastPlayerGrammarAction(char * name);

#endif
