#include<iostream.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<conio.h>

const int nleap[12]={31,28,31,30,31,30,31,31,30,31,30,31};
const int leap[12]={31,29,31,30,31,30,31,31,30,31,30,31};

const char ANAME[4]="uit";
const char APASS[4]="123";

const int addDays=365; 
const int bkLimitDays=7;
char dumm;

//Date
struct date
{
	int day, month;
	unsigned long year;
};

//Book Control Option
struct bookrecord
{
   char bookid[10];
   char bkName[100], authorName[100] ;
   char bkInfo[100];
   int totalBook;
   int bkQuantity;
};
struct updatedbook
{
   char upbookid[10];
   char upBkname[100], upAuthorName[100];
   char upBkinfo[100];
   int uptotalBook;
   int upQuantity;
};

struct lentbook
{
	int lentmemid;
	char lentbkid[10];
	int lentbkno;
	date dtstart;
	date dtexpire;
};

//Member Control Option
struct memberRecord
{
	int memberid;
	char rollno[15];
	char memName[30];
	char address[100];
	char ph[20];
	int memberlimit;
 	date expdate, startdate;
};
struct updatedmember
{
   	int upmemberid; 
	char uprollno[15];
	char upMemname[30];
	char upAddress[100];
	char upPh[20];
	int upMemberlimit;
	date upexpdate, upstartdate;
};

//Comments
struct writeCmt
{
	date wdate;
	char comment[1000];
};

//Admin Menu
char chooseAdmin();

//Book Control Option
char chooseBooks();
void writeBooks();
void updateBooks();
void readBooks();
void searchBooks();
void deleteBooks();

//Member Control Option
char chooseMembers();
void writeMembers();
void readMembers();
void searchMembers();
void deleteMembers();
void updateMembers();

//Book Process
char bookProcess();
void bookissue();
void bookreturn();
void currentList();

//Read Comments
char readComments();

//Choose User
char chooseUser();
char checkbooksinfo();
char checkmemDate();
char usercomment();

//For Date Calculations
date dateFun(int, int, unsigned long, int);
int calLeap(unsigned long);
date noLeapDate(int, int, unsigned long);
date leapDate(int, int, unsigned long);


//interface
void labelLibrary();
void labelAdmin();
void labelUser();
void labelbookoption();
void bkProcessOutput();
void labelmemberoption();
void labelbookoption2();
void bookoutput();
void memberOutput();

//For Interface
void starline(char t,int no)
{
   for(int z=1;z<=no;z++)
      cout<<t<<' ';
   return;
}

int main()
{
	system("color 1f");
	int choice; char again;
	char adminname[20]; char pass[20];
	char getpass, cd1, cd2, correct;
do{	
	system("cls"); 
	cd1='t';
	
	labelLibrary();
	cout<<"  1.Administrator. (Need Password Confirmation !)"<<endl<<endl
		<<"  2.User."<<endl<<endl
		<<"  3.Exit Program."<<endl<<endl
		<<"  Choose (1 or 2 or 3): "; 
	cin>>choice;
	cin.get();
	
	switch(choice)
	{
   		case 1: system("cls");
   		labelLibrary();
   		int i, j; 
		cout<<"Enter Administrator Name: "; 
		gets(adminname);	
		
		do{
		i=1; j=0; 
		if(correct=='n')
		{
			system("cls");
   			labelLibrary();
   			cout<<"Enter Administrator Name: ";
   			cout<<adminname<<endl;
		}
		correct='y';
		cout<<endl<<"Enter Administrator Password: "; 
		
		while(i!=13 && i!=8)
		{
			getpass=getch();
			i=(int)getpass;	
			if(i!=13 && i!=8)
			{
				cout<<"*";
				pass[j]=getpass;
				j=j+1;
			}
			else
			{
				if(i==13 && i!=8)
					correct='y';
				if(i!=13 && i==8)
					correct='n';	
			}
		}
		cout<<endl;
		
	}while(correct=='n');
	cout<<endl;
	
	if(strcmp(adminname,ANAME)==0)
		cd1='t';
	else
		cd1='f';

	cd2='t';
	if(j==3)
	{
		i=0;
		for(i=0; i<j; i++)
		{
			if(pass[i]!=APASS[i])
				cd2='f';
		}
	}
	else
		cd2='f';
		
	if(cd1=='t' && cd2=='t')
		again=chooseAdmin();
	else
	{
		cout<<"Administrator Name or Password is incorrect !!!"<<endl<<endl;
		cout<<"Press Any Key to Continue...";
		getch();
		again='n';
	}
	break;
	 
	case 2: system("cls");
	labelLibrary();
	again=chooseUser(); 
	break;

	case 3: choice=3;
	break;

	default:cout<<"\nInvalid Input !!!"<<endl;
}		
}while(tolower(again)=='n' && choice<3);

cout<<endl<<"\n\t\t\t\t\t\tThanks For Using Our Library Management System . . ."<<endl<<endl<<endl;
	return 0;
}

//Admin Menu
char chooseAdmin()
{
	int admchoice;
	char adminagain;
	do{
   	system("cls"); 
   	labelAdmin();
   	
	cout<<"  1.Book Option."<<endl<<endl
		<<"  2.Member Option."<<endl<<endl
		<<"  3.Book Issue Option."<<endl<<endl
		<<"  4.Read Comments."<<endl<<endl
		<<"  5.Exit from Administrator Menu."<<endl<<endl
	    <<"  Choose (1 or 2 or 3 or 4 or 5): "; 
	cin>>admchoice;
	
	switch(admchoice)
	{
		case 1:adminagain=chooseBooks(); break;
		case 2:adminagain=chooseMembers(); break;
		case 3:adminagain=bookProcess(); break;
		case 4:adminagain=readComments(); break;
		case 5:admchoice=5; adminagain='n'; break;
	   	default:admchoice=5; adminagain='n';
	}
}while(adminagain=='n' && admchoice<5);

	return adminagain;
}

//Choose Book Option Type
char chooseBooks()
{
	system("cls"); 
	int bookchoice; 
	char bookagain='y';
   	bookoutput();
   	
   	cout<<"  1.Add Book Records Or Update Book Quantity."<<endl<<endl
		<<"  2.All Book Records."<<endl<<endl
       	<<"  3.Search Specific Book Record."<<endl<<endl
       	<<"  4.Delete Book Records."<<endl<<endl
       	<<"  5.Exit from Book Option."<<endl<<endl
       	<<"  Choose (1 or 2 or 3 or 4 or 5): ";
   	cin>>bookchoice;
   	
   	switch(bookchoice)
	{
 		case 1:writeBooks(); break;
      	case 2:readBooks(); break;
      	case 3:searchBooks(); break;
      	case 4:deleteBooks(); break;
      	case 5:bookagain='n'; break;
      	default:bookagain='n';
   	}
   	if(bookagain=='y')
   	{
   		cout<<endl<<"Do you want to go back to Book Option(y Or n)?: "; 
	   	cin>>bookagain;
   	}
   	if(tolower(bookagain)=='y')
		bookagain=chooseBooks();
   	else
   		bookagain='n';
	return bookagain;
}

//Add books
void writeBooks()
{
	system("cls");
	bookoutput();
   	FILE *bookout; 
 	bookrecord r; 
 	int wtype; 
 	char getbid[10] ,already, writeagain;
 	
   	cout<<"  1.Add New Book Record."<<endl<<endl
	   	<<"  2.Update Book Quantity."<<endl<<endl
   		<<"  Choose (1 or 2): "; 
  	cin>>wtype; cin.get();
  	
   	switch(wtype)
   	{
		case 1: do{ 
		system("cls");
		bookoutput();
	 	bookout=fopen("BookList.dat","rb"); 
	 	already='y';
	 	
      	cout<<"Enter Book's ID: "; 
	  	gets(getbid);
	  	
      	fread(&r,sizeof(r),1,bookout);
      	while(!feof(bookout))
      	{  
		  	if(strcmpi(getbid,r.bookid)==0)
	    		already='n';
	 		fread(&r,sizeof(r),1,bookout);
      	}
      	fclose(bookout);
      	
		if(already=='y')
		{
			bookout=fopen("BookList.dat","ab"); 
		 	strcpy(r.bookid,getbid);
	 		cout<<endl<<"Enter Book's Title: ";
	 		gets(r.bkName); 
	 		cout<<endl<<"Enter Author's name: ";
	 		gets(r.authorName); 
			cout<<endl<<"Enter Book's Information: ";
			gets(r.bkInfo); 
	 		cout<<endl<<"Enter Total Book's Quantity: ";
	 		cin>>r.totalBook; 
	 		r.bkQuantity=r.totalBook;
	 		
	 		fwrite(&r,sizeof(r),1,bookout);
	 		fclose(bookout);
      	}
      	else
	 		cout<<endl<<"The ID "<<getbid<<" has already existed !!!"<<endl;
	 		
		cout<<endl<<"Do you want to continue adding(y Or n)?: "; 
		cin>>writeagain;
		cin.get();
		
   	}while(tolower(writeagain)=='y');
	break;
	
   		case 2: system("cls"); 
 		bookoutput();
 		updateBooks(); 
 		break;
 		
   		default: cout<<endl<<"Invalid Input !!!"<<endl;
   	}
   	return;
}

