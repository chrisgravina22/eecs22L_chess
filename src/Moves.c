#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "Constants.h"

#include "Piece.h"
#include "Moves.h"


MOVE *NewMove(int rank, int file)
{
	MOVE *move = malloc(sizeof(MOVE));
	move->rank = rank;
	move->file = file;
	
	return move; 
}

void DeleteMove(MOVE *move)
{
	free(move);
}

/* Insert a move to the move list at the end */
void AppendMove(MLIST *list, MOVE *newMove)
{
	assert(list);
	MENTRY *newEntry;
	newEntry = malloc(sizeof(MENTRY));
	if(!newEntry)
	{
		//perror("Out of memory! Aborting...");
		exit(10);
	}
	newEntry->Mlist = list;
	newEntry->Prev = list->Last;
	newEntry->Next = NULL;
	newEntry->Move = newMove;
	if(list->Length>0){
		list->Last->Next = newEntry;
	}else{
		list->First = newEntry;
	}
	list->Length++;
	list->Last = newEntry;

}
MLIST *NewList(void)
{
	MLIST *l;
	l = malloc(sizeof(MLIST));
	assert(l);
	if (!l)
	{ 
		//perror("Out of memory! Aborting...");
		exit(10);
	}
	l->Length = 0;
	l->First = NULL;
	l->Last = NULL;

	return l;
}

void DeleteList(MLIST *list)
{
	MENTRY *element, *nextElement;

	assert(list);
	
	if(list->Length == 0)
	{
		free(list);
		return;
	}
	assert(element = list->First);	
	while(element)
	{
		nextElement = element->Next;
		DeleteMove(element->Move);
		free(element);
		element = nextElement;
	}
	free(list);
}
//Returns a list of possible movements for piece at board[rank][file]
MLIST *GenerateMoves(PIECE *board[8][8], int rank, int file)
{
	MLIST *output = NewList();
	switch(board[rank][file]->type)
	{
		case PAWN:
			PawnMoves(output, board, rank, file);
			break;
		case KNIGHT:
			KnightMoves(output, board, rank, file);
			break;
		case BISHOP:
			BishopMoves(output, board, rank, file);
			break;
		case ROOK:
			RookMoves(output, board, rank, file);
			break;
		case QUEEN:
			QueenMoves(output, board, rank, file);
			break;
		case KING:
			KingMoves(output, board, rank, file);
			break;
		
		default:
			return NULL;
	}
	return output;
}

void PawnMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file)
{
	//If it's black, pawn will move down only. If white, up only
	int direction = (board[rank][file]->color == WHITE) ? -1 : 1;
	//printf("%d, %d", rank, file);
	if (!board[rank+direction][file])
	{
		// printf("\nPawn:\n%d\n", direction);
		// printf("%d, %d", rank, file);
		MOVE *once = NewMove(rank+direction, file);
		if(ValidateMove(once, board, rank, file))
		{
			AppendMove(MovementList, once);
		}
		if(!board[rank+2*direction][file] && !board[rank][file]->hasMoved)
		{
			MOVE *twice = NewMove(rank+2*direction, file);
			if(ValidateMove(twice, board, rank, file))
			{
				AppendMove(MovementList, twice);
			}
		}
	}
	//Pawn capture - see's if there is a piece in the diagonals in front of them and, if so, if it's an enemy
	if(file+1 <=7 && board[rank+direction][file+1] && board[rank+direction][file+1]->color != board[rank][file]->color)
	{
		MOVE *capture = NewMove(rank+direction, file+1);
		if(ValidateMove(capture, board, rank, file))
		{
			AppendMove(MovementList, capture);
		}
	}
	if(file-1 >= 0 && board[rank+direction][file-1] && board[rank+direction][file-1]->color != board[rank][file]->color)
	{
		MOVE *capture = NewMove(rank+direction, file-1);
		if(ValidateMove(capture, board, rank, file))
		{
			AppendMove(MovementList, capture);
		}
		
	}
}

void KnightMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file)
{
	CheckKnightMoves(MovementList, board, rank, file, 0);
}
void BishopMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file)
{
	//check south east
	CheckDiagonalMoves(MovementList, board, rank, file, 1, 1, 0);
	
	//check south west
	CheckDiagonalMoves(MovementList, board, rank, file, 1, -1, 0);
	
	//check north east
	CheckDiagonalMoves(MovementList, board, rank, file, -1, 1, 0);
	
	//check nort west
	CheckDiagonalMoves(MovementList, board, rank, file, -1, -1, 0);

}
void RookMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file)
{
	//check moves upwards
	CheckVerticalMoves(MovementList, board, rank, file, -1, 0);

	//check moves downwards
	CheckVerticalMoves(MovementList, board, rank, file, 1, 0);
	
	//check moves to the left
	CheckHorizontalMoves(MovementList, board, rank, file, -1, 0);

	//check moves to the right
	CheckHorizontalMoves(MovementList, board, rank, file, 1, 0);
	

}
void QueenMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file)
{
	//check moves upwards
	CheckVerticalMoves(MovementList, board, rank, file, -1, 0);

	//check moves downwards
	CheckVerticalMoves(MovementList, board, rank, file, 1, 0);
	
	//check moves to the left
	CheckHorizontalMoves(MovementList, board, rank, file, -1, 0);

	//check moves to the right
	CheckHorizontalMoves(MovementList, board, rank, file, 1, 0);

	//check south east
	CheckDiagonalMoves(MovementList, board, rank, file, 1, 1, 0);
	
	//check south west
	CheckDiagonalMoves(MovementList, board, rank, file, 1, -1, 0);
	
	//check north east
	CheckDiagonalMoves(MovementList, board, rank, file, -1, 1, 0);
	
	//check nort west
	CheckDiagonalMoves(MovementList, board, rank, file, -1, -1, 0);

}
void KingMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file)
{
	//Rules for castling
	MOVE *move;
	
	MLIST *toTheRight = NewList(); 
	//If this list is 3 spaces long, it means that the spots between the king
	//and the right-most tower are clear
	CheckHorizontalMoves(toTheRight, board, rank, file, 1, 0);
	//If the list is of appropriate size and neither the king or the rook move, then add castling to 
	//this side as an option
	if(board[rank][7] && !board[rank][file]->hasMoved && !board[rank][7]->hasMoved && toTheRight->Length == 2)
	{
		move = NewMove(rank, 6);
		AppendMove(MovementList, move);
	}
	//Checking to the Left of the king
	MLIST *toTheLeft = NewList();
	CheckHorizontalMoves(toTheLeft, board, rank, file, -1, 0);
	if(board[rank][0] && !board[rank][file]->hasMoved && !board[rank][0]->hasMoved && toTheLeft->Length == 3)
	{
		move = NewMove(rank, 2);
		AppendMove(MovementList, move);
	}
	DeleteList(toTheLeft);
	DeleteList(toTheRight);
	
	//these two arrays contain the cordinates for the possible new locations
	//of the king and will be used in pairs. Ex.: x[1], y[1] mean the NE location from the king 
	
	int x[8] = {0, 1, 1, 1, 0, -1, -1, -1 };
	int y[8] = {1, 1, 0, -1, -1, -1, 0, 1};
	for(int i = 0; i < 8; i++)
	{
		if(file + x[i] <=7 && file + x[i] >=0 && rank + y[i] <=7 && rank + y[i]>=0)
		{
			
			if(!board[rank+y[i]][file+x[i]] || board[rank+y[i]][file+x[i]]->color != board[rank][file]->color)
			{
				move = NewMove(rank+y[i], file+x[i]);
				if(ValidateMove(move, board, rank, file))
				{
					AppendMove(MovementList, move);
				}		
			}
		}

	}
}
//Checking vertical moves of the piece at board[rank][file]
//at a direction (UP = -1 | DOWN = 1). Update's the provided MLIST with the 
//possible moves for the piece at the direction
void CheckVerticalMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int direction, int isCheckingKing)
{
	//a counter to keep track of whick spot we are checking
	int counter = 0;
	counter+=direction; //adding to it so that the player can't the piece to the place it's already in
	MOVE *move;
	//loop through the empty spaces and adding them to the list of possible moves
	//it will stop as soon as it finds a non-empty spot or hits the edge of the board
	while(rank+counter <=7 && rank+counter>=0 && !board[rank+counter][file] ) 
	{
		move = NewMove(rank+counter, file);
		if(isCheckingKing)
		{
			AppendMove(MovementList, move);
		}else if(ValidateMove(move, board, rank, file))
		{
			AppendMove(MovementList, move);
		}	
		counter+=direction;
	}
	//resetting the counter into the board in case we hit the edge of the board
	if(rank+counter == 8 || rank+counter == -1)
	{
		counter-=direction;
	}
	//now checking that we have a piece at the spot we stopped at
	if(board[rank+counter][file] && board[rank][file])
	{
		//if there is a piece, check if the player can kill the piece or not. If so, add it to the list of possible moves
		if(board[rank+counter][file]->color != board[rank][file]->color)
		{
			move = NewMove(rank+counter, file);
			if(isCheckingKing)
			{
				AppendMove(MovementList, move);
			}else if(ValidateMove(move, board, rank, file))
			{
				AppendMove(MovementList, move);
			}
		}
	}else if(board[rank+counter][file] && !board[rank][file])
	{
			move = NewMove(rank+counter, file);
			if(isCheckingKing)
			{
				AppendMove(MovementList, move);
			}else if(ValidateMove(move, board, rank, file))
			{
				AppendMove(MovementList, move);
			}
	}
}

