/*
Úkolem je realizovat funkci, která dokáže nalézt největší číslo v poli. Komplikací je, že čísla jsou reprezentovaná jako spojový seznam jejich cifer.

Předpokládáme jednosměrné spojové seznamy. Prvek spojového seznamu ukládá znak - jednu cifru zápisu čísla. Čísla jsou ukládána směrem od řádu jednotek k vyšším řádům (řád jednotek je na začátku spojového seznamu). Požadovaná funkce dostane pole s odkazy na taková čísla (spojové seznamy) a počet prvků v poli. Jejím výsledkem bude spojový seznam, který reprezentuje největší číslo v zadaném poli.
TITEM je struktura realizující prvek ve spojovém seznamu. Je deklarovaná v testovacím prostředí. Má složku m_Next, která odkazuje na další prvek v seznamu, a složku m_Digit obsahující jednu cifru daného čísla (znak '0' až '9'). Spojový seznam je ukončen hodnotou NULL.

maxOf ( x, nr )
tato funkce dostane v parametrech pole x se spojovými seznamy, každý spojový seznam reprezentuje jako desítkové číslo. Druhým parametrem je počet prvků v poli. Funkce zkontroluje, že se jedná o správně zadaná celá čísla. Pokud je nějaký parametr neplatný nebo pokud pole obsahuje nulový počet prvků, funkce vrátí NULL. V opačném případě (platné vstupní parametry) funkce nalezne největší z předaných čísel a vrátí odkaz na něj. Pokud je největší číslo v poli obsaženo vícekrát, má funkce vrátit odkaz na první výskyt maxima (viz druhý příklad v ukázkovém běhu).

Spojový seznam reprezentuje platné celé číslo, pokud:

obsahuje alespoň jednu cifru (není NULL),
obsahuje pouze cifry '0' až '9'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct Titem {
  struct Titem * m_Next;
  char m_Digit;
} TITEM;
 
TITEM * createItem ( char i ,TITEM * next ) {
  TITEM * l = (TITEM*) malloc ( sizeof(*l) ); 
  l->m_Digit = i;
  l->m_Next = next;
  return l;
}
TITEM * createList(const char * x) {
    int i = 0;
    TITEM * item = NULL;
    while(x[i]) {
     item = createItem (x[i], item);
     i++;
    }
    return item;
}
void delList ( TITEM * l ) {
  while (l) {
      TITEM * tmp = l->m_Next;
      free (l);
      l = tmp;
  }
}

int toInt (char a) {
    int tmp = a - '0';
    if (tmp < 0 || tmp > 9) {
        return 10;
    }
    return tmp;
}

int check (TITEM * x) {
    TITEM * a = x;
    if (a == NULL) {
        return -1;
    }
    int cnt = 0;
    while(a) {
        if (toInt(a->m_Digit) == 10) {
            return -1;
        }
        cnt++;
        a = a->m_Next;
    }
    return cnt;
}

TITEM * maxOf (TITEM **x, int nr) {
    int max = 0, last_max = 0, get_id = 0, cnt = 0;
    int * arr = (int*) malloc (nr * sizeof(int));
    for (int i = 0; i < nr; i++) {
        max = check(x[i]);
        arr[i] = max;
        if (max == -1) {
            free(arr);
            return NULL;
        }
        if (max > last_max) {
            last_max = max;
            get_id = i;
            cnt = 0;
        }
        if (max == last_max) {
            cnt++;
        }
    }
    //printf("cnt %d\n", cnt);
    
    TITEM ** a = (TITEM**) malloc(nr * sizeof(**a));
    for (int i = 0; i < nr; i++) {
        a[i] = x[i];
    }
    
    TITEM * res = a[get_id];
    int empty = 0, id = get_id, count = 0;
    for (int i = 0; i < nr;) {
        //printf("%d != %d\n", arr[i], last_max);
        if (arr[i] != last_max) {
            //printf("skip i = %d\n", i);
            if ((i+1) == nr) i = 0;
            i++;
            continue;
        }

        if (a[i] == NULL) {
            empty++;
            if (empty == cnt) break;
            i++;
            continue;
        }
        //printf("res = %d, a[i] = %d\n", toInt(res->m_Digit), toInt(a[i]->m_Digit));
        if (toInt(res->m_Digit) < toInt(a[i]->m_Digit)) {
            //printf("id = %d, i = %d\n", id, i);
            id = i;
            res = a[i];
        }

        a[i] = a[i]->m_Next;
        count++;

        if (count == cnt) {
            count = 0;
            i = 0;
            res = res->m_Next;
        } else {
            i++;
        }
    }
    free(arr);
    free(a); 
    //printf("id = %d\n", id);
    return x[id];
}

int main ( void ) {
 
    TITEM * a[5];
    TITEM * res;

    //----- Chybny vstup -----------------------------------------------
    a[0] = createList("222");
    a[1] = NULL;
    a[2] = createList("4333");
    a[3] = createList("1");
    res = maxOf(a, 4);
 
    assert(res == NULL);
 
    for(int i = 0; i < 4; i++) delList(a[i]);
 
    //----- Chybna hodnota ---------------------------------------------
    a[0] = createList("29a");
    a[1] = createList("11");
    res = maxOf(a, 2);
 
    assert(res == NULL);
 
    for(int i = 0; i < 2; i++) delList(a[i]);

    //----- Zakladni test ----------------------------------------------
    a[0] = createList("191");
    a[1] = createList("113");
    a[2] = createList("197");
    res = maxOf(a, 3);
    
    assert(res == a[2]);
 
    for(int i = 0; i < 3; i++) delList(a[i]);
 
    //----- Radove vyssi cislo -----------------------------------------
    a[0] = createList("313");
    a[1] = createList("1191");
    a[2] = createList("997");
    res = maxOf(a, 3);
 
    assert(res == a[1]);
 
    for(int i = 0; i < 3; i++) delList(a[i]);
 
    //----- Stejna cisla -----------------------------------------------
    a[0] = createList("27986");
    a[1] = createList("3256");
    a[2] = createList("27986");
    a[3] = createList("17000");
    res = maxOf(a, 4);
 
    assert(res == a[0]);
 
    for(int i = 0; i < 4; i++) delList(a[i]);
 
    //----- Nula -------------------------------------------------------
    a[0] = createList("0");
    a[1] = createList("0");
    a[2] = createList("0");
    a[3] = createList("0");
    a[4] = createList("0");
    res = maxOf(a, 5);
 
    assert(res == a[0]);
 
    for(int i = 0; i < 5; i++) delList(a[i]);
 
    //----- Unsigned Long Long Int -------------------------------------
    a[0] = createList("0");
    a[1] = createList("18446744073709551615");
    a[2] = createList("1112367822345622");
    a[3] = createList("9991234530632948235");
    a[4] = createList("1213004921032");
    res = maxOf(a, 5);
 
    assert(res == a[1]);
 
    for(int i = 0; i < 5; i++) delList(a[i]);

    //----- Unsigned Long Long Int -------------------------------------
    a[0] = createList("18446744073709551615");
    a[1] = createList("18446744073709551615");
    a[2] = createList("18446744073709551615");
    a[3] = createList("18446744073709551615");
    a[4] = createList("1213004921032");
    res = maxOf(a, 5);
    
    assert(res == a[0]);
 
    for(int i = 0; i < 5; i++) delList(a[i]);

    //----- Unsigned Long Long Int -------------------------------------
    a[0] = createList("18446744073709551615");
    a[1] = createList("19446744073709551615");
    a[2] = createList("18446744073709551615");
    a[3] = createList("18446744073709551615");
    a[4] = createList("1213004921032");
    res = maxOf(a, 5);
 
    assert(res == a[1]);
 
    for(int i = 0; i < 5; i++) delList(a[i]);
 
 
    //----- Vetsi jak Unsigned Long Long Int ---------------------------
    a[0] = createList("50230529401950984100481491404914091408580");
    a[1] = createList("50230529401950123123123234492492042044242");
    a[2] = createList("50230529401950984100480123032931110119944");
    a[3] = createList("50230529401950123123123234492400000000000");
    a[4] = createList("50230531000000000000000000000000000000000");
    res = maxOf(a, 5);

    assert(res == a[4]);
 
    for(int i = 0; i < 5; i++) delList(a[i]);
 
    //----- Vetsi jak Unsigned Long Long Int ruzne dlouhe --------------
    a[0] = createList("253051330239013091349049023023");
    a[1] = createList("253051330239013091349049023024");
    a[2] = createList("2094241212100000000000100100");
    a[3] = createList("999919103904248923023");
    a[4] = createList("999999999999999999999999999");
    res = maxOf(a, 5);
 
    assert(res == a[1]);
 
    for(int i = 0; i < 5; i++) delList(a[i]);

    //----- custom --------------
    a[0] = createList("899999999999999999999999999");
    a[1] = createList("899999999999999999999999999");
    a[2] = createList("999999999999999999999999999");
    a[3] = createList("799999999999999999999999999");
    a[4] = createList("699999999999999999999999999");
    res = maxOf(a, 5);
 
    assert(res == a[2]);
 
    for(int i = 0; i < 5; i++) delList(a[i]);

    return 0;
}