//All books record
void readBooks()
{
	system("cls");
   	FILE *bookin; 
 	bookrecord r;
 	long total=0, curtotal=0, bkrecord=0;
 	cout<<"\t\t\t\t\t\t\tAll Books of Library";
   	cout<<endl;
    labelbookoption();
    
   	bookin=fopen("BookList.dat","rb");
   	fread(&r,sizeof(r),1,bookin);
   	while(!feof(bookin))
   	{
		cout<<setw(5)<<r.bookid<<setw(51)<<r.bkName<<setw(29)<<r.authorName
			<<setw(33)<<r.bkInfo<<setw(7)<<r.totalBook<<setw(8)<<r.bkQuantity<<endl<<endl;
		
		curtotal+=r.bkQuantity;
		total+=r.totalBook;	
		bkrecord+=1;
		
      	fread(&r,sizeof(r),1,bookin);
   	}
   	fclose(bookin);
   	cout<<endl;
   	cout<<"Total Number of Book Records in the Library = "<<bkrecord<<endl<<endl;
   	cout<<"Total Number of Book Quantity in the Library = "<<total<<endl<<endl;
   	cout<<"Total Number of Current Book Quantity in the Library = "<<curtotal<<endl;
   	
   	return;
}

//Search book with book's ID and book's name
void searchBooks()
{
	system("cls");
	bookoutput();
	FILE *booksch; 
	bookrecord r;
   	int foundit, srtype; 
 	char getbid[10], getbname[30], searchagain, flag;
 	
	cout<<"  1.Search Book Record with Book's ID."<<endl<<endl
	   	<<"  2.Search Book Record with Book's Title."<<endl<<endl
   		<<"  Choose (1 or 2): "; 
 	cin>>srtype;
 	cin.get();
   	flag='n';
   	
   	switch(srtype)
   	{
       	case 1: system("cls"); 
	   	bookoutput();
    	booksch=fopen("BookList.dat","rb");
		cout<<"Enter Book's ID: "; 
		gets(getbid);
		fread(&r,sizeof(r),1,booksch);
		while(!feof(booksch))
		{
			foundit=strcmpi(getbid,r.bookid);
			if(foundit==0)
			{
				cout<<endl<<endl;
				labelbookoption();
				cout<<setw(5)<<r.bookid<<setw(51)<<r.bkName<<setw(29)<<r.authorName
					<<setw(33)<<r.bkInfo<<setw(7)<<r.totalBook<<setw(8)<<r.bkQuantity<<endl;
 				flag='y';
			}
			fread(&r,sizeof(r),1,booksch);
		}
		fclose(booksch);
		break;
			
       	case 2:system("cls");
	   	bookoutput();
		booksch=fopen("BookList.dat","rb");
	
  		cout<<"Enter Book's Title: "; 
  		gets(getbname);
  		
  		fread(&r,sizeof(r),1,booksch);
  		while(!feof(booksch))
  		{
			foundit=strcmpi(getbname,r.bkName);
			if(foundit==0)
			{
				labelbookoption();
				cout<<setw(5)<<r.bookid<<setw(51)<<r.bkName<<setw(29)<<r.authorName
			   		<<setw(33)<<r.bkInfo<<setw(7)<<r.totalBook<<setw(8)<<r.bkQuantity<<endl;
				flag='y';
			}
			fread(&r,sizeof(r),1,booksch);
		}
		fclose(booksch);
		break;
  			
		default: cout<<endl<<"Invalid Input !!!"<<endl;
   }
	if(flag!='y' && srtype<3)
 		cout<<endl<<"Book Record is not found in the file !!!"<<endl;
 		
	cout<<endl<<"Do you want to continue searching(y Or n)?: "; 
	cin>>searchagain;
	
	if(tolower(searchagain)=='y')
	{
		searchBooks();
	}
   return;
} 

//Delete Book with books number
void deleteBooks()
{
	FILE *bookout, *upbook;
	bookrecord r; updatedbook ur;
	int deltype, foundit; 
	char getbid[10], getbname[100], flag, delagain;
	 
do{
	system("cls");
	bookoutput();
	flag='n';
	cout<<"  1.Delete Book Record by Searching with Book's ID."<<endl<<endl
		<<"  2.Delete Book Record by Searching with Book's Title."<<endl<<endl
		<<"  Choose (1 or 2): "; 
	cin>>deltype;
	cin.get();
	
switch(deltype)
{
	case 1: system("cls");
	bookoutput();
	cout<<"Enter Book's ID you want to delete: "; 
	gets(getbid);
	
	bookout=fopen("BookList.dat","rb"); upbook=fopen("tempBook.dat","wb");
	fread(&r,sizeof(r),1,bookout);
	while(!feof(bookout))
	{
		foundit=strcmpi(getbid,r.bookid);
	 	if(foundit==0)
 		{
		 	flag='y';
		 	cout<<endl;	
	    	cout<<"Record of Book's ID "<<r.bookid<<" has been deleted !"<<endl;
 		}
	 	if(foundit!=0)
	 	{
	 		strcpy(ur.upbookid,r.bookid); 
		 	strcpy(ur.upBkname,r.bkName); 
		 	strcpy(ur.upAuthorName,r.authorName);
			strcpy(ur.upBkinfo,r.bkInfo); 
			ur.uptotalBook=r.totalBook;
			ur.upQuantity=r.bkQuantity;
			
	    	fwrite(&ur,sizeof(ur),1,upbook);
 		}
		fread(&r,sizeof(r),1,bookout);
	}
   	fclose(bookout); fclose(upbook);
   	
   	bookout=fopen("BookList.dat","wb"); upbook=fopen("tempBook.dat","rb");
   	fread(&ur,sizeof(ur),1,upbook);
	while(!feof(upbook))
   	{
		strcpy(r.bookid,ur.upbookid);
		strcpy(r.bkName,ur.upBkname); 
		strcpy(r.authorName,ur.upAuthorName); 
		strcpy(r.bkInfo,ur.upBkinfo); 
		r.totalBook=ur.uptotalBook;
		r.bkQuantity=ur.upQuantity;
		
	 	fwrite(&r,sizeof(r),1,bookout);
	 	fread(&ur,sizeof(ur),1,upbook);
	}
	fclose(bookout); fclose(upbook); 
	break;

	case 2:system("cls");
	bookoutput();
	cout<<"Enter Book's Title you want to delete: "; 
	gets(getbname);
	
	bookout=fopen("BookList.dat","rb"); upbook=fopen("tempBook.dat","wb");
	fread(&r,sizeof(r),1,bookout);
	while(!feof(bookout))
	{
		foundit=strcmpi(getbname,r.bkName);
		if(foundit==0)	
		{
			flag='y';
			cout<<endl;
	    	cout<<"Record of Book's Title "<<r.bkName<<" has been deleted !"<<endl;
		}
		if(foundit!=0)
		{	
			strcpy(ur.upbookid,r.bookid); 
			strcpy(ur.upBkname,r.bkName); 
			strcpy(ur.upAuthorName,r.authorName);
			strcpy(ur.upBkinfo,r.bkInfo);
			ur.uptotalBook=r.totalBook; 
			ur.upQuantity=r.bkQuantity;
			
	    	fwrite(&ur,sizeof(ur),1,upbook);
		}
		fread(&r,sizeof(r),1,bookout);
	}
	fclose(bookout); fclose(upbook);
	
	bookout=fopen("BookList.dat","wb"); upbook=fopen("tempBook.dat","rb");
	fread(&ur,sizeof(ur),1,upbook);
	while(!feof(upbook))
	{
		strcpy(r.bookid,ur.upbookid); 
		strcpy(r.bkName,ur.upBkname); 
		strcpy(r.authorName,ur.upAuthorName); 
		strcpy(r.bkInfo,ur.upBkinfo);
		r.totalBook=ur.uptotalBook;
		r.bkQuantity=ur.upQuantity;
		
		fwrite(&r,sizeof(r),1,bookout);
		fread(&ur,sizeof(ur),1,upbook);
	}
	fclose(bookout); fclose(upbook); 
	break;
	
	default:cout<<"\nInvalid Input !!!"<<endl;
}
if(flag!='y' && deltype<3)
	cout<<endl<<"Book Record is not found in the file !!!"<<endl;	
	
	cout<<endl<<"Do you want to continue deleting(y Or n)?: "; 
	cin>>delagain;
	
}while(tolower(delagain)=='y');

	return;
}