//Checking horizontal moves of the piece at board[rank][file]
//at a direction (LEFT = -1 | RIGHT = 1). Update's the provided MLIST with the 
//possible moves for the piece at the direction
void CheckHorizontalMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int direction, int isCheckingKing)
{
	int counter = 0;
	counter+=direction;
	MOVE *move;
	while(!board[rank][file+counter] && file+counter<8 && file+counter>=0) 
	{
		move = NewMove(rank, file+counter);
		if(isCheckingKing)
		{
			AppendMove(MovementList, move);
		}else if(ValidateMove(move, board, rank, file))
		{
			AppendMove(MovementList, move);
		}		
		counter+=direction;
	}
	
	if(file+counter == 8 || file+counter == -1)
	{
		counter-=direction;
	}
	if(board[rank][file+counter] && board[rank][file])
	{
		if(board[rank][file+counter]->color != board[rank][file]->color)
		{
			move = NewMove(rank, file+counter);
			if(isCheckingKing)
			{
				AppendMove(MovementList, move);
			}else if(ValidateMove(move, board, rank, file))
			{
				AppendMove(MovementList, move);
			}
		}
	}else if(board[rank][file+counter] && !board[rank][file] && board[rank][file+counter]->type != KING)
	{
			move = NewMove(rank, file+counter);
			if(isCheckingKing)
			{
				AppendMove(MovementList, move);
			}else if(ValidateMove(move, board, rank, file))
			{
				AppendMove(MovementList, move);
			}
	}
	
}

//Checks diagonal moves of piece at board[rank][file] until it hits the wall or another piece
//VERTICAL DIRECTION: (UP = -1 | DOWN = 1)
//HORIZONTAL DIRECTION: (LEFT = -1 | RIGHT = 1)
//Example, 1,1 = SE search
//Adds possible movements to provided MovementList
void CheckDiagonalMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int verticalDirection, int horizontalDirection, int isCheckingKing)
{
	int horizontalCounter = 0;
	int verticalCounter = 0;

	verticalCounter += verticalDirection;
	horizontalCounter += horizontalDirection;
	MOVE *move;
	while(!board[rank+verticalCounter][file+horizontalCounter] && (file+horizontalCounter<=7 && file+horizontalCounter>=0 && rank+verticalCounter<=7 && rank+verticalCounter>=0)) 
	{
		move = NewMove(rank+verticalCounter, file+horizontalCounter);
		if(isCheckingKing)
		{
			AppendMove(MovementList, move);
		}else if(ValidateMove(move, board, rank, file))
		{
			AppendMove(MovementList, move);
		}	
		verticalCounter += verticalDirection;
		horizontalCounter += horizontalDirection;
	}
	//if it hit a border and went past it, come back
	if(file+horizontalCounter == 8 || file+horizontalCounter == -1 )
	{
		verticalCounter -= verticalDirection;
		horizontalCounter-=horizontalDirection;
	}
	if(rank+verticalCounter == 8 || rank+verticalCounter == -1 )
	{
		horizontalCounter-=horizontalDirection;
		verticalCounter -= verticalDirection;
	}
	if(board[rank+verticalCounter][file+horizontalCounter] && board[rank][file])
	{
		if(board[rank+verticalCounter][file+horizontalCounter]->color != board[rank][file]->color)
		{
			move = NewMove(rank+verticalCounter, file+horizontalCounter);
			if(isCheckingKing)
			{
				AppendMove(MovementList, move);
			}else if(ValidateMove(move, board, rank, file))
			{
				AppendMove(MovementList, move);
			}
		}
	//only used to see if the king is checked	
	}else if(board[rank+verticalCounter][file+horizontalCounter] && !board[rank][file])
	{
			move = NewMove(rank+verticalCounter, file+horizontalCounter);
			if(isCheckingKing)
			{
				AppendMove(MovementList, move);
			}else if(ValidateMove(move, board, rank, file))
			{
				AppendMove(MovementList, move);
			}
	}
	
}

