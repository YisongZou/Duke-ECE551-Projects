#include "election.h"

#include <stdio.h>
#include <stdlib.h>

//include any other headers you need here...

state_t parseLine(const char * line) {
  //initialize variables
  state_t state_t1;
  state_t1.electoralVotes = 0;
  state_t1.population = 0;
  char * k = state_t1.name;
  for (int l = 0; l < MAX_STATE_NAME_LENGTH; l++) {
    k[l] = ' ';
  }
  int n = 0;
  int i = 0;
  int j = 0;
  char p[20] = " ";
  char q[20] = " ";
  int m = 0;
  int h = 0;

  //check if line is NULL
  if (line == NULL) {
    printf("Wrong format of input, incorrect number of ':'\n");
    exit(EXIT_FAILURE);
  }

  //check if there are 2 ':'
  while (line[m] != '\0') {
    if (line[m] == ':') {
      h++;
    }
    m++;
  }
  if (h != 2) {
    printf("Wrong format of input, incorrect number of ':'\n");
    exit(EXIT_FAILURE);
  }

  //read the content before first ':'
  while (line[n] != ':') {
    state_t1.name[n] = line[n];
    n++;
  }
  state_t1.name[n] = '\0';
  n++;

  //read the content before second ':'
  while (line[n] != ':') {
    if (line[n] < '0' || line[n] > '9') {
      printf("The input of population is not digit\n");
      exit(EXIT_FAILURE);
    }
    p[i] = line[n];
    n++;
    i++;
  }
  p[i] = '\0';
  state_t1.population = atoi(p);
  n++;

  //read the content after the second ':'
  while (line[n] != '\0') {
    if (line[n] < '0' || line[n] > '9') {
      printf("The input of evotes is not digit\n");
      exit(EXIT_FAILURE);
    }
    q[j] = line[n];
    j++;
    n++;
  }
  q[j] = '\0';
  state_t1.electoralVotes = atoi(q);

  //deal with improper input format
  if (n == 0 || state_t1.electoralVotes == 0 || state_t1.population == 0) {
    printf("Wrong input format, some fields are lost or no input at all\n");
    exit(EXIT_FAILURE);
  }
  return state_t1;
  //STEP 1: write me
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //initialize variables
  unsigned int evotes = 0;
  size_t i = 0;

  //calculate electorial votes that the Candidate gets
  while (i < nStates) {
    if (voteCounts[i] > (stateData[i].population / 2)) {
      evotes += stateData[i].electoralVotes;
    }
    i++;
  }
  //STEP 2: write me
  return evotes;
}

//helper function for step3 to decide whether we need a recount
int recount(size_t i, state_t * stateData, uint64_t * voteCounts) {
  if ((voteCounts[i] >= 0.495 * (stateData[i].population)) &&
      (voteCounts[i] <= 0.505 * (stateData[i].population))) {
    return 1;
  }
  else {
    return 0;
  }
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me

  //initialize variables
  size_t i = 0;

  //decide when we should conduct a recount, here I use a helper function recount which is defined above
  while (i < nStates) {
    if (recount(i, stateData, voteCounts)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             ((double)voteCounts[i]) / stateData[i].population * 100);
    }
    i++;
  }
}
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me

  //initialize variables
  size_t i = 0;
  double lwin = 0;
  size_t nwin;
  double win = 0;

  //figure out the argest win and print the percentage
  while (i < nStates) {
    win = ((double)voteCounts[i]) / stateData[i].population * 100;
    if (win > lwin) {
      lwin = win;
      nwin = i;
    }
    i++;
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[nwin].name, lwin);
}
