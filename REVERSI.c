
/************************************************************* Project REVERSI ***********************************************************************/
/*************************************************************  Anton Iosifov  ***********************************************************************/
/*************************************************************  ID: 336490347  ***********************************************************************/
                                                         
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define SIZE 25    /* Max Board size is 20 */

void menu();                                    
char startBoard(char arr[SIZE][SIZE], int size);
void printBoard(char arr[SIZE][SIZE], int size);
void proccessOfGame(char arr[SIZE][SIZE], int size);
bool checkLegalMove(char arr[SIZE][SIZE], int size, int row, int col, char);
void scoring(char arr[SIZE][SIZE], int size, char string1[SIZE], char string2[SIZE]);
int countOfValidMoves(char arr[SIZE][SIZE], int size, char);
bool checkCountOfLegalMove(char arr[SIZE][SIZE], int size, int row, int col, char ch);

void main()
{
	menu();
}

/* Function prints the menu, accepts the selection */
/* from the user and starts the game process.      */
void menu()   
{
	int choice;
	int size;

	char board[SIZE][SIZE] = { 0 };

	printf("Select board size: \n");
	printf("0. Exit \n");
	printf("1. 5x5: \n");
	printf("2. 15x15 \n");
	printf("3. 20x20 \n");

	scanf("%d", &choice);

	if (choice == 0)       /* EXIT */
	{
		return;
	}
	else if (choice == 1)  /* Board 5x5 */
	{
		size = 5;
		board[size][size] = startBoard(board, size);
		proccessOfGame(board, 5);
	}
	else if (choice == 2)  /* Board 15x15 */
	{
		size = 15;
		board[size][size] = startBoard(board, size);
		proccessOfGame(board, 15);
	}
	else if (choice == 3)  /* Board 20x20 */
	{
		size = 20;
		board[size][size] = startBoard(board, size);
		proccessOfGame(board, 20);
	}
	else
	{
		printf("Invalid option. \n");
		menu();
	}
}

/********************************************** Function fills with symbols a board  of the size **********************************************/
/**********************************************   chosen by the user. And puts the initial       **********************************************/
/**********************************************        symbols in the central cells.             **********************************************/
char startBoard(char arr[SIZE][SIZE], int size)      
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			arr[i][j] = '_';
		}
	}

	arr[(size / 2) - 1][(size / 2) - 1] =  'X';
	arr[(size / 2) - 1][size / 2] =  'O';
	arr[size / 2][size / 2] = 'X';
	arr[size / 2][(size / 2) - 1] = 'O';

	return arr;
}


/********************************************** Function prints the initial finished matrix,  **********************************************/
/**********************************************   and then prints each time with changes.     **********************************************/
void printBoard(char arr[SIZE][SIZE], int size)
{
	int i, j;
	int num = 1;
	
	printf("    ");

	for (i = 0; i < size; i++)
	{
		printf("%2d ", i+1);
	}
	printf("\n");

	for (i = 0; i < size; i++)
	{
		printf("%2d  ", num);

		for (j = 0; j < size; j++)
		{
			printf(" %c ", arr[i][j]);
		}

		num++;
		printf("\n");
	}
}

/**********************************************               PROCCESS of the GAME               **********************************************/
/**********************************************   Function will get the names of the players,    **********************************************/
/**********************************************        show the display for the game,            **********************************************/
/**********************************************         get the moves from the players,          **********************************************/
/**********************************************        and check the order of the moves.         **********************************************/

