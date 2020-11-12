#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <vector>

char movetoget(int& x, int& y, const char (&arr)[4][4], char key) {
	key = toupper(key);

	if (key == 'W' && !(y == 0)) {
		y--;
	}
	else if (key == 'S' && !(y == 4))
	{
		y++;
	}
	else if (key == 'D' && !(x == 4)) {
		x++;
	}
	else if (key == 'A' && !(x == 0)) {
		x--;
	}
	return arr[y][x];
}

void Login() {
	bool corect = false;
	char key;
	const char indicator = '*';
	std::string filename = "Passcode.txt";
	std::fstream File(filename, std::fstream::in);

	std::string Passcode;
	const char bord[4][4] = {{'A','B','C','D'},{'E','F','G','H'},{'I','J','K','L'},{'M','N','O','P'}};
	std::vector <char> EnterCode = {'A'};

	if (File) {
		perror("Passcode");
		File >> Passcode;
		int x = 0;
		int y = 0;
		int num = 0;

		while (!corect)
		{
			system("cls");


			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == y && j == x) {
						std::cout << " | " << indicator;
					}
					else {
						std::cout << " | " << bord[i][j];
					}
				}
				std::cout << " |\n";
			}

			key = _getch();

			EnterCode.push_back(movetoget(x, y, bord, key));
			num++;

			if (EnterCode.at(num) != (char)Passcode[num]) {
				int& ax = x;
				int& ay = y;
				ax = 0;
				ay = 0;
				num = 0;
				EnterCode.clear();
				EnterCode.push_back('A');
			}

			if (num == Passcode.size() - 1) {
				return;
			}
		}
	}
	else {
		perror("Passcode");
	}
	File.close();
}

void changePassword() {
	system("cls");
	std::string Filename = "Passcode.txt";
	std::fstream File(Filename, std::fstream::out);
	const char bord[4][4] = { {'A','B','C','D'},{'E','F','G','H'},{'I','J','K','L'},{'M','N','O','P'} };

	std::vector <char> NewPassword = { 'A' };
	const char indicator = '*';
	int x = 0;
	int y = 0;

	char key = 'y';

	if (File) {
		std::cout << "Input new password(Enter with(WASD), (Q)to finnish):\n";

		while (key != 'Q') {
			system("cls");
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == y && j == x) {
						std::cout << " | " << indicator;
					}
					else {
						std::cout << " | " << bord[i][j];
					}
				}
				std::cout << " |\n";
			}

			key = _getch();
			key = toupper(key);
			if (key == 'W' || key == 'A' || key == 'S' || key == 'D') {
				NewPassword.push_back(movetoget(x, y, bord, key));
			}
		}

		std::cout << "Your new password is ";
		for (int i = 0; i < NewPassword.size(); i++) {
			std::cout << NewPassword.at(i);
		}
		std::cout << ". Save it?(Y/N)\n";
		key = _getch();
		key = toupper(key);

		if (key == 'Y')
		{
			for (int i = 0; i < NewPassword.size(); i++) {
				File << NewPassword.at(i);
			}
		}
	}
	else {
		perror("Passcode");
	}

	File.close();
	return;
}