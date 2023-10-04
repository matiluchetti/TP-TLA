#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

char * copyLexeme(const char * lexeme, const int length) {
	char * lexemeCopy = (char *) calloc(length + 1, sizeof(char));
	strncpy(lexemeCopy, lexeme, length);
	return lexemeCopy;
}

void BeginCommentPatternAction() {
	LogDebug("[Flex] [COMMENT] BeginCommentPatternAction............................");
}

void EndCommentPatternAction() {
	LogDebug("[Flex] [COMMENT] EndCommentPatternAction..............................");
}

token AdditionOperatorPatternAction() {
	LogDebug("[Flex] AdditionOperatorPatternAction: '+'.");
	yylval.token = ADD;
	return ADD;
}

token RCurlyPatternAction() {
	LogDebug("[Flex] RCurlyPatternAction: '}'.");
	yylval.token = RCURLY;
	return RCURLY;
}

token ColonPatternAction() {
	LogDebug("[Flex] ColonPatternAction: ':'.");
	yylval.token = COLON;
	return COLON;
}
token SemicolonPatternAction() {
	LogDebug("[Flex] SemicolonPatternAction: ';'.");
	yylval.token = SEMICOLON;
	return SEMICOLON;
}
token CommaPatternAction() {
	LogDebug("[Flex] CommaPatternAction: ','.");
	yylval.token = COMMA;
	return COMMA;
}
token DivisionOperatorPatternAction() {
	LogDebug("[Flex] DivisionOperatorPatternAction: '/'.");
	yylval.token = DIV;
	return DIV;
}

token IntegerPatternAction(const char * lexeme, const int length) {
	LogDebug("[Flex] IntegerPatternAction: '%s' (length = %d).", lexeme, length);
	char * lexemeCopy = copyLexeme(lexeme, length);
	yylval.integer = atoi(lexemeCopy);
	free(lexemeCopy);
	return INTEGER;
}

token MultiplicationOperatorPatternAction() {
	LogDebug("[Flex] MultiplicationOperatorPatternAction: '*'.");
	yylval.token = MUL;
	return MUL;
}

token LCurlyPatternAction() {
	LogDebug("[Flex] LCurlyPatternAction: '{'.");
	yylval.token = LCURLY;
	return LCURLY;
}

token SubtractionOperatorPatternAction() {
	LogDebug("[Flex] SubtractionOperatorPatternAction: '-'.");
	yylval.token = SUB;
	return SUB;
}

token UnknownPatternAction(const char * lexeme, const int length) {
	char * lexemeCopy = copyLexeme(lexeme, length);
	LogDebug("[Flex] UnknownPatternAction: '%s' (length = %d).", lexemeCopy, length);
	free(lexemeCopy);
	yylval.token = ERROR;
	// Al emitir este token, el compilador aborta la ejecución.
	return ERROR;
}

void IgnoredPatternAction(const char * lexeme, const int length) {
	char * lexemeCopy = copyLexeme(lexeme, length);
	LogRaw("[DEBUG] [Flex] IgnoredPatternAction: '");
	LogText(lexemeCopy, length);
	LogRaw("' (length = %d).\n", length);
	free(lexemeCopy);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
	// No se emite ningún token.
}

token SportAction() {
	LogDebug("[Flex] SportAction: '-'.");
	yylval.token = SPORT;
	return SPORT;
}

token OddsAction(){
	LogDebug("[Flex] OddsAction: '-'.");
	yylval.token = ODDS;
	return ODDS;
}


token TeamAction(){
	LogDebug("[Flex] TeamAction: '-'.");
	yylval.token = TEAMS;
	return TEAMS;
}

token TeamNameAction(){
	LogDebug("[Flex] TeamNameAction: '-'.");
	yylval.token = TEAM_NAME;
	return TEAM_NAME;
}

token PlayerNameAction(){
	LogDebug("[Flex] PlayerNameAction: '-'.");
	yylval.token = PLAYER_NAME;
	return PLAYER_NAME;
}

token PlayerListAction(){
	LogDebug("[Flex] PlayerNameAction: '-'.");
	yylval.token = PLAYER_LIST;
	return PLAYER_LIST;
}

token ArrayStartAction(){
	LogDebug("[Flex] ArrayStartAction: '-'.");
	yylval.token = ARRAY_START;
	return ARRAY_START;
}

token ArrayEndAction(){
	LogDebug("[Flex] ArrayEndAction: '-'.");
	yylval.token = ARRAY_END;
	return ARRAY_END;
}

token FormationAction(){
	LogDebug("[Flex] FormationAction: '-'.");
	yylval.token = FORMATION;
	return FORMATION;
}

token StringAction(const char * match){
	yylval.string = (char*) match;
	return STRING;
};