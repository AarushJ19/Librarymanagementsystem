//======================================================
//                   HEADER FILE USED IN PROJECT
//======================================================

#include <iostream>
#include <fstream>	//for file handling
#include <conio.h>	 //to use getch()
#include <stdio.h>
#include <string.h>
#include <iomanip>	//for setw() function
#include "windows.h"	 //for basic file handling
#define MAX_NAME_LEN 60
#include<stdlib.h>
using namespace std;

//======================================================
//                   CLASSES USED IN PROJECT
//======================================================
 



class book
{
	char booknumber[6];
	char book_name[50];
	char author_name[20];
  public:
	void create_book()
	{
		cout<<"\n\t___NEW BOOK ENTRY___\n";
		cout<<"\n\nEnter The book no : ";
		cin>>booknumber;
		cout<<"\n\nEnter The Name of The Book :";
        cin.ignore();
		cin.getline(book_name, MAX_NAME_LEN);
		cout<<"\n\nEnter The Author's Name :";
		cin.getline(author_name, MAX_NAME_LEN);
		cout<<"\n\n\nBook Created Successfully";
	}

	void show_book()
	{
		cout<<"\nBook no. : "<<booknumber;
		cout<<"\nBook Name : ";
		puts(book_name);
		cout<<"Author Name : ";
		puts(author_name);
	}

	void modify_book()
	{
		cout<<"\nBook no. : "<<booknumber;
		cout<<"\nModify Book Name : ";
		cin.ignore();
		cin.getline(book_name, MAX_NAME_LEN);
		cout<<"\nModify Author's Name of Book : ";
		cin.getline(author_name, MAX_NAME_LEN);
	}

	char* retbno()
	{
		return booknumber;
	}

	void report()
	{cout<<booknumber<<setw(30)<<book_name<<setw(30)<<author_name<<endl;}


};

//class ends here

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
    char username[20];
    char password[20];
	int token;
public:
	void create_student()
	{
		system("cls");
	 	cout<<"\n\n\t___NEW STUDENT ENTRY___\n";
		cout<<"\nEnter The admission no : ";
		cin>>admno;
		cout<<"\n\nEnter The Name of The Student : ";
        cin.ignore();
		cin.getline(name, MAX_NAME_LEN);
		token=0;
		stbno[0]='\0';
		cout<<"\n\n___Student Record Created Successfully___";
	}

	void show_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nStudent Name : ";
		puts(name);
		cout<<"\nNo of Book issued : "<<token;
		if(token==1)
			cout<<"\nBook No "<<stbno;
	}

	void modify_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nModify Student Name : ";
		cin.getline(name, MAX_NAME_LEN);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}

	void report()
	{cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

    char* retusername()
    {
        return username;
    }

    char* retpassword()
    {
        return password;
    }

};       

class items
{



}
  //class ends here




//======================================================
//    	global declaration for stream object, object
//======================================================

fstream fp,fp1;
book bk;
student st;


//======================================================
//    	function to write in file
//======================================================

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		system("cls");
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\n___Do you want to add more record___(Y/N?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\n___do you want to add more record___(Y/N?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}


//======================================================
//    	function to read specific record from file
//======================================================


void display_spb(char n[])
{
	cout<<"\n___BOOK DETAILS___\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
		 	flag=1;
		}
	}
	
	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist! Check Details Again.";
	getch();
}

void display_sps(char n[])
{
	cout<<"\n___STUDENT DETAILS___\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}
	
	fp.close();
	if(flag==0)
    		cout<<"\n\nStudent does not exist! Check Details Again.";
 	getch();
}


//======================================================
//    	function to modify record of file
//======================================================


void modify_book()
{
	char n[6];
	int found=0;
	system("cls");
	cout<<"\n\n\t___MODIFY BOOK RECORD___";
	cout<<"\n\n\tEnter The book no. of The book : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\n___Enter The New Details of book___"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
		    	fp.seekp(pos,ios::cur);
		    	fp.write((char*)&bk,sizeof(book));
		    	cout<<"\n\n\t Record Updated Successfully!";
		    	found=1;
		}
	}

    	fp.close();
    	if(found==0)
    		cout<<"\n\n Record Not Found! Check Details Again. ";
    	getch();
}


void modify_student()
{
	char n[6];
	int found=0;
	system("cls");
	cout<<"\n\n\t___MODIFY STUDENT RECORD___ ";
	cout<<"\n\n\tEnter The admission no. of The student : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\nEnter The New Details of student : "<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated Successfully!";
			found=1;
		}
	}
	
	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found! Check Details Again. ";
	getch();
}

//======================================================
//    	function to delete record of file
//======================================================


