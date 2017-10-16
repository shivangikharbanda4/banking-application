#include<fstream.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<iomanip.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int acc_no=101;

/*****************************************************************************
				CLASS: ACCOUNT
*****************************************************************************/

class account
{
  private:
	char name[20];
	char password[20];
	struct address_structure
	{
		char house_no[10];
		char locality[20];
		int sector;
		char city[20];
		char state[20];
	}address;
	char aadhar_card_number[10];
	float balance;
  public:
	int account_no;
	account()
	{}
	account(char p)
	{
		cout<<"Name: ";
		gets(name);

		cout<<"Aadhar Card number: ";
		gets(aadhar_card_number);

		cout<<"Address: \n";

		cout<<"  house no: ";
		gets(address.house_no);

		cout<<"  locality: ";
		gets(address.locality);

		cout<<"  sector: ";
		cin>>address.sector;

		cout<<"  city: ";
		gets(address.city);

		cout<<"  state: ";
		gets(address.state);

		cout<<"Password: ";
		gets(password);

		account_no=acc_no++;

		clrscr();
		cout<<endl<<setw(6)<<"Your account has been created!"<<endl<<"Account number: "<<account_no;
		cout<<endl<<"Please enter amount to start account with: ";
		cin>>balance;

	}
	int check_password(char input[10])
	{
		if(strcmp(input,password)==0)
		{
			cout<<"Password matched \n";
			return(1);
		}
		else
		{
			cout<<"Password didn't match \n";
			return(0);
		}
	}
	void display()
	{
		cout<<endl<<endl<<endl;
		cout<<setw(40)<<"ACCOUNT NUMBER: "<<account_no<<endl<<endl;
		cout<<"   Hi "<<name<<"! Here are your bank details: "<<endl;
		cout<<"      1. Name: "<<name<<endl;
		cout<<"      2. Aadhar card number: "<<aadhar_card_number<<endl;
		cout<<"      3. Address:... "<<endl;
		cout<<"      4. balance: "<<balance<<endl;
	}
	void display_to_administrator()
	{
		clrscr();
		cout<<endl<<endl<<endl;
		cout<<setw(40)<<"ACCOUNT NUMBER: "<<account_no<<endl<<endl;
		cout<<"      1. Name: "<<name<<endl;
		cout<<"      2. Aadhar card number: "<<aadhar_card_number<<endl;
		cout<<"      3. Address:... "<<endl;
		cout<<"      4. balance: "<<balance<<endl;
	}

	void short_display(int y)
	{
		gotoxy(1,y);
			cout<<account_no;
		gotoxy(20,y);
			cout<<name;
		gotoxy(50,y);
			cout<<balance;
	}

	void increase_balance(float money)
	{
		balance+=money;
	}

	void decrease_balance(float money)
	{
		balance-=money;
	}

	friend void modify_account_data();
};
/*****************************************************************************
				CLASS: TRANSACTION
*****************************************************************************/
class transaction
{
	char type;
	float amount;

	public:

	int account_no;
	transaction(int acc_no,char typ,float am)
	{
		account_no=acc_no;
		type=typ;
		amount=am;

	}

	transaction()
	{}

	void display(int y)
	{
		gotoxy(1,y);
			cout<<account_no;
		gotoxy(20,y);
			cout<<type;
		gotoxy(40,y);
			cout<<amount;

	}

};

/*****************************************************************************
				ADMINISTRATOR'S FUNCTIONS
*****************************************************************************/

//CREATE ACCOUNT

void create_account()
{
  clrscr();
  ofstream ofile("account data.dat",ios::app|ios::binary);

  account sample('p');
  ofile.write((char*)&sample,sizeof(sample));
  ofile.close();

}

//MODIFY ACCOUNT DATA:

