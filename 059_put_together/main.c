#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Can not oprn file");
    exit(EXIT_FAILURE);
  }
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  for (size_t m = 0; m < i; m++) {
    char * ptr = strchr(lines[m], '\n');
    *ptr = '\0';
  }

  counts_t * counts = createCounts();
  for (size_t p = 0; p < i; p++) {
    addCount(counts, lookupValue(kvPairs, lines[p]));
  }
  if (fclose(f) != 0) {
    exit(EXIT_FAILURE);
  }
  free(curr);
  for (size_t s = 0; s < i; s++) {
    free(lines[s]);
  }
  free(lines);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Wrong argument number");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)

  for (int i = 2; i < argc; i++) {
    if (argc < 3) {
      fprintf(stderr, "Wrong arguments number");
      exit(EXIT_FAILURE);
    }
    if (argv[i] == NULL) {
      fprintf(stderr, "Wrong argv format");
      exit(EXIT_FAILURE);
    }
    counts_t * c = NULL;
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i], kv);
    char * outname = computeOutputFileName(argv[i]);
    FILE * f = fopen(outname, "w");
    if (f == NULL) {
      fprintf(stderr, "Can not oprn file");
      exit(EXIT_FAILURE);
    }
    printCounts(c, f);
    free(outname);
    freeCounts(c);
    if (fclose(f) != 0) {
      exit(EXIT_FAILURE);
    }
  }

  freeKVs(kv);
  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv

  return EXIT_SUCCESS;
}
