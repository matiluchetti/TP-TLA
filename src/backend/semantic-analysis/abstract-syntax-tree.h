#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct Expression Expression;
typedef struct FormationNumberType FormationNumberType;
typedef struct FormationNumberNode FormationNumberNode;
typedef struct LineupNode LineupNode;
typedef struct PlayerInfoNode PlayerInfoNode;
typedef struct ProbabilityNode ProbabilityNode;
typedef struct TeamNode TeamNode;
typedef struct PlayerNode PlayerNode;


/**
* Para cada no-terminal se define una nueva estructura que representa su tipo
* de dato y, por lo tanto, su nodo en el AST (Árbol de Sintaxis Abstracta).
*/
// typedef struct {
// 	int value;
// } Constant;

/**
* En caso de que un no-terminal ("Factor" en este caso), posea más de una
* regla de producción asociada, se crea además de la estructura un enumerado
* que identitifque cada reducción posible (cada regla de producción). Luego,
* se agrega una instancia de este enumerado dentro del nodo del no-terminal.
*
* De este modo, al recorrer el AST, es posible determinar qué nodos hijos
* posee según el valor de este enumerado.
*/
// typedef enum {
// 	EXPRESSION,
// 	CONSTANT
// } FactorType;

// typedef struct {
// 	FactorType type;
// 	Expression * expression;
// } Factor;

// typedef enum {
// 	ADDITION,
// 	SUBTRACTION,
// 	MULTIPLICATION,
// 	DIVISION,
// 	FACTOR
// } ExpressionType;

// struct Expression {
// 	ExpressionType type;
// 	Expression * leftExpression;
// 	Expression * rightExpression;
// };

// typedef struct {
// 	Expression * expression;
// } Program;

typedef enum {
	PROBABILITY,
	NO_PROBABILITY
}ProbabilityType;

typedef enum {
	FUTBOL_11,
	FUTBOL_8,
	FUTBOL_5,
	HOCKEY,
	BASQUET_5,
	BASQUET_3
} SportType;

typedef enum{
	FORMATION_451,
	FORMATION_352 //poner todos los tipos de formaciones
} FormationNumberType;

typedef struct ProgramNode {
    SportType sport; 
    struct ProbabilityNode * probabilities; 
    struct TeamNode *teams; // Pointer to the first team in the list
} ProgramNode;

struct ProbabilityNode{
	ProbabilityType type;
	int t1_odds;
	int tie_odds;
	int t2_odds;
}ProbabilityNode;

struct TeamNode {
    char *teamName; // Team name (string)
    FormationNumberType formation; 
    struct PlayerNode *players; // Pointer to the first player in the lineup
    struct TeamNode *nextTeam; // Pointer to the next team in the program
}TeamNode;

struct PlayerNode {
    char *playerName; // Player name (string)
    struct PlayerNode *nextPlayer; // Pointer to the next player in the lineup
}PlayerNode;

#endif
