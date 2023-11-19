#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct SportNode SportNode;
typedef struct ProgramNode ProgramNode;
typedef struct Expression Expression;

typedef struct LineupNode LineupNode;
typedef struct PlayerInfoNode PlayerInfoNode;
typedef struct ProbabilityNode ProbabilityNode;
typedef struct MatchNode MatchNode;
typedef struct TeamNode TeamNode;
typedef struct PlayerNode PlayerNode;
typedef struct FormationNode FormationNode;
typedef struct TeamNameNode TeamNameNode;
typedef struct PlayerNameNode PlayerNameNode;


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


struct ProgramNode{
	struct SportNode * info;
};

struct SportNode {
    SportType sport; 
    struct ProbabilityNode * probabilities; 
    struct MatchNode * match; // Pointer to the first team in the list
};

struct ProbabilityNode{
	ProbabilityType type;
	int t1_odds;
	int tie_odds;
	int t2_odds;
};

struct MatchNode{
	struct TeamNode * team1;
	struct TeamNode * team2;
};

struct TeamNode {
    struct TeamNameNode *teamName;
    struct FormationNode *formation; 
    struct PlayerNode *players; // Pointer to the first player in the lineup
    struct TeamNode *nextTeam; // Pointer to the next team in the program
};

struct TeamNameNode{
	char * teamName;
};

struct FormationNode{
	char * formation;
};

struct PlayerNode {
    char *playerName; // Player name (string)
    struct PlayerNode *nextPlayer; // Pointer to the next player in the lineup
};

#endif