//update books quantity searched by id or name
void updateBooks()
{
	FILE *bookout, *upbook, *lent; 
	bookrecord r; updatedbook ur; lentbook lb;
	int modtype, foundit; 
	char getbid[10], upagain, getbname[30], flag;

do{ 
	system("cls");
	bookoutput();
	flag='n';
	cout<<"  1.Update Book Quantity by Searching with Book's ID."<<endl<<endl
		<<"  2.Update Book Quantity by Searching with Book's Title."<<endl<<endl
		<<"  Choose (1 or 2): "; 
	cin>>modtype;
	cin.get();
	
switch(modtype)
{
	case 1: system("cls");
	bookoutput();
	bookout=fopen("BookList.dat","rb"); upbook=fopen("tempBook.dat","wb");
	
	cout<<"Enter Book's ID: "; 
	gets(getbid);
	
	fread(&r,sizeof(r),1,bookout);
	while(!feof(bookout))
	{
		strcpy(ur.upbookid,r.bookid); 
		strcpy(ur.upBkname,r.bkName); 
		strcpy(ur.upAuthorName,r.authorName);
		strcpy(ur.upBkinfo,r.bkInfo); 
		ur.uptotalBook=r.totalBook;
		ur.upQuantity=r.bkQuantity;
		foundit=strcmpi(getbid,ur.upbookid);
		if(foundit==0)
		{
			flag='y';
			cout<<endl<<"Enter Quantity you want to update: "; 
			cin>>ur.uptotalBook;
			
			cout<<"\nQuantity of Book's ID "<<ur.upbookid<<" has been updated from "
				<<r.totalBook<<" to "<<ur.uptotalBook<<endl;
				
			ur.upQuantity=ur.uptotalBook;
			lent=fopen("BookLent.dat","rb");
			fread(&lb,sizeof(lb),1,lent);
			while(!feof(lent))
			{
				if(strcmpi(getbid,lb.lentbkid)==0)
				{
					ur.upQuantity=ur.upQuantity-1;
				}
				fread(&lb,sizeof(lb),1,lent);
			}	
			fclose(lent);
		}
		fwrite(&ur,sizeof(ur),1,upbook);
		fread(&r,sizeof(r),1,bookout);
	}	
	fclose(bookout); fclose(upbook);
			
	bookout=fopen("BookList.dat","wb"); upbook=fopen("tempBook.dat","rb");
	fread(&ur,sizeof(ur),1,upbook);
	while(!feof(upbook))
	{
		strcpy(r.bookid,ur.upbookid); 
		strcpy(r.bkName,ur.upBkname); 
		strcpy(r.authorName,ur.upAuthorName); 
		strcpy(r.bkInfo,ur.upBkinfo);
		r.totalBook=ur.uptotalBook;
		r.bkQuantity=ur.upQuantity;
		
		fwrite(&r,sizeof(r),1,bookout);
		fread(&ur,sizeof(ur),1,upbook);
	}
	fclose(bookout); fclose(upbook); 
	break;
	
	case 2:	system("cls");
	bookoutput();
	bookout=fopen("BookList.dat","rb"); upbook=fopen("tempBook.dat","wb"); 
	
	cout<<"Enter Book's Title: "; 
	gets(getbname);
	
	fread(&r,sizeof(r),1,bookout);
	while(!feof(bookout))
	{
		strcpy(ur.upbookid,r.bookid); 
		strcpy(ur.upBkname,r.bkName); 
		strcpy(ur.upAuthorName,r.authorName);
		strcpy(ur.upBkinfo,r.bkInfo); 
		ur.uptotalBook=r.totalBook;
		ur.upQuantity=r.bkQuantity;
		foundit=strcmpi(getbname,ur.upBkname);
		if(foundit==0)
		{
			flag='y';
			cout<<endl<<"Enter Quantity you want to update: "; 
			cin>>ur.uptotalBook;
			
			cout<<"\nQuantity of Book's Title "<<ur.upBkname<<" has been updated from "
				<<r.totalBook<<" to "<<ur.uptotalBook<<endl;
		}
		fwrite(&ur,sizeof(ur),1,upbook);
		fread(&r,sizeof(r),1,bookout);
	}
	fclose(bookout); fclose(upbook);
			
	bookout=fopen("BookList.dat","wb"); upbook=fopen("tempBook.dat","rb");
	fread(&ur,sizeof(ur),1,upbook);
	while(!feof(upbook))
	{
		strcpy(r.bookid,ur.upbookid); 
		strcpy(r.bkName,ur.upBkname); 
		strcpy(r.authorName,ur.upAuthorName); 
		strcpy(r.bkInfo,ur.upBkinfo);
		r.totalBook=ur.uptotalBook;
		r.bkQuantity=ur.upQuantity;
		
		fwrite(&r,sizeof(r),1,bookout);
		fread(&ur,sizeof(ur),1,upbook);
	}
	fclose(bookout); fclose(upbook); 
	break;
		
		default:cout<<endl<<"Invalid Input !!!"<<endl;
}
	if(flag!='y' && modtype<3)
		cout<<endl<<"Book Record is not found in the file !!!"<<endl;
		
	cout<<endl<<"Do you want to continue updating(y Or n)?: "; 
	cin>>upagain;
	
}while(tolower(upagain)=='y');

	return;
}

//Date Calculations
date dateFun(int ddd, int mmm, unsigned long yyy, int dayamount)
{
	date calculatedDate;
	ddd=ddd+dayamount;
	switch(calLeap(yyy))
	{
		case 1:calculatedDate=noLeapDate(ddd, mmm, yyy);
		break;
		case 2:calculatedDate=leapDate(ddd, mmm, yyy);
		break;
		default:cout<<"Error !"<<endl;
	}
	return calculatedDate;
}

int calLeap(unsigned long y)
{
	if((y%400==0 || y%100!=0) && y%4==0)
		return 2;
	else
		return 1;
}

date noLeapDate(int dy, int mt, unsigned long yr)
{
	date noLeapCalculated; 
	int mm=mt-1;
	while(dy>nleap[mm])
	{
		dy=dy-nleap[mm];
		mm=mm+1;
		if(mm==12)
		{
			mm=0; yr=yr+1;
		}
	}
	noLeapCalculated.day=dy; noLeapCalculated.month=mm+1; noLeapCalculated.year=yr;
	return noLeapCalculated; 
}

date leapDate(int dy, int mt, unsigned long yr)
{
	date leapCalculated;
	int mm=mt-1;
	while(dy>leap[mm])
	{
		dy=dy-leap[mm];
		mm=mm+1;
		if(mm==12)
		{
			mm=0; yr=yr+1;
		}
	}
	leapCalculated.day=dy; leapCalculated.month=mm+1; leapCalculated.year=yr;
	return leapCalculated; 
}

//Choose Member Control Option Type
char chooseMembers()
{
	system("cls"); 
	int memberchoice; 
	char memberagain='y';
	
   	memberOutput();
   	cout<<"  1.Add Member Records."<<endl<<endl
       	<<"  2.All Member Records."<<endl<<endl
       	<<"  3.Search Specific Member Record."<<endl<<endl
       	<<"  4.Update Member Record."<<endl<<endl
       	<<"  5.Delete Member Records."<<endl<<endl
       	<<"  6.Exit from Member Option."<<endl<<endl
       	<<"  Choose (1 or 2 or 3 or 4 or 5 or 6): ";
   	cin>>memberchoice; cout<<endl;
   	
   	switch(memberchoice)
	{
 		case 1:writeMembers(); break;
      	case 2:readMembers(); break;
      	case 3:searchMembers(); break;
      	case 4:updateMembers(); break;
      	case 5:deleteMembers(); break;
      	case 6:memberagain='n'; break;
      	default:memberagain='n';
   	}
   	if(memberagain=='y')
   	{
   		cout<<endl<<"Do you want to go back to Member Option(y Or n)?: "; 
	   	cin>>memberagain;
   	}
   	if(tolower(memberagain)=='y')
		memberagain=chooseMembers();
   	else
   		memberagain='n';
   		
	return memberagain;
}

//Add Members
void writeMembers()
{
   	FILE *memout; 
	memberRecord r; 
 	int getmid; 
 	char already, writeagain;
do{ 
	system("cls"); 
	memberOutput();
	memout=fopen("MemberList.dat","rb"); already='y';
	
	cout<<"Enter Member's ID No: "; 
	cin>>getmid; cin.get();
	
	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{  
		if(getmid==r.memberid)
			already='n';
 		fread(&r,sizeof(r),1,memout);
  	}
  	fclose(memout);
  	
  	if(already!='n')
	{
		memout=fopen("MemberList.dat","ab"); 
		r.memberid=getmid; 
		cout<<endl<<"Enter Roll No: ";
		gets(r.rollno);
		cout<<endl<<"Enter Name: ";
		gets(r.memName); 
		cout<<endl<<"Enter Address: ";
		gets(r.address); 
		cout<<endl<<"Enter Phone Number: ";
		gets(r.ph);
		cout<<endl<<"Enter Member Card Limit: ";
		cin>>r.memberlimit;
		cout<<endl<<"Enter Current Date(day/month/year): "; 
		cin>>r.startdate.day>>dumm>>r.startdate.month>>dumm>>r.startdate.year;
		r.expdate=dateFun(r.startdate.day, r.startdate.month, r.startdate.year, addDays);
		cout<<endl<<"Expiry Date of Member's ID No "<<r.memberid<<" is "<<r.expdate.day<<dumm
			<<r.expdate.month<<dumm<<r.expdate.year<<endl;
			
		fwrite(&r,sizeof(r),1,memout);
		fclose(memout);
	}
	else
		cout<<"\nThe ID number "<<getmid<<" has already existed !!!"<<endl;
		
	cout<<endl<<"Do you want to continue adding(y Or n)?: "; 
	cin>>writeagain;
	
 	}while(tolower(writeagain)=='y');
 	
   	return;	
}

