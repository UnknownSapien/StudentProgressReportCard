
//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class student
 {
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	float per;
	char grade;
	void calculate();	//function to calculate grade
     public:
	void getdata();	//function to accept data from user
	void showdata();	//function to show data on screen
	void show_tabular();
	int retrollno();
 }; //class ends here


void student::calculate()
 {
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=60)
		grade='A';
	else if(per>=50)
		grade='B';
	else if(per>=33)
		grade='C';
	else
		grade='F';
 }

void student::getdata()
 {
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	gets(name);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>cs_marks;
	calculate();
 }

void student::showdata()
 {
	cout<<"\nRoll number of student :     "<<rollno;
	cout<<"\nName of student :            "<<name;
	cout<<"\nMarks in Physics :           "<<p_marks;
	cout<<"\nMarks in Chemistry :         "<<c_marks;
	cout<<"\nMarks in Maths :             "<<m_marks;
	cout<<"\nMarks in English :           "<<e_marks;
	cout<<"\nMarks in Computer Science :  "<<cs_marks;
	cout<<"\nPercentage of student is  :  "<<per;
	cout<<"\nGrade of student is :        "<<grade;
 }

void student::show_tabular()
 {
	cout<<setw(3)<<setfill(' ')<<rollno<<"\t|";
	cout<<setw(3)<<setfill(' ')<<name<<"\t\t\b\b\b|";
	cout<<setw(3)<<setfill(' ')<<p_marks<<"  |";
	cout<<setw(3)<<setfill(' ')<<c_marks<<"  |";
	cout<<setw(3)<<setfill(' ')<<m_marks<<"  |";
	cout<<setw(3)<<setfill(' ')<<e_marks<<"  |";
	cout<<setw(3)<<setfill(' ')<<cs_marks<<"   |";
	cout<<" "<<per<<"  |";
	cout<<"  "<<grade<<"    |";
	cout<<endl;
 }

int  student::retrollno()
 {
	return rollno;
 }


//***************************************************************
//    	function declaration
//****************************************************************

void write_student();	//write the record in binary file
void display_all();		//read all records from binary file
void display_sp(int);	//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();	//display result menu
void intro();	//display welcome screen
void entry_menu();	//display entry menu on screen
void exit() ;

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
 {
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;

		}
	 }while(ch!='3');

 }

//***************************************************************
//    	function to write in file
//****************************************************************

void write_student()
 {
	student st;
	ofstream fout;
	fout.open("student.dat",ios::binary|ios::app);
	st.getdata();
	fout.write((char *) &st, sizeof(student));
	fout.close();
	cout<<"\n\nStudent record Has Been Created ";
	getch();
 }

//***************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
 {
	student st;
	ifstream fin;
	fin.open("student.dat",ios::binary);
	if(!fin)
	 {
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	 }
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(fin.read((char *) &st, sizeof(student)))
	 {
		st.showdata();
		cout<<"\n\n~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~\n";
	 }
	fin.close();

	getch();
 }

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
 {
	student st;
	ifstream fin;
	fin.open("student.dat",ios::binary);
	if(!fin)
	 {
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	 }
	int flag=0;
	while(fin.read((char *) &st, sizeof(student)))
	 {
		if(st.retrollno()==n)
		 {
			 st.showdata();
			 flag=1;
		 }
	 }
	fin.close();
	if(flag==0)
		cout<<"\n\nrecord not exist";

	getch();
 }

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_student(int n)
 {
	int found=0;
	student st;
	fstream Fio;
	Fio.open("student.dat",ios::binary|ios::in|ios::out);
	if(!Fio)
	 {
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	 }
	while(Fio.read((char *) &st, sizeof(student)) && found==0)
	 {
		if(st.retrollno()==n)
		 {
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    int pos=(-1)*sizeof(st);
		    Fio.seekp(pos,ios::cur);
		    Fio.write((char *) &st, sizeof(student));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		 }
	 }
	Fio.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
 }

