#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "Constants.h"

#include "Piece.h"
#include "Moves.h"
//#include "Board.h"

char ColorToChar(PIECE *p);

char TypeToChar(PIECE *p);

int RankToInt(char rank);

int FileToInt(char file);

char IntToFile(int file);

void displayBoard(PIECE *board[8][8]);

int Mate(PIECE *board[8][8], int team);

// Menu Options
int print_menu(){
	int select = 0;
	printf("1. Start New Game (Human vs. AI) \n");
	printf("2. Start New Game (Human vs. Human) \n");
	printf("3. Game Settings \n");
	printf("4. Exit Game \n");
	printf("Choose Option: ");
	scanf("%d", &select);
	getchar(); 
	return select;
}

//player chooses their color
void choose_color (int *player){
	printf("Which color would you like to play as? \n");
	printf("Enter 0 for BLACK or 1 for WHITE: ");
	// prompts the user to choose either BLACK or WHITE
	// loops until they choose a proper color
	while (1) {
		int color;
		scanf("%d", &color);
		getchar();
		if (color == WHITE)
		{
			*player = color;
			printf("You chose WHITE.\n");
			break;
		}
		else if (color == BLACK)
		{	
			*player = color;
			printf("You chose BLACK.\n");
			break;
		}
		else {
			printf("You have entered an invalid color. Please try again\n");
		}			
	}
}

//settings for the game
void settings(int *player){
	while(1){
		int select = 0;
		printf("Settings Options... \n");
		printf("1. Change the player's color\n");
		printf("2. Exit settings \n");
		printf("Please enter the settings options: ");
		scanf("%d", &select);

		if (select == 1) {
			choose_color (player);
		}
		else if (select == 2) {
			break;
		}
		else {
			printf("Invalid Input. Please try again... \n");
		}
	}
	printf ("Settings changed! \n");
}


