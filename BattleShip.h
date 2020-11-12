#pragma once
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

const int M = 6;
const int N = 6;
const char HIT = 'H';
const char MISS = 'M';

void printBoard(char(&c)[M][N]);
void printPlayerBoard(char (&a)[M][N], char (&b)[M][N], int, int, int&);
void Shoot(char(&Board)[M][N], int&, bool&, int&, int&, char(&AI_)[M][N], int&);
void play();
void makeBoard(int numberOfShips, char(&Board)[M][N], int largerships);
void makeBoard3(int numberOfShips, char(&board)[M][N]);

int randomRow() {
	srand(time(NULL));
	int selected = 0;
	selected = rand() % M + 1;
	selected--;
	return selected;
}

int randomColumn() {
	srand(time(NULL));
	int selected = 0;
	selected = rand() % N + 1;
	selected--;
	return selected;
}

void writeLetters(int Column) {
	char Letter;
	if (Column < 9) {
		Column += 65;
	}
	Letter = (char)Column;
	std::cout << Letter;
}

