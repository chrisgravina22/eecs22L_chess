#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "Constants.h"


#include "Piece.h"
PIECE *NewPiece(int color, int type)
{
    PIECE *output = malloc(sizeof(PIECE));
    output->hasMoved = 0;
    output->type = type;
    output->color = color;

    return output;
}

void DeletePiece(PIECE *p)
{
    free(p);
}


