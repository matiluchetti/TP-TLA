#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../support/logger.h"
#include "generator.h"
#include "../support/clist.h"
#include "../semantic-analysis/symbol-table.h"
#define BUFFER_LENGTH 5000

int Generator(ProgramNode * initial);
int validator(ProgramNode * initial);
char * getPlayersArray(int team_idx);
char * getMatchProbabilities(ProgramNode * initial);
char * getTeamName(ProgramNode* initial, int team_idx);
char * getFormation(ProgramNode* initial, int team_idx);


#endif
