#ifndef BOARD_H
#define BOARD_H


#include "Piece.h"

typedef struct Board BOARD;

struct board
{
    LOCATION *First;
    LOCATION *Last;
    int Length;
}



#endif
