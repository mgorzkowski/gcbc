#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    printf("Usage: generateRandomKey filename bits\n");
    return 1;
  }

  FILE* keyFile;
  keyFile = fopen(argv[1], "w");
  if(keyFile == NULL)
  {
    printf("Cannot open key file");
    return 2;
  }
  int bytes = atoi(argv[2]) / 8;
  printf("bytes = %d\n", bytes);
  srand(time(NULL));
  for(int i=0; i<bytes/4; i++)
  {
    fprintf(keyFile, "%08X\n", rand());
  }
  return 0;
}
