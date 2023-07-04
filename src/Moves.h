#ifndef MOVES_H
#define MOVES_H

typedef struct Move MOVE;
typedef struct MoveEntry MENTRY;
typedef struct MoveList	MLIST;

struct Move
{
	int rank;
	int file;
};

struct MoveEntry
{
	MLIST *Mlist;
	MENTRY *Prev;
	MENTRY *Next;
	MOVE *Move;
};
struct MoveList
{
	MENTRY *First;
	MENTRY *Last;
	int Length;
};

MOVE *NewMove(int rank, int file);

void DeleteMove(MOVE *m);

/* Insert a RGB image to the image list at the end */
void AppendMove(MLIST *list, MOVE *newmove);

MLIST *NewList(void);

void DeleteList(MLIST *list);

MLIST *GenerateMoves(PIECE *board[8][8], int rank, int file);

void PawnMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file);

void KnightMoves(MLIST *MovementList,PIECE *board[8][8], int rank, int file);

void BishopMoves(MLIST *MovementList,PIECE *board[8][8], int rank, int file);

void RookMoves(MLIST *MovementList,PIECE *board[8][8], int rank, int file);

void QueenMoves(MLIST *MovementList,PIECE *board[8][8], int rank, int file);

void KingMoves(MLIST *MovementList,PIECE *board[8][8], int rank, int file);

void CheckHorizontalMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int direction, int isCheckingKing);

void CheckVerticalMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int direction, int isCheckingKing);

void CheckDiagonalMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int verticalDirection, int horizontalDirection, int isCheckingKing);

void CheckKnightMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int isCheckingKing);

int KingIsChecked(PIECE *board[8][8], int turn);

int goThroughLists(MLIST *ListOfThreats, PIECE *board[8][8], PIECE *Majesty, int Enemy1, int Enemy2);

int ValidateMove(MOVE *move, PIECE *board[8][8], int OriginalRank, int OriginalFile);
#endif
