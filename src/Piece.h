#ifndef PIECE_H
#define PIECE_H

typedef struct Piece PIECE;
typedef struct Location LOCATION;

struct Piece
{
    int color;
    int type;
    int hasMoved;
};

PIECE *NewPiece(int color, int type);

void DeletePiece(PIECE *p);

#endif