int main(void)
{
	srand(time(NULL));
	int player = 1; //initialize player to be WHITE
	printf("Welcome to JTDA's Chess \n");
	int option = print_menu();
	switch(option) {
		case 1:
			printf("You chose a Human vs. AI match! \n");
			break;
		case 2:
			printf("You chose a Human vs. Human match! \n");
			//HumanVsHuman();
			break;
		case 3:
			settings(&player);
			break;
		case 4:
			printf("Thanks for playing. Exiting the game...\n");
			exit(0);
			break;
	}	


   	PIECE *board[8][8];	// declare board of pointers to pieces

	// declare piece structs
	PIECE *bPawn1, *bPawn2, *bPawn3, *bPawn4, *bPawn5, *bPawn6, *bPawn7, *bPawn8;
	PIECE *wPawn1, *wPawn2, *wPawn3, *wPawn4, *wPawn5, *wPawn6, *wPawn7, *wPawn8;
	PIECE *bRook1, *bRook2, *bKnight1, *bKnight2, *bBishop1, *bBishop2, *bQueen, *bKing;
	PIECE *wRook1, *wRook2, *wKnight1, *wKnight2, *wBishop1, *wBishop2, *wQueen, *wKing;


	// create new pieces 
	bPawn1 = NewPiece(BLACK, PAWN);
	bPawn2 = NewPiece(BLACK, PAWN);
	bPawn3 = NewPiece(BLACK, PAWN);
	bPawn4 = NewPiece(BLACK, PAWN);
	bPawn5 = NewPiece(BLACK, PAWN);
	bPawn6 = NewPiece(BLACK, PAWN);
	bPawn7 = NewPiece(BLACK, PAWN);
	bPawn8 = NewPiece(BLACK, PAWN);

	wPawn1 = NewPiece(WHITE, PAWN);
	wPawn2 = NewPiece(WHITE, PAWN);
	wPawn3 = NewPiece(WHITE, PAWN);
	wPawn4 = NewPiece(WHITE, PAWN);
	wPawn5 = NewPiece(WHITE, PAWN);
	wPawn6 = NewPiece(WHITE, PAWN);
	wPawn7 = NewPiece(WHITE, PAWN);
	wPawn8 = NewPiece(WHITE, PAWN);

	bRook1 = NewPiece(BLACK, ROOK);
	bRook2 = NewPiece(BLACK, ROOK);
	bKnight1 = NewPiece(BLACK, KNIGHT);
	bKnight2 = NewPiece(BLACK, KNIGHT);
	bBishop1 = NewPiece(BLACK, BISHOP);
	bBishop2 = NewPiece(BLACK, BISHOP);
	bQueen = NewPiece(BLACK, QUEEN);
	bKing = NewPiece(BLACK, KING);

	wRook1 = NewPiece(WHITE, ROOK);
        wRook2 = NewPiece(WHITE, ROOK);
        wKnight1 = NewPiece(WHITE, KNIGHT);
        wKnight2 = NewPiece(WHITE, KNIGHT);
        wBishop1 = NewPiece(WHITE, BISHOP);
        wBishop2 = NewPiece(WHITE, BISHOP);
        wQueen = NewPiece(WHITE, QUEEN);
        wKing = NewPiece(WHITE, KING);

	// assing pointers to pieces to proper position on board
	board[0][0] = bRook1;
	board[0][1] = bKnight1;
	board[0][2] = bBishop1;
	board[0][3] = bQueen;
	board[0][4] = bKing;
	board[0][5] = bBishop2;
	board[0][6] = bKnight2;
	board[0][7] = bRook2;

	board[1][0] = bPawn1;
        board[1][1] = bPawn2;
        board[1][2] = bPawn3;
        board[1][3] = bPawn4;
        board[1][4] = bPawn5;
        board[1][5] = bPawn6;
        board[1][6] = bPawn7;
        board[1][7] = bPawn8;

	board[6][0] = wPawn1;
        board[6][1] = wPawn2;
        board[6][2] = wPawn3;
        board[6][3] = wPawn4;
        board[6][4] = wPawn5;
        board[6][5] = wPawn6;
        board[6][6] = wPawn7;
        board[6][7] = wPawn8;

	board[7][0] = wRook1;
        board[7][1] = wKnight1;
        board[7][2] = wBishop1;
        board[7][3] = wQueen;
        board[7][4] = wKing;
        board[7][5] = wBishop2;
        board[7][6] = wKnight2;
        board[7][7] = wRook2;

	// assign NULL to positions without pieces
	for(int rank = 2; rank < 6; rank++)
	{
		for(int file = 0; file < 8; file++)
		{
				board[rank][file] = NULL;
		}
	}

	int turn = 1;	// initializes a turn counter

	char rankStart, fileStart;
	int rankStartInt, fileStartInt;
	char rankFinal, fileFinal;
	int rankFinalInt, fileFinalInt;
	char userMoveStart[2];
	char userMoveFinal[2];
	
	// Creates and opens the logfile to record moves
	int moveCounter = 0;
	FILE *f;
	f = fopen("logfile.txt", "w+");
	fprintf(f, "Move    White    Black\n");
	
	int checkmate = 0;
	int promotionChoice = 0;
	int passantTurnW = 0;
	int passantTurnB = 0;

	while(checkmate != 1)
	{
		if( (player == BLACK && turn%2 == 0) || (player==WHITE && turn%2==1) )
		{
			displayBoard(board);

			MLIST *AvailableMoves;
			AvailableMoves = NewList();
			//while the user does not input a valid piece of their color, keep asking
			while(1)
			{
				if(player)
				{
					printf("WHITE: ");
				}else{
					printf("BLACK: ");
				}
				printf("Input the space of the piece you would like to move: ");
						scanf("%s", userMoveStart);
				getchar();
				
				//parsing the user input into ints
				sscanf(userMoveStart, "%c%c", &fileStart, &rankStart);
				rankStartInt = RankToInt(rankStart);
				fileStartInt = FileToInt(fileStart);

				//If the user has picked an empty space, loop again 
				if(!board[rankStartInt][fileStartInt])
				{

					printf("You must NOT move an empty space. Please choose a piece\n");	
					continue;
				}else if(player != board[rankStartInt][fileStartInt]->color)
				{
					printf("You must not choose a piece from the enemy team\n");
					continue;

				}
				
				AvailableMoves = GenerateMoves(board, rankStartInt, fileStartInt);
				//If the user has picked a piece that has no moves, loop
				if(AvailableMoves->Length <= 0)
				{
					printf("There are no available moves for this piece, please choose another one\n");	
					continue;
				}
				break;
							
			}

			int validMove = 0;
			printf("\nThere are %d moves possible for this piece:", AvailableMoves->Length);
			if(AvailableMoves->Length>0)
			{
				MENTRY *element = AvailableMoves->First;
				MENTRY *nextElement;
				assert(element);
				while(element)
				{
					nextElement = element->Next;
					printf("\n%c%d", IntToFile(element->Move->file), 8-element->Move->rank);
					element = nextElement;
				}

			}


			while(!validMove)
			{
				//we'll go through the piece's possible movements and check if the user inputted
				//a valid destination
				MENTRY *element = AvailableMoves->First;
				MENTRY *nextElement;
				assert(element);

				printf("\nInput the space you would like that piece to move to: ");
				scanf("%s", userMoveFinal);
				getchar();
				//parsing the user input into ranks and files
						sscanf(userMoveFinal, "%c%c", &fileFinal, &rankFinal);

						rankFinalInt = RankToInt(rankFinal);
						fileFinalInt = FileToInt(fileFinal);	
				//Loop while there are still possible movements to check or if a match is found	
				while(element)
				{
					nextElement = element->Next;	
					//if the user input matches any of the valid destinations
					if(element->Move->rank == rankFinalInt && element->Move->file == fileFinalInt)
					{
						validMove = 1;

						//checks if en passant has happened
						if(board[rankFinalInt][fileFinalInt])
						{
							if(board[rankFinalInt][fileFinalInt]->type == TEMP_PAWN)
							{
								if(player == WHITE)
								{
									DeletePiece(board[rankFinalInt + 1][fileFinalInt]);
									board[rankFinalInt + 1][fileFinalInt] = NULL;
								}
								else if(player == BLACK)
								{
									DeletePiece(board[rankFinalInt - 1][fileFinalInt]);
									board[rankFinalInt - 1][fileFinalInt] = NULL;
								}
							}
						}
						
						// free capture piece from memory
						if(board[rankFinalInt][fileFinalInt])
						{
							DeletePiece(board[rankFinalInt][fileFinalInt]);
						}

						//mopve the piece
						board[rankFinalInt][fileFinalInt] = board[rankStartInt][fileStartInt];
						board[rankStartInt][fileStartInt] = NULL;
						//logging of movement
						fprintf(f, "%s \n", userMoveFinal);
						fprintf(f, " %d", moveCounter);
						fprintf(f, "                %s", userMoveStart);
						moveCounter += 1;
						turn++;

						// Promotion of Pawn
						if(board[rankFinalInt][fileFinalInt]->type == PAWN)
						{
							// Checks if pawn has moved to opposite end of board
							if((player == BLACK && rankFinalInt == 7) || (player == WHITE && rankFinalInt == 0))
							{
								// loops until valid selection
								while(promotionChoice != 1 && promotionChoice != 2 && promotionChoice != 3 && promotionChoice != 4)
								{
									printf("Which piece would you like to promote your pawn to?\n");
									printf("Press 1 for Queen, 2 for Rook, 3 for Knight, or 4 for Bishop: ");
									scanf("%d", &promotionChoice);			
									if(promotionChoice > 4 || promotionChoice < 0)
									{
										printf("That was not a valid selection! Try again\n");
									}
								}
								printf("Your pawn has been promoted!\n");

								// promotes pawn to specified piece type
								if(promotionChoice == 1)
								{
									board[rankFinalInt][fileFinalInt]->type = QUEEN;
								}
								else if(promotionChoice == 2)
								{
									board[rankFinalInt][fileFinalInt]->type = ROOK;
								}
								else if(promotionChoice == 3)
								{
									board[rankFinalInt][fileFinalInt]->type = KNIGHT;
								}
								else if(promotionChoice == 4)
								{
									board[rankFinalInt][fileFinalInt]->type = BISHOP;
								}

								// resets choice for next time a pawn is promoted
								promotionChoice = 0;
							}
						}

						// Castling
						if(board[rankFinalInt][fileFinalInt]->type == KING && board[rankFinalInt][fileFinalInt]->hasMoved == 0)
						{
							if(fileFinalInt == 6)
							{
								board[rankFinalInt][5] = board[rankFinalInt][7];
								board[rankFinalInt][7] = NULL;
							}
							else if(fileFinalInt == 2)
							{
								board[rankFinalInt][3] = board[rankFinalInt][0];
								board[rankFinalInt][0] = NULL;
							}
						}


						// removes temporary piece created by en passant
						if(passantTurnW == 1 && player == WHITE)
						{
							for(int i = 0; i < 8; i++)
							{
								if(board[5][i])
								{
									if(board[5][i]->type == TEMP_PAWN)
									{
										DeletePiece(board[5][i]);
										board[5][i] = NULL;
									}
								}
							}
							
							passantTurnW = 0;
						}
						else if(passantTurnB == 1 && player == BLACK)
						{
							for(int i = 0; i < 8; i++)
							{
								if(board[2][i])
								{
									if(board[2][i]->type == TEMP_PAWN)
									{
										DeletePiece(board[2][i]);
										board[2][i] = NULL;
									}
								}
							}
							
							passantTurnB = 0;
						}

						// En Passant
						if(board[rankFinalInt][fileFinalInt]->type == PAWN)
						{
							if(player == BLACK && rankFinalInt == rankStartInt + 2)
							{
								PIECE *tempPawn;
								tempPawn = NewPiece(BLACK, TEMP_PAWN);
								board[rankStartInt + 1][fileStartInt] = tempPawn;
								passantTurnB = 1;
							}
							else if(player == WHITE && rankFinalInt == rankStartInt - 2)
							{
								PIECE *tempPawn;
								tempPawn = NewPiece(WHITE, TEMP_PAWN);
								board[rankStartInt - 1][fileStartInt] = tempPawn;
								passantTurnW = 1;
							}
						}

						board[rankFinalInt][fileFinalInt]->hasMoved = 1;

						break;
					}
					element = nextElement;						
				}
				if(!validMove)
				{
					printf("\nInvalid move, please insert another destination\n");
				}
			}

			DeleteList(AvailableMoves);
			//Add logging of movements
		}
		else 
		{
			printf("Computer Move!\n");
			int color = !player;
			MLIST *AvailableMoves = NewList();
			MOVE *ComputerMove;
			MLIST *ComputerPieces = NewList();
			for(int y =  0; y<8; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					if(board[y][x] && board[y][x]->color == color)
					{
						ComputerMove = NewMove(y, x);
						AppendMove(ComputerPieces, ComputerMove);
					}
					
				}
			}
			int random = 0;
			int rank = 0;
			int file = 0;
			int finalRank = 0;
			int finalFile = 0;
			int counter = 0;
			MENTRY *element;
			MENTRY *nextElement;
			while(AvailableMoves->Length == 0){
				random = rand()%ComputerPieces->Length;
				element = ComputerPieces->First;
				while(element)
				{
					nextElement = element->Next;
					if(counter == random)
					{
						file = element->Move->file;	
						rank = element->Move->rank;
					}
					counter++;
					element = nextElement;
				}
				counter = 0;
				AvailableMoves = GenerateMoves(board, rank, file);
			}
			random = rand()%AvailableMoves->Length;
			element = AvailableMoves->First;
			while(element)
			{
				nextElement = element->Next;
				if(counter == random)
				{
					finalFile = element->Move->file;	
					finalRank= element->Move->rank;
				}
				counter++;
				element = nextElement;
			}

			//checks if en passant has happened
			if(board[finalRank][finalFile])
			{
				if(board[rankFinalInt][fileFinalInt]->type == TEMP_PAWN)
				{
					if(color == WHITE)
					{
						DeletePiece(board[finalRank + 1][finalFile]);
						board[finalRank + 1][finalFile] = NULL;
					}
					else if(color == BLACK)
					{
						DeletePiece(board[finalRank - 1][finalFile]);
						board[finalRank - 1][finalFile] = NULL;
					}
				}
			}
						
			// free capture piece from memory
			if(board[finalRank][finalFile])
			{
				DeletePiece(board[finalRank][finalFile]);
			}

			board[finalRank][finalFile] = board[rank][file];
			board[rank][file] = NULL;

			// Promotion of Pawn
			if(board[finalRank][finalFile]->type == PAWN)
			{
				// Checks if pawn has moved to opposite end of board
				if((color == BLACK && finalRank == 7) || (color == WHITE && finalRank == 0))
				{
					// promotes pawn to queen
					board[finalRank][finalFile]->type = QUEEN;
					printf("The computer's PAWN has been promoted to a QUEEN!\n");
				}
			}

			// Castling
			if(board[finalRank][finalFile]->type == KING && board[finalRank][finalFile]->hasMoved == 0)
			{
				if(finalFile == 6)
				{
					board[finalRank][5] = board[finalRank][7];
					board[finalRank][7] = NULL;
				}
				else if(finalFile == 2)
				{
					board[finalRank][3] = board[finalRank][0];
					board[finalRank][0] = NULL;
				}
			}


			// removes temporary piece created by en passant
			if(passantTurnW == 1 && color == WHITE)
			{
				for(int i = 0; i < 8; i++)
				{
					if(board[5][i])
					{
						if(board[5][i]->type == TEMP_PAWN)
						{
							DeletePiece(board[5][i]);
							board[5][i] = NULL;
						}
					}
				}
							
				passantTurnW = 0;
			}
			else if(passantTurnB == 1 && color == BLACK)
			{
				for(int i = 0; i < 8; i++)
				{
					if(board[2][i])
					{
						if(board[2][i]->type == TEMP_PAWN)
						{
							DeletePiece(board[2][i]);
							board[2][i] = NULL;
						}
					}
				}
							
				passantTurnB = 0;
			}

			// En Passant
			if(board[finalRank][finalFile]->type == PAWN)
			{
				if(color == BLACK && finalRank == rank + 2)
				{
					PIECE *tempPawn;
					tempPawn = NewPiece(BLACK, TEMP_PAWN);
					board[rank + 1][file] = tempPawn;
					passantTurnB = 1;
				}
				else if(color == WHITE && finalRank == rank - 2)
				{
					PIECE *tempPawn;
					tempPawn = NewPiece(WHITE, TEMP_PAWN);
					board[rank - 1][file] = tempPawn;
					passantTurnW = 1;
				}
			}

			board[finalRank][finalFile]->hasMoved = 1;

			turn++;
			DeleteList(AvailableMoves);
			DeleteList(ComputerPieces);
			
		}
		
		if(Mate(board, WHITE))
		{
			printf("GAME OVER, BLACK WINS!");
			checkmate = 1;
		}
		if(Mate(board, BLACK))
		{
			printf("GAME OVER, WHITE WINS!");
			checkmate = 1;
		}
		
	}
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j])
			{
				DeletePiece(board[i][j]);
			}
		}
	}
}
int Mate(PIECE *board[8][8], int team)
{
	int output = 1;
	MOVE *piece;
	MLIST *pieces = NewList();
	for(int y =  0; y<8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if(board[y][x] && board[y][x]->color == team)
			{
				piece = NewMove(y, x);
				AppendMove(pieces, piece);
			}
			
		}
	}
	MENTRY *entry;
	MENTRY *nextEntry;
	MLIST *possibleMoves = NewList();
	entry = pieces->First;
	while (entry)
	{
		nextEntry = entry->Next;
		possibleMoves = GenerateMoves(board, entry->Move->rank, entry->Move->file);
		if(possibleMoves->Length > 0)
		{
			return 0;
		}
		entry = nextEntry;
	}
	return output;
}
// converts an int color of a piece to a letter representing that color
char ColorToChar(PIECE *p)
{
	if(p)
	{
		if(p->color == 0 && p->type != TEMP_PAWN)
		{
			return 'b';
		}
		else if(p->color == 1 && p->type != TEMP_PAWN)
		{
			return 'w';
		}
		else
		{
			return ' ';
		}
	}
	else
	{
		return ' ';
	}
}