void modify_account_data()
{
	ifstream ifile("account data.dat",ios::binary);
	ofstream ofile("temp.dat",ios::binary);

	account record;

	int account_no;
	cout<<"Please enter account number: ";
	cin>>account_no;

	int flag=0, choice;

	cout<<"enter field to be modified (1-6; 6 for password): ";
	cin>>choice;

	cout<<"\nPlease enter new data: ";

	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));


		if(ifile.eof())
			break;

		if(record.account_no==account_no)
		{
			flag=1;
			switch(choice)
			{
			 case 1:
				gets(record.name);
				break;
			 case 2:
				gets(record.aadhar_card_number);
				break;
			 case 3:
				//address
				break;
			 case 5:
				cin>>record.account_no;
				break;
			 case 6:
				gets(record.password);
				break;
			 default:
				cout<<"Invalid choice!";

			}
		}

		ofile.write((char*)&record,sizeof(record));

	}

	ofile.close();
	remove("account data.dat");
	rename("temp.dat","account data.dat");

	if(flag)
		cout<<"Data successfully modified. ";
	else
		cout<<"Action unsuccessful. ";
	getch();

}


//CLOSE ACCOUNT:

void close_account()
{
	ifstream ifile("account data.dat",ios::binary);
	ofstream ofile("temp.dat",ios::binary);
	account record;
	int account_no;

	cout<<"Please enter account number of account to be deleted: ";
	cin>>account_no;

	int flag=0;

	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));


		if(ifile.eof())
			break;

		if(record.account_no==account_no)
		{
			flag=1;
			continue;
		}

		else
			ofile.write((char*)&record,sizeof(record));

	}

	ofile.close();
	remove("account data.dat");
	rename("temp.dat","account data.dat");

	if(flag)
		cout<<"Successfully deleted! ";
	else
		cout<<"Account not found";

	getch();

}

//DISPLAY DETAILS OF AN ACCOUNT
void display_details_of_account()
{
	ifstream ifile("account data.dat",ios::binary);

	account record;
	int account_no;

	cout<<"Please enter account number of account to be viewed: ";
	cin>>account_no;

	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));


		if(ifile.eof())
			break;

		if(record.account_no==account_no)
		{
			record.display_to_administrator();
		}

	}

	cout<<"Press any key to go back to menu. ";
	getch();
}
//DISPLAY LIST OF ACCOUNTS

void display_all_accounts()
{
	clrscr();
	ifstream ifile("account data.dat",ios::binary);
	account record;
	gotoxy(1,3);
		cout<<"Account no. ";
	gotoxy(20,3);
		cout<<"Name";
	gotoxy(50,3);
		cout<<"Balance: ";
	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));

		if(ifile.eof())
			break;
		record.short_display(i+5);


	}

	cout<<"\nPress any key to go back to administrator menu. ";
	getch();
}

void view_all_transactions()
{
 ifstream ifile("transactions.dat",ios::binary);
 clrscr();
 transaction record;

	gotoxy(1,3);
		cout<<"Account no.: ";
	gotoxy(20,3);
		cout<<"Type: ";
	gotoxy(50,3);
		cout<<"Amount: ";
	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));

		if(ifile.eof())
			break;
		record.display(i+5);


	}

	cout<<"\n\n\n  Press any key to go back to administrator menu. ";
	getch();

}

/*****************************************************************************
				LOGIN
*****************************************************************************/

int login(account& record)
{
 clrscr();

 gotoxy(15,5);
	cout<<char(169);
	for(int i=0;i<50;i++)
		cout<<char(22);
	cout<<char(170);
 gotoxy(15,15);
	cout<<char(192);
	for(i=0;i<50;i++)
		cout<<char(22);
	cout<<char(192);
 for(i=0;i<10;i++)
 {
	gotoxy(15,i+5);
	cout<<char(179);
 }
 for(i=0;i<10;i++)
 {
	gotoxy(66,i+5);
	cout<<char(179);
 }

 gotoxy(35,7);
 cout<<"LOGIN";
 gotoxy(34,8);
 cout<<"-------";

 cout<<endl<<setw(40)<<"Account number: ";
 int acc_no;
 char password[10];

 cin>>acc_no;

 ifstream accounts("account data.dat",ios::binary);
 int flag=0;


 for(i=0;;i++)
 {
	accounts.read((char*)&record,sizeof(record));

	if(accounts.eof())
		break;

	if(record.account_no==acc_no)
	{
		int check,subflag=0;
		for(int j=0;j<3;j++)
		{
			cout<<setw(40)<<"Password: ";
			gets(password);
			check=record.check_password(password);
			if(check==1)
			{
				subflag=1;
				break;
			}


		}

		if(subflag==0)
		{
			cout<<"Your Account has been blocked. Please contact nearest branch."<<endl<<"Press any key to go back to menu. ";
			getch();
			return(0);
		}
		flag=1;
		break;
	}
 }
 if(flag==0)
 {
	cout<<setw(35)<<"account not found!"<<endl<<setw(50)<<"Press any key to go back to menu.";
	getch();
	return(0);
 }
 else
	return(1);

}


