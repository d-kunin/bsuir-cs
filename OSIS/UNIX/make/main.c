#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct Entry {
  char *  wrong;
  char *  valid;
} entry_t;

int isValid(char const * test, entry_t dict[], int dictSize, char ** valid) {
  int i;
  for (i = 0; i < dictSize; ++i) {
    if (strcmp(test, dict[i].wrong) == 0) {
	// this is "wrong word" change it
      *valid = dict[i].valid;
      return 0;
    }
  }
  return 1;
}

int main(int argc, char* args[])
{
  entry_t dict[] = {
    {"Windows", "Unix"},
    {"C#", "Java"},
    {"VS", "emacs"},
    {"Microsoft", "Open Source"}
  };

  char buf[256];      
  char * vbuf;
  for(; scanf("%255s", buf) != EOF; ) {
    if (isValid(buf, dict, 4, &vbuf)) {
	printf("%s ",buf);
    } else {
	printf("%s ", vbuf);
    } 
  }
  return 0;
}
