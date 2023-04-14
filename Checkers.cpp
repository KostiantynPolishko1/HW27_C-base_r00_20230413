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

bool CheckStepPlayer1(char desk[8][8], int &x, int &y, int x1, int y1, int x2, int y2)
{
	if (desk[y2][x2] == '-' && (abs(x2 - x1) == 1 && abs(y2 - y1) == 1))
	{
			return true;
	}
	
	if (desk[y2][x2] == '-' && (abs(x2-x1) > 1 && abs(y2-y1) > 1))
	{
		x = (x1 + x2) / 2;
		y = (y1 + y2) / 2;
		
		if (desk[y][x] == 'Y')
			return true;
	}
}

void Player1(char desk[8][8])
{
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	int count = 0;
	bool tf = false;

	cout 
		<< "\nPlayer1:"
		<< "\n  select pos \"Checker\":\n";
	cout << "\t\tLetter: ";
	cin >> checker1.x;
	cout << "\t\tNumber: ";
	cin >> checker1.y;

	x1 = static_cast<int>(checker1.x) - 97;
	y1 = abs(checker1.y -= 8);
	desk[y1][x1] = '-';

	start1:
	cout
		<< "\nPlayer1:"
		<< "\n  select new pos \"Checker\":\n";
	cout << "\t\tLetter: ";
	cin >> checker1.x;
	cout << "\t\tNumber: ";
	cin >> checker1.y;

	x2 = static_cast<int>(checker1.x) - 97;
	y2 = abs(checker1.y -= 8);

	tf = CheckStepPlayer1(desk, x, y, x1, y1, x2, y2);
	if (tf)
	{
		desk[y2][x2] = 'X';
		if (abs(x2 - x1) > 1 && abs(y2 - y1) > 1)
		{
			desk[y][x] = '-';
			count++;
		}
	}
	else
	{
		cout << "\n\tNo step";
		goto start1;
	}
	
}

void Player2(char desk[8][8])
{
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;

	cout
		<< "\nPlayer2:"
		<< "\n  select pos \"Checker\":\n";
	cout << "\t\tLetter: ";
	cin >> checker2.x;
	cout << "\t\tNumber: ";
	cin >> checker2.y;

	x1 = static_cast<int>(checker2.x) - 97;
	y1 = abs(checker2.y -= 8);
	desk[y1][x1] = '-';

	cout
		<< "\nPlayer2:"
		<< "\n  select new pos \"Checker\":\n";
	cout << "\t\tLetter: ";
	cin >> checker2.x;
	cout << "\t\tNumber: ";
	cin >> checker2.y;

	x2 = static_cast<int>(checker2.x) - 97;
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
		if (i < 8)
		{
			cout << "  ";
			for (int j = 0; j < 8; j++)
				cout << " ---";
		}
		if (i < 7)
		cout << endl;
	}
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
			cout << "\n     ";
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