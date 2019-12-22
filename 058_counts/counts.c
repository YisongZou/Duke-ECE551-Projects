#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->n = 0;
  counts->u = 0;
  counts->p = NULL;

  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME

  int k = 0;
  if (name == NULL) {
    c->u++;
  }
  else {
    if (c->p == NULL) {
      c->p = realloc(c->p, (c->n + 1) * sizeof(*c->p));
      c->p[c->n].v = NULL;
      c->p[c->n].v = realloc(c->p[c->n].v, 1 + strlen(name) * sizeof(*name));
      strcpy(c->p[c->n].v, name);
      c->p[c->n].m = 1;
      c->n++;
    }
    else {
      for (int i = 0; i < c->n; i++) {
        if (strcmp(c->p[i].v, name) == 0) {
          c->p[i].m++;
          k = 1;
        }
      }
      if (k == 0) {
        c->p = realloc(c->p, (c->n + 1) * sizeof(*c->p));
        c->p[c->n].v = NULL;
        c->p[c->n].v = realloc(c->p[c->n].v, 1 + strlen(name) * sizeof(*name));
        strcpy(c->p[c->n].v, name);
        c->p[c->n].m = 1;
        c->n++;
      }
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->n; i++) {
    fprintf(outFile, "%s: %d\n", c->p[i].v, c->p[i].m);
  }
  if (c->u > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->u);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->n; i++) {
    free(c->p[i].v);
  }
  free(c->p);
  free(c);
}