//Read Members
void readMembers()
{
	system("cls");
   	FILE *memin; 
 	memberRecord r;
 	long memtotal=0;
 	cout<<"\t\t\t\t\t\t\tAll Members of Library";
   	cout<<endl;
   	labelmemberoption();
   	
   	memin=fopen("MemberList.dat","rb");
   	fread(&r,sizeof(r),1,memin);
   	while(!feof(memin))
   	{	
		cout<<setw(3)<<r.memberid<<setw(9)<<r.rollno<<setw(20)<<r.memName
			<<setw(44)<<r.address<<setw(14)<<r.ph<<setw(12)<<r.memberlimit
			<<setw(8)<<r.startdate.day<<'/'<<r.startdate.month<<'/'<<r.startdate.year
			<<setw(8)<<r.expdate.day<<'/'<<r.expdate.month<<'/'<<r.expdate.year<<endl<<endl;
		memtotal+=1;
			
		fread(&r,sizeof(r),1,memin);
   	}
	fclose(memin);
	cout<<endl;
	cout<<"Total Number of Members in the Library = "<<memtotal<<endl;
	
   	return;	
}

//Search Member with ID or Name
void searchMembers()
{
	system("cls");
	memberOutput();
	FILE *memsch; 
	memberRecord r;
   	int getmid, foundit, srtype; 
 	char getmname[30], flag, searchagain;
 	
   	cout<<"  1.Search Member Record with Member's ID No."<<endl<<endl
	   	<<"  2.Search Member Record with Member's name."<<endl<<endl
   		<<"  Choose action (1 or 2): "; 
  	cin>>srtype; 
	flag='n';
	
   	switch(srtype)
   	{
       	case 1:	system("cls");
 		memberOutput();
   		memsch=fopen("MemberList.dat","rb");
   		
		cout<<"Enter Member's ID No: "; 
		cin>>getmid;
		
		fread(&r,sizeof(r),1,memsch);
		while(!feof(memsch))
		{
			if(getmid==r.memberid)
			{
				flag='y';
				cout<<endl<<endl;
				labelmemberoption();
				cout<<setw(3)<<r.memberid<<setw(9)<<r.rollno<<setw(20)<<r.memName
					<<setw(44)<<r.address<<setw(14)<<r.ph<<setw(12)<<r.memberlimit
					<<setw(8)<<r.startdate.day<<'/'<<r.startdate.month<<'/'<<r.startdate.year
					<<setw(8)<<r.expdate.day<<'/'<<r.expdate.month<<'/'<<r.expdate.year<<endl;
			}
			fread(&r,sizeof(r),1,memsch);
		}
		fclose(memsch);
		break;
			
       	case 2: system("cls");
	   	memberOutput();
	   	memsch=fopen("MemberList.dat","rb");
	   		
	   	cin.get();
		cout<<"Enter Member's name: "; 
		gets(getmname);
		
		fread(&r,sizeof(r),1,memsch);
		while(!feof(memsch))
		{
       		foundit=strcmpi(getmname,r.memName);
       		if(foundit==0)
       		{
       			flag='y';
       			cout<<endl<<endl;
       			labelmemberoption();
				cout<<setw(3)<<r.memberid<<setw(9)<<r.rollno<<setw(20)<<r.memName
					<<setw(44)<<r.address<<setw(14)<<r.ph<<setw(12)<<r.memberlimit
					<<setw(8)<<r.startdate.day<<'/'<<r.startdate.month<<'/'<<r.startdate.year
					<<setw(8)<<r.expdate.day<<'/'<<r.expdate.month<<'/'<<r.expdate.year<<endl;
			}
			fread(&r,sizeof(r),1,memsch);
		}
		fclose(memsch);
		break;
  			
       default: cout<<endl<<"Invalid Input !!!"<<endl;
   }
	if(flag!='y' && srtype<3)
 		cout<<endl<<"Member Record is not found in the file !!!"<<endl;
 		
	cout<<endl<<"Do you want to continue searching(y Or n)?: "; 
	cin>>searchagain;
	
	if(tolower(searchagain)=='y')
	{
		searchMembers();
	}
   return;
}

//Update Member Record
void updateMembers()
{
	FILE *memout, *upmem;
	memberRecord r; updatedmember ur;
	int updatetype, getmid; 
	char upagain, flag;
	
do{
	system("cls");
	memberOutput();
	flag='n';
    cout<<"  1.Modify Member's Roll Number."<<endl<<endl
	    <<"  2.Modify Member's Name."<<endl<<endl
        <<"  3.Modify Member's Address."<<endl<<endl
        <<"  4.Modify Member's Phone Number."<<endl<<endl
        <<"  5.Modify Member's Limit."<<endl<<endl
        <<"  6.Update Member Card."<<endl<<endl
		<<"  Choose (1 or 2 or 3 or 4 or 5 or 6 ): ";
	 cin>>updatetype;
switch(updatetype)
{
	case 1:system("cls"); 
	memberOutput(); 
	memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
	
 	cout<<"Enter Member's ID No to update: ";
  	cin>>getmid;
  	
   	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{
		ur.upmemberid=r.memberid; 
		strcpy(ur.uprollno,r.rollno); 
		strcpy(ur.upMemname,r.memName); 
		strcpy(ur.upAddress,r.address); 
		strcpy(ur.upPh,r.ph); 
 		ur.upMemberlimit=r.memberlimit;
 		ur.upexpdate=r.expdate; 
	 	ur.upstartdate=r.startdate;
	 	
 		if(getmid==ur.upmemberid)
		{
			flag='y';
			cout<<"\nEnter Roll No you want to change: ";
			cin.get(); gets(ur.uprollno);
			
			cout<<"\nRoll number of Member's ID No "<<ur.upmemberid<<" has been updated from "
					<<r.rollno<<" to "<<ur.uprollno<<endl;			
			}
			fwrite(&ur,sizeof(ur),1,upmem);
			fread(&r,sizeof(r),1,memout);
		}	
	fclose(memout); fclose(upmem);
		
	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid; 
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname); 
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh); 
		r.memberlimit=ur.upMemberlimit; 
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
	 	fwrite(&r,sizeof(r),1,memout);
		fread(&ur,sizeof(ur),1,upmem);
	}
	fclose(memout); fclose(upmem);
	break;	
	 
	case 2: system("cls");
	memberOutput();
 	memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
 	
  	cout<<"Enter Member's ID No to update: ";
  	cin>>getmid;
  	
	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{
 		ur.upmemberid=r.memberid; 
		strcpy(ur.uprollno,r.rollno); 
		strcpy(ur.upMemname,r.memName); 
 		strcpy(ur.upAddress,r.address); 
	 	strcpy(ur.upPh,r.ph); 
	 	ur.upMemberlimit=r.memberlimit;
 		ur.upexpdate=r.expdate; 
	 	ur.upstartdate=r.startdate;
 		if(getmid==ur.upmemberid)
		{
			flag='y';
			cout<<"\nEnter Name you want to change: ";
			cin.get(); gets(ur.upMemname);
			
			cout<<"\nName of Member's ID No "<<ur.upmemberid<<" has been updated from "
				<<r.memName<<" to "<<ur.upMemname<<endl;
		}
		fwrite(&ur,sizeof(ur),1,upmem);
		fread(&r,sizeof(r),1,memout);
	}	
	fclose(memout); fclose(upmem);
		
	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid; 
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname); 
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh); 
		r.memberlimit=ur.upMemberlimit; 
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
	 	fwrite(&r,sizeof(r),1,memout);
		fread(&ur,sizeof(ur),1,upmem);
	}
	fclose(memout); fclose(upmem);
	break;
		 
	case 3:system("cls");
	memberOutput();
 	memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
 	
  	cout<<"Enter Member's ID No to update: ";
   	cin>>getmid;
	
 	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{
		ur.upmemberid=r.memberid; 
		strcpy(ur.uprollno,r.rollno); 
		strcpy(ur.upMemname,r.memName); 
 		strcpy(ur.upAddress,r.address); 
	 	strcpy(ur.upPh,r.ph); 
	 	ur.upMemberlimit=r.memberlimit;
 		ur.upexpdate=r.expdate; 
	 	ur.upstartdate=r.startdate;
 		if(getmid==ur.upmemberid)
		{
			flag='y';
			cout<<"\nEnter Address you want to change: ";
			cin.get(); gets(ur.upAddress);
			
			cout<<"\nAddress of Member's ID No "<<ur.upmemberid<<" has been updated from "
				<<r.address<<" to "<<ur.upAddress<<endl;
		}
		fwrite(&ur,sizeof(ur),1,upmem);
		fread(&r,sizeof(r),1,memout);
	}	
	fclose(memout); fclose(upmem);
		
	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid; 
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname); 
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh); 
		r.memberlimit=ur.upMemberlimit; 
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
	 	fwrite(&r,sizeof(r),1,memout);
		fread(&ur,sizeof(ur),1,upmem);
	}
	fclose(memout); fclose(upmem);
	break;
		
	case 4: system("cls");
	memberOutput();
	memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
	
 	cout<<"Enter Member's ID No to update: ";
  	cin>>getmid;
	    
	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{
		ur.upmemberid=r.memberid; 
		strcpy(ur.uprollno,r.rollno); 
		strcpy(ur.upMemname,r.memName); 
 		strcpy(ur.upAddress,r.address); 
	 	strcpy(ur.upPh,r.ph); 
	 	ur.upMemberlimit=r.memberlimit;
 		ur.upexpdate=r.expdate; 
 		ur.upstartdate=r.startdate;
		if(getmid==ur.upmemberid)
		{
			flag='y';
			cout<<"\nEnter Phone Number you want to change: ";
			cin.get(); gets(ur.upPh);
			
			cout<<"\nPhone Number of Member's ID No "<<ur.upmemberid<<" has been updated from "
				<<r.ph<<" to "<<ur.upPh<<endl;
		}
		fwrite(&ur,sizeof(ur),1,upmem);
		fread(&r,sizeof(r),1,memout);
		
	}	
	fclose(memout); fclose(upmem);
		
	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid; 
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname); 
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh); 
		r.memberlimit=ur.upMemberlimit; 
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
	 	fwrite(&r,sizeof(r),1,memout);
		fread(&ur,sizeof(ur),1,upmem);
	}
	fclose(memout); fclose(upmem);
	break;
		
	case 5:system("cls");
	memberOutput();
	memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
 	
	cout<<"Enter Member's ID No to update: ";
  	cin>>getmid;
   	
   	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{
		ur.upmemberid=r.memberid; 
		strcpy(ur.uprollno,r.rollno); 
		strcpy(ur.upMemname,r.memName); 
 		strcpy(ur.upAddress,r.address); 
	 	strcpy(ur.upPh,r.ph); 
	 	ur.upMemberlimit=r.memberlimit;
 		ur.upexpdate=r.expdate; 
	 	ur.upstartdate=r.startdate;
		if(getmid==ur.upmemberid)
		{
			flag='y';
			cout<<"\nEnter Number of Limit you want to change: "; 
			cin>>ur.upMemberlimit;
			
			cout<<"\nLimit of Member's ID No "<<ur.upmemberid<<" has been updated from "
				<<r.memberlimit<<" to "<<ur.upMemberlimit<<endl;
		}
		fwrite(&ur,sizeof(ur),1,upmem);
		fread(&r,sizeof(r),1,memout);
		
	}	
	fclose(memout); fclose(upmem);
		
	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid; 
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname); 
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh); 
		r.memberlimit=ur.upMemberlimit; 
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
	 	fwrite(&r,sizeof(r),1,memout);
		fread(&ur,sizeof(ur),1,upmem);
	}
	fclose(memout); fclose(upmem);
	break;
	
	case 6: system("cls");
	memberOutput();
	memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
	
 	cout<<"Enter Member's ID No to update: ";
  	cin>>getmid;
   
 	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{
		ur.upmemberid=r.memberid; 
		strcpy(ur.uprollno,r.rollno); 
		strcpy(ur.upMemname,r.memName); 
 		strcpy(ur.upAddress,r.address); 
	 	strcpy(ur.upPh,r.ph); 
	 	ur.upMemberlimit=r.memberlimit;
 		ur.upexpdate=r.expdate; 
	 	ur.upstartdate=r.startdate;	
		if(getmid==ur.upmemberid)
		{
			flag='y'; 
			cout<<"\nEnter Current Date: "; 
			cin>>r.startdate.day>>dumm>>r.startdate.month>>dumm>>r.startdate.year;
			
			ur.upexpdate=dateFun(r.startdate.day, r.startdate.month, r.startdate.year, addDays);
			
			cout<<"\nExpiry date of Member's ID No "<<ur.upmemberid<<" is "
				<<ur.upexpdate.day<<dumm<<ur.upexpdate.month<<dumm<<ur.upexpdate.year<<" now."<<endl;
						
		}
		fwrite(&ur,sizeof(ur),1,upmem);
		fread(&r,sizeof(r),1,memout);
	}	
	fclose(memout); fclose(upmem);
		
	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid; 
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname); 
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh); 
		r.memberlimit=ur.upMemberlimit; 
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
	 	fwrite(&r,sizeof(r),1,memout);
		fread(&ur,sizeof(ur),1,upmem);
	}
	fclose(memout); fclose(upmem);
	break;
				
	default:cout<<"\nInvalid Input !!!"<<endl;
}
	if(flag!='y' && updatetype<7)
		cout<<"\nMember Record is not found in the file !!!"<<endl;
		
	cout<<"\nDo you want to continue modifying(y Or n)?: "; 
	cin>>upagain;
	
	}while(tolower(upagain)=='y');
	return;
}

