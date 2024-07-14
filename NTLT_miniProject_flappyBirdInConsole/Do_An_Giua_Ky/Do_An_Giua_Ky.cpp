#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

const int width = 30;
const int height = 20;
int birdX, birdY;
int obstacleX, obstacleGapY;
int score;
int highscore = 0;
bool gameOver;

void Setup() {
	gameOver = false;
	birdX = width / 5;
	birdY = height / 2;
	obstacleX = width;
	obstacleGapY = rand() % (height - 6) + 3;
	score = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == birdX && i == birdY)  
				cout << "*"; 
			else if (j == obstacleX && (i < obstacleGapY || i > obstacleGapY + 2)) // Khoảng trống có 3 ô
				cout << "|";
			else
				cout << " ";
		}
		cout << endl;
	}

		for (int j = 0; j < width; j++) {
			cout << "-"; 
		}
	cout << endl;

	cout << "Score: " << score << "    Highscore: " << highscore << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case ' ':
			birdY -= 3; //Khi nhấn phím space, chim bay lên 3 đơn vị
			break;

		}
	}
}

void Logic() {
	birdY++; //Chim rơi xuống mỗi lần lặp
	if (birdY > height || birdY < 0) gameOver = true;
	if (obstacleX == birdX) {
		if (birdY < obstacleGapY || birdY > obstacleGapY + 2) {
			gameOver = true; //Kiểm tra va chạm
		}
		else {
			score++;
		}
	}

	obstacleX--; // Di chuyển cột sang trái
	if (obstacleX < 0) { 
		obstacleX = width;
		obstacleGapY = rand() % (height - 6) + 3;
	}
}

void MainMenu() {
	system("cls");
	cout << "Chao mung den voi game Console Flappy Bird!" << endl;
	cout << "1. Choi Game" << endl;
	cout << "2. Luat Choi" << endl;
	cout << "3. Thoat" << endl;
	cout << "Lua chon cua ban: ";
}

void ShowRules() {
	system("cls");
	cout << "Luat Choi:" << endl;
	cout << "- Nhan phim space de chim bay." << endl;
	cout << "- Tranh cac vat can." << endl;
	cout << "- Choi dat muc diem cao nhat co the!" << endl << endl;
	system("pause"); 
}

int main() {
	char choice;
	while (true) {
		MainMenu();
		choice = _getch();

		if (choice == '1') {
			Setup();
			while (!gameOver) {
				Draw();
				Input();
				Logic();
				Sleep(100); 
			}

			if (score > highscore) {
				highscore = score;
			}
			cout << "Game Over! Diem cua ban: " << score << ". Diem cao nhat: " << highscore << endl;
			system("pause"); // Dừng màn hình để xem điểm
		}
		else if (choice == '2') {
			ShowRules();
		}
		else if (choice == '3') {
			break;
		}
	}
	return 0;
}