#include "../support/logger.h"
#include "generator.h"
#include "../../backend/support/shared.h"


/**
 * Implementación de "generator.h".
 */

void noQuotes(char *cadena) {
    char *inicio = strchr(cadena, '"');
    if (inicio != NULL) {
        char *fin = strchr(inicio + 1, '"');
        if (fin != NULL) {
            size_t longitud = fin - inicio - 1;
            strncpy(cadena, inicio + 1, longitud);
            cadena[longitud] = '\0';
        }
    }
}


int Generator(ProgramNode * initial) {


	static FILE * htmlFile;

	htmlFile = fopen("./out/match.html", "w");

	if(!validator(initial)){
        return -1;
    }

	char * team1Name = getTeamName(initial,0);
	char * team2Name = getTeamName(initial,1);
	char * sport = getSport(initial);
	char * formation1 = getFormation(initial,0);
	noQuotes(formation1);
	LogInfo(formation1);
	char * formation2 = getFormation(initial,1);
	noQuotes(formation2);
	char ** players1 = getPlayersArray(0);
	char ** players2 = getPlayersArray(1);

	

	int defenders = 0, mid = 0, attackers = 0, aux=0;;


	fprintf(htmlFile, "<!DOCTYPE html>\n");
    fprintf(htmlFile, "<html lang=\"en\">\n");
    fprintf(htmlFile, "<head>\n");
    fprintf(htmlFile, "\t<meta charset=\"UTF-8\">\n");
    fprintf(htmlFile, "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(htmlFile, "\t<style>\n");
    fprintf(htmlFile, "\t\tbody {\n");
	if(initial->info->sport != BASQUET_3 && initial->info->sport != BASQUET_5){
    	fprintf(htmlFile, "\t\t\tbackground-color: #4CAF50;\n");
	}else{
		fprintf(htmlFile, "\t\t\tbackground-color: #FFD700;\n");
	}
    fprintf(htmlFile, "\t\t\tdisplay: flex;\n");
    fprintf(htmlFile, "\t\t\tflex-direction: column;\n");
    fprintf(htmlFile, "\t\t\talign-items: center;\n");
    fprintf(htmlFile, "\t\t\theight: 100vh;\n");
    fprintf(htmlFile, "\t\t\tmargin: 0;\n");
    fprintf(htmlFile, "\t\t}\n");
    fprintf(htmlFile, "\n");
    fprintf(htmlFile, "\t\t.field-container {\n");
    fprintf(htmlFile, "\t\t\tdisplay: flex;\n");
    fprintf(htmlFile, "\t\t\tflex-direction: column;\n");
    fprintf(htmlFile, "\t\t\talign-items: center;\n");
    fprintf(htmlFile, "\t\t\tmargin-bottom: 20px;\n");
    fprintf(htmlFile, "\t\t}\n");
    fprintf(htmlFile, "\n");
    fprintf(htmlFile, "\t\t.field {\n");
    fprintf(htmlFile, "\t\t\tdisplay: flex;\n");
    fprintf(htmlFile, "\t\t\tflex-direction: row;\n");
    fprintf(htmlFile, "\t\t\tposition: relative;\n");
    fprintf(htmlFile, "\t\t\twidth: 600px;\n");
    fprintf(htmlFile, "\t\t\theight: 300px;\n");
	if(initial->info->sport != BASQUET_3 && initial->info->sport != BASQUET_5){
    	fprintf(htmlFile, "\t\t\tbackground-color: #2ECC71;\n");
	}else{
		fprintf(htmlFile, "\t\t\tbackground-color: #FFA500;\n");
	}
    fprintf(htmlFile, "\t\t\tborder-radius: 10px;\n");
    fprintf(htmlFile, "\t\t\toverflow: hidden; \n");
    fprintf(htmlFile, "\t\t}\n");
    fprintf(htmlFile, "\n");
    fprintf(htmlFile, "\t\t.column {\n");
    fprintf(htmlFile, "\t\t\tdisplay: flex;\n");
    fprintf(htmlFile, "\t\t\tflex-direction: column;\n");
    fprintf(htmlFile, "\t\t\talign-items: center;\n");
    fprintf(htmlFile, "\t\t\tjustify-content: center;\n");
    fprintf(htmlFile, "\t\t\tflex: 1;\n");
    fprintf(htmlFile, "\t\t}\n");
    fprintf(htmlFile, "\n");
    fprintf(htmlFile, "\t\t.player {\n");
    fprintf(htmlFile, "\t\t\twidth: 40px;\n");
    fprintf(htmlFile, "\t\t\theight: 40px;\n");
    fprintf(htmlFile, "\t\t\tbackground-color: #3498DB;\n");
    fprintf(htmlFile, "\t\t\tcolor: #FFFFFF;\n");
    fprintf(htmlFile, "\t\t\tborder-radius: 50%%;\n");
    fprintf(htmlFile, "\t\t\tmargin-bottom: 10px;\n");
    fprintf(htmlFile, "\t\t\tdisplay: flex;\n");
    fprintf(htmlFile, "\t\t\tjustify-content: center;\n");
    fprintf(htmlFile, "\t\t\talign-items: center;\n");
    fprintf(htmlFile, "\t\t\tfont-size: 12px;\n");
    fprintf(htmlFile, "\t\t}\n");
    fprintf(htmlFile, "\n");
    fprintf(htmlFile, "\t\t.team-divider {\n");
    fprintf(htmlFile, "\t\t\tposition: absolute;\n");
    fprintf(htmlFile, "\t\t\twidth: 2px;\n");
    fprintf(htmlFile, "\t\t\theight: 100%%;\n");
    fprintf(htmlFile, "\t\t\tbackground-color: #FFFFFF;\n");
    fprintf(htmlFile, "\t\t\tleft: 50%%;\n");
    fprintf(htmlFile, "\t\t\ttransform: translateX(-50%%);\n");
    fprintf(htmlFile, "\t\t}\n");
    fprintf(htmlFile, "\n");
    fprintf(htmlFile, "\t\t.info-container {\n");
    fprintf(htmlFile, "\t\t\ttext-align: center;\n");
    fprintf(htmlFile, "\t\t\tcolor: #FFFFFF;\n");
    fprintf(htmlFile, "\t\t}\n");
    fprintf(htmlFile, "\t</style>\n");
    fprintf(htmlFile, "\t<title>Match</title>\n");
    fprintf(htmlFile, "</head>\n");
    fprintf(htmlFile, "<body>\n");
    fprintf(htmlFile, "\t<div class=\"field-container\">\n");
    fprintf(htmlFile, "\t\t<div class=\"field\">\n");


	defenders = 0;
	mid = 0;
	attackers = 0;
	aux = 0;
	LogInfo(formation1);
	if (strlen(formation1) == 3){
		sscanf(formation1, "%2d-%2d", &defenders, &mid);
	}
	else{
		sscanf(formation1, "%2d-%2d-%2d", &defenders, &mid, &attackers);
	}

	if(initial->info->sport != BASQUET_5 && initial->info->sport != BASQUET_3){
    	fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
		fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">%s</div>\n",players1[aux++]);
		fprintf(htmlFile, "\t\t\t</div>\n");
	}


	fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
	for(int j=0; j < defenders; j++){
		fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">%s</div>\n",players1[aux++]);
	}
	fprintf(htmlFile, "\t\t\t</div>\n");
	fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
	for(int j=0; j < mid; j++){
		fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">%s</div>\n",players1[aux++]);

	}
	fprintf(htmlFile, "\t\t\t</div>\n");
	if(attackers != 0){
		fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
		for(int j=0; j < attackers; j++){
		fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">%s</div>\n",players1[aux++]);
		}
		fprintf(htmlFile, "\t\t\t</div>\n");
	}


	fprintf(htmlFile, "\t\t\t<div class=\"team-divider\"></div>\n");
	
	defenders = 0;
	mid = 0;
	attackers = 0;
	LogInfo(formation2);
	if (strlen(formation2) == 3){
		sscanf(formation2, "%2d-%2d", &defenders, &mid);
	}
	else{
		sscanf(formation2, "%2d-%2d-%2d", &defenders, &mid, &attackers);
	}

	aux = defenders + mid + attackers;

	if(initial->info->sport == BASQUET_5 || initial->info->sport == BASQUET_3){
		aux--;
	}

	if(attackers != 0){
		fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
		for(int j=0; j < attackers; j++){
			LogInfo("trying to add player %d",aux);
   			fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">%s</div>\n",players2[aux--]);
						LogInfo("Jugador %d agregado del",aux-1);
		}
		fprintf(htmlFile, "\t\t\t</div>\n");
	}

	fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
	for(int j=0; j < mid; j++){
   			fprintf(htmlFile, "\t\t\t\t<div class=\"player team2\">%s</div>\n",players2[aux--]);
					LogInfo("Jugador %d agregado",aux-1);
	}
	fprintf(htmlFile, "\t\t\t</div>\n");

	fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
	for(int j=0; j < defenders; j++){
   			fprintf(htmlFile, "\t\t\t\t<div class=\"player team2\">%s</div>\n",players2[aux--]);
		LogInfo("Jugador %d agregado",aux-1);
	}
	fprintf(htmlFile, "\t\t\t\t</div>\n");

	if(initial->info->sport != BASQUET_5 && initial->info->sport != BASQUET_3){
		fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
   			fprintf(htmlFile, "\t\t\t\t<div class=\"player team2\">%s</div>\n",players2[aux--]);
		fprintf(htmlFile, "\t\t\t</div>\n");
	}
	

    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 1</div>\n");
    // fprintf(htmlFile, "\t\t\t</div>\n");
    // fprintf(htmlFile, "\n");
    // fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 2</div>\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 3</div>\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 4</div>\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 5</div>\n");
    // fprintf(htmlFile, "\t\t\t</div>\n");
    // fprintf(htmlFile, "\n");
    // fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 6</div>\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 7</div>\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"player team1\">Player 8</div>\n");
    // fprintf(htmlFile, "\t\t\t</div>\n");
    // fprintf(htmlFile, "\n");
    // fprintf(htmlFile, "\t\t\t<div class=\"column\">\n");
    // fprintf(htmlFile, "\t\t\t\t<div class=\"team-divider\"></div>\n");
	fprintf(htmlFile, "\t\t\t</div>\n");
    fprintf(htmlFile, "\t\t<div class=\"info-container\">\n");
    fprintf(htmlFile, "\t\t\t<h2>Información del Partido</h2>\n");
	fprintf(htmlFile, "\t\t\t<p>%s VS %s</p>\n", team1Name, team2Name);
	free(team1Name);
	free(team2Name);
	if(initial->info->probabilities->type == PROBABILITY){
		char * odds = getMatchProbabilities(initial);
    	fprintf(htmlFile, "\t\t\t<p>%s</p>\n", odds);
		free(odds);
	}
	fprintf(htmlFile, "\t\t\t<p>Formaciones: %s %s</p>\n", formation1, formation2);
	free(formation1);
	free(formation2);
    fprintf(htmlFile, "\t\t</div>\n");
    fprintf(htmlFile, "\t</div>\n");
    fprintf(htmlFile, "</body>\n");
    fprintf(htmlFile, "</html>\n");



	fclose(htmlFile);
	 return 0;
}

