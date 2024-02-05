#include <stdio.h>

int main(int argc, char *argv[]) {

  for (size_t i = 0; i <= argc; i++)
    printf("[%zu] :\t%s\n", i, argv[i]);
  return (1);
}
