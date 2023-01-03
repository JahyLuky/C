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
 
typedef struct TNode
{
    struct TNode * m_Next;
    char           m_Digit;
} TNODE;
 
TNODE * createNode ( char digit, TNODE * next )
{
    TNODE * n = (TNODE *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TNODE * l)
{
    while (l)
    {
        TNODE * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

TNODE * shiftLeft ( TNODE * a, unsigned int shift ) {

}

int main (int argc, char * argv []) {
    TNODE * a = NULL, * res = NULL;
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
    
    a = createNode ( 'a',
        createNode ( 'w',
            createNode ( '0', NULL )));
    res = shiftLeft ( a, 12 );
    assert ( res == NULL );
    deleteList ( a );
    
    a = NULL;
    res = shiftLeft ( a, 1 );
    assert ( res == NULL );
    return 0;
}