#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include <cwchar>
#include <windows.h>
using namespace std;
int rec_flag=0,no=0;
char rec_ind[5];

struct record
{
	char ph_no[50], name[15], addr[50], email[50],ind[10];
}rec[50];

struct index
{
    char ph_no[50], ind[20];
}in[20],temp;

int owner_authen() {
	char o_username[20], o_password[20];
	char o_user[20] = "admin", o_pass[20] = "admi";
	cout << endl << endl;
	cout.width(25);
	cout << "Enter id and Password\n" << "------------------------------------------------------------------------------------\n";
	cout << endl << "username: ";
	cin >> o_username;
	cout << "password: ";
	cin >> o_password;
	cout << "------------------------------------------------------------------------------------\n";
	if (strcmp(o_username, o_user) == 0 && strcmp(o_password, o_pass) == 0)
		return 1;
	else
		return 0;
}


void sort_index()
{
	int i, j;
	for (i = 0;i < no - 1;i++)
		for (j = 0;j < no - i - 1;j++)
			if (strcmp(in[j].ph_no, in[j + 1].ph_no) > 0)
			{
				temp = in[j];
				in[j] = in[j + 1];
				in[j + 1] = temp;
			}
}



void retrive_record(char *ind) {
	
	int flag = 0, i = 0;
	
    for(int i=0;i<no;i++) {
      if(strcmp(rec[i].ind,ind)==0) {
      	strcpy(rec_ind,ind);
		  rec_flag=1;
		  cout<<"\nRecord found:";
		  cout<<rec[i].ph_no<<"|"<<rec[i].name<<"|"<<rec[i].addr<<"|"<<rec[i].email<<"\n";
		  return;
		}
    }
}




	

int search_index(char *ph_no) {

	int flag=0;
	for(int i=0;i<no;i++) {
	  if(strcmp (in[i].ph_no,ph_no)==0) {
	  	retrive_record(in[i].ind);
		flag=1;
		}
	}
    if(flag)
		return 1;
	else
		return -1;
}

int search_ph_no(char *ph_no,int j) {

	int flag=0;
	for(int i=0;i<j;i++) {
	  if(strcmp (rec[i].ph_no,ph_no)==0) {
	     flag=1;
		 break;
		}
    }
    if(flag)
	  return 1;
    else
	  return -1;
}

void delet(char *pph_no) {
	
	rec_flag=0;
    int fr=0;
    search_index(pph_no);
    if(!rec_flag) {
		cout<<"\nDeletion failed record not found";
		return;
	}
    for(int i=0;i<no;i++) {
		if(strcmp(rec[i].ind,rec_ind)==0) {
		
			fr=i;
			break;
		}
	}
    for(int i=fr;i<no-1;i++) {
		rec[i]=rec[i+1];
		char str[3]; //itoa(i,str,10);
		sprintf(str,"%d",i);
		strcpy(rec[i].ind,str);
	}
    no--;
    fstream f1,f2;
    f1.open("tel1.txt",ios::out);
    f2.open("telindex1.txt",ios::out);
    for(int i=0;i<no;i++) {
		strcpy(in[i].ph_no,rec[i].ph_no);
		strcpy(in[i].ind,rec[i].ind);
	}
	sort_index();
    for(int i=0;i<no;i++) {
		f1<<rec[i].ind<<"|"<<rec[i].ph_no<<"|"<<rec[i].name<<"|"<<rec[i].addr<<"|"<<rec[i].email<<"\n";
		f2<<in[i].ph_no<<"|"<<in[i].ind<<"\n";
	}
	f1.close();
	f2.close();
    cout<<"\nDeletion successful\n";
}

void modify(char *ph_no) {

	fstream f3;
	char ind[5];
	int i, j;
	f3.open("tel1.txt", ios::in);
	if(!f3) {
		cout << "err\\\\\\\\\\\\\\\\n";
		exit(0);
	}
	i=0;
	while(!f3.eof()) {
		f3.getline(rec[i].ind, 5, '|');
		f3.getline(rec[i].ph_no, 50, '|');
		f3.getline(rec[i].name, 15, '|');
		f3.getline(rec[i].addr, 50, '|');
		f3.getline(rec[i].email,50,'\n');
		strcpy(rec[i].ind,ind);
		strcpy(in[i].ph_no,ph_no);
		strcpy(in[i].ind,ind);
		i++;
	}
	
	for(j=0;j<i;j++) {

		if(strcmp(ph_no, rec[j].ph_no)==0) {
			cout << "\nThe old values of the record with Phone number " << ph_no << " are: ";
			cout << "\nPhone Number: " << rec[j].ph_no;
			cout << "\nName: " << rec[j].name;
			cout << "\nAddress: \n" << rec[j].addr;
				cout << "\nEmail: \n\n" << rec[j].email;
			
			cout << "\nEnter the new data: ";
			cout << "\nPhone number: "; cin >> rec[j].ph_no;
			cout << "\nName "; cin >> rec[j].name;
			cout << "\nAddress: "; cin >> rec[j].addr;
			cout<<"\nEmail:";cin>>rec[j].email;
			break;
		}
	}
	if(j==i) {
		cout << "\nThe record with Phone Number " << ph_no << " is not present\n";
		return;
	}
	f3.close();
	fstream f4, f5;
	f4.open("tel1.txt", ios::out);
	f5.open("telindex1.txt", ios::out);
	if(!f4) {
		cout << "err\\\\\\\\\\\\\\\\n";
		return;
	}
	for(j=0;j<i;j++){
	
		f4 << j<<'|'<<rec[j].ph_no << '|' << rec[j].name << '|' << rec[j].addr << '|' << rec[j].email<< endl;
		strcpy(in[j].ph_no,rec[j].ph_no);
        f5 << in[j].ph_no << '|'<<j<<"\n";
}
			cout<<in[j].ph_no;
		
	f4.close();
}