//delete members with id number and student name
void deleteMembers()
{
	FILE *memout, *upmem;
	memberRecord r; updatedmember ur;
	int deltype, foundit; int getmid; char getmname[30], delagain, flag;
do{
	system("cls");memberOutput();
	flag='n';
	cout<<"  1.Delete Member Record by Searching with Member's ID No."<<endl<<endl
	    <<"  2.Delete Member Record by Searching with Member's name."<<endl<<endl
		<<"  Choose(1 or 2): "; 
	cin>>deltype; 
	
switch(deltype)
{
	case 1: system("cls");memberOutput();
	   memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
	   
		cout<<"Enter Member's ID No you want to delete: "; 
        cin>>getmid;
        
      	fread(&r,sizeof(r),1,memout);
	    while(!feof(memout))
	    {
	 		ur.upmemberid=r.memberid; 
	 		strcpy(ur.uprollno,r.rollno); 
	 		strcpy(ur.upMemname,r.memName);
	 		strcpy(ur.upAddress,r.address); 
	 		strcpy(ur.upPh,r.ph);
	 		ur.upMemberlimit=r.memberlimit;
	 		ur.upexpdate=r.expdate; 
	 		ur.upstartdate=r.startdate;
	 		if(getmid==ur.upmemberid)	
	 		{
	 			flag='y';
	    		cout<<"\nRecord of Member's ID No "<<ur.upmemberid<<" has been deleted !"<<endl;
	 		}
	 		if(getmid!=ur.upmemberid)
	 		{
	    		fwrite(&ur,sizeof(ur),1,upmem);
 			}
		 	fread(&r,sizeof(r),1,memout);
		}
	fclose(memout); fclose(upmem);
	
 	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid;
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname);
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh);
		r.memberlimit=ur.upMemberlimit;
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
		fwrite(&r,sizeof(r),1,memout);
	 	fread(&ur,sizeof(ur),1,upmem);
	}
	fclose(memout); fclose(upmem);
	break;
		   
   case 2: system("cls"); memberOutput();
   memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
   
	cout<<"Enter Member's name you want to delete: "; 
 	cin.get(); gets(getmname);
 	
  	fread(&r,sizeof(r),1,memout);
	while(!feof(memout))
	{
		ur.upmemberid=r.memberid; 
		strcpy(ur.uprollno,r.rollno); 
		strcpy(ur.upMemname,r.memName);
		strcpy(ur.upAddress,r.address); 
		strcpy(ur.upPh,r.ph);
		ur.upMemberlimit=r.memberlimit;
		ur.upexpdate=r.expdate; 
		ur.upstartdate=r.startdate;
		foundit=strcmpi(getmname,ur.upMemname);
	 	if(foundit==0)
	 	{
			flag='y';	 	
		 	cout<<"\nRecord of Member's name "<<ur.upMemname<<" has been deleted !"<<endl;
	 	}
 		if(foundit!=0)
		{
			fwrite(&ur,sizeof(ur),1,upmem);
		}
		fread(&r,sizeof(r),1,memout);
	}
	fclose(memout); fclose(upmem);
	
	memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
	fread(&ur,sizeof(ur),1,upmem);
	while(!feof(upmem))
	{
		r.memberid=ur.upmemberid;
		strcpy(r.rollno,ur.uprollno); 
		strcpy(r.memName,ur.upMemname);
		strcpy(r.address,ur.upAddress); 
		strcpy(r.ph,ur.upPh);
		r.memberlimit=ur.upMemberlimit;
		r.expdate=ur.upexpdate; 
		r.startdate=ur.upstartdate;
		
	 	fwrite(&r,sizeof(r),1,memout);
		fread(&ur,sizeof(ur),1,upmem);
	}	
	fclose(memout); fclose(upmem); 
   	break;
    
   	default: cout<<"\nInvalid Input !!!"<<endl;   	
}
	if(flag!='y' && deltype<3)
		cout<<"\nMember Record is not found in the file !!!"<<endl;
		
	cout<<"\nDo you want to continue deleting(y Or n)?: "; 
	cin>>delagain;
	
}while(tolower(delagain)=='y');
	
	return;
}

//choose Book Process
char bookProcess()
{
	system("cls"); 
	int protype; char backagain='y';
	bkProcessOutput();
	cout<<"  1.Issue Books."<<endl<<endl
		<<"  2.Return Books."<<endl<<endl
		<<"  3.Current Issued Books List."<<endl<<endl
		<<"  4.Exit from Book Issue Option."<<endl<<endl
		<<"  Choose (1 or 2 or 3 or 4): "; 
	cin>>protype;
	
	switch(protype)
	{
		case 1:bookissue(); break;
		case 2:bookreturn(); break;
		case 3:currentList(); break;
		case 4:backagain='n'; break;
		default:backagain='n';
	}
	if(backagain=='y')
   	{
   		cout<<"\nDo you want to go back to Book Issue Option(y Or n)?: "; 
	   	cin>>backagain;
   	}
   	if(tolower(backagain)=='y')
		backagain=bookProcess();
   	else
   		backagain='n';
	return backagain;
}

