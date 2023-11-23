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



"["                                         { return ArrayStartAction();}
"]"                                         { return ArrayEndAction();}

"{"											{ return LCurlyPatternAction(); }
"}"											{ return RCurlyPatternAction(); }
":"                                         { return ColonPatternAction(); }
";"                                         { return SemicolonPatternAction(); }
","                                         { return CommaPatternAction(); }

"\"deporte\""                               { return SportAction(); }
"\"Hockey\""                                { return SportValueAction(yytext, yyleng); }
"\"Basquet 3\""                             { return SportValueAction(yytext, yyleng); }
"\"Basquet 5\""                             { return SportValueAction(yytext, yyleng); }
"\"Futbol 5\""                              { return SportValueAction(yytext, yyleng); }
"\"Futbol 8\""                              { return SportValueAction(yytext, yyleng); }
"\"Futbol 11\""                             { return SportValueAction(yytext, yyleng); }

"\"probabilidades\""                        { return OddsAction(); }
\"[0-9][0-9]-[0-9][0-9]-[0-9][0-9]\"        { return OddsPercentagesValueAction(yytext, yyleng);}
\"[1-5]-[1-5](-[1-5])?\"                    { return FormationNumberValueAction(yytext,yyleng);}


"\"equipos\""                               { return TeamAction();}
"\"nombre\""                                { return TeamNameAction();}
"\"jugadores\""                             { return PlayerListAction();}
"\"jugador\""                               { return PlayerNameAction();}
"\"formacion\""                             { return FormationAction();}

{string}                                    { return StringAction(yytext, yyleng);}

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{whitespace}+								{ IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
