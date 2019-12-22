#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rotate(char * r, char * q) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      *(q + 10 * j + 9 - i) = *(r + 10 * i + j);
    }
  }
  for (int k = 0; k < 10; k++) {
    for (int l = 0; l < 10; l++) {
      fprintf(stdout, "%c", *(q + 10 * k + l));
    }
    fprintf(stdout, "\n");
  }
}
int main(int argc, char ** argv) {
  char array[10][10] = {{0}};
  char store[10][10] = {{0}};
  char * p = &store[0][0];
  char * q = &array[0][0];
  int c;
  int n = 0;
  if (argc != 2) {
    fprintf(stderr, "Command line argument error\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "f is NULL\n");
    return EXIT_FAILURE;
  }
  while ((c = fgetc(f)) != EOF) {
    n++;

    if ((c > 127) || (c < -128)) {
      fprintf(stderr, "Input not char\n");
      return EXIT_FAILURE;
    }

    if ((n % 11 == 0) && (c != '\n')) {
      fprintf(stderr, "Input error\n");
      return EXIT_FAILURE;
    }

    if (n > 110) {
      fprintf(stderr, "Input too long\n");
      return EXIT_FAILURE;
    }

    if (c != '\n') {
      *p = c;
      p++;
    }
  }

  if (n != 110) {
    fprintf(stderr, "Input too short\n");
    return EXIT_FAILURE;
  }

  char * r = &store[0][0];

  rotate(r, q);

  if (fclose(f) != 0) {
    fprintf(stderr, "Failure to close the input file\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