//Issue Books
void bookissue()
{
	system("cls"); 
	bkProcessOutput();
	FILE *memout, *bookout, *upmem, *upbook, *lent;
	bookrecord r; updatedbook ur; 
	memberRecord mr; updatedmember umr; lentbook lb;
	int getmid, getbkno;		
	date din;
	char getbid[10], foundm='n', mlimit='n', memexpire='n', foundb='n', blimit='n', lendagain;
	char bkNoalready, bkissue='n'; 	
	
	cout<<"Enter Member's ID No: "; 
	cin>>getmid;
	
	memout=fopen("MemberList.dat","rb");
	fread(&mr,sizeof(mr),1,memout);
	while(!feof(memout))
	{
		if(getmid==mr.memberid)
		{
			foundm='y';
			if(mr.memberlimit>0)
				mlimit='y';
			if(foundm=='y' && mlimit=='n')
				cout<<"\nLimit of Member's ID No "<<getmid<<" is over !!!"<<endl;
				
			if(mlimit=='y')
			{
				cout<<"\nEnter Current Date(day/month/year): "; 
				cin>>din.day>>dumm>>din.month>>dumm>>din.year;
				cin.get();
				if(din.year<mr.expdate.year)
					memexpire='y';
				else
				{
					if(din.year==mr.expdate.year)
					{
						if(din.month<mr.expdate.month)
							memexpire='y';
						else
						{
							if(din.month==mr.expdate.month)
							{
								if(din.day<=mr.expdate.day)
									memexpire='y';
								else
									memexpire='n';
							}	
						}
					}
				}
			}
			
		}
		fread(&mr,sizeof(mr),1,memout);
	}
	fclose(memout);
	
	if(foundm=='y' && mlimit=='y' && memexpire=='n')
		cout<<"\nMember's ID No "<<getmid<<" has been already expired !!!"<<endl;
	if(foundm!='y')	
		cout<<"\nInvalid Member's ID No !!!"<<endl;
	
	if(foundm=='y' && mlimit=='y' && memexpire=='y')
	{
		bookout=fopen("BookList.dat","rb"); upbook=fopen("tempBook.dat","wb");
		cout<<"\nEnter Book's ID: "; 
		gets(getbid);
		
		fread(&r,sizeof(r),1,bookout);
		while(!feof(bookout))
		{
			bkNoalready='y';
			
			strcpy(ur.upbookid,r.bookid); 
		 	strcpy(ur.upBkname,r.bkName); 
		 	strcpy(ur.upAuthorName,r.authorName);
			strcpy(ur.upBkinfo,r.bkInfo);
			ur.uptotalBook=r.totalBook;
		 	ur.upQuantity=r.bkQuantity;
			if(strcmpi(getbid,ur.upbookid)==0)
			{
				foundb='y';
				
				if(ur.upQuantity>=1)
				{
					blimit='y';
					
					cout<<endl<<"Enter Book's No: "; 
					cin>>getbkno;
					if(getbkno>0 && getbkno<=ur.uptotalBook)
					{
						lent=fopen("BookLent.dat","rb");
						fread(&lb,sizeof(lb),1,lent);
						while(!feof(lent))
						{
							if(getbkno==lb.lentbkno && strcmpi(getbid,lb.lentbkid)==0)
							{
								bkNoalready='n';
								cout<<endl<<"Book's No "<<getbkno<<" has been already issued !!!"<<endl;
							}
							fread(&lb,sizeof(lb),1,lent);
						}
						fclose(lent);
					
						if(bkNoalready!='n')
						{
							bkissue='y';
							lb.lentmemid=getmid; 
							strcpy(lb.lentbkid,ur.upbookid);
							lb.lentbkno=getbkno;
							lb.dtstart=din;
							lb.dtexpire=dateFun(din.day, din.month, din.year, bkLimitDays);
							
							cout<<"\nExpiry Date of Book's No "<<getbkno<<" ( Book's ID - "<<ur.upbookid<<" )"<<" is "
							<<lb.dtexpire.day<<'/'<<lb.dtexpire.month<<'/'<<lb.dtexpire.year<<endl;
					
							lent=fopen("BookLent.dat","ab");
							fwrite(&lb,sizeof(lb),1,lent);
							fclose(lent);	
					
					
							ur.upQuantity=ur.upQuantity-1;
							cout<<"\nQuantity of Book's ID "<<ur.upbookid<<" is "<<ur.upQuantity<<" now. "<<endl;
						}
					}
					else
						cout<<endl<<"Invalid Book's No !!!"<<endl;
				}
			}
			fwrite(&ur,sizeof(ur),1,upbook);
			fread(&r,sizeof(r),1,bookout);
		}
		fclose(bookout); fclose(upbook);
		
		bookout=fopen("BookList.dat","wb"); upbook=fopen("tempBook.dat","rb");
		fread(&ur,sizeof(ur),1,upbook);
		while(!feof(upbook))
		{
			strcpy(r.bookid,ur.upbookid); 
			strcpy(r.bkName,ur.upBkname); 
			strcpy(r.authorName,ur.upAuthorName); 
			strcpy(r.bkInfo,ur.upBkinfo);
			r.totalBook=ur.uptotalBook; 
			r.bkQuantity=ur.upQuantity;
			
			fwrite(&r,sizeof(r),1,bookout);
			fread(&ur,sizeof(ur),1,upbook);
		}
		fclose(bookout); fclose(upbook);
		
		if(foundb=='y' && blimit=='y' && bkissue=='y')
		{
			memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
			fread(&mr,sizeof(mr),1,memout);
			while(!feof(memout))
			{
				umr.upmemberid=mr.memberid; 
	 			strcpy(umr.uprollno,mr.rollno); 
			 	strcpy(umr.upMemname,mr.memName);
	 			strcpy(umr.upAddress,mr.address); 
			 	strcpy(umr.upPh,mr.ph);
	 			umr.upMemberlimit=mr.memberlimit;
	 			umr.upexpdate=mr.expdate; 
			 	umr.upstartdate=mr.startdate;
	 			if(getmid==umr.upmemberid)
	 			{
	 				umr.upMemberlimit=umr.upMemberlimit-1;
	 				cout<<"\nLimit of Member's ID No "<<umr.upmemberid<<" is "<<umr.upMemberlimit<<" now. "<<endl;
 				}
 				fwrite(&umr,sizeof(umr),1,upmem);
 				fread(&mr,sizeof(mr),1,memout);
			}
			fclose(memout); fclose(upmem);
			
			memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
			fread(&umr,sizeof(umr),1,upmem);
			while(!feof(upmem))
			{
				mr.memberid=umr.upmemberid; 
	 			strcpy(mr.rollno,umr.uprollno); 
			 	strcpy(mr.memName,umr.upMemname);
	 			strcpy(mr.address,umr.upAddress); 
			 	strcpy(mr.ph,umr.upPh);
	 			mr.memberlimit=umr.upMemberlimit;
	 			mr.expdate=umr.upexpdate; 
			 	mr.startdate=umr.upstartdate;
			 	
	 			fwrite(&mr,sizeof(mr),1,memout);
	 			fread(&umr,sizeof(umr),1,upmem);
			}
			fclose(memout); fclose(upmem);
		}
		if(foundb=='y' && blimit=='n')
			cout<<"\nOut of Book !!!"<<endl;
		if(foundb=='n' && blimit=='n') 
			cout<<"\nInvalid Book's ID !!!"<<endl;
	}
		
	cout<<"\nDo you want to continue to issue book(y Or n)?: "; 
	cin>>lendagain;
	
	if(tolower(lendagain)=='y')
	{
		bookissue();
	}
	
	return;
}

