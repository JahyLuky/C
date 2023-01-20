/*
Úkolem je realizovat funkci, která dokáže sčítat celá čísla zadaná jako spojové seznamy.

Předpokládáme jednosměrné spojové seznamy. Prvek spojového seznamu ukládá znak - jednu cifru desítkového zápisu čísla. Čísla jsou ukládána směrem od řádu jednotek k vyšším řádům (řád jednotek je na začátku spojového seznamu). Požadovaná funkce dostane dva spojové seznamy, které reprezentují taková celá čísla. Jejím výsledkem je nově vytvořený spojový seznam, který reprezentuje výsledek součtu takto zadaných čísel. Funkce nesmí měnit spojové seznamy předané v parametrech.

TITEM
je struktura realizující prvek ve spojovém seznamu. Je deklarovaná v testovacím prostředí. Má složku m_Next, která odkazuje na další prvek v seznamu, a složku m_Digit obsahující jednu cifru daného čísla (znak '0' až '9'). Spojový seznam je ukončen hodnotou m_Next = NULL.
addList ( a, b )
tato funkce dostane v parametrech dvě celá čísla reprezentovaná spojovými seznamy výše. Funkce zkontroluje, že se jedná o správně zadaná celá čísla. Pokud je nějaký parametr neplatný, funkce vrátí NULL. Pokud jsou oba parametry platná celá čísla, funkce vrátí nově vytvořený spojový seznam obsahující součet čísel z parametrů.
Spojový seznam reprezentuje platné celé číslo, pokud:
obsahuje alespoň jednu cifru (není NULL),
obsahuje pouze cifry '0' až '9',
číslo neobsahuje zbytečné úvodní nuly (tedy v naší reprezentaci spojový seznam nekončí zbytečnými nulami).
CISLO A:

[2] → [3] → [9] → [NULL]

Cislo B:

[5] → [3] → [1] → [NULL]

Vysledek:

[7] → [6] → [0] → [1] → [NULL]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;
 
TITEM * createItem(char digit, TITEM * next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}
 
void deleteList(TITEM * l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
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

char toChar (int a) {
    return a + '0';
}

int check (TITEM * a, int start) {
    if (a != NULL) {
        int tmp = toInt(a->m_Digit);
        // not a number
        if (tmp == 10) {
            return 1;
        }
        // number ends with zero
        if (tmp == 0 && a->m_Next == NULL
            && start != 1) {
            return 1;
        }
    }
    return 0;
}

TITEM * addList ( TITEM * a, TITEM * b ) {
    if (a == NULL || b == NULL) return NULL;
    TITEM * aa = a;
    TITEM * bb = b;
    int start = 0;
    
    while (aa != NULL || bb != NULL) {
        start++;
        if (check(aa, start)) {
            return NULL;
        }
        if (check(bb, start)) {
            return NULL;
        }
        if (aa == NULL) {
            bb = bb->m_Next;
            continue;
        }
        if (bb == NULL) {
            aa = aa->m_Next;
            continue;
        }
        if (aa != NULL && bb != NULL) {
            aa = aa->m_Next;
            bb = bb->m_Next;
        }
    }

    TITEM * res = (TITEM*) malloc(sizeof(*res));
    TITEM * head = res;
    int sum = 0, carry = 0;
    
    while (a || b) {
        // only b
        if (a == NULL) {
            sum = toInt(b->m_Digit) + carry;

            if (sum > 9) {
                carry = 1;
                sum -= 10;
            } else {
                carry = 0;
            }

            res->m_Digit = toChar(sum);

            if (b->m_Next == NULL) {
                res->m_Next = NULL;
            } else {
                res->m_Next = (TITEM*) malloc(sizeof(*res));
                res = res->m_Next;
            }

            b = b->m_Next;
            continue;
        }
        // only a
        if (b == NULL) {
            sum = toInt(a->m_Digit) + carry;

            if (sum > 9) {
                carry = 1;
                sum -= 10;
            } else {
                carry = 0;
            }

            res->m_Digit = toChar(sum);

            if (a->m_Next == NULL) {
                res->m_Next = NULL;
            } else {
                res->m_Next = (TITEM*) malloc(sizeof(*res));
                res = res->m_Next;
            }

            a = a->m_Next;
            continue;
        }
        // both nodes
        sum = toInt(a->m_Digit) + toInt(b->m_Digit);
        
        if (sum > 9) {
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }

        res->m_Digit = toChar(sum);

        if (a->m_Next == NULL && b->m_Next == NULL) {
            res->m_Next = NULL;
        } else {
            res->m_Next = (TITEM*) malloc(sizeof(*res));
            res = res->m_Next;
        }

        a = a->m_Next;
        b = b->m_Next;
        continue;
    }
    // last sum was 9 + something -> we need more digits
    if (carry) {
        res->m_Next = (TITEM*) malloc(sizeof(*res));
        res = res->m_Next;
        res->m_Digit = '1';
        res->m_Next = NULL;
    }

    return head;
}

int main(int argc, char *argv[]) {
    TITEM * a, * b, * res;
 
    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('5',
         createItem('0',
          createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('2', createItem('3', createItem('3', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('2', createItem('3', createItem('9', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('9', createItem('9', createItem('9', NULL)));
    b = createItem('1', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '0');
    assert (res->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('9', createItem('9', createItem('9', NULL)));
    b = createItem('2', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '1');
    assert (res->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    return 0;
}