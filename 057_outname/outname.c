#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t n = 0;
  for (size_t i = 0; inputName[i] != '\0'; i++) {
    n = i;
  }
  n++;
  char * p = malloc((n + 8) * sizeof(*p));
  char * j = ".counts";
  strcpy(p, inputName);
  strcat(p, j);

  return p;
}
