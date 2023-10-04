%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expression;
	int factor;
	int constant;
	int sportvalue;
	int sportline;
	int oddsline;
	int teamsline;
	int formationline;
	int nameline;
	int team;
	int playersline;
	int playerline;

	// Terminales.
	token token;
	int integer;
	char * string; 
}

// Un token que jamás debe ser usado en la gramática.
%token <token> ERROR

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD
%token <token> SUB
%token <token> MUL
%token <token> DIV

%token <token> LCURLY
%token <token> RCURLY
%token <token> SPORT
%token <token> COLON
%token <token> SEMICOLON
%token <token> HOCKEY
%token <token> FUTBOL
%token <token> BASQUET
%token <token> COMMA
%token <token> ODDS
%token <token> ODDSPERCENTAGES
%token <token> ARRAY_START
%token <token> ARRAY_END
%token <token> TEAMS
%token <token> TEAM_NAME
%token <token> FORMATION
%token <token> PLAYER_LIST
%token <token> PLAYER_NAME
%token <token> FORMATIONNUMBER

%token <token> STRING
%token <integer> INTEGER

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant> constant
%type <sportvalue> sportvalue
%type <oddsline> oddsline
%type <sportline> sportline
%type <team> team
%type <nameline> nameline
%type <teamsline> teamsline
%type <formationline> formationline
%type <playersline> playersline
%type <playerline> playerline




// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program

%%

program: expression													{ $$ = ProgramGrammarAction($1); }
	;

expression: LCURLY expression RCURLY								{ $$ = ExpressionFactorGrammarAction($2); }
	| LCURLY sportline COMMA oddsline COMMA teamsline RCURLY		{ $$ = Return0();}
	;


sportline:  SPORT COLON sportvalue									{ $$ = Return0();}

sportvalue:    BASQUET                                       		{ $$ = Return0();}
	| FUTBOL													  	{ $$ = Return0();}
	| HOCKEY														{ $$ = Return0();}
	;

oddsline: ODDS COLON ODDSPERCENTAGES								{ $$ = Return0();}
	;

teamsline: TEAMS COLON ARRAY_START team COMMA team ARRAY_END 		{ $$ = Return0();}
	;

team: LCURLY nameline COMMA formationline COMMA playersline RCURLY	{ $$ = Return0();}

nameline: TEAM_NAME COLON STRING									{ $$ = Return0();}

formationline: FORMATION COLON FORMATIONNUMBER						{ $$ = Return0();}

playersline: PLAYER_LIST COLON ARRAY_START playerline ARRAY_END		{ $$ = Return0();}
playerline: LCURLY PLAYER_NAME COLON STRING RCURLY /*COMMA*/		{ $$ = Return0();}

%%