/*****************************************************************************
			EXISTING ACCOUNT FUNCTIONS
*****************************************************************************/


//MAKE TRANSACTION:

int make_transaction(int pay_account_no)
{
	ifstream ifile("account data.dat",ios::binary);
	ofstream ofile("temp.dat",ios::binary);
	ofstream ofile2("transactions.dat",ios::app,ios::binary);
	account record;

	int flag1=0,flag2=1;
	float amount;
	int receive_account_no;

	cout<<"Please enter Login ID of receipient: ";
	cin>>receive_account_no;
	cout<<"Please enter amount to be transfered: ";
	cin>>amount;

	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));


		if(ifile.eof())
			break;

		if(record.account_no==pay_account_no)
		{
			record.decrease_balance(amount);
			flag1=1;
		}
		if(record.account_no==receive_account_no)
		{
			record.increase_balance(amount);
			flag2=1;
		}

		ofile.write((char*)&record,sizeof(record));

	}

	ofile.close();
	remove("account data.dat");
	rename("temp.dat","account data.dat");

	if(flag1==1&&flag2==1)
	{
		transaction record1(pay_account_no,'p',amount);
		transaction record2(receive_account_no,'r',amount);
		ofile2.write((char*)&record1,sizeof(record1));
		ofile2.write((char*)&record2,sizeof(record2));
		return(1);
	}
	else
		return(0);


}


//DEPOSIT MONEY:

int deposit_money(int account_no)
{
	ifstream ifile("account data.dat",ios::binary);
	ofstream ofile("temp.dat",ios::binary);
	ofstream ofile2("transactions.dat",ios::app,ios::binary);
	account record;

	int flag=0;
	float amount;

	cout<<"Please enter amount deposited: ";
	cin>>amount;

	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));


		if(ifile.eof())
			break;

		if(record.account_no==account_no)
		{
			record.increase_balance(amount);
			flag=1;
		}

		ofile.write((char*)&record,sizeof(record));

	}

	ofile.close();
	remove("account data.dat");
	rename("temp.dat","account data.dat");

	if(flag==1)
	{
		transaction record2(account_no,'d',amount);
		ofile2.write((char*)&record2,sizeof(record2));
		return 1;
	}
	else
		return 0;
}

//WITHDRAW MONEY:

int withdraw_money(int account_no)
{
	ifstream ifile("account data.dat",ios::binary);
	ofstream ofile("temp.dat",ios::binary);
	ofstream ofile2("transactions.dat",ios::app,ios::binary);
	account record;

	int flag=0;
	float amount;

	cout<<"Please enter amount withdrawn: ";
	cin>>amount;

	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));


		if(ifile.eof())
			break;

		if(record.account_no==account_no)
		{
			record.decrease_balance(amount);
			flag=1;
		}

		ofile.write((char*)&record,sizeof(record));

	}

	ofile.close();
	remove("account data.dat");
	rename("temp.dat","account data.dat");

	if(flag==1)
	{
		transaction record2(account_no,'w',amount);
		ofile2.write((char*)&record2,sizeof(record2));
		return 1;
	}
	else
		return 0;

}

void view_transaction_history(int account_no)
{
	clrscr();
	ifstream ifile("transactions.dat",ios::binary||ios::app);
	transaction record;
	int y=3;

	gotoxy(1,2);
		cout<<"Account No.";
	gotoxy(20,2);
		cout<<"Type";
	gotoxy(40,2);
		cout<<"Amount";

	for(int i=0;;i++)
	{
		ifile.read((char*)&record,sizeof(record));

		if(ifile.eof())
			break;

		if(record.account_no==account_no)
			record.display(y++);
	}

	cout<<"\n\n\n  NOTE: \n   d- deposited, w-withdrawn, p-payed, r- received";
	cout<<"\n Press any key to go back to menu.";
	getch();
}

