#include <iostream>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char fly[2][7] = { '>' , '<', '(' , '(' , '(' , '*', '>' , '_' , '_' , '_' , '_' , '_' , '_' , '_' };
int birdPos = 6;
int score = 0;

void gotoxy(int x, int y) {

	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {


	if (size == 0)
	{
		size = 20;
	}

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;

	SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);

	for (int i = 0; i < SCREEN_WIDTH; i++) {

		gotoxy(i, 0); cout << "+";
		gotoxy(i, SCREEN_HEIGHT); cout << "+";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {

		gotoxy(0, i); cout << "+";
		gotoxy(SCREEN_WIDTH, i); cout << "+";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {

		gotoxy(WIN_WIDTH, i); cout << "+";
	}
}

void genPipe(int ind) {

	gapPos[ind] = 3 + rand() % 14;
}

void drawPipe(int ind) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);

	if (pipeFlag[ind] == true) {

		for (int i = 0; i < gapPos[ind]; i++) {

			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "<->";
		}

		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {

			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "<->";
		}
	}
}

void erasePipe(int ind) {


	if (pipeFlag[ind] == true) {

		for (int i = 0; i < gapPos[ind]; i++) {

			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}

		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {

			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
	}
}

void drawBird() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);


	for (int i = 0; i < 2; i++) {

		for (int j = 0; j < 7; j++) {

			gotoxy(j + 2, i + birdPos); cout << fly[i][j];
		}
	}
}

void eraseBird() {

	for (int i = 0; i < 2; i++) {

		for (int j = 0; j < 7; j++) {

			gotoxy(j + 2, i + birdPos); cout << " ";
		}
	}
}

int collision() {

	if (pipePos[0] >= 61) {

		if (birdPos<gapPos[0] || birdPos > gapPos[0] + GAP_SIZE) {

			return 1;
		}
	}
	return 0;
}

void gameover() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);

	system("cls");
	cout << endl;

	cout << "\n\n\n\n\t\t\t\t Your score is " << score << endl;
	cout << "\n\t\t\t\t------  Better Luck Next Time !! -----------" << endl;
	cout << "\n\t\t\t\tPress any key to go back to menu.";

	_getch();
}

void updateScore() {

	gotoxy(WIN_WIDTH + 7, 6); cout << "Score: " << score << endl;
}

void instructions() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);

	system("cls");
	cout << "\n\n\n\n\t\t\t\tInstructions";
	cout << "\n\n\t\t\t\tThe Game Is Very Easy to Play";
	cout << "\n\t\t\t\t--Press spacebar to make fish fly";
	cout << "\n\n\n\n\t\t\t\t-Press any key to go back to menu.";

	_getch();
}

void play() {

	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;

	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);

	gotoxy(WIN_WIDTH + 4, 2); cout << "Save the Fish";
	gotoxy(WIN_WIDTH + 4, 3); cout << "From Red Pipes";
	gotoxy(WIN_WIDTH + 6, 5); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 7); cout << "----------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "Control";
	gotoxy(WIN_WIDTH + 7, 13); cout << "--------";
	gotoxy(WIN_WIDTH + 2, 14); cout << " Spacebar = jump";



	gotoxy(WIN_WIDTH + 1, 21); cout << "Designed By:";
	gotoxy(WIN_WIDTH + 2, 23); cout << "Umer Naveed";
	gotoxy(WIN_WIDTH + 2, 24); cout << "Aiman Fatima";
	gotoxy(WIN_WIDTH + 2, 25); cout << "Komal Ikhlaq";

	gotoxy(10, 5); cout << "Please enter any key to start";


	_getch();

	gotoxy(10, 5); cout << "                               ";

	while (1) {

		if (_kbhit()) {

			char ch = _getch();
			if (ch == 32) {

				if (birdPos > 3) {

					birdPos -= 3;
				}
			}
			if (ch == 27) {

				break;
			}
		}

		drawBird();
		drawPipe(0);
		drawPipe(1);
		if (collision() == 1) {

			gameover();
			return;
		}

		Sleep(100);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2) {

			gameover();
			return;
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42) {

			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}

		if (pipePos[0] > 68) {

			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}
	}
}

int main() {



	setcursor(0, 0);
	srand((unsigned)time(NULL));

	do {

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);


		system("cls");
		gotoxy(10, 5); cout << "-------------------------";
		gotoxy(10, 6); cout << "|     Save the Fish    |";
		gotoxy(10, 7); cout << "-------------------------";
		gotoxy(10, 9); cout << "1. Lets Start Game";
		gotoxy(10, 10); cout << "2. Open Instructions";
		gotoxy(10, 11); cout << "3. QUIT";
		gotoxy(10, 13); cout << "Select Option: ";

		char op = _getche();

		if (op == '1') play();
		else if (op == '2') instructions();
		else if (op == '3') exit(0);

	} while (1);

	return 0;
}