#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#define SIZE 100;
using namespace std;

string currentUser;
void menu();
void readTransaction(double& balance, string date[], double amount[], int& count);
void transaction(double& balance, string date[], double amount[], int& count);
void displayTransactionDetail(double& balance, string date[], double amount[], int& count);

int main()
{
	double balance = 0, amount[100] = { NULL };
	int count, select;
	string date[100];

	getline(cin, currentUser);
	do
	{
		cout << "Username: " << currentUser << endl;
		menu();
		cout << "Choice: ";
		cin >> select;
		if (select == 3)
		{
			system("cls");
			transaction(balance, date, amount, count);
		}
		else if (select == 4)
		{
			system("cls");
			displayTransactionDetail(balance, date, amount, count);
			system("pause");
		}
		else if (select == 5)
		{
			system("cls");
			cout << "Exiting..." << endl;
			break;
		}
		else
		{
			system("cls");
			cout << "Not available" << endl;
		}
		system("cls");
	}while (select != 5);
	return 0;
}

void menu()
{
	cout << "1. Display Item List" << endl;
	cout << "2. Add Item List" << endl;
	cout << "3. Perform Transaction" << endl;
	cout << "4. Display Transaction History" << endl;
	cout << "5. Quit" << endl;
}

void readTransaction(double& balance, string date[], double amount[], int& count)
{
	ifstream infile(currentUser + "_transaction.txt");
	if (infile.is_open())
	{
		infile >> balance;
		count = 0;
		while (!infile.eof())
		{
			infile >> date[count] >> amount[count];
			count++;
		}
	}
	else {
		cout << "The file is unable to open" << endl;
	}
	infile.close();
}

void transaction(double& balance, string date[], double amount[], int& count)
{	
	readTransaction(balance, date, amount, count);
	ofstream outfile(currentUser + "_transaction.txt");
	char choice;
	if (outfile.is_open()) 
	{
		do 
		{
			cout << "Available Balance: RM " << balance << endl;
			cout << "Amount of Transaction: RM ";
			cin >> amount[count];
			balance = balance + amount[count];
			cout << "Date of Transaction (DD//MM//YYYY): ";
			cin.ignore();
			cin >> date[count];
			count++;
			cout << "Continue? (1-yes, 2-no): ";
			cin >> choice;
			cin.ignore();
			system("cls");
		} while (choice == '1');

		outfile << balance << endl;
		for (int i = 0; i < count; i++)
		{
			outfile << date[i] << " " << amount[i] << endl;
		}

		outfile.close();
	}
}

void displayTransactionDetail(double& balance, string date[], double amount[], int& count)
{
	readTransaction(balance, date, amount, count);
	cout << "Available Balance: " << balance << endl;
	cout << endl;
	for (int i = 1; i < count; i++)
	{
		cout << "Transaction " << i << endl;
		cout << "Date: " << date[i - 1] << endl;
		if (amount[i - 1] > 0)
			cout << "Top Up Amount: " << amount[i - 1] << endl;
		else
			cout << "Spend Up Amount: " << amount[i - 1] << endl;
		cout << endl;
	}
}
