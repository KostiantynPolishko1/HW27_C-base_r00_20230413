#include<iostream>
#include<string>

using namespace std;

void printResultTable(const string descriptions[], const string(*whites)[2], const string(*blacks)[2], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << "|  " << (i + 1) << "  | " << descriptions[i];
		for (int j = 0; j < (16 - descriptions[i].length()); ++j)
		{
			cout << ' ';
		}
		
		cout << " | " << whites[i][0];
		for (int j = 0; j < (14 - whites[i][0].length()); ++j)
		{
			cout << ' ';
		}

		cout << " | " << blacks[i][0];
		for (int j = 0; j < (14 - blacks[i][0].length()); ++j)
		{
			cout << ' ';

		}

		cout << " |" << endl;
		cout << "|     | ";
		for (int j = 0; j < 16; ++j)
		{
			cout << ' ';
		}

		cout << " | " << whites[i][1];
		for (int j = 0; j < (14 - whites[i][1].length()); ++j)
		{
			cout << ' ';
		}

		cout << " | " << blacks[i][1];
		for (int j = 0; j < (14 - blacks[i][1].length()); ++j)
		{
			cout << ' ';
		}
		cout << " |" << endl;

	}

	cout << "----------------------------------------------------------" << endl;

}

int main()
{
	string descriptions[] = { "won", "remain", "steps", "king", "winner" };
	string whites[5][2] = { {"Player 1", " "}, {" ", " "}, {" ", " "}, {" ", " "}, {" ", " "} };
	string blacks[5][2] = { {"Player 2", " "}, {" ", " "}, {" ", " "}, {" ", " "}, {" ", " "} };
	int size = sizeof(descriptions) / sizeof(descriptions[0]);

	cout << "----------------------------------------------------------" << endl;
	cout << "| Num |    Description    |     White     |     Black     |" << endl;
	cout << "----------------------------------------------------------" << endl;

	printResultTable(descriptions, whites, blacks, size);

	return 0;
}
