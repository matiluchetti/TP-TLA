#include "../support/logger.h"
#include "generator.h"
#include "../../backend/support/shared.h"

/**
 * Implementación de "generator.h".
 */

static FILE * pythonFile;


int Generator(ProgramNode * initial) {
	pythonFile = fopen("./output/imageGenerator.py", "w");

	if(!validator(initial)){
        return -1;
    }

    fprintf(pythonFile, "from PIL import Image, ImageFont, ImageDraw\n");
	char * team1Name = getTeamName(initial,0);
    fprintf(pythonFile, "team1 name = %s\n",team1Name);
    free(team1Name);
	char * players1Array = getPlayersArray(0);
	fprintf(pythonFile,"players = [%s]\n", players1Array);
	free(players1Array);
	char * team2Name = getTeamName(initial,1);
    fprintf(pythonFile, "team2 name = %s\n",team2Name);
    free(team2Name);
	char * players2Array = getPlayersArray(1);
	fprintf(pythonFile,"players = [%s]\n", players2Array);
	free(players2Array);
	char * matchProbabilities = getMatchProbabilities(initial);
    fprintf(pythonFile, "Probabilities = '%s'\n",matchProbabilities);
    free(matchProbabilities);
	char * formation1 = getFormation(initial, 0);
    fprintf(pythonFile, "formation for team 1 = [%s]\n",formation1);
    free(formation1);
	char * formation2 = getFormation(initial, 1);
    fprintf(pythonFile, "formation for team 2 = [%s]\n",formation2);
    free(formation2);
	
	if (initial->info->sport == FUTBOL_11 || initial->info->sport == FUTBOL_8 || initial->info->sport == FUTBOL_5 || initial->info->sport == HOCKEY){

	}
	//basquet
	else{

	}
	
	return 1;
}

int validator(ProgramNode * initial){
	
	symbol_t* symbolTable = getSymbolTable();
	SportType sportType = initial->info->sport;
    CList* teamsList = symbolTable->teams;
    teams_t * team1 = (teams_t *)CList_At_(symbolTable->teams, 0);
	CList * players1List = team1->players;
	
	int players2;
	
	int teamsAmm = CList_Count_(teamsList);
	teams_t * team2 = (teams_t *)CList_At_(symbolTable->teams, 1);
	CList * players2List = team2->players;
    int players1 = players1List->count(players1List);
	if(teamsAmm == 1){
		players2 = -1;
	}{
		players2 = players2List->count(players2List);
	}

	// debo tener la misma cantidad de jugadores en ambos equipos
	if( players1 != players2 && players2 == -1){
		state.succeed = false;
		state.result = 3;
		return 0;
	}
    
// la cantidad de jugadores por equipo debe se acorde a su deporte
	if(sportType == BASQUET_3 && players1 != 3 
		|| ((sportType == BASQUET_5 || sportType == FUTBOL_5) && players1 != 5)
		|| ((sportType == HOCKEY || sportType == FUTBOL_8) && (players1 != 8 && players1 != 11))
		){
			state.succeed = false;
			state.result = 3;
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
        char string[12];
        strcpy(string,  buff);

        char * token = strtok(string, "-");
        
        while (token != NULL) {
            num  = atoi(token);
            aux += num;
            token = strtok(NULL, "-");
        }
        // en futbol y hockey no cuento al arquero, en basquet si
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
			return  0;
		}
	}


    return 1;
	

}

char * getPlayersArray(int team_idx) {
    char * resultBuffer = calloc(1, BUFFER_LENGTH * sizeof(char));
    symbol_t* symbolTable = getSymbolTable();
	teams_t  * team = (teams_t *)CList_At_(symbolTable->teams, team_idx);
	CList * playersList = team->players;
    for (int i = 0; i < playersList->count(playersList)-1; i++) {
        player_t * player = playersList->at(playersList, i);
        char * playerName = player->name;
        sprintf(resultBuffer + strlen(resultBuffer), "{\"Player\": \"%d\", \"name\": \"%s\"},", i+1, playerName);
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
	sprintf(resultBuffer + strlen(resultBuffer), "{\"Probabilites\": Team 1 wins: \"%d\", \"Tie\": \"%d\",  Team 2 wins: \"%d\"}", probability->t1_odds, probability->tie_odds, probability->t2_odds);

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
	return resultBuffer;
}