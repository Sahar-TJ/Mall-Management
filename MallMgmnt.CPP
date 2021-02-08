#include<iostream.h>
#include<string.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<fstream.h>
void create_record();
void delete_record();
void modify_record();
void search_record();
void viewall_records();
void csearch_record();
void cview_record();

class mall
{
 int shopno;
 char name[25];
 float come,go;
 public:
 void getdata()
{
	cout<<endl<<"Enter name: ";
	gets(name);
	cout<<"Enter shop number: ";
	cin>>shopno;
	cout<<endl<<"Enter visiting hours: ";
	cout<<endl<<"\tFrom: ";
	cin>>come;
	cout<<" To: ";
	cin>>go;
}
void putdata()
{
	cout<<endl<<"Name: "<<name;
	cout<<endl<<"Shopno: "<<shopno;
	cout<<endl<<"Visiting hours: "<<come<<" - "<<go;
	cout<<endl<<"********************"<<endl;
}
int ret_roll()
{
   return shopno;
}
char *ret_name()
{
	return name;
}
};
int main()
{
  clrscr();
  int choice,choicec,choicemain;
  char cont,ccont;
  char un[10]="mmeis";
  char pw[10]="student";
  char unc[10]="mall";
  char pwc[10]="123";
  char u[10],p[10];
  cout<<"\tWhich user do u want to choose?\n\t    1.Admin      2.Customer\n"<<endl<<endl;
  cout<<"Enter choice: ";
  cin>>choicemain;
  switch(choicemain)
  {
  case 1:
  cout<<"\nHello Admin! Pls enter the following:"<<endl;
  break;
  case 2:
  cout<<"\nHey Customer! Pls enter the following:"<<endl;
  break;
  default:
  cout<<"\n\t\tWRONG CHOICE!"<<endl;
  exit(0);
  }
  cout<<"\nEnter the username: ";
  cin>>u;
  cout<<endl<<"\nEnter the password: ";
  cin>>p;
if(strcmp(un,u)==0&&strcmp(pw,p)==0)
{
do
{
  clrscr();
  cout<<"\t\t********MALL MANAGEMENT SYSTEM********";
  cout<<endl<<"1.Create a shop"<<endl<<"2.Delete a shop"<<endl<<"3.Modify a shop"<<endl;
  cout<<"4.Search a shop"<<endl<<"5.View data"<<endl<<"6.Exit";
  cout<<endl<<"\tEnter your choice: ";
  cin>>choice;
switch(choice)
{
case 1:
create_record();
break;
case 2:
delete_record();
break;
case 3:
modify_record();
break;
case 4:
search_record();
break;
case 5:
viewall_records();
break;
case 6:
exit(0);
break;
default:
cout<<"\n\tWRONG CHOICE!"<<endl;
}
cout<<endl<<"Press y to continue: ";
cin>>cont;
}while(cont=='y');
}



else if(strcmp(unc,u)==0&&strcmp(pwc,p)==0)
{
do
{
	clrscr();
	cout<<endl<<"\t\tHi there!"<<endl<<"\t    Welcome to the mall!"<<endl;
	cout<<endl<<"1.Search a shop \n2.View all shops \n3.Exit";
	cout<<endl<<"\tEnter a choice: ";
	cin>>choicec;
switch(choicec)
{
case 1:
csearch_record();
break;
case 2:
cview_record();
break;
case 3:
exit(0);
break;
default:
cout<<endl<<"\n\tWRONG CHOICE!!!"<<endl;
break;
}
cout<<"Do you want to continue? Then press 'k' for yes ";
cin>>ccont;
}while(ccont=='k');
}



getch();
return 0;
}


void create_record()
{
	mall s;
	s.getdata();
	ofstream fout;
	fout.open("student.dat",ios::app|ios::binary);
	fout.write((char *)&s,sizeof(s));
	fout.close();
}
void viewall_records()
{
	mall s;
	ifstream fin("student.dat",ios::in|ios::binary);
	fin.read((char *)&s,sizeof(s));
	while(!fin.eof())
{
		s.putdata();
		fin.read((char *)&s,sizeof(s));
}
	fin.close();
}
void search_record()
{
	mall s;
	int r;
	int found=0;
	ifstream fin;
	fin.open("student.dat",ios::in|ios::binary);
	cout<<endl<<"Enter the shop number of the mall to be searched: ";
	cin>>r;
	while(!fin.eof())
{
		fin.read((char *)&s,sizeof(s));
		if(s.ret_roll()==r)
{
		  s.putdata();
		  found=1;
		  break;
}
}
	if(found==0)
	cout<<"\n\tSEARCH UNSUCCESSFULL!"<<endl<<endl;
	fin.close();
}
void modify_record()
{
	mall s;
	fstream file("student.dat",ios::in|ios::out|ios::binary);
	int found=0,r;
	cout<<endl<<"Enter the shop number of the mall to be modified: ";
	cin>>r;
	while(!file.eof())
{
	 file.read((char *)&s,sizeof(s));
	 if(s.ret_roll()==r)
{
	  s.putdata();
	  found=1;
	  cout<<endl<<"Enter the new data: "<<endl;
	  s.getdata();
	  int pos=file.tellg()-sizeof(s);
	  file.seekp(pos,ios::beg);
	  file.write((char *)&s,sizeof(s));
	  break;
}
}
	if(found==0)
	cout<<"\nRecord doesnt exist!"<<endl<<endl;
	file.close();
}
void delete_record()
{
	mall s;
	ifstream fin("student.dat",ios::in|ios::binary);
	ofstream fout("temp.dat",ios::out|ios::binary);
	int r;
	int found=0;
	cout<<endl<<"Enter the shop number to be deleted : ";
	cin>>r;
	while(fin.read((char *)&s,sizeof(s)))
{
	if(s.ret_roll()!=r)
{
	 fout.write((char *)&s,sizeof(s));
}
	else
{
	  cout<<"\n\tDATA DELETED!"<<endl<<endl;
	  s.putdata();
	  found=1;
}
}
fin.close();
fout.close();
remove("student.dat");
rename("temp.dat","student.dat");
if (found==0)
cout<<endl<<"\tRECORD DOESN'T EXIST!\n";
}

void csearch_record()
{
	mall s;
	char n[25];
	int found=0;
	ifstream fin;
	fin.open("student.dat",ios::in|ios::binary);
	cout<<endl<<"Enter the shop name of the mall to be searched: ";
	cin>>n;
	while(!fin.eof())
{
		fin.read((char *)&s,sizeof(s));
		if(strcmp(s.ret_name(),n)==0)
{
		  s.putdata();
		  found=1;
		  break;
}
}
	if(found==0)
	cout<<"\n\tSEARCH UNSUCCESSFULL!"<<endl<<endl;
	fin.close();
}



void cview_record()
{
	mall s;
	ifstream fin("student.dat",ios::in|ios::binary);
	fin.read((char *)&s,sizeof(s));
	while(!fin.eof())
{
		s.putdata();
		fin.read((char *)&s,sizeof(s));
}
	fin.close();
}