int main() {
	
		system("color E1");
			CONSOLE_FONT_INFOEX cfi;
cfi.cbSize = sizeof(cfi);
cfi.nFont = 0;
cfi.dwFontSize.X = 0;                   // Width of each character in the font
cfi.dwFontSize.Y = 20;                  // Height
cfi.FontFamily = FF_DONTCARE;
cfi.FontWeight = FW_NORMAL;
std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


	fstream file1,file3;
	int choice, i;
	char ind[5],pph_no[50],ph_no[50],name[15],addr[50],email[50];
	 cout << "\n\n\t\t-----------TELEPHONE DIRECTORY-------------\n\n";
	
	 
		int check;
		check = owner_authen();
		if (check == 1)
		{system("CLS");
			cout << "Welcome \n" << "----------------------------------------------------------------\n";
			while (1)
			{
	
	
    for(;;) {
    
        cout << "\nPlease choose among the following options\n";
		cout << "\n1:Enter new directory\n2:Search directory\n3:Delete existing directory\n4:Display existing directory\n5:Modify existing directory\n6:Exit\n";
		cout << "\nEnter your choice\n";
		cin >> choice;
		switch(choice) {
			case 1: {
				fstream file1;
				file1.open("tel1.txt", ios::app|ios::out);
				if(!file1) {
					cout << "File creation error\n";
					exit(0);
				}
				int n;
			    system("CLS");
				cout<<"Please Enter no of citizen\n";
				cin>>n;
	        	cout<<"enter the details\n";
		        for(i=no;i<no+n;i++)
				{
				cout<<"\nEnter Citizen: "<<i+1<<" ";
			
					cout << "\nEnter Phone Number: ";
				cin >> rec[i].ph_no;
					cout << "\nEnter Name: ";
				cin >> rec[i].name;
			
				cout << "\nEnter Address: ";
				cin >> rec[i].addr;
				cout << "\nEnter Email: ";
				cin >> rec[i].email;
				int q=search_ph_no(rec[i].ph_no,i);
				file1<<i<<"|"<<rec[i].ph_no<<"|"<<rec[i].name<<"|"<<rec[i].addr<<"|"<<rec[i].email<<"\n";
				}
				file1.close();
				no=no+n;
				fstream f1, file2;
				file2.open("telindex1.txt",ios::out);
				f1.open("tel1.txt",ios::in);
			for(i=0;i<no;i++)
				 {
					f1.getline(ind,5,'|');
					f1.getline(ph_no,50,'|');
					f1.getline(name,15,'|');
					f1.getline(addr,50,'|');
					f1.getline(email,50,'\n');
					strcpy(rec[i].ind,ind);
					strcpy(in[i].ph_no,ph_no);
					strcpy(in[i].ind,ind);
				}
				sort_index();
				
	     //cout<<"\nafter sorting index file contents are\n";
	       //for(i=0;i<no;i++)
	       //cout<<in[i].ph_no<<" "<<in[i].ind<<endl;
	       for(i=0;i<no;i++)
	       {
		   file2<<in[i].ph_no<<"|"<<in[i].ind<<"\n";
	       }
	       file1.close();
	       file2.close();
	       break;
	      }
			case 2: {
				system("CLS");
				cout<<"\nEnter the Phone Number of the person whose record is to be displayed\n";
				cin>>pph_no;
				int q=search_index(pph_no);
				if(q==1)
					cout<<"\nSearch sucessful\n";
				else
					cout<<"\nNot successful\n";
				break;
			}
			case 3: {
				system("CLS");
				cout<<"\nEnter the Phone Number of the person whose record is to be deleted\n";
				cin>>pph_no;
				delet(pph_no);
				break;
			}
			case 4: {
				system("CLS");
				fstream f1;
				f1.open("tel1.txt",ios::in);
				if(!f1) {
					cout<<"err\\\\\\\\\\\\\\\\n";
					exit(0);
				}
				int i=0;
				while(i!=no) {
					f1.getline(ind,5,'|');
					f1.getline(ph_no,50,'|');
					f1.getline(name,15,'|');
					f1.getline(addr,50,'|');
					f1.getline(email,50,'\n');
					cout<<"Phone Number: "<<ph_no<<"\t"<<"Name: "<<name<<"\t"<<"Address:"<<addr<<"\t"<<"Email\n"<<email<<endl;
					i++;
				}
				break;
			}
			case 5:
				system("CLS");
			     cout<<"\nEnter the phone Number of the person whose record needs to be modified\n";
				cin>>pph_no;
				modify(pph_no);
				break;		

			
			case 6: {
				cout<<"\nEnding program";
				exit(0);
			}
			default: cout<<"\nInvalid\n"; break;
			
			
		}}}
	}
}

