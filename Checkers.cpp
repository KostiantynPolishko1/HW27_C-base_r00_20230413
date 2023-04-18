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

void printResultTable(char desk[8][8], int nchecker, int count1, int count2, int &step1, int &step2);

int kickKing(char desk[8][8], int x1, int y1, int x2, int y2, char ch, int quarter);

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

bool CheckStepKing(char desk[8][8], int x1, int y1, int x2, int y2, char ch, int &quarter)
{
	bool tf = false;
	int dx = 0, dy = 0;
	char chop{};
	dx = x2 - x1;
	dy = y2 - y1;

	if (ch == 'X')
		chop = 'Y';
	if (ch == 'Y')
		chop = 'X';

	if (desk[y2][x2] == '#')
	{
		if (abs(dx) == abs(dy))
			tf = true;
	}
	else
		return false;

	if (dx < 0 && dy < 0)
		quarter = 1;
	if (dx > 0 && dy < 0)
		quarter = 2;
	if (dx > 0 && dy > 0)
		quarter = 3;
	if (dx < 0 && dy > 0)
		quarter = 4;

	if (tf)
	{
		//Checking free space for step of Dyke
		switch (quarter)
		{
		case 1:
			//I quarter - Up & Left
			for (int i = 1; i < abs(dx) - 1; i++)
			{
				if (desk[(y1 - i)][(x1 - i)] == ch)
					return false;
				if (desk[(y1 - i)][(x1 - i)] == chop && desk[(y1 - i) - 1][(x1 - i) - 1] == chop)
					return false;
			}
			break;
		case 2:
			//II quarter - Up & Right
			for (int i = 1; i < abs(dx) - 1; i++)
			{
				if (desk[(y1 - i)][(x1 + i)] == ch)
					return false;
				if (desk[(y1 - i)][(x1 + i)] == chop && desk[(y1 - i) - 1][(x1 + i) + 1] == chop)
					return false;
			}
			break;
		case 3:
			//III quarter - Down & Right
			for (int i = 1; i < abs(dx) - 1; i++)
			{
				if (desk[(y1 + i)][(x1 + i)] == ch)
					return false;
				if (desk[(y1 + i)][(x1 + i)] == chop && desk[(y1 + i) + 1][(x1 + i) + 1] == chop)
					return false;
			}

			break;
		case 4:
			//IV quarter - Down & Left
			for (int i = 1; i < abs(dx) - 1; i++)
			{
				if (desk[(y1 + i)][(x1 - i)] == ch)
					return false;
				if (desk[(y1 + i)][(x1 - i)] == chop && desk[(y1 + i) + 1][(x1 - i) - 1] == chop)
					return false;
			}
			break;
		default: return false;
		}
	}
	
	return true;
}

int stepKing(char desk[8][8], int x1, int y1, char dyke, char ch)
{
	int x = 0, y = 0, count = 0, quarter = 0;
	int x2, y2;
	bool tf;
restart2:
	tf = false;
	x2 = 0, y2 = 0;
	cout 
		<< "\n Your Turn, "
		<< (dyke == 'W' ? "White King " : "Black King ") << dyke
		<< "\n Enter direction: (Like a1, g6...) -> ";

	getline(cin, checker1.x);

	if (checker1.x.length() != 2)
	{
		cout << "\n\tIncorrectly entered";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart2;
	}

	if (checker1.x[0] == 'q' || checker1.x[0] == 'Q')
	{
		cout << "\n\t!!!Exit. Stop Game!!!\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		return -1;
	}

	x2 = static_cast<int>(checker1.x[0]) - 97;

	if (x2 < 0 || x2 > 7)
	{
		cout << "\nLetter is not respect to a...h\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart2;
	}

	y2 = static_cast<int>(checker1.x[1]) - 49;

	if (y2 < 0 || y2 > 7)
	{
		cout << "\n Number is out of 1...7\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart2;
	}

	y2 = abs(y2 -= 7);

	if (desk[y2][x2] != '#')
	{
		cout << "\n\tNo step";
		goto restart2;
	}

	tf = CheckStepKing(desk, x1, y1, x2, y2, ch, quarter);
	if (tf)
	{
		if(abs(x2-x1) > 1)
			count = kickKing(desk, x1, y1, x2, y2, ch, quarter);

		desk[y1][x1] = '#';
		desk[y2][x2] = dyke;
	}
	else
	{
		cout << "\n\tNo step";
		goto restart2;
	}

	return count;
}