int validator(ProgramNode * initial){
	
	symbol_t* symbolTable = getSymbolTable();
	SportType sportType = initial->info->sport;
    Table* players1List = symbolTable->team1;
	
	int players2;
	
	int teamsAmm = symbolTable->size;
	Table * players2List = symbolTable->team2;
    int players1 = countList(players1List);
	if(teamsAmm == 1){
		players2 = -1;
	}{
		players2 = countList(players2List);
	}

	// debo tener la misma cantidad de jugadores en ambos equipos
	if( players1 != players2 && players2 == -1){
		state.succeed = false;
		state.result = 3;
		LogError("Linea 86");
		return 0;
	}
    if(sportType == HOCKEY)
	 LogInfo("es hockey");
// la cantidad de jugadores por equipo debe se acorde a su deporte
	if(sportType == BASQUET_3 && players1 != 3 
		|| ((sportType == BASQUET_5 || sportType == FUTBOL_5) && players1 != 5)
		|| ((sportType == HOCKEY || sportType == FUTBOL_8) && (players1 != 8 && players1 != 11))
		){
			state.succeed = false;
			state.result = 3;
			LogError("Error en tipo de deporte");
			return 0;
		}
   
   // la cantidad de jugadores en la formacion debe ser acorde

   char * buff;
   
   for (int i = 0; i < teamsAmm; i++){
        int aux = 0, num;
        if(i==0){
			buff = initial->info->match->team1->formation->formation;
		}
		else{
			buff = initial->info->match->team2->formation->formation;
		}
		int defenders = 0, mid = 0, attackers = 0;
		if (strlen(buff) == 5){
			sscanf(buff, "\"%2d-%2d\"", &defenders, &mid);
		}
		else{
			sscanf(buff, "\"%2d-%2d-%2d\"", &defenders, &mid, &attackers);
		}
		aux = defenders + mid + attackers;
		LogInfo("Players are %d, aux is %d",players1,aux);
        if( players1 != (aux + 1) && (players1 != aux && sportType != BASQUET_3 && sportType != BASQUET_5)){
            state.succeed = false;
            state.result = 3;
            return 0;
        }
    }

	// si tengo probabilidades, deben ser positiivas y sumar 100
	if(initial->info->probabilities->type == PROBABILITY){
		int odds1 = initial->info->probabilities->t1_odds;
		int odds2 = initial->info->probabilities->t2_odds;
		int oddsT = initial->info->probabilities->tie_odds;
		if(odds1 < 0 || odds2 < 0 || oddsT < 0 || odds1 + odds2 + oddsT != 100){
			state.succeed = false;
			state.result = 3;
					LogError("Linea 139");
			return  0;
		}
	}

    return 1;
}

