#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

int is_palindrom (char * s, size_t len) {
  size_t white_space_cnt = 0, new_len = 0;
  char * str = (char*) malloc((len+1) * sizeof(str));

  for (size_t i = 0; i < len; i++)
  {
    if (isspace(s[i]) != 0) {
      white_space_cnt++;
      continue;
    }
    str[new_len++] = s[i];
  }
  str[++new_len] = '\0';

  if (white_space_cnt == len) {
    free(str);
    return -1;
  }

  len = new_len - 2;
  size_t half_len = (len / 2) + 1;
  size_t char_case_diff = 0;

  for (size_t i = 0; i < half_len; i++)
  {
    if (tolower(str[i]) != tolower(str[len-i])) {
      free(str);
      return 0;
    }
    if (islower(str[i]) != islower(str[len-i]))
      char_case_diff = 1;
  }
  if (char_case_diff)
    printf("Retezec je palindrom (case-insensitive).\n");
  else
    printf("Retezec je palindrom (case-sensitive).\n");

  free(str);
  return 1;
}


int main ( void ) {
  size_t cap = 0, len = 0;
  char *str = NULL;
  int palin = 0;

  printf("Zadejte retezec:\n");
  while (1) {
    getline(&str, &cap, stdin);
    len = strlen(str);
    if (str[len-1] != '\n' ) {
      printf("Nespravny vstup.\n");
      free(str);
      return 0;
    }
    if (feof(stdin)) {
      if (str[0] == '\n') {
        printf("Nespravny vstup.\n");
        free(str);
        return 0;
      }
      free(str);
      break;
    }

    palin = is_palindrom(str, len - 1);

    if (palin == 0)
      printf("Retezec neni palindrom.\n");
    else if (palin == -1) {
      printf("Nespravny vstup.\n");
      free(str);
      return 0;
    }
  }
  return 1;
}