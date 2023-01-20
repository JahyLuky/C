/*
Parafráze zadání

Ukolem je vytvořit rozhraní pro správu studentů ucházejících se o splnění zkoušky.
Na vstupu jsou zadáná jména studentů ve formátu X: Jmeno1 Jmeno2 Jmeno3,
kde „X“ je buď písmeno „R“ (zaregistroval se na zkoušku) nebo „P“ (přišel na zkoušku).
Jmeno1, Jmeno2 a Jmeno3 má maximálně 32 znaků a může být zadáno jedno až tři jména studenta, přičemz mezi jmény je právě jedna mezera.
BONUS: Pocet jmen nebyl omezeny a jejich velikost taky nebyla omezena.
Jména studentů jsou stejná i pakliže nejsou ve stejném pořadí, nebo mají jinak velká písmena
Ladislav Vagner == Vagner Ladislav == LaDIslAV VagNER.
Ukolem je:
1) vypsat ty studenty, kteří se zaregistrovali na zkoušku, ale nepřišli
2) vypsat ty studenty, kteří přišli na zkoušku, ale nezaregistrovali se
Výpis jmen studentů musí být ve stejnem pořadí jako při zadání jmen a také case-sensitivite jako na vstupu.
např. vstup Franta PEPA jeDnička → výstup Franta PEPA jeDnička
Poradi vypsání ruznych jmen studentu neni urceno, Progtest si jej upraví.
Pokud byli zadáni studenti přihlášní na zkoušku se stejným jménem např. Jarda Pepa == PePA jaRDA,
ale registrován byl pouze jeden student s tímto jménem (např. JArda PePA), tak platí priorita toho, který byl na vstupu zadaný jako první.
Nespravny Vstup:
1) Nejdrive se zadavaji Registrovani studenti a poté Přítomní. Pokud na vstupu je zadán Registrovaný student až po přítomném je vstup chybný.
2) Na začátku řádky není identifikátor P nebo R.
! prádný vstup není nesprávný vstup

Studenti:
R: Ladislav Vagner
R: Jan Travnicek
R: Jan Novy Jan
R: Jan Kuba
P: Jan Novy
P: Jan Travnicek
P: VAGNER Ladislav
P: Vagner Ladislav

bude mít výstup

Nepritomni:
* Jan Novy Jan
* Jan Kuba
Bez registrace:
* Jan Novy
* Vagner Ladislav
Studenti:
R: Ladislav Vagner
R: Jan Travnicek
P: Ladislav Vagner
P: Jan Travnicek

Nepritomni:
Bez registrace:
Studenti:
R: Ladislav Vagner
R: Jan Travnicek
R: Janek Pepek
P: vaGneR lAdislaV
P: Jan Travnicek

Nepritomni:
* Janek Pepek
Bez registrace:
Studenti:

Nepritomni:
Bez registrace:
Studenti:
R: Vagner Jaroslav
R: Jan Novak
R: JaROSLAV VaGNer
R: Honza Jarda PEpicek
P: Novak Jan
P: Jaroslav Vagner
P: Honza Jarda PEpicek
P: Tonik

Nepritomni:
JaROSLAV VaGNer
Bez registrace:
Tonik
Studenti:
R: Vagner Jaroslav
O: Jan Novak
Nespravny vstup.
Studenti:
R: Vagner Jaroslav
R: Jan Novak
R: JaROSLAV VaGNer
P: Tonik Josef
R: Honza Balik
Nespravny vstup.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct NAME {
    char * name1;
    char * name2;
    char * name3;
    char state; // R, P, D - done
    int num;
} name;

char * get_names (char * str, int len, int * idx) {
    if (*idx == len) {
        return NULL;
    }
    int j = 0, i = *idx;
    char * name = (char *) malloc(33 * sizeof(char));
    for (; i < (len-1); i++, j++)   
    {
        if (str[i] == ' ' || str[i] == '\n') {
            break;
        }
        name[j] = str[i];
        //printf("%c", str[i]);
    }
    name[j] = '\0';
    *idx = i+1;
    //printf("%s\n", name);
    return name;
}

int main (void) {
    char * str = NULL;
    size_t buff = 0;
    char last_char = 'a';
    int id = 0, id2 = 0, size = 1, size2 = 1, len = 0, idx = 0, in = 0;
    name ** arr = (name**) malloc(size * sizeof(**arr));
    name ** arr2 = (name**) malloc(size2 * sizeof(**arr2));
    printf("Studenti:\n");
    while (1) {
        if (feof(stdin)) {
            free(str);
            break;
        }
        in = getline(&str, &buff, stdin);
        if (in == -1) {
            // empty input
            if (id == 0) {
                free(str);
                break;
            }
            continue;
        }
        len = (strlen(str));
        idx = 3;
        // name{1,2,3} <= 32 + 3 spaces + 2 R/P:
        if (len > 60 || (last_char == 'P' && str[0] == 'R')) {
            printf("err1: %s\n", str);
            free(str);
            return 1;
        }
        if (str[0] == 'R') {
            arr[id] = (name*) malloc(sizeof(name));
            arr[id]->state = 'R';
            arr[id]->name1 = (get_names(str, len, &idx));
            arr[id]->num = 1;
            arr[id]->name2 = (get_names(str, len, &idx));
            if (arr[id]->name2 != NULL) {
                arr[id]->num = 2;
            }
            arr[id]->name3 = (get_names(str, len, &idx));
            if (arr[id]->name3 != NULL) {
                arr[id]->num = 3;
            }
            id++;
            if (id == size) {
                size *= 2;
                arr = (name**) realloc(arr, size * sizeof(*arr));
            }
        } else if (str[0] == 'P') {
            arr2[id2] = (name*) malloc(sizeof(name));
            arr2[id2]->state = 'P';
            arr2[id2]->num = 1;
            arr2[id2]->name1 = (get_names(str, len, &idx));
            arr2[id2]->name2 = (get_names(str, len, &idx));
            if (arr2[id2]->name2 != NULL) {
                arr2[id2]->num = 2;
            }
            arr2[id2]->name3 = (get_names(str, len, &idx));
            if (arr2[id2]->name3 != NULL) {
                arr2[id2]->num = 3;
            }
            id2++;
            if (id2 == size2) {
                size2 *= 2;
                arr2 = (name**) realloc(arr2, size2 * sizeof(*arr));
            }
        } else {
            printf("err2: %s\n", str);
            free(str);
            return 1;
        }
        last_char = str[0];
    }

    for (int i = 0; i < id; i++) {
        for (int j = 0; j < id2; j++) {
            if (arr2[j]->state == 'D') {
                continue;
            }
            if (arr[i]->num != arr2[j]->num) {
                break;
            }
            if (arr[i]->num == 1) {
                if (strcasecmp(arr[i]->name1, arr2[j]->name1) == 0) {
                    arr[i]->state = 'D';
                    arr2[j]->state = 'D';
                    break;
                }
            }
            if (arr[i]->num == 2) {
                if (strcasecmp(arr[i]->name1, arr2[j]->name1) == 0 
                 || strcasecmp(arr[i]->name1, arr2[j]->name2) == 0) {
                    if (strcasecmp(arr[i]->name2, arr2[j]->name1) == 0 
                     || strcasecmp(arr[i]->name2, arr2[j]->name2) == 0) {
                        arr[i]->state = 'D';
                        arr2[j]->state = 'D';
                        break;
                    }
                }
            }
            if (arr[i]->num == 3) {
                if (strcasecmp(arr[i]->name1, arr2[j]->name1) == 0 
                 || strcasecmp(arr[i]->name1, arr2[j]->name2) == 0
                 || strcasecmp(arr[i]->name1, arr2[j]->name3) == 0) {
                    if (strcasecmp(arr[i]->name2, arr2[j]->name1) == 0 
                     || strcasecmp(arr[i]->name2, arr2[j]->name2) == 0
                     || strcasecmp(arr[i]->name2, arr2[j]->name3) == 0) {
                        if (strcasecmp(arr[i]->name3, arr2[j]->name1) == 0 
                        || strcasecmp(arr[i]->name3, arr2[j]->name2) == 0
                        || strcasecmp(arr[i]->name3, arr2[j]->name3) == 0) {
                            arr[i]->state = 'D';
                            arr2[j]->state = 'D';
                            break;
                    }
                    }
                }
            }
        }
    }

    printf("Nepritomni:\n");
    for (int i = 0; i < id; i++) {
        if (arr[i]->state == 'R') {
            if (arr[i]->name2 == NULL) {
                printf("* %s\n", arr[i]->name1);
            } else {
                if (arr[i]->name3 == NULL) {
                    printf("* %s ", arr[i]->name1);
                    printf("%s\n", arr[i]->name2);
                } else {
                    printf("* %s ", arr[i]->name1);
                    printf("%s ", arr[i]->name2);
                    printf("%s\n", arr[i]->name3);
                }
            }
        }
        free(arr[i]->name1);
        free(arr[i]->name2);
        free(arr[i]->name3);
        free(arr[i]);
    }
    free(arr);

    printf("Bez registrace:\n");
    for (int i = 0; i < id2; i++) {
        if (arr2[i]->state == 'P') {
            if (arr2[i]->name2 == NULL) {
                printf("* %s\n", arr2[i]->name1);
            } else {
                if (arr2[i]->name3 == NULL) {
                    printf("* %s ", arr2[i]->name1);
                    printf("%s\n", arr2[i]->name2);
                } else {
                    printf("* %s ", arr2[i]->name1);
                    printf("%s ", arr2[i]->name2);
                    printf("%s\n", arr2[i]->name3);
                }
            }
        }
        free(arr2[i]->name1);
        free(arr2[i]->name2);
        free(arr2[i]->name3);
        free(arr2[i]);
    }
    free(arr2);

    return 0;
}