/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
Name: Sreeniketh Raghavan 
Student ID: 165551013
UPI: srag400
*/

// Function 1: This function outputs the middle prize value when three values are given as inputs to the function
int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	// If prize 1 is the middle value return the value of prize 1
	if (((prize1 >= prize2) && (prize1 <= prize3)) || ((prize1 <= prize2) && (prize1 >= prize3))) {

		return prize1;
	}

	// If prize 2 is the middle value return the value of prize 2
	else if (((prize2 >= prize1) && (prize2 <= prize3)) || ((prize2 <= prize1) && (prize2 >= prize3))) {

		return prize2;
	}

	// If prize 1 and prize 2 aren't the middle values, return the value of prize 3
	else {
		return prize3;
	}
}

// Function 2: This function outputs the position in an array of a given length where a four in a row sequence begins, else it returns 0
int FourInARow(int values[], int length)
{
	int i;

	// Stepping through each element of the array
	for (i = 0; i < length; i++) {

		// Checks for four in a row sequence and also ensures that only the length or the number of elements given as an input to the function are checked, though the array may be longer
		if ((values[i] == values[i + 1]) && (values[i] == values[i + 2]) && (values[i] == values[i + 3]) && (i + 3 < length)) {

			return i;
		}
	}

	return -1;
}

// Function 3: This function converts a binary or base 2 number to a decimal or base 10 number
int BinaryToDecimal(int binary)
{ 	
	int decimal = 0;
	int positionMultiplier = 1;
	int digit;

	// While loop steps through the digits of the binary number from the least significant bit (LSB) to the most significant bit (MSB)
	while (binary != 0) {

		// The remainder when divided by 10 will always be the LSB and then the entire binary number is divided by 10 to make the digit to the left the LSB
		digit = binary % 10;
		binary /= 10;

		// As we step one digit to the left, the value of that digit doubles which is kept track of by the variable postionMultiplier which doubles after during iteration of the while loop
		decimal += digit * positionMultiplier;
		positionMultiplier += positionMultiplier;
	}

	return decimal;
}

// Function 4 (a): This is a helper function which swaps two array elements at positions i and j respectively with each other
void Swap(double *values, int i, int j)
{
	double temp;
	temp = values[i];

	// Swapping the elements
	values[i] = values[j];
	values[j] = temp;
}

// Function 4 (b): This is a helper function which checks if an element in an array is larger than the next element, and if so swaps the two elements around
void Bubble(double *values, int length)
{
	int i;
	for (i = 0; i < length - 1; i++) {

		// If the element is greater than the next element, use the Swap function to swap the two elements
		if (values[i] > values[i + 1]) {
			Swap(values, i, i + 1);
		}
	}
}

// Function 4 (c): This function outputs the median value of all the elements present in an array
double MedianAbility(double abilities[], int length)
{	
	// Perform the bubble sort algorithm on all the elements in the array using the Bubble function to sort the elements in an ascending order
	for (int i = 0; i < length; i++){

		Bubble(abilities, length);
	}

	// If the number of elements is odd, choose the middle element as the median
	if (length % 2 == 1) {

		return abilities[(length-1)/2];
	}

	// If the number of elements is even, take the average of the two middle values as the median
	return (abilities[(length-1)/2] + abilities[length/2]) / 2;
}

// Function 5: This function removes any extra spaces present between characters in a string and replaces them with a single space
void RemoveSpaces(char *name)
{
	// Getting the length of the string and subtracting 1 as we only need to check length - 1 characters due to the code using the successive character value as well
	int length = strlen(name) - 1;
	int i = 0;
	int j;
	
	// Checking for all characters present in the string
	while (i <= length) {

		// If there are 2 consecutive spaces present, delete the left space by moving all the characters after the space one position to the left
		if (name[i] == ' ' && name[i + 1] == ' ') {
			for (j = i; j <= length; j++) {
				name[j] = name[j + 1];
				i--;
			}
			length--;
		}

		i++;
	}
}

// Function 6: This function initialises or creates the connect4 game board for the specified size
void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	int i, j;

	// Fills the board array with 0s or empty spaces to start with 
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {

			board[i][j] = 0;
		}
	}

	// Inserts the 3s or fixed pieces depending on the size of the board	
	if (size % 2 == 1) {

		// An odd sized board will have one fixed piece in the middle of the board
		board[size / 2][size / 2] = 3;
	}

	else {

		// An even sized board will have four fixed pieces in the middle of the board
		for (i = size / 2 - 1; i <= size / 2; i++) {
			for (j = size / 2 - 1; j <= size / 2; j++) {

				board[i][j] = 3;
			}
		}
	}
}

