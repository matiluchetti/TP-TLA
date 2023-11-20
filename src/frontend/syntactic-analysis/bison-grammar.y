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
	SportNode * sportNode;
	ProgramNode * programNode;
	LineupNode * lineupNode;
	PlayerInfoNode * playerInfoNode;
	ProbabilityNode * probabilityNode;
	MatchNode * matchNode;
	TeamNode * teamNode;
	PlayerNode * playerNode;
	FormationNode * formationNode;
	TeamNameNode * teamNameNode;
	PlayerNameNode * playerNameNode;

	// No-terminales (frontend).
	int initial;
	int program;
	int expression;
	int oddsline;
	int formationline;
	int nameline;
	int playerline;
	int player;

	int fivesportvalue;
	int eightsportvalue;

	int teamsline;

	int team;

	// Terminales.
	token token;
	int integer;
	char * string; 
}

// Un token que jamás debe ser usado en la gramática.
%token <token> ERROR

// IDs y tipos de los tokens terminales generados desde Flex.

%token <token> LCURLY
%token <token> RCURLY
%token <token> SPORT
%token <token> SPORTVALUE
%token <token> COLON
%token <token> SEMICOLON
%token <token> FUTBOL11
%token <token> FUTBOL8
%token <token> FUTBOL5
%token <token> FUTBOL
%token <token> BASQUET3
%token <token> BASQUET5
%token <token> COMMA
%token <token> ODDS

%token <token> ARRAY_START
%token <token> ARRAY_END
%token <token> TEAMS
%token <token> TEAM_NAME
%token <token> FORMATION
%token <token> PLAYER_LIST
%token <token> PLAYER_NAME


%token <string> STRING
%token <integer> INTEGER
%token <string> FORMATIONNUMBER
%token <string> ODDSPERCENTAGES

// Tipos de dato para los no-terminales generados desde Bison.
%type <programNode> program
%type <sportNode> expression
%type <probabilityNode> oddsline
%type <teamNameNode> nameline
%type <formationNode> formationline
%type <playerNode> playerline
%type <playerNode> player


%type <matchNode> teamsline

%type <teamNode> team


// El símbolo inicial de la gramatica.
%start program

%%

program: expression													{ $$ = ProgramGrammarAction($1); }
	;

expression: LCURLY SPORT COLON SPORTVALUE COMMA oddsline 
		teamsline RCURLY									{ $$ = SportGrammarAction($4, $6 ,$7);}
	;
	
oddsline: ODDS COLON ODDSPERCENTAGES COMMA						{ $$ = OddsGrammarAction($3);}
	| %empty													{ $$ = NoOddsGrammarAction();}
	;
	
teamsline: TEAMS COLON ARRAY_START team COMMA team ARRAY_END	{ $$ = MatchGrammarAction($4,$6);}
	;

team: LCURLY nameline COMMA formationline COMMA player RCURLY	{ $$ = TeamGrammarAction($2, $4,$6);}
	;

nameline: TEAM_NAME COLON STRING									{ $$ = TeamNameGrammarAction($3);}
	;

formationline: FORMATION COLON FORMATIONNUMBER						{ $$ = FormationGrammarAction($3);}
	;

player: PLAYER_LIST COLON ARRAY_START playerline ARRAY_END			{$$ = PlayerListGrammarAction($4);}
	;

playerline: LCURLY PLAYER_NAME COLON STRING RCURLY COMMA playerline		{ $$ = PlayerGrammarAction($4,$7);}
	|	LCURLY PLAYER_NAME COLON STRING RCURLY 							{ $$ = LastPlayerGrammarAction($4);}
	;


%%
