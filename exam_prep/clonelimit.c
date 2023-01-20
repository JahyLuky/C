/*
Zadání bylo odstraňování duplicit ze spojáku podle limitu (limit 1 → max jeden výskyt čísla, limit 2 → max dva výskyty jednoho čísla).

Implementace funkce cloneLimit(TITEM *a, int limit)

Limit menší než 1 nebo prázdný spoják vrací NULL.

vstup: 1->2->3->1->2->5 limit 1                   výstup: 1->2->3->5
vstup: 1->2->4->2->4->1->3->1->1->4->2->5 limit 2 výstup: 1->2->4->2->4->1->3->5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem
{
	struct TItem * m_Next;
	int            m_Val;
} TITEM;
 
TITEM * createItem ( int value, TITEM * next )
{
	TITEM * n = (TITEM *) malloc (sizeof ( *n ));
	n -> m_Val = value;
	n -> m_Next = next;
	return n;
}
 
void deleteList (TITEM * l)
{
	while (l)
	{
		TITEM * tmp = l -> m_Next;
		free (l);
		l = tmp;
	}
}
 
TITEM * cloneLimit(TITEM *a, int limit)  {
/* TO DO*/
}

int main (void) {

    return 0;
}