// Function 7: This function takes an input of the move the player wants to make and adds that move to the board of the specified size
void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	int i;
	int rowFull = 0;
	int colFull = 0;
	int obstruction = 0;

	// If the side is West, and there is a token blocking the move
	if (side == 'W') {

		for (i = 0; i < size; i++) {

			if ((board[i][0] == 1 || board[i][0] == 2) && (i == move)) {

				*lastRow = -1;
				*lastCol = -1;
				
				// No move can be made from the West side for that row and hence 1 is stored in the variable rowFull
				rowFull = 1;

				break;
			}
		}

		// If a token is not blocking the move
		if (rowFull == 0) {

			for (i = 0; i < size; i++) {

				// Steps through columns and places a token only when an obstruction is reached, i.e, another token or a fixed piece
				if (board[move][i] == 1 || board[move][i] == 2 || board[move][i] == 3) {

					board[move][i - 1] = player;

					*lastRow = move;
					*lastCol = i - 1;

					obstruction = 1;

					break;
				}
			}

			// If no obstruction is present in the row, then the token slides through to the very end of the board
			if (obstruction == 0) {

				board[move][size - 1] = player;

				*lastRow = move;
				*lastCol = size - 1;
			}
		}
	}

	// If the side is North, and there is a token blocking the move
	if (side == 'N') {

		for (i = 0; i < size; i++) {

			if ((board[0][i] == 1 || board[0][i] == 2) && (i == move)) {

				*lastRow = -1;
				*lastCol = -1;

				// No move can be made from the North side for that column and hence 1 is stored in the variable colFull
				colFull = 1;

				break;
			}
		}

		// If a token is not blocking the move
		if (colFull == 0) {

			for (i = 0; i < size; i++) {

				// Steps through rows and places a token only when an obstruction is reached, i.e, another token or a fixed piece
				if (board[i][move] == 1 || board[i][move] == 2 || board[i][move] == 3) {

					board[i - 1][move] = player;

					*lastRow = i - 1;
					*lastCol = move;

					obstruction = 1;

					break;
				}
			}

			// If no obstruction is present in the column, then the token slides through to the very end of the board
			if (obstruction == 0) {

				board[size - 1][move] = player;

				*lastRow = size - 1;
				*lastCol = move;
			}
		}
	}

	// If the side is South, and there is a token blocking the move
	if (side == 'S') {

		for (i = 0; i < size; i++) {

			if ((board[size - 1][i] == 1 || board[size - 1][i] == 2) && (i == move)) {

				*lastRow = -1;
				*lastCol = -1;

				// No move can be made from the South side for that column and hence 1 is stored in the variable colFull
				colFull = 1;

				break;
			}
		}

		// If a token is not blocking the move
		if (colFull == 0) {

			for (i = size - 1; i >= 0; i--) {

				// Steps through rows and places a token only when an obstruction is reached, i.e, another token or a fixed piece
				if (board[i][move] == 1 || board[i][move] == 2 || board[i][move] == 3) {

					board[i + 1][move] = player;

					*lastRow = i + 1;
					*lastCol = move;

					obstruction = 1;

					break;
				}
			}

			// If no obstruction is present in the column, then the token slides through to the very end of the board
			if (obstruction == 0) {

				board[0][move] = player;

				*lastRow = 0;
				*lastCol = move;
			}
		}
	}

	// If the side is East, and there is a token blocking the move
	if (side == 'E') {

		for (i = 0; i < size; i++) {

			if ((board[i][size - 1] == 1 || board[i][size - 1] == 2) && (i == move)) {

				*lastRow = -1;
				*lastCol = -1;

				// No move can be made from the East side for that row and hence 1 is stored in the variable rowFull
				rowFull = 1;

				break;
			}
		}

		// If a token is not blocking the move
		if (rowFull == 0) {

			for (i = size - 1; i >= 0; i--) {

				// Steps through columns and places a token only when an obstruction is reached, i.e, another token or a fixed piece
				if (board[move][i] == 1 || board[move][i] == 2 || board[move][i] == 3) {

					board[move][i + 1] = player;

					*lastRow = move;
					*lastCol = i + 1;

					obstruction = 1;

					break;
				}
			}

			// If no obstruction is present in the column, then the token slides through to the very end of the board
			if (obstruction == 0) {

				board[move][0] = player;

				*lastRow = move;
				*lastCol = 0;
			}
		}
	}
}

// Function 8: This function checks whether the game is over when a move is made 
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int i;
	int westBlocked = 0, northBlocked = 0, eastBlocked = 0, southBlocked = 0;
	int checkRow = row, checkCol = col;

	for (i = 0; i < size; i++) {
		
		// Counts the number of positions blocked by a token from the North side
		if (board[0][i] == 1 || board[0][i] == 2) {

			northBlocked += 1;
		}

		// Counts the number of positions blocked by a token from the West side
		if (board[i][0] == 1 || board[i][0] == 2) {

			westBlocked += 1;
		}

		// Counts the number of positions blocked by a token from the South side
		if (board[size - 1][i] == 1 || board[size - 1][i] == 2) {

			southBlocked += 1;
		}

		// Counts the number of positions blocked by a token from the East side
		if (board[i][size - 1] == 1 || board[i][size - 1] == 2) {

			eastBlocked += 1;
		}
	}

	// If the last move results in no more valid moves being available, the player who made the last move is returned
	if (westBlocked == size && northBlocked == size && eastBlocked == size && southBlocked == size) {

		return player;
	}

	// Checking if the last token placed resulted in a four in a row horizontally 
	for (i = 0; i < size - 3; i++) {

		if (board[row][i] == player && board[row][i + 1] == player && board[row][i + 2] == player && board[row][i + 3] == player) {

			return player;
		}
	}

	// Checking if the last token placed resulted in a four in a row vertically 
	for (i = 0; i < size - 3; i++) {

		if (board[i][col] == player && board[i + 1][col] == player && board[i + 2][col] == player && board[i + 3][col] == player) {

			return player;
		}
	}

	// Starting from the position of the last token placed and moving diagonally leftwards and upwards till we hit the walls of the board
	while (checkRow != 0 && checkCol != 0) {

		checkRow--;
		checkCol--;
	}

	// Starting from the position where we hit either the top or the left wall of the board and stepping diagonally rightwards and downwards
	while (checkRow != size - 3 && checkCol != size - 3) {
		
		// Checking 4 in a row diagonally 
		if (board[checkRow][checkCol] == player && board[checkRow + 1][checkCol + 1] == player && board[checkRow + 2][checkCol + 2] == player && board[checkRow + 3][checkCol + 3] == player) {

			return player;
		}

		checkRow++;
		checkCol++;
	}

	checkRow = row;
	checkCol = col;

	// Starting from the position of the last token placed and moving diagonally rightwards and upwards till we hit the walls of the board
	while (checkRow != 0 && checkCol != size - 1) {

		checkRow--;
		checkCol++;
	}

	// Starting from the position where we hit either the bottom or the right wall of the board and stepping diagonally leftwards and downwards
	while (checkRow != size - 3 && checkCol != 2) {

		// Checking 4 in a row diagonally 
		if (board[checkRow][checkCol] == player && board[checkRow + 1][checkCol - 1] == player && board[checkRow + 2][checkCol - 2] == player && board[checkRow + 3][checkCol - 3] == player) {

			return player;
		}

		checkRow++;
		checkCol--;
	}

	return 0;
}

