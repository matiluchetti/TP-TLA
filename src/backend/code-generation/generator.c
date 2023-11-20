#include "../support/logger.h"
#include "generator.h"
#include "../../backend/support/shared.h"


/**
 * Implementación de "generator.h".
 */

static FILE * pythonFile;


int Generator(ProgramNode * initial) {
	//pythonFile = fopen("./output/imageGenerator.py", "w");

	if(!validator(initial)){
        return -1;
    }

    // fprintf(pythonFile, "from PIL import Image, ImageFont, ImageDraw\n");
	// char * team1Name = getTeamName(initial,0);
    // fprintf(pythonFile, "team1 name = %s\n",team1Name);
    // free(team1Name);
	// char * players1Array = getPlayersArray(0);
	// fprintf(pythonFile,"players = [%s]\n", players1Array);
	// free(players1Array);
	// char * team2Name = getTeamName(initial,1);
    // fprintf(pythonFile, "team2 name = %s\n",team2Name);
    // free(team2Name);
	// char * players2Array = getPlayersArray(1);
	// fprintf(pythonFile,"players = [%s]\n", players2Array);
	// free(players2Array);
	// char * matchProbabilities = getMatchProbabilities(initial);
    // fprintf(pythonFile, "Probabilities = '%s'\n",matchProbabilities);
    // free(matchProbabilities);
	// char * formation1 = getFormation(initial, 0);
    // fprintf(pythonFile, "formation1 = [%s]\n",formation1);
    // free(formation1);
	// char * formation2 = getFormation(initial, 1);
    // fprintf(pythonFile, "formation2 = [%s]\n",formation2);
    // free(formation2);
	
	// fprintf(pythonFile, "for formation in formation1:\n");
    // fprintf(pythonFile, "\tformationQty1 = formation1.split(\"-\")\n"
    //                     "\tdefenseNumber1 = int(formationQty1[0])\n"
    //                     "\tmidfieldNumber1 = int(formationQty1[1])\n"
    //                     "\tattackNumber1 = int(formationQty1[2])\n");
	// fprintf(pythonFile, "for formation in formation2:\n");
    // fprintf(pythonFile, "\tformationQty2 = formation.split(\"-\")\n"
    //                     "\tdefenseNumber2 = int(formationQty2[0])\n"
    //                     "\tmidfieldNumber2 = int(formationQty2[1])\n"
    //                     "\tattackNumber2 = int(formationQty2[2])\n");
	// if (initial->info->sport == FUTBOL_11 || initial->info->sport == FUTBOL_8 || initial->info->sport == FUTBOL_5 || initial->info->sport == HOCKEY){
	// 	fprintf(pythonFile,"\tpitch_image = Image.open(\"resources/SoccerHockeyField.jpeg\").convert(\"RGBA\")\n");
	// }
	// //basquet
	// else{
	// 	fprintf(pythonFile,"\tpitch_image = Image.open(\"resources/BasketballCourt.jpeg\").convert(\"RGBA\")\n");
	// }
	// fclose(pythonFile);
	
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

char * getPlayersArray(int team_idx) {
    char * resultBuffer = calloc(1, BUFFER_LENGTH * sizeof(char));
    symbol_t* symbolTable = getSymbolTable();
	Table * playersList;
	if(team_idx == 0){
		playersList = symbolTable->team1;
	}
	else{
		playersList = symbolTable->team2;
	}
    for (int i = 0; i < countList(playersList)-1; i++) {
		char * name = indexList(playersList,i);
        sprintf(resultBuffer + strlen(resultBuffer), "{\"Player\": \"%d\", \"name\": \"%s\"},", i+1, name);
    }
	
    // player_t* player = players1List->at(playerList, players1List->count(players1List)-1);
    // if (player->number == -1)
    //     sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": \"\", \"name\": \"%s\"}", player->name);
    // else {
    //     sprintf(resultBuffer + strlen(resultBuffer), "{\"number\": \"%d\", \"name\": \"%s\"}", player->number,player->name);
    // }
    return resultBuffer;
}

char * getMatchProbabilities(ProgramNode * initial){
	ProbabilityNode * probability = initial->info->probabilities;
	if (probability->type == NO_PROBABILITY){
		return strdup("");
	}
	char* resultBuffer = calloc(1, BUFFER_LENGTH * sizeof(char));
	sprintf(resultBuffer, "{\"Probabilites\": Team 1 wins: \"%d\", \"Tie\": \"%d\",  Team 2 wins: \"%d\"}", probability->t1_odds, probability->tie_odds, probability->t2_odds);
	free(resultBuffer);

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
	sprintf(resultBuffer + strlen(resultBuffer), "\"%s\"", formation);
		free(resultBuffer);
	return resultBuffer;
}