void proccessOfGame(char arr[SIZE][SIZE], int size)
{
	int row;
	int col;
	int step = 0;
	char namePlayer1[SIZE] = { 0 };
	char namePlayer2[SIZE] = { 0 };
	
	printf("Enter first player name: ");
	scanf("%s", namePlayer1);
	printf("Enter second player name : ");
	scanf("%s", namePlayer2);
	printf("\n");
	
	printBoard(arr, size);
	printf("\n");

	while (step < size * size - 4)
	{
		if (countOfValidMoves(arr, size, 'O') == 0 && countOfValidMoves(arr, size, 'X') == 0)
		{
			break;
		}
		if (step % 2 == 0)
		{
			printf("Player %s (X) turn \n", namePlayer1);
		}
		else
		{
			printf("Player %s (O) turn \n", namePlayer2);
		}
	
		if (step % 2 == 0)
		{
			if (countOfValidMoves(arr, size, 'X') == 0)
			{
				printf("Player %s (X) has no valid moves. \n", namePlayer1);
				step++;
			}
			else
			{
				printf("Enter your move (row + column): ");
				scanf("%d %d", &row, &col);

				if (checkLegalMove(arr, size, row - 1, col - 1, 'X') == true)
				{
					arr[row - 1][col - 1] = 'X';
					printBoard(arr, size);
					printf("\n");
					step++;
				}
				else
				{
					printf("Invalid move.\n");
				}
			}
		}
		else if (step % 2 != 0)
		{   
			if (countOfValidMoves(arr, size, 'O') == 0)
			{
				printf("Player %s (O) has no valid moves. \n", namePlayer2);
				step++;
			}
			else
			{
				printf("Enter your move (row + column): ");
				scanf("%d %d", &row, &col);

				if (checkLegalMove(arr, size, row - 1, col - 1, 'O') == true)
				{
					arr[row - 1][col - 1] = 'O';
					printBoard(arr, size);
					printf("\n");
					step++;
				}
				else
				{
					printf("Invalid move.\n");
				}
			}
		}
	}

	scoring(arr, size, namePlayer1, namePlayer2);
}
      

/**********************************************   Function will get the names of the players,    **********************************************/
/**********************************************        show the display for the game,            **********************************************/
/**********************************************         get the moves from the players,          **********************************************/
/**********************************************        and check the order of the moves.         **********************************************/

bool checkLegalMove(char arr[SIZE][SIZE], int size, int row, int col, char ch)
{
	int i, j;
	char ch1, ch2;
	bool move = false;
	int validMoves;
	
	if (ch == 'X')
	{
		ch1 = 'X';
		ch2 = 'O';
	}
	else
	{
		ch1 = 'O';
		ch2 = 'X';
	}
	
    if (arr[row][col + 1] == ch2)
	{
		for (j = col + 2; j < size; j++)
		{
			if (arr[row][j] == ch1)
			{
				move = true;

				for (j = col + 1; arr[row][j] != ch1; j++)
				{
					arr[row][j] = ch1;
				}

				break;
				
			}
		}	
	}

	if (arr[row][col - 1] == ch2)
	{
		for (j = col - 2; j >= 0; j--)
		{
			if (arr[row][j] == ch1)
			{
				move = true;

				for (j = col - 1; arr[row][j] != ch1; j--)
				{
					arr[row][j] = ch1;
				}

				break;
			}
		}	
	}

	if (arr[row+1][col] == ch2)
	{
		for (i = row + 2; i < size; i++)
		{
			if (arr[i][col] == ch1)
			{
				move = true;

				for (i = row + 1; arr[i][col] != ch1; i++)
				{
					arr[i][col] = ch1;
				}

				break;
			}
				
		}
	}

	if (arr[row - 1][col] == ch2)
	{
		for (i = row - 2; i >= 0; i--)
		{
			if (arr[i][col] == ch1)
			{
				move = true;

				for (i = row - 1; arr[i][col] != ch1; i--)
				{
					arr[i][col] = ch1;
				}

				break;
			}
				
		}
	}

	if (arr[row - 1][col + 1] == ch2)
	{
		for (i = row - 2, j = col + 2; i >= 0 && j < size; i--, j++)
		{
			if (arr[i][j] == ch1)
			{
				move = true;

				for (i = row - 1, j = col + 1; arr[i][j] != ch1; i--, j++)
				{
					arr[i][j] = ch1;
				}

				break;
			}	
		}
	}

	if (arr[row - 1][col - 1] == ch2)
	{
		for (i = row - 2, j = col - 2; i >= 0 && j >= 0; i--, j--)
		{
			if (arr[i][j] == ch1)
			{
				move = true;

				for (i = row - 1, j = col - 1; arr[i][j] != ch1; i--, j--)
				{
					arr[i][j] = ch1;
				}

				break;
			}
		}
	}

	if (arr[row + 1][col - 1] == ch2)
	{
		for (i = row + 2, j = col - 2; i < size && j >= 0; i++, j--)
	    {
			if (arr[i][j] == ch1)
			{
				move = true;

				for (i = row + 1, j = col - 1; arr[i][j] != ch1; i++, j--)
				{
					arr[i][j] = ch1;
				}

				break;
			}
	    }
	}

	if (arr[row + 1][col + 1] == ch2)
	{
		for (i = row + 2, j = col + 2; i < size && j < size; i++, j++)
		{
			if (arr[i][j] == ch1)
			{
				move = true;

				for (i = row + 1, j = col + 1; arr[i][j] != ch1; i++, j++)
				{
					arr[i][j] = ch1;
				}

				break;
			}
		}
	}

	return move;
	
}
/******************************************** CHECKING A COUNT of VALID MOVES *****************************************************/
int countOfValidMoves(char arr[SIZE][SIZE], int size, char ch)
{
	int i, j;
	int count = 0;

	for (i = 1; i <= size; i++)
	{
		for (j = 1; j <= size; j++)
		{
			if (arr[i - 1][j - 1] == '_')
			{
				if (checkCountOfLegalMove(arr, size, i - 1, j - 1, ch) == true)
				{
					count++;
				}
			}
		}
	}

	return count;
}

