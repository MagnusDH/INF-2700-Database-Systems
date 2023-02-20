#include <stdio.h>
#include  <string.h>

int main ( int argc, char* argv[])
{
  char str[200];

  while (strcmp(str,".quit") != 0)
    {
      // scanf ("%s", str);
      fgets (str, 200, stdin);
      printf("%s\n", str);
    }

  return (0);
}
