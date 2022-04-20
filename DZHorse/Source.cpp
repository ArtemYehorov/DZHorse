#include <iostream>
#include <windows.h>
using namespace std;

const int k = 5; // chess board size

int ar[k][k];

const int shift_count = 8;

int step_back = 0;

void Steps()
{
	HANDLE d = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD STEP;
	STEP.X = 0;
	STEP.Y = 11;
	SetConsoleCursorPosition(d, STEP);
	SetConsoleTextAttribute(d, 10);
	cout << "Steps Back " << step_back << endl;
}

COORD shift[]
{
	{ 1, -2 }, { 2, -1 }, { 2, 1 }, { 1, 2 },
	{ -1, 2 }, { -2, 1 }, { -2, -1 }, { -1, -2 }
};

void show_state()
{
	COORD info{ 0, 1 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, info);
	SetConsoleTextAttribute(h, 10);
	for (int y = 0; y < k; y++)
	{
		for (int x = 0; x < k; x++)
		{
			cout << " \t" << ar[y][x];
		}
		cout << "\n\n";
	}
}

bool pony(int x, int y, int step)
{
	Steps();
	show_state();
	Sleep(1000);

	ar[y][x] = step;
	if (step >= k * k)
		return true;

	for (int i = 0; i < shift_count; i++)
	{
		if ((x + shift[i].X >= 0) && (x + shift[i].X < k) &&
			(y + shift[i].Y >= 0) && (y + shift[i].Y < k) &&
			(ar[y + shift[i].Y][x + shift[i].X] == 0))
		{
			if (pony(x + shift[i].X, y + shift[i].Y, step + 1))
				return true;
		}
	}

	ar[y][x] = 0;
	

	if (ar[y][x] == 0)
	{
		Steps();
		step_back++;

		show_state();
		Sleep(1000);

		MessageBox(NULL, TEXT("The horse is in trouble!"),TEXT("Stop!"), MB_OK);
	}

	return false;
}

int main()
{
	system("title Horse Move");
	int x, y;
	cout << "Put position, two numbers from 0 to " << k - 1 << ":\n";
	cin >> x >> y;
	if (x < 0 || x > k - 1) x = 0;
	if (y < 0 || y > k - 1) y = 0;
	system("cls");

	pony(x, y, 1);

	// results
	show_state();
	Steps();
	system("pause");
}