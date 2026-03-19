#include<iostream>
#include<string>

using namespace std;

class Groups
{
public:
	string NameGroupe;
	int unsigned quantity;
};
void CheckCin()
{
	if (cin.fail())
	{
		cout << "Input error! Please enter a number." << endl;
		cin.clear();
		cin.ignore(10000000, '\n');
	}
	else
	{

	}
}

void AddGroupe(Groups*& ArrGroupe, int& size)
{
	Groups* temp_mas = new Groups[size + 1];

	for (int i = 0; i < size; i++)
	{
		temp_mas[i] = ArrGroupe[i];
	}

	cout << "\nEnter the name groupe: ";
	cin.ignore(10000000, '\n');
	getline(cin, temp_mas[size].NameGroupe);
	cout << "\nEnter quantity students  (quantity < 30!!!): ";
	while(!(cin >> temp_mas[size].quantity))
	    {
		CheckCin();
		}
	while(temp_mas[size].quantity > 30)
	{
	    cout << "Error!!! Quantity cannot exceed 30!!! Enter quantity students again: ";
		cin >> temp_mas[size].quantity;
	}


	delete[] ArrGroupe;


	ArrGroupe = temp_mas;
	size ++;
	cout << "Group added successfully!\n";
}
void EnterDataManually(Groups *&ArrGroupe, int& size)
{
	bool Flag = false;
	while (Flag == false)
	{
		cout << "\n1. Add group" << endl;
		cout << "2. Return to the menu" << endl;
		int n = 0;
		cin >> n;
		CheckCin();
		switch (n)
		{
		case 1:
			AddGroupe(ArrGroupe, size);
			break;
		case 2:
			Flag = true;
			break;
		default:
			cout << "Invalid choice! Please enter 1 or 2." << endl;

		}
	}
}

void menu1(Groups *ArrGroupe, int size)
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
	CheckCin();
	switch (k)
	{
	case 1:
		EnterDataManually (ArrGroupe, size);
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		cout << "Invalid choice! Please enter 1, 2 or 3." << endl;
	}
}
void menu(Groups *ArrGroupe, int size)
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
			menu1(ArrGroupe, size);
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
	int size = 0;
	Groups* ArrGroupe = new Groups[size];

	menu(ArrGroupe, size);

	return 0;
}