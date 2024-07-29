#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

class Bank_Account
{
	int Money_Deposit;
	char type;
	int acno;
	char name[70];

public:
	void report() ;
	int retMoney_Deposit() ;	
	void create_Bank_Account();
	void dep(int);
	int retacno() ;
	void Display_Account() ;
	void Updation();
	char rettype() ;
	void draw(int);
};

void Bank_Account::Updation()
{
	cout << "\n\tBank_Account No. : " << acno;
	cout << "\n\tUpdation Bank_Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n\tUpdation Type of Bank_Account : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\tUpdation Balance Total-Money : ";
	cin >> Money_Deposit;
}
void Bank_Account::create_Bank_Account()
{
	system("CLS");
	cout << "\n\tPlease Enter the Bank_Account No. : ";
	cin >> acno;
	cout << "\n\n\tPlease Enter the Name of the Bank_Account holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n\tPlease Enter Type of the Bank_Account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\tPlease Enter The Starting Total-Money : ";
	cin >> Money_Deposit;
	cout << "\n\n\tBank_Account Created..";
}

void Bank_Account::Display_Account() 
{
	cout << "\n\tBank_Account No. : " << acno;
	cout << "\n\tBank_Account Holder Name : ";
	cout << name;
	cout << "\n\tType of Bank_Account : " << type;
	cout << "\n\tBalance Total-Money : " << Money_Deposit;
}

int Bank_Account::retacno() 
{
	return acno;
}

char Bank_Account::rettype() 
{
	return type;
}
void Bank_Account::report() 
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << Money_Deposit << endl;
}
void Bank_Account::dep(int x)
{
	Money_Deposit += x;
}
void Bank_Account::draw(int x)
{
	Money_Deposit -= x;
}
int Bank_Account::retMoney_Deposit() 
{
	return Money_Deposit;
}

void Welcome();

void write_Bank_Account();
void display_sp(int);
void display_all();

void delete_Bank_Account(int);
void Money_Deposit_withdraw(int, int);
void Updation_Bank_Account(int);

int main()
{
	Welcome();
	char ch;
	int num;
	do
	{
		system("CLS");
		cout << "\n\n\t\t============================";

		cout << "\n\t\tBANK MANAGEMENT SYSTEM";
		cout << "\n\t\t============================";
		Sleep(100);
		cout << "\n\n\t\t    ::MAIN MENU::\n";
		Sleep(100);
		cout << "\n\t\t1. NEW Bank_Account";
		Sleep(100);
		cout << "\n\t\t2. Money_Deposit Total-Money";
		Sleep(100);
		cout << "\n\t\t3. WITHDRAW Total-Money";
		Sleep(100);
		cout << "\n\t\t4. BALANCE ENQUIRY";
		Sleep(100);
		cout << "\n\t\t5. ALL Bank_Account HOLDER LIST";
		Sleep(100);
		cout << "\n\t\t6. CLOSE the Bank_Account";
		Sleep(100);
		cout << "\n\t\t7. Updation the Bank_Account";
		Sleep(100);
		cout << "\n\t\t8. EXIT";
		Sleep(100);
		cout << "\n\n\t\tSelect Your Option (1-8): ";
		cin >> ch;

		switch (ch)
		{
		case '1':
			write_Bank_Account();
			break;
		case '2':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : ";
			cin >> num;
			Money_Deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : ";
			cin >> num;
			Money_Deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : ";
			cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : ";
			cin >> num;
			delete_Bank_Account(num);
			break;
		case '7':
			system("CLS");
			cout << "\n\n\tPlease Enter The Bank_Account No. : ";
			cin >> num;
			Updation_Bank_Account(num);
			break;
		case '8':
			system("CLS");
			cout << "\n\n\tBrought To You By code-projects.org";
			break;
		default:
			cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}

void write_Bank_Account()
{
	Bank_Account ac;
	ofstream outFile;
	outFile.open("Bank_Account.dat", ios::binary | ios::app);
	ac.create_Bank_Account();
	outFile.write((char*)&ac, sizeof(Bank_Account));
	outFile.close();
}


void delete_Bank_Account(int n)
{
	Bank_Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("Bank_Account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read((char*)&ac, sizeof(Bank_Account)))
	{
		if (ac.retacno() != n) {
			outFile.write((char*)&ac, sizeof(Bank_Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("Bank_Account.dat");
	rename("Temp.dat", "Bank_Account.dat");
	cout << "\n\nRecord Deleted ..";
}

void display_sp(int n)
{
	Bank_Account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("Bank_Account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\tBALANCE DETAILS\n";
	while (inFile.read((char*)&ac, sizeof(Bank_Account)))
	{
		if (ac.retacno() == n)
		{
			ac.Display_Account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\n\tBank_Account number does not exist";
}

void display_all()
{
	system("CLS");
	Bank_Account ac;
	ifstream inFile;
	inFile.open("Bank_Account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	else
	cout << "\n\n\t\tBank_Account HOLDER LIST\n\n";
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n";
	Sleep(10);
	while (inFile.read((char*)&ac, sizeof(Bank_Account)))
	{
		ac.report();
	}
	inFile.close();
}
void Updation_Bank_Account(int n)
{
	bool found = false;
	Bank_Account ac;
	fstream File;
	File.open("Bank_Account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read((char*)&ac, sizeof(Bank_Account));
		if (ac.retacno() == n)
		{
			ac.Display_Account();
			cout << "\n\n\tPlease Enter The New Details of Bank_Account" << endl;
			ac.Updation();
			int pos = (-1) * static_cast<int>(sizeof(Bank_Account));
			File.seekp(pos, ios::cur); 
			File.write((char*)&ac, sizeof(Bank_Account));
			cout << "\n\n\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n\tRecord Not Found ";
}

void Money_Deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	Bank_Account ac;
	fstream File;
	File.open("Bank_Account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read((char*)&ac, sizeof(Bank_Account));
		if (ac.retacno() == n)
		{
			ac.Display_Account();
			if (option == 1)
			{
				cout << "\n\n\tTO Money_Deposit Total-Money";
				cout << "\n\n\tPlease Enter The Total-Money to be Money_Deposited: ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW Total-Money";
				cout << "\n\n\tPlease Enter The Total-Money to be withdraw: ";
				cin >> amt;
				int bal = ac.retMoney_Deposit() - amt;
				if (bal < 0)
					cout << "Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur); // fn1353
			File.write((char*)&ac, sizeof(Bank_Account));
			cout << "\n\n\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n\tRecord Not Found ";
}

void Welcome(){
	system("cls");

	cout << "\n\n" << endl;

	cout << "\t\t\t **       ** ***** **      ****   ****  ***     *** ***** " << endl;
	cout << "\t\t\t **       ** **    **     **  ** **  ** ** ** ** ** **    " << endl;
	cout << "\t\t\t **  ***  ** ***** **     **     **  ** **  ***  ** ***** " << endl;
	cout << "\t\t\t ** ** ** ** **    **     **  ** **  ** **       ** **    " << endl;
	cout << "\t\t\t ***     *** ***** *****   ****   ****  **       ** ***** " << endl;
	system("color 2");

	Sleep(2000);
	system("cls");
}
