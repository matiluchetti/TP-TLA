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
	int oddsline;
	int nameline;
	int playerline;


	int eightformationline;
	int fiveformationline;
	int threeformationline;

	int fivesportvalue;
	int eightsportvalue;

	int threeteamsline;
	int fiveteamsline;
	int eightteamsline;

	int threeplayersline;
	int fiveplayersline;
	int eightplayersline;

	int eightteam;
	int fiveteam;
	int threeteam;

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
%token <token> EIGHTFORMATIONNUMBER
%token <token> THREEFORMATIONNUMBER
%token <token> FIVEFORMATIONNUMBER

%token <token> STRING
%token <integer> INTEGER

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <oddsline> oddsline
%type <nameline> nameline
%type <playerline> playerline

%type <eightformationline> eightformationline
%type <fiveformationline> fiveformationline
%type <threeformationline> threeformationline

%type <eightsportvalue> eightsportvalue
%type <fivesportvalue> fivesportvalue

%type <threeteamsline> threeteamsline
%type <fiveteamsline> fiveteamsline
%type <eightteamsline> eightteamsline

%type <threeplayersline> threeplayersline
%type <fiveplayersline> fiveplayersline
%type <eightplayersline> eightplayersline

%type <eightteam> eightteam
%type <fiveteam> fiveteam
%type <threeteam> threeteam




// El símbolo inicial de la gramatica.
%start program

%%

program: expression													{ $$ = ProgramGrammarAction($1); }
	;

expression: 
	LCURLY SPORT COLON fivesportvalue COMMA oddsline 
		 fiveteamsline RCURLY									{ $$ = Return0();}
	| LCURLY SPORT COLON eightsportvalue COMMA oddsline
		 eightteamsline RCURLY 								{ $$ = Return0();}
	| LCURLY SPORT COLON BASQUET COMMA oddsline						
		 threeteamsline RCURLY 								{ $$ = Return0();}
	;

//deportes que aceptan formacion de 8 y de 11
eightsportvalue: HOCKEY												{ $$ = Return0();}	
	| FUTBOL														{ $$ = Return0();}	
	;

//deportes que aceptan formacion de 5
fivesportvalue: BASQUET												{ $$ = Return0();}
	| FUTBOL														{ $$ = Return0();}
	;

	
oddsline: ODDS COLON ODDSPERCENTAGES COMMA						{ $$ = Return0();}
	| %empty
	;


fiveteamsline: TEAMS COLON ARRAY_START fiveteam COMMA fiveteam ARRAY_END 		{ $$ = Return0();}
	;

	
threeteamsline: TEAMS COLON ARRAY_START threeteam COMMA threeteam ARRAY_END	{ $$ = Return0();}
	;


eightteamsline: TEAMS COLON ARRAY_START eightteam COMMA eightteam ARRAY_END	{ $$ = Return0();}
	;
	

eightteam: LCURLY nameline COMMA eightformationline COMMA eightplayersline RCURLY	{ $$ = Return0();}
	;

fiveteam: LCURLY nameline COMMA fiveformationline COMMA fiveplayersline RCURLY	{ $$ = Return0();}
	;

threeteam: LCURLY nameline COMMA threeformationline COMMA threeplayersline RCURLY	{ $$ = Return0();}
	;

nameline: TEAM_NAME COLON STRING									{ $$ = Return0();}
	;

eightformationline: FORMATION COLON EIGHTFORMATIONNUMBER						{ $$ = Return0();}
	;
fiveformationline: FORMATION COLON FIVEFORMATIONNUMBER						{ $$ = Return0();}
	;
threeformationline: FORMATION COLON THREEFORMATIONNUMBER						{ $$ = Return0();}
	;

/* formacion 11 y 8*/
eightplayersline: PLAYER_LIST COLON ARRAY_START playerline COMMA  		
		playerline COMMA playerline COMMA playerline COMMA 
		playerline COMMA playerline COMMA playerline COMMA 
		playerline COMMA playerline COMMA playerline COMMA 
		playerline ARRAY_END										{ $$ = Return0();}
	|	PLAYER_LIST COLON ARRAY_START playerline COMMA playerline 	
		COMMA playerline COMMA playerline COMMA playerline COMMA playerline
		COMMA playerline COMMA playerline ARRAY_END	{ $$ = Return0();}
	;

/* formacion 5*/
fiveplayersline: PLAYER_LIST COLON ARRAY_START playerline COMMA  		
		playerline COMMA playerline COMMA playerline COMMA 
		playerline ARRAY_END										{ $$ = Return0();}
	;

/* formacion 3*/
threeplayersline: PLAYER_LIST COLON ARRAY_START playerline COMMA  		
		playerline COMMA playerline ARRAY_END						{ $$ = Return0();}
	;

playerline: LCURLY PLAYER_NAME COLON STRING RCURLY 		{ $$ = Return0();}


%%
