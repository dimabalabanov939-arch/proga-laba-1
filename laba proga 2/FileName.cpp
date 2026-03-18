#include<iostream>
#include<string>

using namespace std;

class Groups
{
public:
	string NameGroup;
	int unsigned quantity;
};
void menu1(Groups ArrStudents)
{
	cout << "======================================" << endl;
	cout << "=              CHOISE                =" << endl;
	cout << "======================================" << endl;
	cout << "1. Enter the data manually" << endl;
	cout << "2. Enter data via a .txt file" << endl;
	cout << "3. Enter data via a .bin file" << endl;
	cout << "Enter action number: " << endl;
	int k;
	cin >> k;
	if (cin.fail())
	{
		cout << "Input error! Please enter a number." << endl;
		cin.clear();
		cin.ignore(10000000, '\n');
	}
	else
	{
		cin.ignore(10000000, '\n');
	}
	switch (k)
	{
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	default:
		cout << "Invalid choice! Please enter 1, 2 or 3." << endl;
	}
}
void menu(Groups ArrStudents)
{
	while (1)
	{
		cout << "======================================" << endl;
		cout << "=               MENU                 =" << endl;
		cout << "======================================" << endl;
		cout << "1. Enter the data" << endl;
		cout << "2. Output data" << endl;
		cout << "3. Add data" << endl;
		cout << "4. Delete data" << endl;
		cout << "5. Calculating the size" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter action number: " << endl;
		int k;
		cin >> k;
		if (cin.fail())
		{
			cout << "Input error! Please enter a number." << endl;
			cin.clear();
			cin.ignore(10000000, '\n');
		}
		else
		{
			cin.ignore(10000000, '\n');
		}
		switch (k)
		{
		case 1:
			menu1(ArrStudents);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			cout << "Exiting program..." << endl;
			exit(0);
		default:
			cout << "Invalid choice! Please enter 1, 2, 3, 4, 5 or 6." << endl;
		}

	}
}
int main()
{
	Groups* ArrStudents;
	ArrStudents->quantity = 0;
	ArrStudents = new Groups[ArrStudents->quantity];

	menu(*ArrStudents);

	return 0;
}