int kickKing(char desk[8][8], int x1, int y1, int x2, int y2, char ch, int quarter)
{
	int dx = 0, dy = 0, nkick = 0;
	char chop{};
	dx = x2 - x1;
	dy = y2 - y1;

	if (ch == 'X')
		chop = 'Y';
	if (ch == 'Y')
		chop = 'X';

	//Checking free checkers for kick them by King
	switch (quarter)
	{
	case 1:
		//I quarter - Up & Left
		for (int i = 1; i < abs(dx); i++)
		{
			if (desk[(y1 - i)][(x1 - i)] == chop)
				{
					desk[(y1 - i)][(x1 - i)] = '#';
					nkick++;
				}
		}
		break;
	case 2:
		//II quarter - Up & Right
		for (int i = 1; i < abs(dx); i++)
		{
			if (desk[(y1 - i)][(x1 + i)] == chop)
				{
					desk[(y1 - i)][(x1 + i)] = '#';
					nkick++;
				}
		}
		break;
	case 3:
		//III quarter - Down & Right
		for (int i = 1; i < abs(dx); i++)
		{
			if (desk[(y1 + i)][(x1 + i)] == chop)
			{
				desk[(y1 + i)][(x1 + i)] = '#';
				nkick++;
			}
		}
		break;
	case 4:
		//IV quarter - Down & Left
		for (int i = 1; i < abs(dx); i++)
		{
			if (desk[(y1 + i)][(x1 - i)] == chop)
			{
				desk[(y1 + i)][(x1 - i)] = '#';
				nkick++;
			}
		}
		break;
	}

	return nkick;
}

