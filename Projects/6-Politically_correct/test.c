#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

typedef struct {
    int id_replace; // index in replace
    int str_size; // size of peplace[i][1]
    int real_str_size; // size of *replace[i]
    int start; // first letter to change in text
    int add_size; // peplace[i][1] - *replace[i]
} rep;

// Compare 2 strings
// 0 -> 1 string is substring of another
// 1 -> strings are different
char *find_substring(const char *a, const char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int flag = 1;
    char *res;
    if (lenA < lenB)
        flag = 0;
    if (flag) {
        res = (char *) strstr(a, b);
        return res;
    } else {
        res = (char *) strstr(b, a);
        return res;
    }
}

// Compare 2 strings
// idx -> index where substring starts
// -1 -> strings are different
int change_substring(char *a, char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    char *pA = a; 
    char *pB = b;
    char *p_tmp;
    int id_A = 0, id_B = 0, found = 0, idx = 0;

    if (lenA < lenB) {
        int tmp = lenA;
        lenA = lenB;
        lenB = tmp;
    }

    for (;id_A < lenA; id_A++) {
        if (*pA == *pB) {
            p_tmp = pA;
            for (id_B = 0; id_B < lenB; id_B++) {
                if (*p_tmp != *pB) {
                    break;
                } else {
                    p_tmp++;
                    pB++;
                }
            }
            pB = b;
            if (id_B == lenB) {
                found = 1;
                idx = id_A;
                break;
            }
        }
        pA++;
    }
    if (found)
        return idx;
    return -1;
}

char *newSpeak(const char *text, const char *(*replace)[2]) {
    if (*replace[0] == NULL) {
        char *text_cp = strdup(text);
        return text_cp;
    }
    
    // Looking for substring in replace
    int j = 1, cnt = 0;
    while (1) {
        if (*replace[j] != NULL && cnt != j) {
            //printf("%s %s\n", *replace[cnt], *replace[j]);
            if (find_substring(*replace[cnt], *replace[j])) {
                return NULL;
            }
            j++;
        } else {
            cnt++;
            if (*replace[cnt] == NULL)
                break;
            j = 0;
        }
    }

    rep * arr = (rep*) malloc(cnt * sizeof(rep));
    //printf("%s -> %s[0] to %s[1]\n", text, *replace[0], replace[0][1]);
    char *text_cp = strdup(text);
    int start = 0, id = 0, num = 0;
    for (; id < cnt; id++) {
        start = change_substring(text_cp, (char *) *replace[id]);
        if (start != -1) {
            arr[num].id_replace = id;
            arr[num].start = start;
            arr[num].str_size = strlen(replace[id][1]);
            arr[num].real_str_size = strlen((char*)*replace[id]);
            arr[num].add_size = arr[num].str_size - strlen((char*)*replace[id]);
            printf("Change '%s' for '%s'\n", (char *) *replace[id], (char*)replace[id][1]);
            printf("id: %d\nstart: %d\nstr_size: %d\nadd: %d\n", arr[num].id_replace, arr[num].start, arr[num].str_size, arr[num].add_size);
            num++;
        }
    }

    // no substring
    if (num == 0)
        return text_cp;

    int len = strlen(text_cp);
    int pass = 0;
    int i = 0;
    char * tmp, *p;
    tmp = (char*)malloc((len+arr[i].add_size) * sizeof(char));
    len = len+arr[i].add_size;
    int add = arr[i].add_size;
    p = (char*)replace[arr[i].id_replace][1];
    for (int j = 0; j < (len+arr[i].add_size); j++) {
        //tmp = (char*) realloc(text_cp, (len+arr[i].add_size) * sizeof(char));
        
        if (j < arr[i].start) {
            tmp[j] = text_cp[j];
        }
        if (pass == arr[i].str_size) {
            if (add < 0)
                tmp[j] = text_cp[j+add];
            else
                tmp[j] = text_cp[j-add];
        }
        if (j >= arr[i].start && pass != arr[i].str_size) {
            tmp[j] = p[pass++];
        }
    }
    pass = 0;
    i = 1;
    char *tmp1 = (char*)malloc((len+arr[i].add_size) * sizeof(char));
    add = arr[i].add_size;
    p = (char*)replace[arr[i].id_replace][1];
    for (int j = 0; j < len; j++) {
        //tmp = (char*) realloc(text_cp, (len+arr[i].add_size) * sizeof(char));
        
        if (j < arr[i].start) {
            tmp1[j] = tmp[j];
        }
        if (pass == arr[i].str_size) {
            if (add < 0)
                tmp1[j] = tmp[j+add];
            else
                tmp1[j] = tmp[j-add];
        }
        if (j >= arr[i].start && pass != arr[i].str_size) {
            tmp1[j] = p[pass++];
        }
    }

    printf("tmp: %s\n", tmp);
    printf("final: %s\n", tmp1);
    printf("-----------------------------------------\n");
    return tmp1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  char * res;

  const char * d1 [][2] =
  {
    { "murderer", "termination specialist" },
    { "failure", "non-traditional success" },
    { "specialist", "person with certified level of knowledge" },
    { "dumb", "cerebrally challenged" },
    { "teacher", "voluntary knowledge conveyor" },
    { "evil", "nicenest deprived" },
    { "incorrect answer", "alternative answer" },
    { "student", "client" },
    { NULL, NULL }
  };


  const char * d2 [][2] =
  {
    { "fail", "suboptimal result" },
    { "failure", "non-traditional success" },
    { NULL, NULL }
  };


  res = newSpeak ( "Everybody is happy.", d1 );
  assert ( ! strcmp ( res, "Everybody is happy." ) );
  free ( res );

  res = newSpeak ( "The student answered an incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
  printf("len1: %ld, len2: %ld\n", strlen("The student answered an incorrect answer."), strlen("The client answered an alternative answer."));
  free ( res );

  res = newSpeak ( "He was dumb, his failure was expected.", d1 );
  assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
  free ( res );

  res = newSpeak ( "The evil teacher became a murderer.", d1 );
  assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
  free ( res );

  res = newSpeak ( "Devil's advocate.", d1 );
  assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
  free ( res );

  res = newSpeak ( "Hello.", d2 );
  assert ( ! res );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */