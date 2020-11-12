#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cstdio>
#include "Login.h"
#include "BattleShip.h"

/*
	 *  .  . *       *    .        .        .   *    ..
 .    *        .   ###     .      .        .            *
    *.   *        #####   .     *      *        *    .
  ____       *  ######### *    .  *      .        .  *   .
 /   /\  .     ###\#|#/###   ..    *    .      *  .  ..  *
/___/  ^8/      ###\|/###  *    *            .      *   *
|   ||%%(        # }|{  #
|___|,  \\  ejm    }|{
*/

void makeEmptyBoard(char Board[M][N]) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			Board[i][j] = ' ';
		}
	}
}

void Tryplacing(char(&Board)[M][N], int& x, int& y) {
	int temp = 0;
	for (int i = 0; i < M; i++) {
		temp = M - i - 1;
		for (int j = 0; j < N; j++) {
			if (Board[temp][j] == HIT) {
				if (i == 5 && j == 5) {
					if (Board[temp + 1][j] == ' ') {
						x = i - 1;
						y = j;
						return;
					}
					if (Board[temp][j - 1] == ' ') {
						x = i;
						y = j - 1;
						return;
					}
				}
				else if (i == 5 && j < 5)
				{
					if (Board[temp + 1][j] == ' ') {
						x = i - 1;
						y = j;
						return;
					}
					if (Board[temp][j + 1] == ' ') {
						x = i;
						y = j + 1;
						return;
					}
				}
				else if (i < 5 && j == 5)
				{
					if (Board[temp - 1][j] == ' ') {
						x = i + 1;
						y = j;
						return;
					}
					else if (Board[temp][j - 1] == ' ') {
						x = i;
						y = j - 1;
						return;
					}
				}
				else if (i < 5 && j < 5 && i > 0 && j > 0) {
					if (Board[temp - 1][j] == ' ') {
						x = i + 1;
						y = j;
						return;
					}
					else if (Board[temp][j + 1] == ' ') {
						x = i;
						y = j + 1;
						return;
					}
					else if (Board[temp + 1][j] == ' ') {
						x = i - 1;
						y = j;
						return;
					}
					else if (Board[temp][j - 1] == ' ' ) {
						x = i;
						y = j - 1;
						return;
					}
				}
				else if (temp == 0 && j == 0) {
					if (Board[temp - 1][j] == ' ') {
						x = i + 1;
						y = j;
						return;
					}
					else if (Board[temp][j + 1] == ' ') {
						x = i;
						y = j + 1;
						return;
					}
				}
			}
		}
	}
}

void AI(char (&PlayerBoard)[M][N], int &Phit, char (&AIBord)[M][N], int &row, int &column, char (&AIDisplay)[M][N], char (&Board)[M][N], int &AIhit) {

	std::cout << "AI's bord:\n";
	printPlayerBoard(AIDisplay, AIBord, row, column, Phit);

	int x = 0;
	int y = 0;

	bool intelligentselction = true;

	do
	{
		x = randomRow();
		y = randomColumn();

		Tryplacing(PlayerBoard, x, y);

		if (!(PlayerBoard[M - x - 1][y] == HIT || PlayerBoard[M - x - 1][y] == MISS)) {
			intelligentselction = false;
		}

	} while (intelligentselction);

	std::cout << "Your board:\n";
	printPlayerBoard(PlayerBoard, Board, x, y, AIhit);
}

void play() {

	int numberOfShots = 18;
	bool playing = true;
	int numberOfHits;
	int AIhits;
	int ships = 9;
	char PlayerBoard[M][N];
	char AIBoard[M][N];

	makeEmptyBoard(PlayerBoard);
	makeBoard3(ships, PlayerBoard);
	makeEmptyBoard(AIBoard);
	makeBoard3(ships, AIBoard);

	Shoot(PlayerBoard, numberOfShots, playing, numberOfHits, ships, AIBoard, AIhits);
}

