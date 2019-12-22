#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int max(int * count) {
  int max = count[0];
  int n = 0;
  for (int i = 0; i < 26; i++) {
    if (count[i] > max) {
      max = count[i];
      n = i;
    }
  }
  return n;
}

int decrypt(FILE * f) {
  int c;
  int key;
  char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int count[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      count[c - 'a']++;
    }
  }
  int n = max(count);
  key = alphabet[n] - 'e';
  if (key < 0) {
    key += 26;
  }
  return key;
}
int main(int argc, char ** argv) {
  int key;
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  key = decrypt(f);
  fprintf(stdout, "%d\n", key);
  if (fclose(f) != 0) {
    return EXIT_FAILURE;
    perror("Failed to close the input file!");
  }
  return EXIT_SUCCESS;
}
