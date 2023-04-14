#include<iostream>;
#include<cstdint>;
#include<cstdlib>
#include<string>;
#include<Windows.h>;
using namespace std;

//Game "Checkers"
struct Checkers
{
	char player;
	int y;
	string x;

} checker1, checker2;

void dataPrint(char desk[8][8]);

int checkV()
{
	int a;
	while (true) // the cycle continues until the user enters the correct value
	{
		cin >> a;
		if (cin.fail()) // if the previous extraction was unsuccessful,
		{
			cout << "Incorrect input. Enter int value: ";
			cin.clear(); // then return the cin to 'normal' mode of operation
			cin.ignore(32767, '\n'); // and remove the previous input values from the input buffer
		}
		else // if all is well, return a
		{
			cin.ignore(32767, '\n'); // and remove the previous input values from the input buffer
			return a;
		}
	}

	return 0;
}

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

int Player(char desk[8][8], char ch)
{
	int x = 0, y = 0;
	int x1, y1;
	int x2, y2;
	bool tf;

restart1:
	tf = false;
	x1 = 0, y1 = 0;
	cout 
		<< (ch == 'X'? "\n  White checker " : "\n  Black checker ") << ch
		<< " (Q - STOP GAME.)"
		<< "\n  select pos:";
	cout << "\n\tLetter: ";
	getline(cin, checker1.x);
	if(checker1.x.length() > 1)
	{
		cout << "\n\tIncorrectly entered";
		goto restart1;
	}

	if (checker1.x[0] == 'q' || checker1.x[0] == 'Q')
	{
		cout << "\n\t!!!EXIT. STOP GAME!!!\n";
		return -1;
	}

	x1 = static_cast<int>(checker1.x[0]) - 97;

	if (x1 < 0 || x1 > 7)
	{
		cout << "\nLetter is not respect to a...h\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(32767, '\n');
		goto restart1;
	}

	cout << "\tNumber: ";
	checker1.y = checkV();

	y1 = abs(checker1.y -= 8);

	tf = CheckPosPlayer(desk, x1, y1, ch);

	if (tf)
	{
		if (desk[y1][x1] == ch)
			desk[y1][x1] = '#';
		else
		{
			cout << "\n\tNo step";
			goto restart1;
		}
	}
	else
	{
		cout << "\n\tNo step";
		goto restart1;
	}


restart2:
	tf = false;
	x2 = 0, y2 = 0;
	cout
		<< (ch == 'X' ? "\n  White checker " : "\n  Black checker ") << ch
		<< " (Q - STOP GAME.)"
		<< "\n  indicate pos:\n";
	cout << "\tLetter: ";
	getline(cin, checker1.x);
	if (checker1.x.length() > 1)
	{
		cout << "\n\tIncorrectly entered";
		goto restart2;
	}

	if (checker1.x[0] == 'q' || checker1.x[0] == 'Q')
	{
		cout << "\n\t!!!Exit. Stop Game!!!\n";
		return -1;
	}

	x2 = static_cast<int>(checker1.x[0]) - 97;

	if (x2 < 0 || x2 > 7)
	{
		cout << "\nLetter is not respect to a...h\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(32767, '\n');
		goto restart2;
	}
	cout << "\tNumber: ";
	checker1.y = checkV();

	y2 = abs(checker1.y -= 8);

	if (desk[y2][x2] != '#')
	{
		cout << "\n\tNo step";
		goto restart2;
	}

	tf = CheckStepPlayer(desk, x, y, x1, y1, x2, y2, ch);
	if (tf)
	{
		desk[y2][x2] = ch;
		if (abs(x2 - x1) > 1 && abs(y2 - y1) > 1)
		{
			desk[y][x] = '#';
			return 1;
		}
	}
	else
	{
		cout << "\n\tNo step";
		goto restart2;
	}

	return 0;
}

int dataProcess(char desk[8][8], int nchecker)
{
	dataPrint(desk);
	//Move checkers trought the desk
	int count1 = 0, index1 = 0;
	int count2 = 0, index2 = 0;
	
	do
	{

		//Functions of Player1
		
		index1 = Player(desk, 'X');
		if (index1 == -1)
		{
			return 0;
		}
		count1 += index1;

		system("CLS");
		dataPrint(desk);
		cout << "\n\tQty of won Black Checker: " << count1;
		cout << "\n\t\t\tRemain: " << nchecker - count1 << endl;

		//Functions of Player1
		index2 = Player(desk, 'Y');
		if (index2 == -1)
		{
			return 0;
		}
		count2 += index2;

		system("CLS");
		dataPrint(desk);
		cout << "\n\tQty of won White Checker: " << count2;
		cout << "\n\t\t\tRemain: " << nchecker - count2 << endl;

	} while (count1 < nchecker || count2 < nchecker);
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
	int nchecker = 12;

	//Functions
	fillDesk(arr);
	dataProcess(arr, nchecker);

	return 0;
}