// Function 9: This function converts the board 2D array into a string with directions, row and column numbers displayed, along with special characters for different tokens, fixed pieces and empty spaces, which can then be displayed
void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	int i, j;
	int row = 0;
	int position = 0;
	char indexNo = '0';

	// Start with 2 dashes
	boardString[0] = '-';
	boardString[1] = '-';
	position = 2;

	// Fill up the top row with the character 'N' depending on the size of the board
	for (i = 2; i < size + 2; i++) {

		boardString[i] = 'N';
		position++;
	}

	// End the first line with 2 more dashes and a new line character
	boardString[position] = '-';
	position++;
	boardString[position] = '-';
	position++;
	boardString[position] = '\n';
	position++;

	// Start the second line with 2 dashes 
	boardString[position] = '-';
	position++;
	boardString[position] = '-';
	position++;

	j = position;

	// Fill out the North direction indicies depending on the size of the board
	for (i = j; i < size + j; i++) {

		boardString[i] = indexNo;
		indexNo++;
		position++;
	}

	// End the line with 2 dashes and a new line character 
	boardString[position] = '-';
	position++;
	boardString[position] = '-';
	position++;
	boardString[position] = '\n';
	position++;

	// indexNo is a character which keeps track of the West and East side indicies
	indexNo = '0';

	// Repeat for size - 1 rows
	while (indexNo != size + '0') {

		// Start the third line with a 'W'
		boardString[position] = 'W';
		position++;		

		// Store the index number associated with the West direction for that row
		boardString[position] = indexNo;
		position++;

		// Fill out the characters corresponding to the board array's first row
		for (i = 0; i < size; i++) {

			if (board[row][i] == 0) {

				boardString[position] = '.';
				position++;
			}

			if (board[row][i] == 3) {

				boardString[position] = '#';
				position++;
			}

			if (board[row][i] == 1) {

				boardString[position] = 'X';
				position++;
			}

			if (board[row][i] == 2) {

				boardString[position] = 'O';
				position++;
			}
		}

		// Store the index number associated with the East direction for that row
		boardString[position] = indexNo;
		position++;
		indexNo++;

		// Store the character 'E' corresponding to the East direction 
		boardString[position] = 'E';
		position++;

		// End the row with a new line character
		boardString[position] = '\n';
		position++;
		row++;
	}

	// After the middle part of the board is done corresponding to the board array
	// For the second last row start with 2 dashes 
	boardString[position] = '-';
	position++;
	boardString[position] = '-';
	position++;

	indexNo = '0';

	j = position;
	
	// Fill out the indicies corresponding to the South direction 
	for (i = j; i < size + j; i++) {

		boardString[i] = indexNo;
		indexNo++;
		position++;
	}

	// Store 2 dashes to end the row along with a new line character 
	boardString[position] = '-';
	position++;
	boardString[position] = '-';
	position++;
	boardString[position] = '\n';
	position++;

	// Start the last row of the string with 2 dashes 
	boardString[position] = '-';
	position++;
	boardString[position] = '-';
	position++;

	j = position;

	// Fill out the character 'S' depending on the size of the board
	for (i = j; i < size + j; i++) {

		boardString[i] = 'S';
		position++;
	}

	// End the string with 2 dashes and a new line character 
	boardString[position] = '-';
	position++;
	boardString[position] = '-';
	position++;
	boardString[position] = '\n';
	position++;

	boardString[position] = '\0';
}

