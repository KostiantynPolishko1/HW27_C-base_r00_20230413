#include<iostream>;
#include<Windows.h>;
using namespace std;

//Game "Checkers"
struct Checkers
{
	char player;
	char x;
	int y;

} checker1, checker2;

void dataPrint(char desk[8][8]);

void fillDesk(char desk[8][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			desk[i][j] = '-';

	for (int i = 0; i < 8; i++)
	{
		if (i < 3)
			for (int j = 0; j < 8; j++)
			{
				if (((i + j) % 2))
					desk[i][j] = 'Y';
			}
		if (i > 4)
			for (int j = 0; j < 8; j++)
			{
				if (((i + j) % 2))
					desk[i][j] = 'X';
			}
	}
}

void Player1(char desk[8][8])
{
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;

	cout 
		<< "\nPlayer1:"
		<< "\n select pos \"Checker\":\n";
	cout << "\tLetter: ";
	cin >> checker1.x;
	cout << "\tNumber: ";
	cin >> checker1.y;

	x1 = static_cast<int>(checker1.x) - 65;
	y1 = abs(checker1.y -= 8);
	desk[y1][x1] = '-';

	cout
		<< "\nPlayer1:"
		<< "\n select new pos \"Checker\":\n";
	cout << "\tLetter: ";
	cin >> checker1.x;
	cout << "\tNumber: ";
	cin >> checker1.y;

	x2 = static_cast<int>(checker1.x) - 65;
	y2 = abs(checker1.y -= 8);
	desk[y2][x2] = 'X';
}

void Player2(char desk[8][8])
{
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;

	cout
		<< "\nPlayer2:"
		<< "\n select pos \"Checker\":\n";
	cout << "\tLetter: ";
	cin >> checker2.x;
	cout << "\tNumber: ";
	cin >> checker2.y;

	x1 = static_cast<int>(checker2.x) - 65;
	y1 = abs(checker2.y -= 8);
	desk[y1][x1] = '-';

	cout
		<< "\nPlayer2:"
		<< "\n select new pos \"Checker\":\n";
	cout << "\tLetter: ";
	cin >> checker2.x;
	cout << "\tNumber: ";
	cin >> checker2.y;

	x2 = static_cast<int>(checker2.x) - 65;
	y2 = abs(checker2.y -= 8);
	desk[y2][x2] = 'Y';
}

void dataProcess(char desk[8][8])
{
	dataPrint(desk);

	//Move checkers trought the desk
	
	do
	{
		Player1(desk);
		system("CLS");
		dataPrint(desk);

		Player2(desk);
		system("CLS");
		dataPrint(desk);

	} while (true);


}

void dataPrint(char desk[8][8])
{
	char ch = 'A';

	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << 8 - i << " | ";
		for (int j = 0; j < 8; j++)
			cout << desk[i][j] << " | ";
		cout << endl << " ";
		if (i < 7)
		{
			cout << "  ";
			for (int j = 0; j < 8; j++)
				cout << " ---";
		}
		cout << endl;
	}
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
			cout << "col  ";
		cout << ch++ << "   ";
	}
	cout << endl;
}

int main()
{
	char arr[8][8]{};

	//Function
	fillDesk(arr);
	dataProcess(arr);
	//dataPrint(arr);

	return 0;
}