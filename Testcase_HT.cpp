#include "HashTable_2.h"
#include "HashTable_2.cpp"
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	//Подготовка консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	SetConsoleTextAttribute(hConsole, 9);

	//
	//Variables
	const short SIZEHT = 4;
	srand(static_cast<unsigned int>(time(NULL)));
	HashTable<string> ht(SIZEHT, 1.2, 2);
	string inputKey;
	string value;
	int choise;

	//Main Loop
	while (true)
	{
		cout << "Choose Action: 1: Insert    2: Erase    3:Get Element    4:Show Table    5: Exit\n";
		cin >> choise;
		cin.get();
		system("cls");
		switch (choise)
		{
		case 1: //Insert
		{
			cout << "KEY : ";
			getline(cin, inputKey, '\n');
			cout << "VALUE : ";
			getline(cin, value, '\n');
			ht.insert(inputKey, value);
			cout << "\n";
			break;
		}

		case 2: //Erase
		{
			cout << "KEY : ";
			getline(cin, inputKey, '\n');
			ht.erase(inputKey);
			cout << "\n";
			break;
		}
		case 3: //Get Element
		{
			try
			{
				cout << "KEY : ";
				getline(cin, inputKey, '\n');

				cout << "VALUE = " << ht.Get(inputKey) << endl;
			}
			catch (exception& ex)
			{
				cout << "\n" << ex.what() << "\n";
			}
 				break;
		}
		case 4: //Show Table
		{
			cout << "\nPRINT :\n";
			ht.printHT();
			break;
		}
		case 5: //Exit
		{
			exit(000111000);
		}
		}
	}
}