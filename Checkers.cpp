#include<iostream>;
#include<cstdint>;
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
		{
			if ((i + j) % 2)
				desk[i][j] = '#';
			else
				desk[i][j] = '-';
		}
			

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

bool CheckPosPlayer(char desk[8][8], int x1, int y1, char checker)
{
	char ch{};
	if (checker == 'X')
		ch = 'Y';
	else
		ch = 'X';

	//Checking free space for step checker X
	//I quarter - Up & Left
	if (desk[y1 - 1][x1 - 1] == '#' && checker == 'X')
		return true;
	if ((desk[(y1 - 1)][(x1 - 1)] == ch) && (desk[y1 - 2][x1 - 2] == '#'))	//to kick X & Y
		return true;

	//II quarter - Up & Right
	if (desk[y1 - 1][x1 + 1] == '#' && checker == 'X')
		return true;
	if ((desk[y1 - 1][x1 + 1] == ch) && (desk[y1 - 2][x1 + 2] == '#'))	//to kick X & Y
		return true;

	//III quarter - Down & Right
	if (desk[y1 + 1][x1 + 1] == '#' && checker == 'Y')
		return true;
	if ((desk[y1 + 1][x1 + 1] == ch) && (desk[y1 + 2][x1 + 2] == '#'))	//to kick X & Y
		return true;

	//IV quarter - Down & Left
	if (desk[y1 + 1][x1 - 1] == '#' && checker == 'Y')
		return true;
	if ((desk[y1 + 1][x1 - 1] == ch) && (desk[y1 + 2][x1 - 2] == '#'))	//to kick X & Y
		return true;

	return false;
}

bool CheckStepPlayer(char desk[8][8], int &x, int &y, int x1, int y1, int x2, int y2, char ch)
{
	if (desk[y2][x2] == '#' && (abs(x2 - x1) == 1 && abs(y2 - y1) == 1))
	{
		if (ch == 'X')
		{
			if (y2 < y1)
				return true;
		}
		else
			if (y2 > y1)
				return true;
	}

	if (desk[y2][x2] == '#' && (abs(x2-x1) > 1 && abs(y2-y1) > 1))
	{
		x = (x1 + x2) / 2;
		y = (y1 + y2) / 2;
		
		if (ch == 'X')
		{
			if (desk[y][x] == 'Y')
				return true;
		}
		else
			if (desk[y][x] == 'X')
				return true;
	}

	return false;
}

void Player(char desk[8][8], char ch)
{
	int x = 0, y = 0;
	int x1, y1;
	int x2, y2;
	bool tf;

start1:
	tf = false;
	x1 = 0, y1 = 0;
	cout 
		<< "\nPlayer " << ch << ": "
		<< "\n  select pos \"Checker\":\n";
	cout << "\t\tLetter: ";
	cin >> checker1.x;
	cout << "\t\tNumber: ";
	cin >> checker1.y;

	x1 = static_cast<int>(checker1.x) - 97;
	y1 = abs(checker1.y -= 8);

	tf = CheckPosPlayer(desk, x1, y1, ch);

	if (tf)
	{
		if (desk[y1][x1] == ch)
			desk[y1][x1] = '#';
		else
		{
			cout << "\n\tNo step";
			goto start1;
		}
	}
	else
	{
		cout << "\n\tNo step";
		goto start1;
	}


start2:
	tf = false;
	x2 = 0, y2 = 0;
	cout
		<< "\nPlayer " << ch << ": "
		<< "\n  select new pos \"Checker\":\n";
	cout << "\t\tLetter: ";
	cin >> checker1.x;
	cout << "\t\tNumber: ";
	cin >> checker1.y;

	x2 = static_cast<int>(checker1.x) - 97;
	y2 = abs(checker1.y -= 8);

	if (desk[y2][x2] != '#')
	{
		cout << "\n\tNo step";
		goto start2;
	}

	tf = CheckStepPlayer(desk, x, y, x1, y1, x2, y2, ch);
	if (tf)
	{
		desk[y2][x2] = ch;
		if (abs(x2 - x1) > 1 && abs(y2 - y1) > 1)
		{
			desk[y][x] = '#';
		}
	}
	else
	{
		cout << "\n\tNo step";
		goto start2;
	}
	
}

void dataProcess(char desk[8][8])
{
	dataPrint(desk);

	//Move checkers trought the desk
	
	do
	{
		//Functions of Players
		Player(desk, 'X');
		system("CLS");
		dataPrint(desk);

		Player(desk, 'Y');
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
		cout << "\t" << 8 - i << " | ";
		for (int j = 0; j < 8; j++)
			cout << desk[i][j] << " | ";
		cout << endl << " ";
		if (i < 8)
		{
			cout << "\t  ";
			for (int j = 0; j < 8; j++)
				cout << " ---";
		}
		if (i < 7)
		cout << endl;
	}
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
			cout << "\n\t    ";
		cout << ch++ << "   ";
	}
	cout << endl;
}

int main()
{
	char arr[8][8]{};

	//Functions
	fillDesk(arr);
	dataProcess(arr);
	//dataPrint(arr);

	return 0;
}