/*****************************************************************************
			MENU (ADMIN, ACCOUNT, MAIN)
*****************************************************************************/

void admin_menu()
{
 int choice,flag=0;

 for(int i=0;;i++)
 {
  clrscr();

  cout<<"\n\n\n\n"<<setw(40)<<"ADMINISTRATOR MENU \n\n";
  cout<<"Please choose operation: \n";
  cout<<"    1. Create Account \n";
  cout<<"    2. Close an account \n";
  cout<<"    3. Modify details of an account \n";
  cout<<"    4. View account details of an account \n";
  cout<<"    5. View list of all accounts (account number, name, balance \n";
  cout<<"    6. View transaction history \n";
  cout<<"    7. Go back to main menu \n";

  cout<<"Please enter choice (1-6): ";
  cin>>choice;

  switch(choice)
  {
	case 1:
		create_account();
		break;
	case 2:
		close_account();
		break;
	case 3:
		modify_account_data();
		break;
	case 4:
		display_details_of_account();
		break;
	case 5:
		display_all_accounts();
		break;
	case 6:
		view_all_transactions();
		break;
	case 7:
		flag=1;
		break;
	default:
	{
		"Invalid choice! \nPlease press any key to go back to main menu.";
		getch();
		flag=1;
		break;
	}
  }

  if(flag)
	break;
 }
}

void account_menu()
{
 account record,record2;
 int a;

 a=login(record);

 if(a)
 {
  for(int i;;i++)
  {

	 clrscr();
	 ifstream ifile("account data.dat",ios::binary);
	 for(int j=0;;j++)
	 {
		ifile.read((char*)&record2,sizeof(record));


		if(ifile.eof())
			break;

		if(record.account_no==record2.account_no)
		{
			record2.display();
		}
	}

	 cout<<"\n\n\n\n\n   Please choose operation: "<<endl;
	 cout<<"    1. View transactions history"<<endl;
	 cout<<"    2. Deposit money"<<endl;
	 cout<<"    3. Withdraw money"<<endl;
	 cout<<"    4. Make Transaction"<<endl;
	 cout<<"    5. Go back to main menu"<<endl;

	 int choice,exit=0,flag=0;

	 cout<<"   Please enter choice(1-5): ";
	 cin>>choice;

	 switch(choice)
	 {
		case 1:
			view_transaction_history(record.account_no);
			flag=1;
			break;

		case 2:
			flag=deposit_money(record.account_no);
			break;
		case 3:
			flag=withdraw_money(record.account_no);
			break;
		case 4:
			flag=make_transaction(record.account_no);
			break;
		case 5:
			exit=1;
			break;
		default:
			cout<<"invalid choice!";
			continue;

	 }

	 if(exit==0&&choice!=1)
	 {
		if(flag==1)
			cout<<"Action successful!";
		else
			cout<<"Action unsuccessful. ";
	 }
	 getch();

	 if(exit)
		break;
  }
 }
}



void main_menu()
{
  for(int i=0;;i++)
  {
	clrscr();

	cout<<"\n\n\n\n\n\n"<<setw(40)<<"MAIN MENU"<<endl;

	cout<<"\n  Please choose one of the following operations: "<<endl;
	cout<<"   1. Administrator "<<endl;
	cout<<"   2. User "<<endl;
	cout<<"   3. Exit program"<<endl;

	cout<<"\nPLEASE NOTE:\n All access to creation, modification and closing of accounts is only with the administrator. In case the user wants to carry out any of the operations mentioned above the user is requested to contact nearest branch for the same. "<<endl<<endl;

	cout<<"Enter choice (1-3): ";
	int choice,exit=0;
	cin>>choice;

	switch(choice)
	{
		case 1:
			admin_menu();
			break;
		case 2:
			account_menu();
			break;
		case 3:
			exit=1;
			break;
		default:
		{
			cout<<"invalid choice!";
			continue;
		}
	}

	if(exit)
		break;

  }
}




void main()
{
  clrscr();

  ofstream ofile("account data.dat",ios::binary);
  ofile.close();

  ofstream ofile2("transactions.dat",ios::binary);
  ofile2.close();

  main_menu();

}