/************************************************       WHO ARE YOU, WINNER OR NOT?        ************************************************/
void scoring(char arr[SIZE][SIZE], int size, char string1[SIZE], char string2[SIZE])
{
	int i, j;
	int countPlayer1 = 0;       // Count of 'X' in matrix.
	int countPlayer2 = 0;       // Count of 'O' in matrix.

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (arr[i][j] == 'X')
			{
				countPlayer1++;
			}
			else if (arr[i][j] == 'O')
			{
				countPlayer2++;
			}
		}
	}

	if (countPlayer1 > countPlayer2)
	{
		printf("%s is WINNER !!! \n", string1);
	}
	else
	{
		printf("%s is WINNER !!! \n", string2);
	}
	
}
/**************************************** Function checks all coordinates and count how many valid moves we have *****************************************/
bool checkCountOfLegalMove(char arr[SIZE][SIZE], int size, int row, int col, char ch)
{
	int i, j;
	char ch1, ch2;
	bool move = false;
	int validMoves;

	if (ch == 'X')
	{
		ch1 = 'X';
		ch2 = 'O';
	}
	else
	{
		ch1 = 'O';
		ch2 = 'X';
	}

	if (arr[row][col + 1] == ch2)
	{
		for (j = col + 2; j < size; j++)
		{
			if (arr[row][j] == ch1)
			{
				move = true;
			}
		}
	}

	if (arr[row][col - 1] == ch2)
	{
		for (j = col - 2; j >= 0; j--)
		{
			if (arr[row][j] == ch1)
			{
				move = true;
			}
		}
	}

	if (arr[row + 1][col] == ch2)
	{
		for (i = row + 2; i < size; i++)
		{
			if (arr[i][col] == ch1)
			{
				move = true;
			}

		}
	}

	if (arr[row - 1][col] == ch2)
	{
		for (i = row - 2; i >= 0; i--)
		{
			if (arr[i][col] == ch1)
			{
				move = true;
			}

		}
	}

	if (arr[row - 1][col + 1] == ch2)
	{
		for (i = row - 2, j = col + 2; i >= 0 && j < size; i--, j++)
		{
			if (arr[i][j] == ch1)
			{
				move = true;
			}
		}
	}

	if (arr[row - 1][col - 1] == ch2)
	{
		for (i = row - 2, j = col - 2; i >= 0 && j >= 0; i--, j--)
		{
			if (arr[i][j] == ch1)
			{
				move = true;
			}
		}
	}

	if (arr[row + 1][col - 1] == ch2)
	{
		for (i = row + 2, j = col - 2; i < size && j >= 0; i++, j--)
		{
			if (arr[i][j] == ch1)
			{
				move = true;
			}
		}
	}

	if (arr[row + 1][col + 1] == ch2)
	{
		for (i = row + 2, j = col + 2; i < size && j < size; i++, j++)
		{
			if (arr[i][j] == ch1)
			{
				move = true;
			}
		}
	}

	return move;
}




