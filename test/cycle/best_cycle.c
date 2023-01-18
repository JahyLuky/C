/*
Úkolem je vytvořit program, který bude vyhledávat plán pro cyklistický výlet. Vstupem programu je zadaná cyklotrasa. Cyklotrasa je definována body, kde lze jízdu začít/ukončit (mezi zadanými body nelze najet/sjet). Úkolem je vybrat, kde začít a kde ukončit cyklistický výlet. Pro plán výletu máme následující omezení:

  Nadmořská výška nástupního bodu musí být vyšší nebo stejná jako nadmořská výška výstupního bodu (chceme jet z kopce nebo v nejhorším po rovině).
  Stoupání uprostřed trasy nevadí, ale celkově musíme klesnout.
  Máme-li více voleb se stejným klesáním, zvolíme tu delší.
Vstupem programu jsou jednotlivé nástupní/koncové body na cyklotrase, např. 210 + 5 300 + 6 270

První vstup udává nadmořskou výšku startovního bodu trasy. Následují další body na trase vždy v podobě + vzdálenost_od_startu nadmořská_výška. Vstup končí s EOF. Výstupem programu je vyhledaný úsek na cyklotrase, kde lze dosáhnout největšího klesání. Výstupem je jednak délka nalezeného úseku, dále dosažené klesání a počet variant kde ho lze dosáhnout. Na dalších řádkách pak následuje výpis těchto úseků (v libovolném pořadí). Může se stát, že nelze vybrat žádný úsek cyklotrasy. Pak má výstup jiný formát. Kontrola vstupu nebyla potřeba.

Procházet cyklotrasu šlo pouze v jednom směru (od startu dál) Na 7.5 bodu stačil algoritmus O(n^2).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct CYCLE {
    int km, vyska;
} cycle;

void print_distance (cycle *** arr, int n, int ** final, int id, int max, int max_km) {
    if (max_km == 0 && max == 0 && id == 0) {
        printf("Nenalezeno\n");
    } else {
        printf("%d km, klesani: %d m, varianty: %d\n", max_km, max, id/2);
        for (int i = 0; i < id; i+=2) {
            printf("+ %d (%d) -> + %d (%d)\n", (**arr)[(*final)[i]].km, 
            (**arr)[(*final)[i]].vyska, 
            (**arr)[(*final)[i+1]].km, (**arr)[(*final)[i+1]].vyska);
        }
    }
}

void get_distance (cycle ** arr, int n) {
    int dist = 0, max = 0, max_km = 0, km = 0, id = 0;
    int * final = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) { 
                continue; 
            }
            dist = (*arr)[i].vyska - (*arr)[j].vyska;
            km = (*arr)[j].km - (*arr)[i].km;
            if (dist > max) {
                id = 0;
                max_km = km;
                max = dist;
                final[id++] = i;
                final[id++] = j;
                continue;
            }
            if (dist == max) {
                if (km > max_km) {
                    max_km = km;
                    id = 0;
                    final[id++] = i;
                    final[id++] = j;
                    continue;
                }
                if (km == max_km) {
                    final[id++] = i;
                    final[id++] = j;
                }
            }
        }
    }
    
    print_distance(&arr, n, &final, id, max, max_km);
    
    free(final);
}

int main (void) {
    printf("Cyklotrasa:\n");
    int start = 0, dist = 0, alt = 0, n = 0, size = 1;
    
    cycle * arr = (cycle*) malloc (size * sizeof(cycle));
    char * s = NULL;
    size_t b;
    char t;
    while (getline(&s, &b, stdin)) {
        if (feof(stdin)) {
            free(s);
            break;
        }
        if (n == 0) {
            sscanf(s, "%d", &start);
            arr[n].km = 0;
            arr[n].vyska = start;
            n++;
        } else {
            sscanf(s, "%c %d %d", &t, &dist, &alt);
            if (t != '+') {
                free(s);
                free(arr);
                return 1;
            }
            arr[n].km = dist;
            arr[n].vyska = alt;
            n++;
        }
        if (n == size) {
            size *= 2;
            arr = (cycle*) realloc(arr, size * sizeof(cycle));
        }
    }

    get_distance(&arr, n);
    
    free(arr);
    return 0;
}