int Player(char desk[8][8], char ch)
{
	int x = 0, y = 0;
	int x1, y1;
	int x2, y2;
	bool tf;
	char dyke{};

	if (ch == 'X')
		dyke = 'W';

	if (ch == 'Y')
		dyke = 'Z';

restart1:
	tf = false;
	x1 = 0, y1 = 0;
	cout 
		<< "\n Your Turn, "
		<< (ch == 'X'? "White checker " : "Black checker ") << ch
		<< "\n Enter position: (Like a1, g6...) -> ";

	getline(cin, checker1.x);

	if ((checker1.x[0] == 'q' || checker1.x[0] == 'Q') && checker1.x.length() == 1)
	{
		cout << "\n\t!!!EXIT. STOP GAME!!!\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		return -1;
	}
	
	if(checker1.x.length() != 2)
	{
		cout << "\n\tIncorrectly entered";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart1;
	}

	x1 = static_cast<int>(checker1.x[0]) - 97;

	if (x1 < 0 || x1 > 7)
	{
		cout << "\n Letter is out of a...h\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1);
		goto restart1;
	}

	y1 = static_cast<int>(checker1.x[1]) - 49;

	if (y1 < 0 || y1 > 7)
	{
		cout << "\n Number is out of 1...7\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart1;
	}
	y1 = abs(y1 -= 7);

	if (desk[y1][x1] == dyke)
	{
		return stepKing(desk, x1, y1, dyke, ch);
	}

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
		<< "\n Your Turn, "
		<< (ch == 'X' ? "White checker " : "Black checker ") << ch
		<< "\n Enter direction: (Like a1, g6...) -> ";

	getline(cin, checker1.x);

	if ((checker1.x[0] == 'q' || checker1.x[0] == 'Q') && checker1.x.length() == 1)
	{
		cout << "\n\t!!!Exit. Stop Game!!!\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		return -1;
	}

	if (checker1.x.length() != 2)
	{
		cout << "\n\tIncorrectly entered";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart2;
	}

	x2 = static_cast<int>(checker1.x[0]) - 97;

	if (x2 < 0 || x2 > 7)
	{
		cout << "\n Letter is out of a...h\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart2;
	}

	y2 = static_cast<int>(checker1.x[1]) - 49;

	if (y2 < 0 || y2 > 7)
	{
		cout << "\n Number is out of 1...7\n";
		cin.clear(); // then return the cin to 'normal' mode of operation
		cin.ignore(-1); // and remove the previous input values from the input buffer
		goto restart2;
	}
	y2 = abs(y2 -= 7);

	if (desk[y2][x2] != '#')
	{
		cout << "\n\tNo step";
		goto restart2;
	}

	tf = CheckStepPlayer(desk, x, y, x1, y1, x2, y2, ch);
	if (tf)
	{
		if ((ch == 'X' && y2 == 0) || (ch == 'Y' && y2 == 7))
		{
			desk[y2][x2] = dyke;
		}
		else
		{
			desk[y2][x2] = ch;
		}
		
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
	int count1 = 0, index1 = 0, step1 = 0;
	int count2 = 0, index2 = 0, step2 = 0;

	printResultTable(desk, nchecker, count1, count2, step1, step2);

	do
	{
		//Functions of Player1
		
		index1 = Player(desk, 'X');
		step1++;

		if (index1 == -1)
		{
			return 0;
		}
		count1 += index1;

		system("CLS");
		dataPrint(desk);
		printResultTable(desk, nchecker, count1, count2, step1, step2);
		
		if (count1 == nchecker)
		{
			cout << "\n\tWHITE CHECKER WON THE GAME!!!";
			return 0;
		}

		//Functions of Player2
		index2 = Player(desk, 'Y');
		step2++;

		if (index2 == -1)
		{
			return 0;
		}
		count2 += index2;

		system("CLS");
		dataPrint(desk);
		printResultTable(desk, nchecker, count1, count2, step1, step2);

		if (count2 == nchecker)
		{
			cout << "\n\tBLACK CHECKER WON THE GAME!!!";
			return 0;
		}

	} while (true);
}

void printResultTable(char desk[8][8], int nchecker, int count1, int count2, int &step1, int &step2)
{
	//Sample data for game result
	string descriptions[] = { "won", "remain", "steps", "king", "winner" };
	string dresult[5][2] = { {"-", "-"}, {"-", "-"}, {"-", "-"}, {"-", "-"}, {"-", "-"} };
	int size = 5;
	int whiteK = 0, blackK = 0;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (desk[i][j] == 'W')
				whiteK++;

			if (desk[i][j] == 'Z')

				blackK++;
		}

	count1 == 0 ? dresult[0][0] = "-" : dresult[0][0] = to_string(count1);
	count2 == 0 ? dresult[0][0] = "-" : dresult[0][1] = to_string(count2);

	dresult[1][0] = to_string(nchecker - count1);
	dresult[1][1] = to_string(nchecker - count2);

	step1 == 0 ? dresult[2][0] = "-" : dresult[2][0] = to_string(step1);
	step2 == 0 ? dresult[2][2] = "-" : dresult[2][1] = to_string(step2);
	
	whiteK == 0 ? dresult[3][0] = "-" : dresult[3][0] = to_string(whiteK);
	blackK == 0 ? dresult[3][1] = "-" : dresult[3][1] = to_string(blackK);
	
	if (count1 == nchecker)
		dresult[4][0] = "Play1";

	if (count2 == nchecker)
		dresult[4][0] = "Play2";

	//Displaying the table header
	cout
		<< "\n\t\tTABLE of DATA GAME"
		<< "\n\t -----------------------------------"
		<< "\n\t| Num | Description | White | Black |"
		<< "\n\t -----------------------------------" << endl;

	//Outputting game result data using a loop
	for (int i = 0; i < size; i++)
	{
		cout
			<< "\t|  " << (i + 1) << "  | "
			<< descriptions[i] << "\t    | "
			<< dresult[i][0] << (dresult[i][0].length() < 2 ? "     | " : "    | ")
			<< dresult[i][1] << (dresult[i][1].length() < 2 ? "     | " : "    | ") << endl;
	}
	cout << "\t -----------------------------------\n";
	cout << "\n\t(Q - STOP GAME.)" << endl;
}

void dataPrint(char desk[8][8])
{
	char ch = 'A';

	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
		{
			cout << "\t  ";
			for (int j = 0; j < 8; j++)
				cout << " ---";
			cout << endl;
		}
		
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