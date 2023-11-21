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
	static FILE * cssFile;

	htmlFile = fopen("./out/match.html", "w");
	cssFile = fopen("./out/match.css", "w");

	if(!validator(initial)){
        return -1;
    }

	char * team1Name = getTeamName(initial,0);
	char * team2Name = getTeamName(initial,1);
	char * sport = getSport(initial);
	char * odds = getMatchProbabilities(initial);
	char * formation1 = getFormation(initial,0);
	noQuotes(formation1);
	LogInfo(formation1);
	char * formation2 = getFormation(initial,1);
	noQuotes(formation2);
	char ** players1 = getPlayersArray(0);
	char ** players2 = getPlayersArray(1);
	fprintf(htmlFile, "<head>\n"
						"\t <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css\">\n"
                        "\t <link rel=\"stylesheet\" href=\"match.css\">\n"
						"</head>\n");
	fprintf(htmlFile,	"<body>\n"
						"\t<header>\n"
						"\t\tPartido de %s\n"
						"equipo 1: %s VS equipo 2: %s\n"
						"\t\tLas probabilidades son: %s\n"
						"\t</header>\n ", sport,team1Name, team2Name, odds);
	free(team1Name);
	free(team2Name);
	fprintf(htmlFile, "\t<main>\n");
	fprintf(htmlFile, "\t\t<div class=\"pitch\">\n");
	fprintf(htmlFile, "\t\t\t<h4>%s %s</h4>\n", formation1, formation2);
	fprintf(htmlFile, "\t\t\t<div class=\"container\">\n");
	int defenders = 0, mid = 0, attackers = 0, aux=0;;
	LogInfo(formation1);
	if (strlen(formation1) == 3){
		sscanf(formation1, "%2d-%2d", &defenders, &mid);
	}
	else{
		sscanf(formation1, "%2d-%2d-%2d", &defenders, &mid, &attackers);
	}

	if(initial->info->sport != BASQUET_5 && initial->info->sport != BASQUET_3){
		fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
		fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players1[aux++]);
		fprintf(htmlFile, "\t\t\t\t</div>\n");
	}


	fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
	for(int j=0; j < defenders; j++){
		fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players1[aux++]);
		LogInfo("Jugador %d agregado",aux-1);
	}
	fprintf(htmlFile, "\t\t\t\t</div>\n");
	fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
	for(int j=0; j < mid; j++){
		fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players1[aux++]);
					LogInfo("Jugador %d agregado",aux-1);
	}
	fprintf(htmlFile, "\t\t\t\t</div>\n");
	if(attackers != 0){
		fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
		for(int j=0; j < attackers; j++){
			fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players1[aux++]);
						LogInfo("Jugador %d agregado del",aux-1);
		}
		fprintf(htmlFile, "\t\t\t\t</div>\n");
	}
	fprintf(htmlFile,"\t\t\t</div>\n");	 
	fprintf(htmlFile,"\t\t</div>\n");	 
	fprintf(htmlFile, "\t\t\t<div class=\"container\">\n");
	
	LogInfo("Todo bien");
	
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

	if(attackers != 0){
		fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
		for(int j=0; j < attackers; j++){
			fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players2[aux--]);
						LogInfo("Jugador %d agregado del",aux-1);
		}
		fprintf(htmlFile, "\t\t\t\t</div>\n");
	}

	fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
	for(int j=0; j < mid; j++){
		fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players2[aux--]);
					LogInfo("Jugador %d agregado",aux-1);
	}
	fprintf(htmlFile, "\t\t\t\t</div>\n");

	fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
	for(int j=0; j < defenders; j++){
		fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players2[aux--]);
		LogInfo("Jugador %d agregado",aux-1);
	}
	fprintf(htmlFile, "\t\t\t\t</div>\n");

	if(initial->info->sport != BASQUET_5 && initial->info->sport != BASQUET_3){
		fprintf(htmlFile, "\t\t\t\t<div class=\"row\">\n");
		fprintf(htmlFile, "\t\t\t\t\t<div class=\"pos\">%s</div>\n", players2[aux--]);
		fprintf(htmlFile, "\t\t\t\t</div>\n");
	}
	fprintf(htmlFile,"\t\t\t</div>\n");	 
	fprintf(htmlFile,"\t\t</div>\n");	 
	fprintf(htmlFile, "\t</main>\n");
	fprintf(htmlFile, "</body>");
	
	
	 fprintf(cssFile, "body {\n");
    fprintf(cssFile, "    margin: 0 auto;\n");
    fprintf(cssFile, "    background: #34495e;\n");
    fprintf(cssFile, "    font-family: \"Open Sans\", sans-serif;\n");
    fprintf(cssFile, "    cursor: default;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, "header {\n");
    fprintf(cssFile, "    width: 100%%;\n");
    fprintf(cssFile, "    color: #eee;\n");
    fprintf(cssFile, "    border-bottom: 1px solid #eee;\n");
    fprintf(cssFile, "    font-size: 15px;\n");
    fprintf(cssFile, "    padding: 20px 70px;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, "main {\n");
    fprintf(cssFile, "    padding: 40px 50px;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, ".line{\n");
    fprintf(cssFile, "    width:100%%;\n");
    fprintf(cssFile, "    background: black;\n");
    fprintf(cssFile, "    height: 3px;\n");
    fprintf(cssFile, "    margin-top:10px;\n");
    fprintf(cssFile, "    margin-bottom:10px;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, ".pitch {\n");
    fprintf(cssFile, "    background: #26A65B;\n");
    fprintf(cssFile, "    width: 500px;\n");
    fprintf(cssFile, "    height: 355px;\n");
    fprintf(cssFile, "    border-radius: 5px;\n");
    fprintf(cssFile, "    padding: 20px;\n");
    fprintf(cssFile, "    margin: 0 16px;\n");
    fprintf(cssFile, "    display: inline-block;\n");
    fprintf(cssFile, "    position: relative;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, ".pitch h4 {\n");
    fprintf(cssFile, "    color: #eee;\n");
    fprintf(cssFile, "    text-align: center;\n");
    fprintf(cssFile, "    margin: -20 153px;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, ".pitch .container {\n");
    fprintf(cssFile, "    display: flex;\n");
    fprintf(cssFile, "    flex-direction: column;\n");
    fprintf(cssFile, "    height: 100%%;\n");
    fprintf(cssFile, "    padding: 5px;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, ".row {\n");
    fprintf(cssFile, "    display: flex;\n");
    fprintf(cssFile, "    justify-content: space-around;\n");
    fprintf(cssFile, "    width: 100%%;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, ".pos {\n");
    fprintf(cssFile, "    width: 40px;\n");
    fprintf(cssFile, "    height: 40px;\n");
    fprintf(cssFile, "    border-radius: 20px;\n");
    fprintf(cssFile, "    background: #BDC3C7;\n");
    fprintf(cssFile, "    color: #34495e;\n");
    fprintf(cssFile, "    text-align: center;\n");
    fprintf(cssFile, "    line-height: 40px;\n");
    fprintf(cssFile, "    font-size: 15px;\n");
    fprintf(cssFile, "    font-weight: 100;\n");
    fprintf(cssFile, "    transition: .3s linear all;\n");
    fprintf(cssFile, "    margin: 0 5px;\n");
    fprintf(cssFile, "}\n\n");

    fprintf(cssFile, ".pos:hover {\n");
    fprintf(cssFile, "    color: #BDC3C7;\n");
    fprintf(cssFile, "    background: #34495e;\n");
    fprintf(cssFile, "}\n");



	fclose(htmlFile);
	fclose(cssFile);
	
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
		strcpy(resultBuffer[i],name);
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
	sprintf(resultBuffer, "Equipo 1 gana: \"%d\", \"Empate\": %d\",  Equipo 2 gana: \"%d\"}", probability->t1_odds, probability->tie_odds, probability->t2_odds);
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

