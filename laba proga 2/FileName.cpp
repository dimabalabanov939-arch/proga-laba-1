#include<iostream>
#include<cmath>
#include <fstream>
#include <cstring>

using namespace std;

struct Groups
{
	char NameGroupe[100];
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
}

void AddGroupe(Groups*& ArrGroupe, int &size)
{
	Groups* temp_mas = new Groups[size + 1];

	for (int i = 0; i < size; i++)
	{
		temp_mas[i] = ArrGroupe[i];
	}

	cout << "\nEnter the name groupe: ";
	cin.ignore(10000000, '\n');
	cin.getline(temp_mas[size].NameGroupe, 100);
	cout << "\nEnter quantity students  (quantity < 30!!!): ";
	cin >> temp_mas[size].quantity;
	while (cin.fail() || temp_mas[size].quantity > 30 || temp_mas[size].quantity <= 0) 
	{
		if (cin.fail()) {
			cout << "Error! Please enter a number! ";
		}
		else if (temp_mas[size].quantity > 30) {
			cout << "Error!!! Quantity cannot exceed 30!!! ";
		}
		else if (temp_mas[size].quantity <= 0) {
			cout << "Error!!! Quantity must be positive!!! ";
		}
		cout << "Enter quantity students again: ";
		cin >> temp_mas[size].quantity;
		CheckCin();
	}


	delete[] ArrGroupe;


	ArrGroupe = temp_mas;
	size ++;
	cout << "Group added successfully!\n";
}
void EnterDataManually(Groups*& ArrGroupe, int &size)
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
void OutputInConsole(Groups *ArrGroupe, int &size)
{
	cout << "1. Output all" << endl;
	cout << "2. Output one" << endl;
	cout << "Enter action number: " << endl;
	int k;
	int n = 0;
	cin >> k;
	CheckCin();

	switch (k)
	{
	case 1:
		for (int i = 0; i < size; i++)
		{
			cout << endl << i + 1 << ". Name groupe: " <<  ArrGroupe[i].NameGroupe << "\n Quantity students: " << ArrGroupe[i].quantity << endl;
		}
		break;
	case 2:
		cout << "\nEnter number group: ";
		cin >> n;
		CheckCin();
		cout << n << ". Name groupe: " << ArrGroupe[n - 1].NameGroupe << "\n Quantity students: " << ArrGroupe[n - 1].quantity << endl;
		break;
	default:
		cout << "Invalid choice! Please enter 1 or 2." << endl;
	}
}
void OutputInTxtFile(Groups* ArrGroupe, int& size)
{
	if (size == 0)
	{
		cout << "Error: No data to write. The array is empty." << endl;
		return;
	}

	char filename[256];
	cout << "Enter the name of the .txt file to save: ";
	cin.ignore(10000000, '\n');
	cin.getline(filename, 256);

	ofstream file(filename);

	if (!file.is_open())
	{
		cout << "Error: Unable to create/open file " << filename << endl;
		return;
	}

	file << "=== GROUPS DATA ===" << endl;
	file << "Total groups: " << size << endl;
	file << "===================" << endl << endl;

	for (int i = 0; i < size; i++)
	{
		file << "Group #" << i + 1 << ":" << endl;
		file << "Name: " << ArrGroupe[i].NameGroupe << endl;
		file << "Quantity of students: " << ArrGroupe[i].quantity << endl;
		file << "-------------------" << endl;
	}

	file.close();

	cout << "Successfully wrote " << size << " groups to file " << filename << endl;
}
void OutputInBinFile(Groups* ArrGroupe, int& size)
{
	if (size == 0)
	{
		cout << "Error: No data to write. The array is empty." << endl;
		return;
	}

	char filename[256];
	cout << "Enter the name of the .bin file to save: ";
	cin.ignore(10000000, '\n');
	cin.getline(filename, 256);

	ofstream file(filename, ios::binary);

	if (!file.is_open())
	{
		cout << "Error: Unable to create/open file " << filename << endl;
		return;
	}

	file.write(reinterpret_cast<char*>(&size), sizeof(size));

	for (int i = 0; i < size; i++)
	{
		file.write(reinterpret_cast<char*>(&ArrGroupe[i].quantity), sizeof(ArrGroupe[i].quantity));

		int nameLength = strlen(ArrGroupe[i].NameGroupe) + 1;
		file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

		file.write(ArrGroupe[i].NameGroupe, nameLength);
	}

	file.close();

	cout << "Successfully wrote " << size << " groups to binary file " << filename << endl;
}
void ReadTxtFile(Groups*& ArrGroupe, int& size)
{
	char filename[256];
	cout << "Enter the name of the .txt file: ";
	cin.ignore(10000000, '\n');
	cin.getline(filename, 256);

	ifstream file(filename);

	if (!file.is_open())
	{
		cout << "Error: Unable to open file " << filename << endl;
		return;
	}
		
	int count = 0;
	char buffer[100];
	int tempQuantity;

	Groups* tempArr = nullptr;
	int tempSize = 0;


	while (file.getline(buffer, 100))
	{

		if (strlen(buffer) == 0)
			continue;


		if (!(file >> tempQuantity))
		{
			cout << "Error: Invalid data format in file. Skipping group: " << buffer << endl;
			file.clear();
			file.ignore(10000000, '\n');
			continue;
		}

		file.ignore(10000000, '\n');

		if (tempQuantity <= 0 || tempQuantity > 30)
		{
			cout << "Error: Invalid quantity (" << tempQuantity << ") for group \"" << buffer
				<< "\". Quantity must be between 1 and 30. Skipping this group." << endl;
			continue;
		}

		Groups* newArr = new Groups[tempSize + 1];

		for (int i = 0; i < tempSize; i++)
		{
			newArr[i] = tempArr[i];
		}

		strcpy_s(newArr[tempSize].NameGroupe, buffer);
		newArr[tempSize].quantity = tempQuantity;

		delete[] tempArr;


		tempArr = newArr;
		tempSize++;
	}

	file.close();

	if (tempSize > 0)
	{
		if (ArrGroupe != nullptr)
			delete[] ArrGroupe;

		ArrGroupe = tempArr;
		size = tempSize;

		cout << "Successfully read " << size << " groups from file " << filename << endl;
	}
	else
	{
		cout << "No data read from file " << filename << endl;
		if (tempArr != nullptr)
			delete[] tempArr;
	}
}
void ReadBinFile(Groups*& ArrGroupe, int& size)
{
	char filename[256];
	cout << "Enter the name of the .bin file: ";
	cin.ignore(10000000, '\n');
	cin.getline(filename, 256);

	ifstream file(filename, ios::binary);

	if (!file.is_open())
	{
		cout << "Error: Unable to open file " << filename << endl;
		return;
	}

	int readSize;
	file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));

	if (file.fail())
	{
		cout << "Error: Failed to read data from binary file." << endl;
		file.close();
		return;
	}

	if (readSize <= 0)
	{
		cout << "Error: Invalid data in file (size = " << readSize << ")" << endl;
		file.close();
		return;
	}

	Groups* tempArr = nullptr;
	int tempSize = 0;

	for (int i = 0; i < readSize; i++)
	{
		int quantity;
		file.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));

		if (file.fail())
		{
			cout << "Error: Failed to read quantity for group " << i + 1 << endl;
			delete[] tempArr;
			file.close();
			return;
		}

		if (quantity <= 0 || quantity > 30)
		{
			cout << "Error: Invalid quantity (" << quantity << ") for group " << i + 1
				<< ". Quantity must be between 1 and 30. Skipping this group." << endl;

			int nameLength;
			file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
			if (file.fail())
			{
				cout << "Error: Failed to skip invalid group data." << endl;
				delete[] tempArr;
				file.close();
				return;
			}

			file.seekg(nameLength, ios::cur);
			if (file.fail())
			{
				cout << "Error: Failed to skip invalid group data." << endl;
				delete[] tempArr;
				file.close();
				return;
			}
			continue;
		}

		int nameLength;
		file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

		if (file.fail() || nameLength <= 0 || nameLength > 100)
		{
			cout << "Error: Invalid name length for group " << i + 1 << endl;
			delete[] tempArr;
			file.close();
			return;
		}

		char* buffer = new char[nameLength];
		file.read(buffer, nameLength);

		if (file.fail())
		{
			cout << "Error: Failed to read group name for group " << i + 1 << endl;
			delete[] buffer;
			delete[] tempArr;
			file.close();
			return;
		}

		if (strlen(buffer) == 0)
		{
			cout << "Error: Empty group name for group " << i + 1 << ". Skipping." << endl;
			delete[] buffer;
			continue;
		}

		Groups* newArr = new Groups[tempSize + 1];

		for (int j = 0; j < tempSize; j++)
		{
			newArr[j] = tempArr[j];
		}

		strcpy_s(newArr[tempSize].NameGroupe, buffer);
		newArr[tempSize].quantity = quantity;

		delete[] buffer;
		delete[] tempArr;

		tempArr = newArr;
		tempSize++;
	}

	file.close();

	if (tempSize > 0)
	{
		if (ArrGroupe != nullptr)
			delete[] ArrGroupe;

		ArrGroupe = tempArr;
		size = tempSize;

		cout << "Successfully read " << size << " groups from binary file " << filename << endl;
	}
	else
	{
		cout << "No valid data read from binary file " << filename << endl;
		if (tempArr != nullptr)
			delete[] tempArr;
	}
}
void menu1(Groups*& ArrGroupe, int &size)
{
	cout << "======================================" << endl;
	cout << "=              CHOICE                =" << endl;
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
		ReadTxtFile(ArrGroupe, size);
		break;
	case 3:
		ReadBinFile(ArrGroupe, size);
		break;
	default:
		cout << "Invalid choice! Please enter 1, 2 or 3." << endl;
	}
}
void menu2(Groups* ArrGroupe, int &size)
{
	cout << "======================================" << endl;
	cout << "=              CHOISE                =" << endl;
	cout << "======================================" << endl;
	cout << "1. Output the data in console" << endl;
	cout << "2. Output data in a .txt file" << endl;
	cout << "3. Output data in a .bin file" << endl;
	cout << "Enter action number: " << endl;
	int k;
	cin >> k;
	CheckCin();
	switch (k)
	{
	case 1:
		OutputInConsole(ArrGroupe, size);
		cout << "\nPress Enter to continue...";
		cin.ignore(10000000, '\n');
		cin.get();
		break;
	case 2:
		OutputInTxtFile(ArrGroupe, size);
		break;
	case 3:
		OutputInBinFile(ArrGroupe, size);
		break;
	default:
		cout << "Invalid choice! Please enter 1, 2 or 3." << endl;
	}
}
void menu3(Groups*& ArrGroupe, int& size)
{
	cout << "Enter number groups for delete: ";
	int n = 0;
	cin >> n;
	while (cin.fail() || n < 1 || n > size)
	{
		if (cin.fail()) {
			cout << "Error! Please enter a number! ";
		}
		else if (n < 1) 
		{
			cout << "Error!!! Number groups can not be < 1! ";
		}
		else if (n > size) 
		{
			cout << "Error!!! Please enter number < " << size << "! ";
		}
		cout << "Enter number groups again: ";
		cin >> n;
		CheckCin();
	}
	Groups* newArr = new Groups[size - 1];

	int newIndex = 0;
	for (int i = 0; i < size; i++)
	{
		if (i != n - 1) 
		{
			newArr[newIndex] = ArrGroupe[i];
			newIndex++;
		}
	}

	delete[] ArrGroupe;

	ArrGroupe = newArr;
	size--;

	cout << "Group successfully deleted!" << endl;
}
void menu4(Groups*& ArrGroupe, int& size)
{
	cout << "1. Calculating the size .txt file" << endl;
	cout << "2. Calculating the size .bin file" << endl;
	cout << "Enter action number: " << endl;
	int k;
	cin >> k;
	if (cin.fail())
	{
		cout << "Input error! Please enter a number." << endl;
		cin.clear();
		cin.ignore(10000000, '\n');
	}

	char filename[256];

	switch (k)
	{
	case 1:
	{
		cout << "Enter the name of the .txt file: ";
		cin.ignore(10000000, '\n');
		cin.getline(filename, 256);

		ifstream txtFile(filename, ios::binary | ios::ate);
		if (txtFile.is_open())
		{
			cout << ".txt file size: " << txtFile.tellg() << " bytes" << endl;
			txtFile.close();
		}
		else
		{
			cout << "Error: Unable to open .txt file" << endl;
		}
		break;
	}
	case 2:
	{
		cout << "Enter the name of the .bin file: ";
		cin.ignore(10000000, '\n');
		cin.getline(filename, 256);

		ifstream binFile(filename, ios::binary | ios::ate);
		if (binFile.is_open())
		{
			cout << ".bin file size: " << binFile.tellg() << " bytes" << endl;
			binFile.close();
		}
		else
		{
			cout << "Error: Unable to open .bin file" << endl;
		}

		cout << "\nPress Enter to continue...";
		cin.get();
		break;
	}
	default:
		cout << "Invalid choice! Please enter 1 or 2." << endl;
	}
}
void menu(Groups *&ArrGroupe, int &size)
{
	while (1)
	{
		cout << "======================================" << endl;
		cout << "=               MENU                 =" << endl;
		cout << "======================================" << endl;
		cout << "1. Enter the data" << endl;
		cout << "2. Output data" << endl;
		cout << "3. Delete data" << endl;
		cout << "4. Calculating the size" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter action number: " << endl;
		int k;
		cin >> k;
		if (cin.fail())
		{
			cout << "Input error! Please enter a number." << endl;
			cin.clear();
			cin.ignore(10000000, '\n');
		}
		switch (k)
		{
		case 1:
			menu1(ArrGroupe, size);
			break;
		case 2:
			menu2(ArrGroupe, size);
			break;
		case 3:
			menu3(ArrGroupe, size);
			break;
		case 4:
			menu4(ArrGroupe, size);
			break;
		case 5:
			cout << "Exiting program..." << endl;
			exit(0);
			break;
		default:
			cout << "Invalid choice! Please enter 1, 2, 3, 4, 5 or 6." << endl;
		}

	}
}
int main()
{
	int size = 0;
	Groups* ArrGroupe = nullptr;

	menu(ArrGroupe, size);

	return 0;
}