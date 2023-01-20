/*
Funkce shiftLeft si bere v parametru číslo v šestnáctkové soustavě reprezentované jako spojový seznam. Stejně jako v předchozích úlohách je číslo uloženo pozpátku, tudíž hlavou spojového seznamu je nejnižší řád. Např.:

3 -> 2 -> 1 -> NULL <=> 123(hex) <=> 291(dec)
Vaše funkce musí číslo bitově posunout o shift pozic doleva (parametr). Výsledek pak vrátí jako odkaz na hlavu nově vytvořeného spojového seznamu. Původní číslo se nesmí změnit. Ukázka práce programu:

123(hex) << 1 = 246(hex)
1af(hex) << 3 = d78(hex)

Funkce musí zároveň správně detekovat nesprávná čísla. Taková čísla:
- jsou NULL
- číslice není v rozmezí '0-9' nebo 'a-f'
- obsahuje přebytečné nuly

V takovém případě funkce vrací NULL.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TNode {
    struct TNode * m_Next;
    char m_Digit;
} TNODE;
 
TNODE * createNode ( char digit, TNODE * next ) {
    TNODE * n = (TNODE *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TNODE * l) {
    while (l) {
        TNODE * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

int toInt (char a) {
    int tmp = a - '0';
    // valid number
    if (tmp >= 0 && tmp <= 9) {
        return tmp;
    }
    if (a == 'a') return 10;
    if (a == 'b') return 11;
    if (a == 'c') return 12;
    if (a == 'd') return 13;
    if (a == 'e') return 14;
    if (a == 'f') return 15;
    return -1;
}

int checkDigit (char a) {
    int tmp = toInt(a);
    if (tmp < 0 || tmp > 15) return 1;
    return 0;
}

int check (TNODE * a) {
    if (a == NULL) return 1;
    while (a) {
        // digit is not 0-9 or 'a'-'f'
        if (checkDigit(a->m_Digit)) return 1;
        // zero in the end
        if (a->m_Next == NULL && a->m_Digit == '0') return 1;
        a = a->m_Next;
    }
    return 0;
}

TNODE * shiftLeft ( TNODE * a, unsigned int shift ) {
    if (check(a)) {
        return NULL;
    }

    // a != null -> save first digit
    TNODE * tmp = a->m_Next;
    int num = toInt(a->m_Digit);
    int new_num = 0, mocnina = 1;
    while (tmp) {
        new_num = toInt(tmp->m_Digit);
        num += new_num * (16 * mocnina);
        mocnina *= 16;
        tmp = tmp->m_Next;
    }
    // shift number
    num = num << shift;
    // create buffer
    char buff [1000];
    // sprintf to convert 'num' to HEX format (%x)
    sprintf(buff, "%x", num);
    
    int len = strlen(buff);
    TNODE * res = (TNODE*) malloc(sizeof(*res));
    TNODE * head = res;
    // last index in buff -> first number
    for (int i = len - 1; i >= 0; i--) {
        res->m_Digit = buff[i];
        if (i == 0) {
            res->m_Next = NULL;
        } else {
            res->m_Next = (TNODE*) malloc(sizeof(*res));
            res = res->m_Next;
        }
    }

    return head;
}

int main (int argc, char * argv []) {
    TNODE * a = NULL, * res = NULL;

    a = createNode ( 'a',
        createNode ( 'w',
            createNode ( '0', NULL )));
    res = shiftLeft ( a, 12 );
    assert ( res == NULL );
    deleteList ( a );
    
    a = NULL;
    res = shiftLeft ( a, 1 );
    assert ( res == NULL );


    a = createNode ( '3',
        createNode ( '2',
            createNode ( '1', NULL )));
    res = shiftLeft ( a, 1 );
    assert ( res -> m_Digit == '6' );
    assert ( res -> m_Next -> m_Digit == '4' );
    assert ( res -> m_Next -> m_Next -> m_Digit == '2' );
    assert ( res -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( res );
   
    a = createNode ( 'f',
        createNode ( 'a',
            createNode ( '1', NULL )));
    res = shiftLeft ( a, 3 );
    assert ( res -> m_Digit == '8' );
    assert ( res -> m_Next -> m_Digit == '7' );
    assert ( res -> m_Next -> m_Next -> m_Digit == 'd' );
    assert ( res -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( res );
    
    a = createNode ( 'c',
        createNode ( '5',
            createNode ( '4',
            createNode ( 'd',
                createNode ( '1', NULL )))));
    res = shiftLeft ( a, 5 );
    assert ( res -> m_Digit == '0' );
    assert ( res -> m_Next -> m_Digit == '8' );
    assert ( res -> m_Next -> m_Next -> m_Digit == 'b' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Digit == '8' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == 'a' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == '3' );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( res );
    
    return 0;
}