//Return Books
void bookreturn()
{
	FILE *memout, *bookout, *upmem, *upbook, *lent, *uplent;
	bookrecord r; updatedbook ur; 
	memberRecord mr; updatedmember umr; 
	lentbook lb; 
	date din;
	int getmid, getbkno;
	char getbid[10], foundit='n', condt='n', flag='n', retrnagain;
	system("cls"); 
	bkProcessOutput();
	
	cout<<"Enter Member's ID No: "; 
	cin>>getmid;
	cin.get();
	cout<<endl<<"Enter Book's ID: "; 
	gets(getbid);
	cout<<endl<<"Enter Book's No: "; 
	cin>>getbkno;
	
	lent=fopen("BookLent.dat","rb");
	fread(&lb,sizeof(lb),1,lent);
	while(!feof(lent) && foundit!='y')
	{
		if(getmid==lb.lentmemid && strcmpi(getbid,lb.lentbkid)==0 && getbkno==lb.lentbkno)
		{
			foundit='y'; 
			cout<<endl<<"Enter Current Date(day/month/year): "; 
			cin>>din.day>>dumm>>din.month>>dumm>>din.year;
			if(din.year<=lb.dtexpire.year)
			{
				if(din.month<=lb.dtexpire.month)
				{
					if(din.day<=lb.dtexpire.day)
						condt='y';
				}
			}
		}
		fread(&lb,sizeof(lb),1,lent);
	}
	fclose(lent);
	if(foundit=='y' && condt!='y')
		cout<<"\nExpiry Date of Book's No "<<getbkno<<" ( Book's ID - "<<lb.lentbkid<<" )"<<" has been over !!!"<<endl;
	if(foundit=='y')
	{
		lent=fopen("BookLent.dat","rb"); uplent=fopen("tempLent.dat","wb");
		fread(&lb,sizeof(lb),1,lent);
		while(!feof(lent))
		{
			if(getmid!=lb.lentmemid || strcmpi(getbid,lb.lentbkid)!=0 || getbkno!=lb.lentbkno)
			{		
				fwrite(&lb,sizeof(lb),1,uplent);
			}
			fread(&lb,sizeof(lb),1,lent);			
		}
		fclose(lent); fclose(uplent);
				
		lent=fopen("BookLent.dat","wb"); uplent=fopen("tempLent.dat","rb");
		fread(&lb,sizeof(lb),1,uplent);
		while(!feof(uplent))
		{
			fwrite(&lb,sizeof(lb),1,lent);
			fread(&lb,sizeof(lb),1,uplent);
		}
		fclose(lent); fclose(uplent);
		
		memout=fopen("MemberList.dat","rb"); upmem=fopen("tempMember.dat","wb");
		fread(&mr,sizeof(mr),1,memout);
		while(!feof(memout))
		{
			umr.upmemberid=mr.memberid;
			strcpy(umr.uprollno,mr.rollno);
			strcpy(umr.upMemname,mr.memName);
			strcpy(umr.upAddress,mr.address);
			strcpy(umr.upPh,mr.ph);
			umr.upMemberlimit=mr.memberlimit;
			umr.upexpdate=mr.expdate;
			umr.upstartdate=mr.startdate;
			if(getmid==umr.upmemberid && umr.upMemberlimit<4 && flag!='y')
			{
				flag='y';
				umr.upMemberlimit=umr.upMemberlimit+1;
				cout<<"\nLimit of Member's ID No "<<getmid<<" is "<<umr.upMemberlimit<<" now."<<endl;
			}
			fwrite(&umr,sizeof(umr),1,upmem);
			fread(&mr,sizeof(mr),1,memout);
		}
		fclose(memout); fclose(upmem);
				
		if(flag!='y')
			cout<<"\nLimit of Member's ID No "<<getmid<<" has been already full !!!"<<endl;
					
		memout=fopen("MemberList.dat","wb"); upmem=fopen("tempMember.dat","rb");
		fread(&umr,sizeof(umr),1,upmem);
		while(!feof(upmem))
		{
			mr.memberid=umr.upmemberid;
			strcpy(mr.rollno,umr.uprollno);
			strcpy(mr.memName,umr.upMemname);
			strcpy(mr.address,umr.upAddress);
			strcpy(mr.ph,umr.upPh);
			mr.memberlimit=umr.upMemberlimit;
			mr.expdate=umr.upexpdate;
			mr.startdate=umr.upstartdate;
					
			fwrite(&mr,sizeof(mr),1,memout);
			fread(&umr,sizeof(umr),1,upmem);
		}
		fclose(memout); fclose(upmem);
		
		flag='n';
		bookout=fopen("BookList.dat","rb"); upbook=fopen("tempBook.dat","wb");
		fread(&r,sizeof(r),1,bookout);
		while(!feof(bookout))
		{
			strcpy(ur.upbookid,r.bookid);
			strcpy(ur.upBkname,r.bkName);
			strcpy(ur.upAuthorName,r.authorName);
			strcpy(ur.upBkinfo,r.bkInfo);
			ur.uptotalBook=r.totalBook;
			ur.upQuantity=r.bkQuantity;
			if(strcmpi(getbid,ur.upbookid)==0 && ur.upQuantity<ur.uptotalBook && flag!='y')
			{
				flag='y';
				ur.upQuantity=ur.upQuantity+1;
				cout<<"\nQuantity of Book's ID "<<ur.upbookid<<" is "<<ur.upQuantity<<" now."<<endl;
			}
			fwrite(&ur,sizeof(ur),1,upbook);
			fread(&r,sizeof(r),1,bookout);
		}
		fclose(bookout); fclose(upbook);
		
		if(flag!='y')
			cout<<"\nQuantity of Book's ID "<<getmid<<" has been already full !!!"<<endl;
				
		bookout=fopen("BookList.dat","wb"); upbook=fopen("tempBook.dat","rb");
		fread(&ur,sizeof(ur),1,upbook);
		while(!feof(upbook))
		{
			strcpy(r.bookid,ur.upbookid);
			strcpy(r.bkName,ur.upBkname);
			strcpy(r.authorName,ur.upAuthorName);
			strcpy(r.bkInfo,ur.upBkinfo);
			r.totalBook=ur.uptotalBook;
			r.bkQuantity=ur.upQuantity;
					
			fwrite(&r,sizeof(r),1,bookout);
			fread(&ur,sizeof(ur),1,upbook);
		}
		fclose(bookout); fclose(upbook);
		
	}
	else
		cout<<"\nInput Member's ID No "<<getmid<<" and Book's No "<<getbkno<<"( Book's ID - "<<getbid<<" )"
			<<" is not found in the file !!!"<<endl;

	cout<<"\nDo you want to continue returning(y Or n)?: "; 
	cin>>retrnagain;
	
	if(tolower(retrnagain)=='y')
		bookreturn();		
		
	return;
}

//Current List of Members and Books
void currentList()
{
	system("cls");
	cout<<"\t\t\t\t\t\t\tCurrent Issued Books List"<<endl<<endl;
	starline('_',68);
   	cout<<endl <<endl;
	cout<<setw(12)<<"Member ID No"<<setw(12)<<"Book ID"<<setw(12)<<"Book No"
	<<setw(15)<<"Start Date"<<setw(15)<<"Expiry Date"<<endl;
	starline('_',68);
   	cout<<endl <<endl;
	
	FILE *curList;
	lentbook lb;
	
	curList=fopen("BookLent.dat","rb");	
	fread(&lb,sizeof(lb),1,curList);
	while(!feof(curList))
	{
		cout<<setw(12)<<lb.lentmemid<<setw(12)<<lb.lentbkid<<setw(12)<<lb.lentbkno
			<<setw(8)<<right<<lb.dtstart.day<<'/'<<lb.dtstart.month<<'/'<<lb.dtstart.year
			<<setw(8)<<right<<lb.dtexpire.day<<'/'<<lb.dtexpire.month<<'/'<<lb.dtexpire.year<<endl;
		cout<<endl;
			
		fread(&lb,sizeof(lb),1,curList);
	}
	fclose(curList);
	cout<<endl;
	
	return;
}

//User Option
char chooseUser()
{
	int userchoice;
	char useragain;
    do{
   	system("cls"); 
   	labelUser();
	
    cout<<"  1.Search Book Records."<<endl<<endl
	    <<"  2.Check Member's card expire date."<<endl<<endl
	    <<"  3.Write comments for Library."<<endl<<endl
    	<<"  4.Exit from User Option."<<endl<<endl
	    <<"  Choose (1 or 2 or 3 or 4): ";
    cin>>userchoice;
    
    switch(userchoice)
    {
    	
    	case 1:useragain=checkbooksinfo(); break;
    	case 2:useragain=checkmemDate(); break;
    	case 3:useragain=usercomment(); break;
    	case 4:userchoice=4; useragain='n'; break;
	   	default:userchoice=4; useragain='n';
	}
}while(useragain=='n' && userchoice<4);
		
	return useragain;
}