//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_student(int n)
 {
	int g=0;
	student st;
	ifstream fin;
	fin.open("student.dat",ios::binary);
	if(!fin)
	 {
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	 }
	ofstream fout;
	fout.open("Temp.dat",ios::binary);
	while(fin.read((char *) &st, sizeof(student)))
	 {
		if(st.retrollno()!=n)
		 {
			fout.write((char *) &st, sizeof(student));
		 }
		 else
		 {
			g=1;
		 }
	 }
	fout.close();
	fin.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(g==1)
	   cout<<"\n\n\tRecord Deleted ..";
	else
	   cout<<"\n\nFILE NOT FOUND.....";
	getch();
 }

//***************************************************************
//    	function to display all students grade report
//****************************************************************

void class_result()
 {
	student st;
	ifstream fin;
	fin.open("student.dat",ios::binary);
	if(!fin)
	 {
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	 }
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"~~~~~~~~^~~~~~~~~~~~~^~~~~~^~~~~~^~~~~~^~~~~~^~~~~~~^~~~~~~~~^~~~~~~~~\n";
	cout<<"R.No    | Name       |  P  |  C  |  M  |  E  |  CS  |  %age  |  Grade|"<<endl;
	cout<<"~~~~~~~~^~~~~~~~~~~~~^~~~~~^~~~~~^~~~~~^~~~~~^~~~~~~^~~~~~~~~^~~~~~~~~\n";
	while(fin.read((char *) &st, sizeof(student)))
	 {
		st.show_tabular();
		cout<<"~~~~~~~~^~~~~~~~~~~~~^~~~~~^~~~~~^~~~~~^~~~~~^~~~~~~^~~~~~~~~^~~~~~~~~\n";
	 }

	getch();
	fin.close();
 }

//***************************************************************
//    	function to display result menu
//****************************************************************

void result()
 {
	char ch,ein='n';
	int rno;
	do
	 {
	clrscr();
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	clrscr();
	switch(ch)
	 {
	      case '1' :  class_result(); break;
	      case '2' :  cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	      case '3' : cout<<"\n\ndo you want to exit to main minu?(y/n)\t";cin>>ein;
					if(ein=='y')
						exit();
					else
						ein='n';

				  break;

		 }
		getch();
	 }while(ein=='N'||ein=='n');

 }

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
 {
	cout<<"\n\n\n\t\t  STUDENT";
	cout<<"\n\n\t\tREPORT CARD";
	cout<<"\n\n\t\t  PROJECT";
	cout<<"\n\n\n\tMADE BY : ROSHAN KUMAR BASTIA";
	cout<<"\n\tTEACHER:  Mr.R.K.ASNANI";
	cout<<"\n\tSCHOOL :  KENDRIYA VIDYALAYA,BAIKUNTHPUR";
	getch();
 }

//***************************************************************
//    	ENTRY / EDIT MENU FUNCTION
//****************************************************************

void entry_menu()
 {
	char ch;
	int num;
	char ein='n';
	do
	 {      clrscr();
		cout<<"\n\n\n\tENTRY MENU";
		cout<<"\n\n\t1.CREATE STUDENT RECORD";
		cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
		cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
		cout<<"\n\n\t4.MODIFY STUDENT RECORD";
		cout<<"\n\n\t5.DELETE STUDENT RECORD";
		cout<<"\n\n\t6.BACK TO MAIN MENU";
		cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
		cin>>ch;
		clrscr();
		switch(ch)
		 {
			case '1': write_student(); break;
			case '2': display_all(); break;
			case '3': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
					display_sp(num); break;
			case '4': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
					modify_student(num);break;
			case '5': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
					delete_student(num);break;
			case '6': cout<<"\n\ndo you want to exit to main minu?(y/n)\t";cin>>ein;
					if(ein=='y')
						exit();
					else
						ein='n';

				  break;
			default:  cout<<"\a";
		 }
		getch();
	 }while(ein=='N'||ein=='n');
   }
void exit()
 {
 }
//***************************************************************
//    			END OF PROJECT
//***************************************************************