char ** getPlayersArray(int team_idx) {

    symbol_t* symbolTable = getSymbolTable();
	Table * playersList;
	if(team_idx == 0){
		playersList = symbolTable->team1;
	}
	else{
		playersList = symbolTable->team2;
	}
	int playersAmm = countList(playersList);
	char ** resultBuffer = malloc(11 * sizeof(char *));
    for (int i = 0; i < playersAmm; i++) {
		char * name = indexList(playersList,i);
		resultBuffer[i] = malloc(strlen(name) + 1); 
		noQuotes(name);
		strcpy(resultBuffer[i],name);
		noQuotes(resultBuffer);
		printf(resultBuffer[i]);
    }
	

    return resultBuffer;
}

char * getMatchProbabilities(ProgramNode * initial){
	ProbabilityNode * probability = initial->info->probabilities;
	if (probability->type == NO_PROBABILITY){
		return strdup("");
	}
	char* resultBuffer = calloc(1, BUFFER_LENGTH * sizeof(char));
	LogInfo("Odds are %d, %d,%d",probability->t1_odds,probability->tie_odds,probability->t2_odds);
	sprintf(resultBuffer, "Equipo 1 deberia pagar: \"%.2f\", Empate deberia pagar: %.2f\",  Equipo 2 deberia pagar: \"%.2f\"", 100.0/probability->t1_odds, 100.0/probability->tie_odds, 100.0/probability->t2_odds);
	return resultBuffer;
}

char* getTeamName(ProgramNode* initial, int team_idx) {
	TeamNode * team;
	if (team_idx == 0){
		team = initial->info->match->team1;
	}
	else{
		team = initial->info->match->team2;
	}
    char * teamName = team->teamName->teamName;
    return strdup(teamName);
}

char * getFormation(ProgramNode * initial, int team_idx){
	char* resultBuffer = calloc(1, BUFFER_LENGTH * sizeof(char));
	FormationNode * formationNode;
	if(team_idx == 0){
		formationNode = initial->info->match->team1->formation;
	} 
	else{
		formationNode = initial->info->match->team2->formation;
	}
	char * formation = formationNode->formation;
	sprintf(resultBuffer + strlen(resultBuffer), "%s", formation);
	return resultBuffer;
}

char * getSport(ProgramNode * initial){
	SportType type = initial->info->sport;
	switch(type){
		case FUTBOL_11:
			return "futbol 11";
		case FUTBOL_8:
			return "futbol 8";
		case FUTBOL_5:
			return "futbol 5";
		case HOCKEY:
			return "hockey";
		default :
			return "basquet";
	}
}