// Function 10 (a): This function performs moves as an automated bot which follows a certain strategy
void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int i, j, k;
	int counter = 0;
	int row, col;
	int chooseSide;

	if (size % 2 == 1) {

		row = size / 2;
		col = size / 2;
	}

	else {
		row = size / 2 - 1;
		col = row;
	}

	// While the move generated is invalid
	while (board[row][col] != 0) {

		// Randomly chooses a move between 0 and size - 1
		*move = rand() % size;

		// Randomly chooses one of the four directions
		chooseSide = rand() % 4;

		if (chooseSide == 0) {

			*side = 'N';
			row = 0;
			col = *move;
		}

		if (chooseSide == 1) {

			*side = 'S';
			row = size - 1;
			col = *move;
		}

		if (chooseSide == 2) {

			*side = 'E';
			row = *move;
			col = size - 1;
		}

		if (chooseSide == 3) {

			*side = 'W';
			row = *move;
			col = 0;
		}

	}

	// Scans through the board and checks for winning moves, and plays a winning move if one is available 
	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 2; j++) {

			// Checking for 3 in a row horizontally 
			if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player) {

				for (k = j + 3; k < size; k++) {

					// Checking if the path from the East side is clear
					if (board[i][k] != 0) {
						counter++;
					}
				}

				row = i;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = 0; k < j; k++) {

					if (board[i][k] != 0) {
						counter++;
					}
				}

				row = i;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i; k < size; k++) {

					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i - 1][j - 1] != 0) {
					*side = 'S';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i; k < size; k++) {

					if (board[k][j + 3] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i - 1][j + 3] != 0) {
					*side = 'S';
					*move = j + 3;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i; k >= 0; k--) {

					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i + 1][j - 1] != 0) {
					*side = 'N';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i; k >= 0; k--) {

					if (board[k][j + 3] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i + 1][j + 3] != 0) {
					*side = 'N';
					*move = j + 3;
					return;
				}

				counter = 0;
			}

			// Checking for 3 in a row vertically
			if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == player) {

				// Checking if path from the South side is clear
				for (k = j + 3; k < size; k++) {

					if (board[k][i] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = i;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'S';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = 0; k < j; k++) {

					if (board[k][i] != 0) {
						counter++;
					}
				}

				row = 0;
				col = i;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'N';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i; k < size; k++) {

					if (board[j + 3][k] != 0) {
						counter++;
					}
				}

				row = j + 3;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j + 3][i - 1] != 0) {
					*side = 'E';
					*move = j + 3;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i; k < size; k++) {

					if (board[j - 1][k] != 0) {
						counter++;
					}
				}

				row = j - 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j - 1][i - 1] != 0) {
					*side = 'E';
					*move = j - 3;
					return;
				}

				counter = 0;
				
				// Checking if path from the West side is clear
				for (k = i; k >= 0; k--) {

					if (board[j + 3][k] != 0) {
						counter++;
					}
				}

				row = j + 3;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j + 3][i + 1] != 0) {
					*side = 'W';
					*move = j + 3;
					return;
				}

				counter = 0;
				
				// Checking if path from the West side is clear
				for (k = i; k >= 0; k--) {

					if (board[j - 1][k] != 0) {
						counter++;
					}
				}

				row = j - 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j - 1][i + 1] != 0) {
					*side = 'W';
					*move = j - 1;
					return;
				}
				counter = 0;
			}
		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 3; j++) {

			// Checks for a token, then an empty space followed by 2 in a row horizontally
			if (board[i][j] == player && board[i][j + 1] == 0 && board[i][j + 2] == player && board[i][j + 3] == player) {

				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j + 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {

					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 1;
					return;
				}
			}

			counter = 0;

			// Checks for 2 in a row, then an empty space followed by another token horizontally 
			if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == 0 && board[i][j + 3] == player) {
				
				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[k][j + 2] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 2;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {

					if (board[k][j + 2] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 2;
					return;
				}

				counter = 0;
			}

			// Checks for a token, then an empty space followed by 2 in a row vertically
			if (board[j][i] == player && board[j + 1][i] == 0 && board[j + 2][i] == player && board[j + 3][i] == player) {
				
				// Checking if path from the West side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[j + 1][k] != 0) {
						counter++;
					}
				}

				row = j + 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 1][i + 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i + 1; k < size; k++) {

					if (board[j + 1][k] != 0) {
						counter++;
					}
				}

				row = j + 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 1][i - 1] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = j + 1;
					return;
				}

				counter = 0;
			}

			// Checks for 2 in a row, then an empty space followed by another token vertically 
			if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == 0 && board[j + 3][i] == player) {

				// Checking if path from the West side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[j + 2][k] != 0) {
						counter++;
					}
				}

				row = j + 2;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 2][i + 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = j + 2;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i + 1; k < size; k++) {

					if (board[j + 2][k] != 0) {
						counter++;
					}
				}

				row = j + 2;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 2][i - 1] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = j + 2;
					return;
				}

				counter = 0;
			}
		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {

			// Checks for 3 in a row diagonally from top right to bottom left
			if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player) {

				// Checking if path from the East side is clear
				for (k = j - 3; k < size; k++) {
					if (board[i + 3][k] != 0) {
						counter++;
					}
				}

				row = i + 3;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 3][j - 4] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 3;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 3; k >= 0; k--) {
					if (board[i + 3][k] != 0) {
						counter++;
					}
				}

				row = i + 3;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 3;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 3; k < size; k++) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 3; k >= 0; k--) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 4][j - 3] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = j + 1; k < size; k++) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j + 1; k >= 0; k--) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i - 1; k < size; k++) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j + 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i][j + 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 1;
					return;
				}

				counter = 0;

			}

			// Checks for a token, then an empty space followed by 2 in a row diagonally from top right to bottom left
			if (board[i][j] == player && board[i + 1][j - 1] == 0 && board[i + 2][j - 2] == player && board[i + 3][j - 3] == player) {

				// Checking if path from the East side is clear
				for (k = j - 1; k < size; k++) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 1; k >= 0; k--) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i][j - 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 1; k >= 0; k--) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 1;
					return;
				}

				counter = 0;
			}

			// Checks for 2 in a row, then an empty space followed by another token diagonally from top right to bottom left
			if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == 0 && board[i + 3][j - 3] == player) {

				// Checking if path from the East side is clear
				for (k = j - 2; k < size; k++) {
					if (board[i + 2][k] != 0) {
						counter++;
					}
				}

				row = i + 2;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 2;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 2; k >= 0; k--) {
					if (board[i + 2][k] != 0) {
						counter++;
					}
				}

				row = i + 2;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 2;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 2; k < size; k++) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 2;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 2; k >= 0; k--) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 2;
					return;
				}

				counter = 0;
			}
		}
	}

	for (i = size - 1; i >= 0; i--) {
		for (j = size - 1; j >= 0; j--) {

			// Checks for 3 in a row diagonally from bottom right to top left
			if (board[i][j] == player && board[i - 1][j - 1] == player && board[i - 2][j - 2] == player) {

				// Checking if path from the East side is clear
				for (k = j - 3; k < size; k++) {
					if (board[i - 3][k] != 0) {
						counter++;
					}
				}

				row = i - 3;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 3][j - 4] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 3;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 3; k >= 0; k--) {
					if (board[i - 3][k] != 0) {
						counter++;
					}
				}

				row = i - 3;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 3;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i - 3; k < size; k++) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 4][j - 3] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i - 3; k >= 0; k--) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}
				row = 0;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = j + 1; k < size; k++) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j + 1; k >= 0; k--) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}
				row = size - 1;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 1; k >= 0; k--) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j + 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 1;
					return;
				}

				counter = 0;
			}

			// Checks for 2 in a row, then an empty space followed by another token diagonally from bottom right to top left
			if (board[i][j] == player && board[i - 1][j - 1] == player && board[i - 2][j - 2] == 0 && board[i - 3][j - 3] == player) {

				for (k = j - 2; k < size; k++) {
					if (board[i - 2][k] != 0) {
						counter++;
					}
				}

				row = i - 2;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 2;
					return;
				}

				counter = 0;

				for (k = j - 2; k >= 0; k--) {
					if (board[i - 2][k] != 0) {
						counter++;
					}
				}

				row = i - 2;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 2;
					return;
				}

				counter = 0;

				for (k = i - 2; k < size; k++) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 2;
					return;
				}

				counter = 0;

				for (k = i - 2; k >= 0; k--) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}
				row = 0;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 2;
					return;
				}

				counter = 0;

			}

			// Checks for a token, then an empty space, followed by 2 tokens diagonally from bottom right to top left
			if (board[i][j] == player && board[i - 1][j - 1] == 0 && board[i - 2][j - 2] == player && board[i - 3][j - 3] == player) {

				// Checking if path from the East side is clear
				for (k = j - 1; k < size; k++) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 1; k >= 0; k--) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i - 1; k < size; k++) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}
				row = 0;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i][j - 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 1;
					return;
				}

				counter = 0;

			}
		}
	}
}

