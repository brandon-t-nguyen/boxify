#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Mode_e
{
    MODE_ARG,
    MODE_STDIN
} Mode;

static inline
void printBlanks( int count )
{
    for (int i = 0; i < count; ++i)
    {
        putchar(' ');
    }
}

int main( int argc, char * argv[] )
{
    Mode mode = MODE_ARG;
    if (argc == 1)
    {
        mode = MODE_STDIN;
    }

    char * str;
    if (mode == MODE_ARG)
    {
        str = argv[1];
    }
    else
    {
        str = malloc( sizeof(char) * 2048 );
        gets( str );
        /*
        size_t len = 0;
        getline( &str, &len, stdin );
        */
    }
    int len = strlen(str);

    // first line
    for (int i = 0; i < len-1; ++i)
    {
        putchar(str[i]);
        putchar(' ');
    }
    putchar(str[len-1]);
    putchar('\n');

    printBlanks( len*2 - 1);
    putchar('\n');
    // middle lines
    for (int i = 0; i < len-2; ++i)
    {
        putchar( str[i+1] );
        printBlanks( len*2 - 3);
        putchar( str[len-1-i] );
        putchar('\n');
        printBlanks( len*2 - 1);
        putchar('\n');
    }

    // last line
    for (int i = len-1; i > 0; --i)
    {
        putchar(str[i]);
        putchar(' ');
    }
    putchar(str[0]);
    putchar('\n');

    if (mode == MODE_STDIN)
    {
        free(str);
    }
}