//Checks all possible movements for a knight at position board[rank][file]
//Adds possible movements to provided MovementList
void CheckKnightMoves(MLIST *MovementList, PIECE *board[8][8], int rank, int file, int isCheckingKing)
{
	int y[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
    int x[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };
	MOVE *move;
	for(int i = 0; i <  8; i++)
	{
		if(file + x[i] < 8 && file + x[i] >=0 && rank + y[i] <8 && rank + y[i]>=0)
		{
			if(!board[rank+y[i]][file+x[i]] || board[rank+y[i]][file+x[i]]->color != board[rank][file]->color)
			{
				move = NewMove(rank+y[i], file+x[i]);
				if(isCheckingKing)
				{
					AppendMove(MovementList, move);
				}else if(ValidateMove(move, board, rank, file))
				{
					AppendMove(MovementList, move);
				}
			}

		}
	}
}
int ValidateMove(MOVE *move, PIECE *board[8][8], int OriginalRank, int OriginalFile)
{
	PIECE *TemporaryStorage = board[move->rank][move->file];
	int turn = board[OriginalRank][OriginalFile]->color;
	board[move->rank][move->file] = board[OriginalRank][OriginalFile];
	board[OriginalRank][OriginalFile] = NULL;

	int output = KingIsChecked(board, turn);

	board[OriginalRank][OriginalFile] = board[move->rank][move->file];
	board[move->rank][move->file] = TemporaryStorage;
	return !output;
} 


//Returns 1 if the turn player's king is Checked
int KingIsChecked(PIECE *board[8][8], int turn)
{
	PIECE	*Majesty;
	//find the king of the player's turn
	int rank = 0;
	int file = 0;
	for(int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if(!board[y][x])
			{
				continue;
			}
			if(board[y][x]->color == turn && board[y][x]->type == KING)
			{
				rank = y;
				file = x;
			}
		}
	}
	int isChecked = 0;

	MLIST *VerticalThreats = NewList();
	MLIST *HorizontalThreats = NewList();
	MLIST *DiagonalThreats = NewList();
	MLIST *KnightsThreats = NewList();
	
	CheckVerticalMoves(VerticalThreats, board, rank, file, 1, 1);
	CheckVerticalMoves(VerticalThreats, board, rank, file, -1, 1);
	
	CheckHorizontalMoves(HorizontalThreats, board, rank, file, 1, 1);
	CheckHorizontalMoves(HorizontalThreats, board, rank, file, -1, 1);
	
	CheckDiagonalMoves(DiagonalThreats, board, rank, file, 1, 1, 1);
	CheckDiagonalMoves(DiagonalThreats, board, rank, file, 1, -1, 1);
	CheckDiagonalMoves(DiagonalThreats, board, rank, file, -1, 1, 1);
	CheckDiagonalMoves(DiagonalThreats, board, rank, file, -1, -1, 1);
	
	CheckKnightMoves(KnightsThreats, board, rank, file, 1);
	Majesty = board[rank][file];
	
	isChecked = goThroughLists(VerticalThreats, board, Majesty, QUEEN, ROOK);
	if(isChecked)
	{
		return isChecked;
	}
	isChecked = goThroughLists(HorizontalThreats, board, Majesty, QUEEN, ROOK);
	if(isChecked)
	{
		return isChecked;
	}
	isChecked = goThroughLists(DiagonalThreats, board, Majesty, QUEEN, BISHOP);
	if(isChecked)
	{
		return isChecked;
	}
	isChecked = goThroughLists(KnightsThreats, board, Majesty, KNIGHT, KNIGHT);
	if(isChecked)
	{
		return isChecked;
	}
	//If it's black, pawn will move down only. If white, up only
	int direction = (Majesty->color == BLACK) ? 1 : -1;
	if(rank+direction < 8 && file+1 <8)
	{
		if(board[rank+direction][file+1] && board[rank+direction][file+1]->color != Majesty->color && board[rank+direction][file+1]->type == PAWN) 
		{
			return 1;
		}
	}
	if(rank+direction < 8 && file+1 <8)
	{
		if(board[rank+direction][file-1] && board[rank+direction][file-1]->color != Majesty->color && board[rank+direction][file-1]->type == PAWN) 
		{
			return 1;
		}
	}
	
	return isChecked;
	
}

int goThroughLists(MLIST *ListOfThreats, PIECE *board[8][8], PIECE *Majesty, int Enemy1, int Enemy2)
{
	MENTRY *entry;
	MENTRY *nextEntry;
	int isChecked;
	if(ListOfThreats->Length>0)
	{
		entry = ListOfThreats->First;
		assert(entry);
		while(entry)
		{
			nextEntry = entry->Next;
			if(board[entry->Move->rank][entry->Move->file])
			{
				if( (board[entry->Move->rank][entry->Move->file]->color != Majesty->color && (board[entry->Move->rank][entry->Move->file]->type == Enemy1 || board[entry->Move->rank][entry->Move->file]->type == Enemy2) ))
				{
					isChecked = 1;
				}
			}
			entry = nextEntry;
		}
	}
	return isChecked;
}