void delete_student()
{
	char n[6];
	int flag=0;	
	system("cls");
    	cout<<"\n\n\n\t___DELETE STUDENT___";
    	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
    	cin>>n;
    	fp.open("student.dat",ios::in|ios::out);
    	fstream fp2;
    	fp2.open("Temp.dat",ios::out);
    	fp.seekg(0,ios::beg);
    	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
	     		fp2.write((char*)&st,sizeof(student));
		else
	   		flag=1;
	}
    	
	fp2.close();
    	fp.close();
    	remove("student.dat");
    	rename("Temp.dat","student.dat");
    	if(flag==1)
     		cout<<"\n\n\t___Record Deleted___";
    	else
     		cout<<"\n\nRecord not found! Check Details Again.";
    	getch();
}


void delete_book()
{
	char n[6];
	system("cls");
	cout<<"\n\n\n\t___DELETE BOOK___";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)  
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}
    	
	fp2.close();
    	fp.close();
    	remove("book.dat");
    	rename("Temp.dat","book.dat");
    	cout<<"\n\n\t___Record Deleted___";
    	getch();
}



//======================================================
//    	function to display all students list
//======================================================

void display_alls()
{
	system("cls");
     	fp.open("student.dat",ios::in);
     	if(!fp)
     	{
       		cout<<"\n\n\t\tERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
       		return;
     	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"==================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"==================================================================\n";

	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}
     	
	fp.close();
	getch();
}


//======================================================
//    	function to display Books list
//======================================================

void display_allb()
{
	system("cls");
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"\n\n\t\tERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
       		return;
     	}

	cout<<"\n\n\t\t___BOOK LIST___\n\n";
	cout<<"=========================================================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"=========================================================================\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
     	fp.close();
     	getch();
}



//======================================================
//    	function to issue book
//======================================================

void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	system("cls");
	cout<<"\n\n___BOOK ISSUE___";
	cout<<"\n\n\tEnter The student's admission no. : ";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
    	fp1.open("book.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(student)) && found==0)
       	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
		      		cout<<"\n\n\tEnter the book no. : ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
			   		if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
       						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write the current date in backside of your book and submit \nwithin 15 days fine Rs. 1 for each after 15 days period";
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book no does not exist! Check Details Again.";
			}
	    		else
		  		cout<<"You have not returned the last book, Please return the book first.";

		}
	}
      	if(found==0)
		cout<<"___Student record not exist___";
	getch();
  	fp.close();
  	fp1.close();
}

//======================================================
//    	function to deposit book
//======================================================

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    system("cls");
    cout<<"\n\n___BOOK DEPOSIT___";
    cout<<"\n\n\tEnter The student's admission no. : ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				cout<<"\n\nBook deposited in no. of days : ";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine has to deposited Rs. : "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully!";
			}
		    }
		  if(flag==0)
		    cout<<"Book no. does not exist! Check Details Again.";
		      }
		 else
			cout<<"No book is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"Student record not exist!";
	getch();
  fp.close();
  fp1.close();
  }

void gotoxy(short x, short y) { 
	COORD pos = {x, y}; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
} 



//======================================================
//    	INTRODUCTION FUNCTION
//======================================================

void intro()
{
	system("cls");
	gotoxy(35,11);
	cout<<"LIBRARY";
	gotoxy(35,14);
	cout<<"MANAGEMENT";
	gotoxy(35,17);
	cout<<"SYSTEM";
	cout<<"\n\nMADE BY : Aarush Jain, Aahan Shah, Aryan Awasthi";
	cout<<"\n PRN: 21070122005, 21070122003, 21070122025";
	
	getch();
}



//======================================================
//    	ADMINISTRATOR MENU FUNCTION
//======================================================

