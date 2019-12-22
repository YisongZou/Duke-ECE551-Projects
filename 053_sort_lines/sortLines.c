#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void read(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  if (argc == 0) {
    fprintf(stderr, "Wrong number of command line argument");
    return EXIT_FAILURE;
  }

  if (argc == 1) {
    read(stdin);
  }

  if (argc > 1) {
    int i;
    for (i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "f is NULL\n");
        return EXIT_FAILURE;
      }
      read(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "Failure to close the input file\n");
        return EXIT_FAILURE;
      }
    }
  }
  //WRITE YOUR CODE HERE!

  return EXIT_SUCCESS;
}
