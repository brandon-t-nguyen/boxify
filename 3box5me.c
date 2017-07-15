#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Mode_e
{
    MODE_ARG,
    MODE_STDIN
} Mode;

static inline
void setCell( char * buffer, int w, int h, char c,
              int x, int y )
{
    buffer[ x + y*w ] = c;
}

void drawHor( char * buffer, int w, int h, char * str, int len,
              int x, int y )
{
    int i;
    for (i = 0; i < len-1; ++i)
    {
        setCell( buffer, w, h, str[i], x+i*3, y );
        setCell( buffer, w, h, ' ', x+i*3+1, y );
        setCell( buffer, w, h, ' ', x+i*3+2, y );
    }
    setCell( buffer, w, h, str[i], x+i*3, y );
}

void drawVer( char * buffer, int w, int h, char * str, int len,
              int x, int y )
{
    int i;
    for (i = 0; i < len-1; ++i)
    {
        setCell( buffer, w, h, str[i], x, y+i*2 );
        setCell( buffer, w, h, ' ', x, y+i*2+1 );
    }
    setCell( buffer, w, h, str[i], x, y+i*2 );
}

// x and y is the bottom left
void drawDiag( char * buffer, int w, int h, char * str, int len,
               int x, int y )
{
    for (int i = 0; i < len; ++i)
    {
        setCell( buffer, w, h, str[i], x+i*2, y-i );
    }
}

void draw( char * buffer, int w, int h, char * str, int len )
{
    int linew = (len-1)*2 + len;
    int lineh = (len-1) + len;

    // use reverse string
    char * rev = malloc( sizeof(char) * len );
    for (int i = 0; i < len; ++i)
    {
        rev[i] = str[len-1-i];
    }

    // draw back square
    int basex, basey;
    basex = (len-1)*2 + 1 - 1;
    basey = 0;
    drawVer( buffer, w, h, rev, len, basex, basey );
    drawVer( buffer, w, h, str, len, basex+linew-1, basey );
    drawHor( buffer, w, h, rev, len, basex, basey );
    drawHor( buffer, w, h, str, len, basex, basey+lineh-1 );

    // draw the diagonals
    basex = 0;
    basey = (len-1);
    drawDiag( buffer, w, h, str, len, basex, basey );
    drawDiag( buffer, w, h, rev, len, basex+linew-1, basey );
    drawDiag( buffer, w, h, rev, len, basex, basey+lineh-1 );
    drawDiag( buffer, w, h, str, len, basex+linew-1, basey+lineh-1 );

    // draw the front square
    drawVer( buffer, w, h, str, len, basex, basey );
    drawVer( buffer, w, h, rev, len, basex+linew-1, basey );
    drawHor( buffer, w, h, str, len, basex, basey );
    drawHor( buffer, w, h, rev, len, basex, basey+lineh-1 );

    free( rev );
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
    int linew = (len-1)*2 + len;
    int w = linew + (len-1)*2 + 1;

    int lineh = (len-1) + len;
    int h = lineh + len;

    char * buffer = malloc( w * h );
    // put spaces everywhere
    for (int r = 0; r < h; ++r)
    {
        for (int c = 0; c < w; ++c)
        {
            buffer[r*w + c] = ' ';
        }
    }

    draw( buffer, w, h, str, len );

    // print it out
    for (int r = 0; r < h; ++r)
    {
        for (int c = 0; c < w; ++c)
        {
            putchar(buffer[r*w + c]);
        }
        putchar('\n');
    }

    free( buffer );
    if (mode == MODE_STDIN)
    {
        free( str);
    }
}