void admin_menu()
{
	system("cls");
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.CREATE BOOK ";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t9.MODIFY BOOK ";
	cout<<"\n\n\t10.DELETE BOOK ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPLEASE ENTER YOUR CHOICE (1-11) ";
	cin>>ch2;
	switch(ch2)
	{
        case 1: 
            system("cls");
            write_student();
            break;
        case 2: 
            display_alls();
            break;
        case 3:
        {
            char num[6];
            system("cls");
            cout<<"\n\n\tPlease Enter The Admission No. : ";
            cin>>num;
            display_sps(num);
            break;
        }
        case 4: 
            modify_student();
            break;
        case 5: 
            delete_student();
            break;
		case 6: 
            system("cls");
			write_book();
            break;
		case 7: 
            display_allb();
            break;
		case 8: 
        {
            char num[6];
            system("cls");
            cout<<"\n\n\tPlease Enter The book No. : ";
            cin>>num;
            display_spb(num);
            break;
		}
      	case 9: 
            modify_book();
            break;
      	case 10: 
            delete_book();
            break;
     	case 11: 
            return;
      	default:
		cout<<"\a";
   	}
   	admin_menu();
}
void login();
//SIGNUP PANEL OF PROGRAM
void signup()
{
    system("cls");
    cout<<"SIGNUP PANEL\n";
    //creating a dat file to store data
    ofstream file;
    file.open("signup.dat",ios::app);
    
    char username[20],password[20],repassword[20];
    char email[40];
    cout<<"Username : ";
    cin>>username;
    // // check if username already exists in signup.dat file
    // ifstream file1;
    // file1.open("signup.dat",ios::in);
    // while(file1.read((char*)&st,sizeof(student)))
    // {
    //     if(strcmpi(st.retusername(),username)==0)
    //     {
    //         cout<<"Username already exists\n";
    //         cout<<"Please enter a different username\n";
    //         cout<<"Username: ";
    //         cin>>username;
    //     }
    // }
    cout<<"Password :";
    cin>>password;
    cout<<"Re-enter Password :";
    cin>>repassword;
    if(repassword==password)
    {
        cout<<"Email : ";
        cin>>email;

        file<<username<<endl;
        file<<password<<endl;
        file<<email<<endl;
        file.close();

        cout<<"Signup Successful!";
        login();
    }
    else
    {
        cout<<"Password does not match!";
        signup();
    }

    getch();

    /*ENTER USERNAME:
    ENTER EMAIL:
    ENTER PASSWORD:
    RE-ENTER PASSWORD:
    STORE USERNAME AND PASSWORD IN A FILE.*/
}

// lOGIN PANEL OF PROGRAM
void login()
{
    system("cls");
    cout<<"\n\t\tLOGIN PANEL"<<endl;
    char username[20],password[20];
    int i=0;
    char ch;
    system("cls");
    cout<<"Username : " ;
    cin>>username;
    cout<<"Password : ";
    cin.ignore();
    cin>>password;
    //check username and password from signup.dat file
    ifstream file;
    file.open("signup.dat",ios::in);
    while(file.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retusername(),username)==0)
        {
            if(strcmpi(st.retpassword(),password)==0)
            {
                cout<<"Login Successful!";
                admin_menu();
            }
            else
            {
                cout<<"Password does not match!";
                login();
            }
        }
        else
        {
            cout<<"Username does not exist!";
            login();
        }
    }

}
void askForSecretPassword(void){
	string password;
	system("cls");
	cout<<"\n\nEnter your password: ";
	cin>>password;
	int len=password.length();
	system("cls");
	cout<<"Enter numeric password: ";
	for(int i=0;i<len;i++){
		cout<<"*";
	}cout<<endl;}

//======================================================
//    	THE MAIN FUNCTION OF PROGRAM
//======================================================


int main()
{
	system("Color 7C");

	char ch;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
	  	cout<<"\n\n\t03. ADMINISTRATOR MENU";
	  	cout<<"\n\n\t04. EXIT";
	  	cout<<"\n\n\tPlease Select Your Option (1-4) ";
	  	ch=getche();
	  	switch(ch)
	  	{
			case '1':system("cls");
				 book_issue();
			   	 break;
		  	case '2':book_deposit();
			    	 break;
		  	case '3':
			{
				cout<<"Enter The Library Access Code";
				askForSecretPassword();
				system("pause");
				admin_menu();
				 break;
			}
		  	case '4':exit(0);
		  	default :cout<<"\a";
	 }
    	}while(ch!='4');
    return 0;
}

//======================================================
//    			END OF PROJECT
//======================================================





/*
V.1.0.0
    WELCOME TO AARUSH'S LIBRARY MANAGEMENT SYSTEM.

    1. LOGIN
    2. SIGNUP
    
    IF 1,
    ENTER USERNAME:
    ENTER PASSWORD:
    CHECK USERNAME AND PASSWORD FROM DATABASE.

    IF 2,
    ENTER USERNAME:
    ENTER EMAIL:
    ENTER PASSWORD:
    RE-ENTER PASSWORD:
    STORE USERNAME AND PASSWORD IN A FILE.

    IF PASSWORDS MATCH,
    WELCOME TO AARUSH'S LIBRARY MANAGEMENT SYSTEM.

    IF PASSWORDS DON'T MATCH,
    INCORRECT PASSWORD

    IF USERNAME ALREADY EXISTS,
    USERNAME ALREADY EXISTS

    BACKEND...
    TEXT FILE WITH USERNAME AND PASSWORDS
V.1.0.1-5
    BUG FIXES
*/
