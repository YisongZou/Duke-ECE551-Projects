#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  kvarray_t * kv = malloc(sizeof(*kv));
  kv->n = 1;
  kv->kvarray = malloc(kv->n * sizeof(*kv->kvarray));

  FILE * f = fopen(fname, "r");
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    int n = 0;
    int m = 0;

    kv->kvarray = realloc(kv->kvarray, kv->n * sizeof(*kv->kvarray));
    kv->kvarray[i].key = malloc(sizeof(*kv->kvarray[i].key));
    kv->kvarray[i].value = malloc(sizeof(*kv->kvarray[i].value));

    while (lines[i][n] != '=') {
      kv->kvarray[i].key = realloc(kv->kvarray[i].key, (n + 1) * sizeof(*kv->kvarray));
      kv->kvarray[i].key[n] = lines[i][n];
      n++;
    }
    kv->kvarray[i].key = realloc(kv->kvarray[i].key, (n + 1) * sizeof(*kv->kvarray));
    kv->kvarray[i].key[n] = '\0';
    n++;

    while (lines[i][n] != '\n') {
      kv->kvarray[i].value =
          realloc(kv->kvarray[i].value, (m + 1) * sizeof(*kv->kvarray));
      kv->kvarray[i].value[m] = lines[i][n];
      n++;
      m++;
    }

    kv->kvarray[i].value = realloc(kv->kvarray[i].value, (m + 1) * sizeof(*kv->kvarray));
    kv->kvarray[i].value[m] = '\0';
    curr = NULL;
    i++;
    kv->n++;
  }
  kv->n--;
  free(curr);
  for (size_t j = 0; j < i; j++) {
    free(lines[j]);
  }
  free(lines);

  if (fclose(f) != 0) {
    exit(EXIT_FAILURE);
  }
  return kv;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int j = 0; j < pairs->n; j++) {
    free(pairs->kvarray[j].key);
    free(pairs->kvarray[j].value);
  }
  free(pairs->kvarray);
  free(pairs);
}
void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int j = 0; j < pairs->n; j++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[j].key, pairs->kvarray[j].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int n = 0;
  for (int j = 0; j < pairs->n; j++) {
    if (strcmp(key, pairs->kvarray[j].key) == 0) {
      n = j;
      return pairs->kvarray[n].value;
    }
  }
  return NULL;
}
