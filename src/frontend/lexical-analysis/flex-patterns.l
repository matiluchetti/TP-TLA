%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
digit			[0-9]
endline			[\n]
whitespace		[ \f\n\r\t\v]
string          \"[A-Za-z0-9 ]+\"
%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ IgnoredPatternAction(yytext, yyleng); }
<COMMENT>{endline}+							{ IgnoredPatternAction(yytext, yyleng); }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"*"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

"["                                         { return ArrayStartAction(yytext);}
"]"                                         { return ArrayEndAction(yytext);}

"{"											{ return LCurlyPatternAction(yytext); }
"}"											{ return RCurlyPatternAction(yytext); }
":"                                         { return ColonPatternAction(yytext); }
";"                                         { return SemicolonPatternAction(yytext); }
","                                         { return CommaPatternAction(yytext); }

"\"deporte\""                               { return SportAction(yytext); }
"\"Hockey\""                                     { return HOCKEY; }
"\"Basquet\""                                    { return BASQUET; }
"\"Futbol\""                                    { return FUTBOL; }

"\"probabilidades\""                        { return OddsAction(); }
\"[0-9][0-9]-[0-9][0-9]-[0-9][0-9]\"      { return ODDSPERCENTAGES;}
\"[0-9]-[0-9]-[0-9]\"                       { return FORMATIONNUMBER;}

"\"equipos\""                               { return TeamAction();}
"\"nombre\""                                { return TeamNameAction();}
"\"jugador\""                               { return PlayerNameAction();}
"\"jugadores\""                             { return PlayerListAction();}
"\"formacion\""                             { return FormationAction();}

{string}                                    { return StringAction(yytext);}

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{whitespace}+								{ IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
