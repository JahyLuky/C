#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define INITIAL_CAPACITY 100
#define DEBUG 0

long * getInput ( long * maxLoad, long * maxTex )
{
    printf ( "Zatez:\n" );

    *maxLoad = *maxTex = 0;

    long cap = INITIAL_CAPACITY;
    long * timeline = (long*) calloc (cap,  sizeof ( *timeline ) );

    while ( ! feof ( stdin ) )
    {
        char * load = NULL;
        size_t bSizeLoad = 0;
        getdelim ( &load, &bSizeLoad, ':', stdin );
        char * endPtrLoad;
        long intLoad = strtol ( load, &endPtrLoad, 10 );
        free ( load );

        char * fin = NULL;
        size_t bSizeFin = 0;
        getdelim ( &fin, &bSizeFin, '.', stdin );
        char * endPtrFin;
        long intFin = strtol ( fin, &endPtrFin, 10 );
        free ( fin );

        char * tex = NULL;
        size_t bSizeTex = 0;
        getline ( &tex, &bSizeTex, stdin );
        char * endPtrTex;
        char * texTrim = &(tex[1]);
        long intTex = strtol ( texTrim, &endPtrTex, 10);
        free ( tex );

        long newCap = 0;
        if ( intTex > cap )
        {
            newCap += intTex + cap;
            long * newTimeline = (long*) calloc ( newCap, sizeof ( *newTimeline) );
            memcpy ( newTimeline, timeline, sizeof ( timeline) * cap );
            free ( timeline );
            timeline = newTimeline;
            cap = newCap;
        }

        for ( long i = intFin; i < intTex; i ++ )
        {
            timeline[i] += intLoad;

            if ( timeline[i] > *maxLoad )
                *maxLoad = timeline[i];
        }

        if ( intTex > *maxTex )
            *maxTex = intTex;
    }

    return timeline;
}

#if DEBUG
void DB_printLoad ( const long * timeline, const long max )
{
	for ( long i = 0; i <= max; i ++ )
	{
		if ( timeline[i] == ( i == 0 ? -1 : timeline[i-1] ) )
			continue;

		printf ( "[%ld]: %ld\n", i, timeline[i] );
	}
}
#endif

void printMaxLoad ( const long * timeline, const long maxLoad, const long maxTex )
{
    printf ( "Nejvyssi zatez: %ld\n", maxLoad );

#if DEBUG
    DB_printLoad ( timeline, maxTex );
#endif

    for ( long i = 0; i <= maxTex; i ++ )
    {
        long start, end;

        if ( timeline[i] == maxLoad )
        {
            start = i;

            while ( timeline[i] == maxLoad )
                end = i ++;

            printf ( "%ld..%ld\n", start, end + 1 );
        }
    }
}

int main ( void )
{
    long maxLoad, maxTex;
    long * timeline = getInput ( &maxLoad, &maxTex );

    printMaxLoad ( timeline, maxLoad, maxTex );

    free ( timeline );
    return EXIT_SUCCESS;
}