// converts an int type of a piece to a char representing that type
char TypeToChar(PIECE *p)
{
	if(p)
	{
		if(p->type == 0)
		{
			return 'P';
		}
		else if(p->type == 1)
		{
			return 'N';
		}
		else if(p->type == 2)
		{
			return 'B';
		}
		else if(p->type == 3)
		{
			return 'R';
		}
		else if(p->type == 4)
		{
			return 'Q';
		}
		else if(p->type == 5)
		{
			return 'K';
		}
		else
		{
			return ' ';
		}
	}
	else
	{
		return ' ';
	}
}

// converts a char file to an int for the index of the board
int FileToInt(char file)
{
	if(file == 'a')
	{
		return 0;
	}
	else if(file == 'b')
	{
		return 1;
	}
	else if(file == 'c')
	{
		return 2;
	}
	else if(file == 'd')
	{
		return 3;
	}
	else if(file == 'e')
	{
		return 4;
	}
	else if(file == 'f')
	{
		return 5;
	}
	else if(file == 'g')
	{
		return 6;
	}
	else if(file == 'h')
	{
		return 7;
	}
	else
	{
		return 10;
	}
}

// converts a char rank to an int for the index of the board
int RankToInt(char rank)
{
	if(rank == '8')
        {
                return 0;
        }
        else if(rank == '7')
        {
                return 1;
        }
        else if(rank == '6')
        {
                return 2;
        }
        else if(rank == '5')
        {
                return 3;
        }
        else if(rank == '4')
        {
                return 4;
        }
        else if(rank == '3')
        {
                return 5;
	}
	else if(rank == '2')
	{
		return 6;
	}
	else if(rank == '1')
	{
		return 7;
	}
	else
	{
		return 10;
	}
}

void displayBoard(PIECE *board[8][8]){
	// displays the board in an ASCII representation
	printf("\n  +----+----+----+----+----+----+----+----+\n");
	for(int i =0; i < 8; i++)
	{
		printf("%d ", 8-i);
		for(int j = 0; j <= 7; j++)
		{
			printf("| %c%c ", 		ColorToChar(board[i][j]), TypeToChar(board[i][j]));
		}
		printf("|\n  +----+----+----+----+----+----+----+----+\n");
		
	}
	printf("    a    b    c    d    e    f    g    h    \n");

}

char IntToFile(int file)
{
	return 97+file;
}
void MovePiece();