void Shoot(char (&Board)[M][N], int &numberOfShots, bool &shooting, int &hits, int &sinkables, char (&AIBord)[M][N], int &AIHIT) {
	char row;
	char column;
	int ROW_I;
	int Column_I;

	char PlayerBoard[M][N];
	makeEmptyBoard(PlayerBoard);

	char AIDisplay[M][N];
	makeEmptyBoard(AIDisplay);

	std::cout << "AI's bord:\n";
	printBoard(AIDisplay);
	std::cout << "Your board:\n";
	printBoard(Board);

	while (shooting)
	{
		std::cout << "Wich cell do you want to hit(example B3)? ";
		std::cin >> column >> row;

		ROW_I = (int)row;
		ROW_I -= 49;
		column = toupper(column);
		Column_I = (int)column;
		Column_I -= 65;

		numberOfShots--;

		system("Cls");

		AI(PlayerBoard, hits, AIBord, ROW_I, Column_I, AIDisplay, Board, AIHIT);


		if (numberOfShots == 0) {
			shooting = false;
			std::cout << "\nGame ended. No more shots left\n\n";
		}
		else if (hits == sinkables) {
			shooting = false;
			std::cout << "\nGame ended you won\n\n";
		}
		else if (AIHIT == sinkables) {
			shooting = false;
			std::cout << "\nGame ended AI won\n\n";
		}
	}

	
}

void printPlayerBoard(char (&PlayerBoard)[M][N],char (&Board)[M][N], int row, int column, int &numberOfHits) {
	row = M - row - 1;

	if (Board[row][column] == 'S') {
		PlayerBoard[row][column] = HIT;
		numberOfHits++;
	}
	else {
		PlayerBoard[row][column] = MISS;
	}

	printBoard(PlayerBoard);
}

void printBoard(char(&Board)[M][N]) {
	int row = M;
	for (int i = 0; i < M + 2; i++) {
		if (row > 0) {
			std::cout << row << " | ";
		}
		else if (row == 0) {
			std::cout << "  ";
		}
		else {
			std::cout << "  | ";
		}
		for (int j = 0; j < N; j++) {
			if (i < M) {
				std::cout << Board[i][j] << " | ";
			}
			else if (i == M) {
				std::cout << "----";
			}
			else if (i > M) {
				writeLetters(j);
				std::cout << " | ";
			}
		}
		std::cout << "\n";
		row--;
	}
}

void makeBoard(int numberOfShips, char(&Board)[M][N], int largerships) {
	const char SHIP = 'S';
	int inserted = 0;
	int row;
	int column;
	do {
		row = randomRow();
		column = randomColumn();
		if (isblank(Board[row][column])) {
			Board[row][column] = SHIP;
			inserted++;
		}
	} while (inserted < numberOfShips - inserted);
}

void makeBoard3(int numberOfShips, char (&board)[M][N]) {
	const char SHIP = 'S';
	int inserted = 0;
	int row;
	int column;

	do {
		row = randomRow();
		column = randomColumn();
		if (column < 4 && inserted < 3) {
			if ((isblank(board[row][column])) && (isblank(board[row][column + 1])) && (isblank(board[row][column + 2]))) {
				board[row][column] = SHIP;
				board[row][column + 1] = SHIP;
				board[row][column + 2] = SHIP;
				inserted += 3;
			}
		}
		else if (column > 2 && inserted < 3) {
			if ((isblank(board[row][column])) && (isblank(board[row][column - 1])) && (isblank(board[row][column - 2]))) {
				board[row][column] = SHIP;
				board[row][column - 1] = SHIP;
				board[row][column - 2] = SHIP;
				inserted += 3;
			}
		}
		else if (row < 4 && inserted == 3) {
			if ((isblank(board[row][column])) && (isblank(board[row + 1][column])) && (isblank(board[row + 2][column]))) {
				board[row][column] = SHIP;
				board[row +	1][column] = SHIP;
				board[row + 2][column] = SHIP;
				inserted += 3;
			}
		}
		else if (row > 2 && inserted == 3) {
			if ((isblank(board[row][column])) && (isblank(board[row - 1][column])) && (isblank(board[row - 2][column]))) {
				board[row][column] = SHIP;
				board[row - 1][column] = SHIP;
				board[row - 2][column] = SHIP;
				inserted += 3;
			}
		}
	} while (inserted < 6);

	makeBoard(numberOfShips, board, inserted);
}

int mainMenu(bool running) {
	int selection = 0;
	while (running) {
		std::cout << "1: Change the password\n" <<
			"2: Play battleship\n" <<
			"3: Quit\n" <<
			"Select an option(1 - 3) : ";
		std::cin >> selection;
		switch (selection) {
		case 1:
			changePassword();
			break;
		case 2:
			play();
			break;
		case 3:
			return selection;
			break;
		}
	}
}

int main()
{
	Login();
	system("cls");
	bool start = true;
	int stop;
	stop = mainMenu(start);
	if (stop == 3) {
		start = false;
		exit(0);
	}
}