//Check Books' Informations
char checkbooksinfo()
{
	system("cls"); 
	labelUser();
	FILE *bookin;
	bookrecord br; updatedbook ur;
	int userch;
	char schagain='y';
   	int  byName, flag=1; 
	char userStitle[100], userSinfo[100], userSAname[100];
	
	cout<<"  1.All Book Records."<<endl<<endl
	    <<"  2.Search Book Record with Book's Title."<<endl<<endl
	    <<"  3.Search Book Record with Book's Author Name."<<endl<<endl
	    <<"  4.Search Book Record with Book's Information."<<endl<<endl
	    <<"  5.Exit from Search Option."<<endl<<endl
	    <<"  Choose (1 or 2 or 3 or 4 or 5): ";
    cin>>userch;
    cin.get();
    
    switch(userch)
    {
   		case 1:	system("cls");
   			flag=0;
			bookin=fopen("BookList.dat","rb");
		 
          	cout<<"\t\t\t\t\t\t\tAll Books of Library";
			cout<<endl;
			starline('_',68);
			cout<<endl<<endl;
          	labelbookoption2();
          	cout<<endl;
          	
           	fread(&br,sizeof(br),1,bookin);
            while(!feof(bookin))
            {
      	
				cout<<setw(5)<<br.bookid<<setw(52)<<br.bkName<<setw(32)<<br.authorName
					<<setw(32)<<br.bkInfo;
				if(br.bkQuantity==0)
  					cout<<"(Not available)"<<endl;
   				else
     				cout<<"(Available)"<<endl;
   				cout<<endl;
					
              	fread(&br,sizeof(br),1,bookin);
    		}
      		fclose(bookin);
		break;
			
		case 2:system("cls");
			bookoutput(); byName=8;
			bookin=fopen("BookList.dat","rb"); 
			cout<<"Enter Book's Title: "; 
			gets(userStitle);
      	   
       		fread(&br,sizeof(br),1,bookin);
       		while(!feof(bookin))
       		{
       			byName=strcmpi(userStitle,br.bkName);
       			if(byName==0)
       			{
       				cout<<endl<<endl;
       				starline('_',68);
					cout<<endl<<endl;
       				labelbookoption2();
       				cout<<endl;
       					cout<<setw(5)<<br.bookid<<setw(52)<<br.bkName<<setw(32)
						   <<br.authorName<<setw(32)<<br.bkInfo;
            
              		if(br.bkQuantity==0)
	 	           		cout<<"(Not available)"<<endl;
	            	else
	 	        		cout<<"(Available)"<<endl;
       				flag=0;
  				}
  				fread(&br,sizeof(br),1,bookin);
  			}
  			fclose(bookin);
  			cout<<endl;
		break;
  			
		case 3:system("cls");
			bookoutput(); byName=8;
		 	bookin=fopen("BookList.dat","rb");
		 	
	   		cout<<"Enter Book's Author Name: "; 
   			gets(userSAname);
   			cout<<endl<<endl;
   			starline('_',68);
			cout<<endl<<endl;
	   		labelbookoption2();
	   		cout<<endl;
	   		
       		fread(&br,sizeof(br),1,bookin);
       		while(!feof(bookin))
       		{
       			byName=strcmpi(userSAname,br.authorName);
       			if(byName==0)
       			{
       				cout<<setw(5)<<br.bookid<<setw(52)<<br.bkName<<setw(32)
					   <<br.authorName<<setw(32)<<br.bkInfo;
					   
       				if(br.bkQuantity==0)
	 	         		cout<<"(Not available)"<<endl;
            		else
	 	        		cout<<"(Available)"<<endl;
	        		cout<<endl;
       				flag=0;
  				}
  				fread(&br,sizeof(br),1,bookin);
  			}
  			fclose(bookin); 
		break;
	
		case 4:system("cls");
			bookoutput(); 
		 	bookin=fopen("BookList.dat","rb");
		 	
	   		cout<<"Enter Book's Information : "; 
	   		gets(userSinfo);
	   		cout<<endl<<endl;
	   		starline('_',68);
			cout<<endl<<endl;
	   		labelbookoption2();
	   		cout<<endl;
	   		
       		fread(&br,sizeof(br),1,bookin);
       		while(!feof(bookin))
       		{
       			byName=strcmpi(userSinfo,br.bkInfo);
       			if(byName==0)
       			{
		            cout<<setw(5)<<br.bookid<<setw(52)<<br.bkName<<setw(32)
						<<br.authorName<<setw(32)<<br.bkInfo;
           			if(br.bkQuantity==0)
	 	         		cout<<"(Not available) "<<endl;
            		else
	 	        		cout<<"(Available)"<<endl;
    				cout<<endl;
       				flag=0;
  				}
  				fread(&br,sizeof(br),1,bookin);
  			}
  			fclose(bookin); 
		break;
	
		case 5:userch=5; schagain='n'; break;
	
		default:userch=5; schagain='n'; 
   	}
	if(flag!=0 && userch<5)	
 		cout<<"Book Record is not found in the file !!!"<<endl;
 		
	if(userch<5)
 	{	
		cout<<"\nDo you want to go back to Search Option(y Or n)?: ";
		cin>>schagain;
	}	
	if(tolower(schagain)=='y')
		schagain=checkbooksinfo();
	else 
		schagain='n';
		
	return schagain;
}

//checking expire date of member card(check with ID oR name)

char checkmemDate()
{
	system("cls");
	FILE *fp;
	char expagain;
	int userSno, flag=1;
   	memberRecord mr;
   	labelUser();
	fp=fopen("MemberList.dat","rb");
	
	cout<<"Enter Member's ID No: ";
 	cin>>userSno;
 	
 	
	fread(&mr,sizeof(mr),1,fp);
	while(!feof(fp))
	{
		if(userSno==mr.memberid)
		{
  			cout<<endl<<"Expiry Date of Member's ID No "<<userSno<<" is "<<mr.expdate.day<<"/"
			 	<<mr.expdate.month<<"/"<<mr.expdate.year<<endl;
       		flag=0;
		}
		fread(&mr,sizeof(mr),1,fp);
	}
	fclose(fp);

	if(flag!=0)
		cout<<endl<<"Input Member's ID No is not found in the file !!!"<<endl;
	
	cout<<"\nDo you want to continue to check Member's Card Expiry Date(y Or n)?: ";
	cin>>expagain;
	
	if(tolower(expagain)=='y')
		expagain=checkmemDate();
	else
		expagain='n';
	
	return expagain;
}

///users' comment
char usercomment()
{
	system("cls");
	FILE *fp;
	writeCmt getcmt;
	char cmtagain;
	labelUser();
	fp=fopen("Comments.dat","ab");
	
	cout<<"Enter Current Date(day/month/year): ";
	cin>>getcmt.wdate.day>>dumm>>getcmt.wdate.month>>dumm>>getcmt.wdate.year;
	cin.get();
	
	cout<<"\nEnter Comments: ";
	gets(getcmt.comment);
	cout<<endl;
	
	fwrite(&getcmt,sizeof(getcmt),1,fp);
	fclose(fp);
	
	cout<<"Press Any Key to Continue...";
	getch();
	cmtagain='n';
	
	return cmtagain;
}

char readComments()
{
	system("cls"); 
	FILE *fp;
	char rcmtagain;
	writeCmt readcmt;
	
	fp=fopen("Comments.dat","rb");
	starline('*',68);
   	cout<<endl<<endl;
	cout<<"\t\t\t\t\t\t\t    All Comments"<<endl<<endl;
	starline('*',68);
   	cout<<endl<<endl;
   	cout<<"Date\t"<<"\tComments"<<endl<<endl;
   	
   	fread(&readcmt,sizeof(readcmt),1,fp);
   	while(!feof(fp))
   	{
   		cout<<readcmt.wdate.day<<"/"<<readcmt.wdate.month
		   	<<"/"<<readcmt.wdate.year<<"\t";
   		cout<<readcmt.comment<<endl<<endl;
   		fread(&readcmt,sizeof(readcmt),1,fp);
 	}
 	fclose(fp);
 	
 	cout<<"\nPress Any Key to Continue...";
 	getch();
 	rcmtagain='n';
		
	return rcmtagain;	
}


///label
void labelLibrary()
{
	starline('*',68);
   	cout<<endl ;
   	cout<<"\t\t\t\t\t\t\tLibrary Management System "<<endl<<endl
   		<<"\t\t\t\t\t\t\t\tWelcome"<<endl;
   	starline('*',68);
   	cout<<endl<<endl;
   	return;
}
void labelbookoption()
{
   	starline('_',68);
   	cout<<endl;
   	cout<<setw(5)<<"ID"<<setw(51)<<"Name"<<setw(29)<<"Author"<<setw(33)
	   	<<"Information"<<setw(7)<<"Total"<<setw(10)<<"Quantity";
   	cout<<endl;
   	starline('_',68);
   	cout<<endl<<endl;
 	return;
}

void labelbookoption2()
{        		
	cout<<setw(5)<<"ID"<<setw(52)<<"Title"<<setw(32)<<"Author"<<setw(32)<<"Information";
	cout<<endl ;
	starline('_',68);
 	cout<<endl;	
	return;
}

void labelmemberoption()
{
   	starline('_',68);
   	cout<<endl <<endl;
   	cout<<setw(3)<<"ID"<<setw(9)<<"Roll-No"<<setw(20)<<"Name"<<setw(44)<<"Address"<<setw(14)
   	<<"Phone-no"<<setw(12)<<"Card Limit"<<setw(15)<<"Start Date"<<setw(15)<<"Expiry Date";
   	cout<<endl ;
   	starline('_',68);
   	cout<<endl<<endl;
	return;	
}

void bookoutput()
{
	starline('*',68); cout<<endl<<endl;
   	cout<<"\t\t\t\t\t\t\t      Book Option"<<endl<<endl;
   	starline('*',68); cout<<endl<<endl;
	return;	
}

void memberOutput()
{
   	starline('*',68); cout<<endl<<endl;
   	cout<<"\t\t\t\t\t\t\t    Member Option"<<endl<<endl;
   	starline('*',68); cout<<endl<<endl;
}

void labelAdmin()
{
	starline('*',68);
   	cout<<endl ;
   	cout<<"\t\t\t\t\t\t\tLibrary Management System "<<endl<<endl;
   	cout<<"\t\t\t\t\t\t\t\tAdmin Menu"<<endl<<endl;
   	starline('*',68);
   	cout<<endl<<endl;
   	return;
}

void labelUser()
{
	starline('*',68);
   	cout<<endl ;
   	cout<<"\t\t\t\t\t\t\tLibrary Management System "<<endl<<endl;
   	cout<<"\t\t\t\t\t\t\t\tUser Menu"<<endl;
   	starline('*',68);
   	cout<<endl<<endl;
   	return;
}

void bkProcessOutput()
{
	starline('*',68);cout<<endl<<endl;
	cout<<"\t\t\t\t\t\t\t  Books Issue Option"<<endl<<endl;
	starline('*',68);cout<<endl<<endl;
}