// Function 10 (b): This function performs moves as an automated bot which follows exactly the same strategy as Bot 1
void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int i, j, k;
	int counter = 0;
	int row, col;
	int chooseSide;

	if (size % 2 == 1) {

		row = size / 2;
		col = size / 2;
	}

	else {
		row = size / 2 - 1;
		col = row;
	}

	// While the move generated is invalid
	while (board[row][col] != 0) {

		// Randomly chooses a move between 0 and size - 1
		*move = rand() % size;

		// Randomly chooses one of the four directions
		chooseSide = rand() % 4;

		if (chooseSide == 0) {

			*side = 'N';
			row = 0;
			col = *move;
		}

		if (chooseSide == 1) {

			*side = 'S';
			row = size - 1;
			col = *move;
		}

		if (chooseSide == 2) {

			*side = 'E';
			row = *move;
			col = size - 1;
		}

		if (chooseSide == 3) {

			*side = 'W';
			row = *move;
			col = 0;
		}

	}

	// Scans through the board and checks for winning moves, and plays a winning move if one is available 
	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 2; j++) {

			// Checking for 3 in a row horizontally 
			if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player) {

				for (k = j + 3; k < size; k++) {

					// Checking if the path from the East side is clear
					if (board[i][k] != 0) {
						counter++;
					}
				}

				row = i;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = 0; k < j; k++) {

					if (board[i][k] != 0) {
						counter++;
					}
				}

				row = i;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i; k < size; k++) {

					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i - 1][j - 1] != 0) {
					*side = 'S';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i; k < size; k++) {

					if (board[k][j + 3] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i - 1][j + 3] != 0) {
					*side = 'S';
					*move = j + 3;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i; k >= 0; k--) {

					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i + 1][j - 1] != 0) {
					*side = 'N';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i; k >= 0; k--) {

					if (board[k][j + 3] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[i + 1][j + 3] != 0) {
					*side = 'N';
					*move = j + 3;
					return;
				}

				counter = 0;
			}

			// Checking for 3 in a row vertically
			if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == player) {

				// Checking if path from the South side is clear
				for (k = j + 3; k < size; k++) {

					if (board[k][i] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = i;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'S';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = 0; k < j; k++) {

					if (board[k][i] != 0) {
						counter++;
					}
				}

				row = 0;
				col = i;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0) {
					*side = 'N';
					*move = i;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i; k < size; k++) {

					if (board[j + 3][k] != 0) {
						counter++;
					}
				}

				row = j + 3;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j + 3][i - 1] != 0) {
					*side = 'E';
					*move = j + 3;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i; k < size; k++) {

					if (board[j - 1][k] != 0) {
						counter++;
					}
				}

				row = j - 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j - 1][i - 1] != 0) {
					*side = 'E';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = i; k >= 0; k--) {

					if (board[j + 3][k] != 0) {
						counter++;
					}
				}

				row = j + 3;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j + 3][i + 1] != 0) {
					*side = 'W';
					*move = j + 3;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = i; k >= 0; k--) {

					if (board[j - 1][k] != 0) {
						counter++;
					}
				}

				row = j - 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[row][col] == 0 && board[j - 1][i + 1] != 0) {
					*side = 'W';
					*move = j - 1;
					return;
				}
				counter = 0;
			}
		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 3; j++) {

			// Checks for a token, then an empty space followed by 2 in a row horizontally
			if (board[i][j] == player && board[i][j + 1] == 0 && board[i][j + 2] == player && board[i][j + 3] == player) {

				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j + 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {

					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 1;
					return;
				}
			}

			counter = 0;

			// Checks for 2 in a row, then an empty space followed by another token horizontally 
			if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == 0 && board[i][j + 3] == player) {

				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[k][j + 2] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 2;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {

					if (board[k][j + 2] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 2;
					return;
				}

				counter = 0;
			}

			// Checks for a token, then an empty space followed by 2 in a row vertically
			if (board[j][i] == player && board[j + 1][i] == 0 && board[j + 2][i] == player && board[j + 3][i] == player) {

				// Checking if path from the West side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[j + 1][k] != 0) {
						counter++;
					}
				}

				row = j + 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 1][i + 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i + 1; k < size; k++) {

					if (board[j + 1][k] != 0) {
						counter++;
					}
				}

				row = j + 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 1][i - 1] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = j + 1;
					return;
				}

				counter = 0;
			}

			// Checks for 2 in a row, then an empty space followed by another token vertically 
			if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == 0 && board[j + 3][i] == player) {

				// Checking if path from the West side is clear
				for (k = i - 1; k >= 0; k--) {

					if (board[j + 2][k] != 0) {
						counter++;
					}
				}

				row = j + 2;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 2][i + 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = j + 2;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = i + 1; k < size; k++) {

					if (board[j + 2][k] != 0) {
						counter++;
					}
				}

				row = j + 2;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[j + 2][i - 1] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = j + 2;
					return;
				}

				counter = 0;
			}
		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {

			// Checks for 3 in a row diagonally from top right to bottom left
			if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player) {

				// Checking if path from the East side is clear
				for (k = j - 3; k < size; k++) {
					if (board[i + 3][k] != 0) {
						counter++;
					}
				}

				row = i + 3;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 3][j - 4] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 3;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 3; k >= 0; k--) {
					if (board[i + 3][k] != 0) {
						counter++;
					}
				}

				row = i + 3;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 3;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 3; k < size; k++) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 3; k >= 0; k--) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 4][j - 3] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = j + 1; k < size; k++) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j + 1; k >= 0; k--) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i - 1; k < size; k++) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j + 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i][j + 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 1;
					return;
				}

				counter = 0;

			}

			// Checks for a token, then an empty space followed by 2 in a row diagonally from top right to bottom left
			if (board[i][j] == player && board[i + 1][j - 1] == 0 && board[i + 2][j - 2] == player && board[i + 3][j - 3] == player) {

				// Checking if path from the East side is clear
				for (k = j - 1; k < size; k++) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 1; k >= 0; k--) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i][j - 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 1; k >= 0; k--) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 1;
					return;
				}

				counter = 0;
			}

			// Checks for 2 in a row, then an empty space followed by another token diagonally from top right to bottom left
			if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == 0 && board[i + 3][j - 3] == player) {

				// Checking if path from the East side is clear
				for (k = j - 2; k < size; k++) {
					if (board[i + 2][k] != 0) {
						counter++;
					}
				}

				row = i + 2;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 2;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 2; k >= 0; k--) {
					if (board[i + 2][k] != 0) {
						counter++;
					}
				}

				row = i + 2;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 2;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 2; k < size; k++) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 2;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 2; k >= 0; k--) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 2;
					return;
				}

				counter = 0;
			}
		}
	}

	for (i = size - 1; i >= 0; i--) {
		for (j = size - 1; j >= 0; j--) {

			// Checks for 3 in a row diagonally from bottom right to top left
			if (board[i][j] == player && board[i - 1][j - 1] == player && board[i - 2][j - 2] == player) {

				// Checking if path from the East side is clear
				for (k = j - 3; k < size; k++) {
					if (board[i - 3][k] != 0) {
						counter++;
					}
				}

				row = i - 3;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 3][j - 4] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 3;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 3; k >= 0; k--) {
					if (board[i - 3][k] != 0) {
						counter++;
					}
				}

				row = i - 3;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 3;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i - 3; k < size; k++) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 4][j - 3] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i - 3; k >= 0; k--) {
					if (board[k][j - 3] != 0) {
						counter++;
					}
				}
				row = 0;
				col = j - 3;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 3;
					return;
				}

				counter = 0;

				// Checking if path from the East side is clear
				for (k = j + 1; k < size; k++) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j + 1; k >= 0; k--) {
					if (board[i + 1][k] != 0) {
						counter++;
					}
				}

				row = i + 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 1][j + 2] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i + 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i + 1; k < size; k++) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}
				row = size - 1;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j + 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j + 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i + 1; k >= 0; k--) {
					if (board[k][j + 1] != 0) {
						counter++;
					}
				}

				row = 0;
				col = j + 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i + 2][j + 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j + 1;
					return;
				}

				counter = 0;
			}

			// Checks for 2 in a row, then an empty space followed by another token diagonally from bottom right to top left
			if (board[i][j] == player && board[i - 1][j - 1] == player && board[i - 2][j - 2] == 0 && board[i - 3][j - 3] == player) {

				for (k = j - 2; k < size; k++) {
					if (board[i - 2][k] != 0) {
						counter++;
					}
				}

				row = i - 2;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 3] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 2;
					return;
				}

				counter = 0;

				for (k = j - 2; k >= 0; k--) {
					if (board[i - 2][k] != 0) {
						counter++;
					}
				}

				row = i - 2;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 2;
					return;
				}

				counter = 0;

				for (k = i - 2; k < size; k++) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 3][j - 2] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 2;
					return;
				}

				counter = 0;

				for (k = i - 2; k >= 0; k--) {
					if (board[k][j - 2] != 0) {
						counter++;
					}
				}
				row = 0;
				col = j - 2;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 2;
					return;
				}

				counter = 0;

			}

			// Checks for a token, then an empty space, followed by 2 tokens diagonally from bottom right to top left
			if (board[i][j] == player && board[i - 1][j - 1] == 0 && board[i - 2][j - 2] == player && board[i - 3][j - 3] == player) {

				// Checking if path from the East side is clear
				for (k = j - 1; k < size; k++) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = size - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j - 2] != 0 && board[row][col] == 0) {
					*side = 'E';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the West side is clear
				for (k = j - 1; k >= 0; k--) {
					if (board[i - 1][k] != 0) {
						counter++;
					}
				}

				row = i - 1;
				col = 0;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 1][j] != 0 && board[row][col] == 0) {
					*side = 'W';
					*move = i - 1;
					return;
				}

				counter = 0;

				// Checking if path from the South side is clear
				for (k = i - 1; k < size; k++) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}

				row = size - 1;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i - 2][j - 1] != 0 && board[row][col] == 0) {
					*side = 'S';
					*move = j - 1;
					return;
				}

				counter = 0;

				// Checking if path from the North side is clear
				for (k = i - 1; k >= 0; k--) {
					if (board[k][j - 1] != 0) {
						counter++;
					}
				}
				row = 0;
				col = j - 1;

				// If the path is clear and the move is valid, store the winning move in the pointers and end the function
				if (counter == 0 && board[i][j - 1] != 0 && board[row][col] == 0) {
					*side = 'N';
					*move = j - 1;
					return;
				}

				counter = 0;

			}
		}
	}
}