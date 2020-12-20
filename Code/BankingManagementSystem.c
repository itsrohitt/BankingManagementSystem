#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<dos.h>

void displayWelcomePage();

void loginPageAccountHolder();
void displayAccountHolderMenu(long int);
void displayNewAccountPage();
int viewAccDetails(long int,int);
void updateAccDetails(long int);
void ReadAndUpdate();
void viewAccountBalance(long int);
void viewTransactionHistory(long int);
void addToTransactions(long int,char[],long long int);
void depositAmount(long int);
void withdrawAmount(long int);
void changePin(long int);
void closeAccount(long int);
int generateAccNo();

void loginPageEmployee();
void displayEmployeeMenu();
void AccountsList();
void viewAccHolderDetails();
void editAccHolderDetails();
void closeAccHolderAccount();
void addMoneyToATM();
void disableATMServices();

void updateATMAmount(char, long long int);
long long int checkATMAmount();

void loadingPage(char[]);
void menuBorder();
void gotoxy(int, int);
void clrscr(void);

COORD coord={0,0};
FILE *ptr,*ptr1,*ptr2;
boolean ATMServices = TRUE;

struct newAcc
{
    long int AccNo;
    int PIN;
    char fullName[20];
    char fatherName[20];
    int age;
    char gender[10];
    char nationality[20];
    int DOB;
    long long int phoneNo;
    char AadhaarNo[15];
    char MaritalStatus[5];
    char EducationLevel[20];
    char occupation[20];
    int accBal;
}Account,traverse;

int main()
{
    char welMsge[] = "WELCOME TO VCE STUDENT BANK.";
    char tqMsge[] = "THANK YOU";
    srand(time(NULL));
    loadingPage(welMsge);
    displayWelcomePage();
    Sleep(1000);
    clrscr();
    loadingPage(tqMsge);
}

void displayWelcomePage()
{
    int choice;
    clrscr();
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tWELCOME TO BANKING MANAGEMENT SYSTEM\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,14);      printf("\xDB\t\xB2\xB2\xB2 1. LOGIN TO YOUR ACCOUNT");
    gotoxy(40,16);      printf("\xDB\t\xB2\xB2\xB2 2. CREATE AN ACCOUNT");
    gotoxy(40,18);      printf("\xDB\t\xB2\xB2\xB2 3. TO LOGIN AS EMPLOYEE");
    gotoxy(40,20);      printf("\xDB\t\xB2\xB2\xB2 4. EXIT");
    gotoxy(42,26);      printf("Enter your Choice : ");        scanf("%d",&choice);    fflush(stdin);
    switch(choice)
    {
        case 1:     loginPageAccountHolder();       break;
        case 2:     displayNewAccountPage();        break;
        case 3:     loginPageEmployee();            break;
        case 4:     break;
        default:    printf("\033[1;31m");
                    gotoxy(64,28);      printf("INVALID CHOICE!!"); 
                    printf("\033[0m");
                    Sleep(1500);        displayWelcomePage();
                    break;
    }
}

void loginPageAccountHolder()
{
    clrscr();
    long int Ano;
    int pw,flag=0;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tLOGIN TO YOUR ACCOUNT\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,14);      printf("\xDB\t\xB2\xB2\xB2 ENTER ACCOUNT NUMBER : ");
    gotoxy(40,16);      printf("\xDB\t\xB2\xB2\xB2 ENTER PIN : ");
    gotoxy(75,14);      scanf("%d",&Ano);   gotoxy(75,16);      scanf("%d",&pw);

    ptr = fopen("records.txt","r");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        if(traverse.AccNo == Ano)
        {
            flag=1;
            if(traverse.PIN == pw)
            {
                gotoxy(58,23);      printf("******PASSWORD MATCHED******");   Sleep(500);
                gotoxy(62,25);      printf("-----LOGGING IN-----");           Sleep(1000);
                fclose(ptr);
                displayAccountHolderMenu(Ano);
            }
            else
            {
                fclose(ptr);
                gotoxy(57,23);      printf("WARNING : WRONG PASSWORD!!!!!"); Sleep(1200);
                gotoxy(47,25);      printf("ENTER 1 TO TRY AGAIN..0 TO RETURN TO MAIN MENU..");
                int opt;    gotoxy(60,27);   printf("ENTER YOUR CHOICE: ");  scanf("%d",&opt);
                if(opt==1)
                {
                    loginPageAccountHolder();
                }
                else
                {
                    displayWelcomePage();
                }
            }
        }
    }
    if(flag != 1)
    {
        fclose(ptr);
        gotoxy(60,23);      printf("INVALID ACCOUNT DETAILS!!!");   Sleep(1000);
        gotoxy(61,25);      printf("RETURNING TO MAINMENU!!!");     Sleep(1500);    displayWelcomePage();
    }
}

void displayAccountHolderMenu(long int accountNo)
{
    clrscr();
    int option;
    gotoxy(40,10);      printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tMENU\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,13);  printf("\xDB\t1. VIEW ACCOUNT DETAILS ");
    gotoxy(40,14);  printf("\xDB\t2. UPDATE ACCOUNT DETAILS ");
    gotoxy(40,15);  printf("\xDB\t3. VIEW ACCOUNT BALANCE ");
    gotoxy(40,16);  printf("\xDB\t4. VIEW TRANSACTION HISTORY ");
    gotoxy(40,17);  printf("\xDB\t5. DEPOSIT ");
    gotoxy(40,18);  printf("\xDB\t6. WITHDRAW ");
    gotoxy(40,19);  printf("\xDB\t7. CHANGE PIN ");
    gotoxy(40,20);  printf("\xDB\t8. CLOSE ACCOUNT ");
    gotoxy(40,21);  printf("\xDB\t9. LOGOUT ");
    gotoxy(42,26);  printf("Enter your Choice : ");     scanf("%d",&option);

    switch(option)
    {
        case 1:     viewAccDetails(accountNo,1);         break;
        case 2:     updateAccDetails(accountNo);         break;
        case 3:     viewAccountBalance(accountNo);       break;
        case 4:     viewTransactionHistory(accountNo);   break;
        case 5:     depositAmount(accountNo);            break;
        case 6:     withdrawAmount(accountNo);           break;
        case 7:     changePin(accountNo);                break;
        case 8:     closeAccount(accountNo);             break;
        case 9:     displayWelcomePage();                break;
        default:    printf("\033[1;31m");
                    gotoxy(64,27);  printf("INVALID ENTRY!!!");     Sleep(1000);
                    printf("\033[0m");
                    displayAccountHolderMenu(accountNo);     break;
    }
}

void displayNewAccountPage()
{
    clrscr();
    int valid,ok;
    ptr = fopen("records.txt","a+");
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tCREATE AN ACCOUNT\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(45,12);  printf("FULL NAME: ");
    gotoxy(45,13);  printf("FATHER NAME: ");
    gotoxy(45,14);  printf("AGE: ");
    gotoxy(45,15);  printf("GENDER (M/F): ");
    gotoxy(45,16);  printf("NATIONALITY: ");
    gotoxy(45,17);  printf("DATE OF BIRTH(DDMMYYYY): ");
    gotoxy(45,18);  printf("PHONE NO: ");
    gotoxy(45,19);  printf("AADHAAR NUMBER: ");
    gotoxy(45,20);  printf("MARITAL STATUS(Y/N): ");
    gotoxy(45,21);  printf("EDUCATION LEVEL: ");
    gotoxy(45,22);  printf("OCCUPATION: ");
    gotoxy(45,23);  printf("Initial Deposit: ");

    Account.AccNo = generateAccNo();
    Account.PIN = (rand() % 9000)+1000 ;
    fullName:
    gotoxy(75,12);      gets(Account.fullName);
    gotoxy(45,27);      printf("                                                     ");
    if(strlen(Account.fullName)>25||strlen(Account.fullName)<5)
	{   
        printf("\033[1;31m");
		gotoxy(50,27);  printf("FullName should be less than 25 characters !");
        printf("\033[0m");
        gotoxy(75,12);  printf("                         ");
		goto fullName;
	}
    else
	{
		for (int b=0;b<strlen(Account.fullName);b++)
		{
			if (isalpha(Account.fullName[b]) || Account.fullName[b] == ' ')
			{ 
				valid=1;
			}
			else
			{
				valid=0;
				break;
			}
		}
		if(!valid)
		{
            printf("\033[1;31m");
			gotoxy(49,27);  printf("FullName can contain only Alphabets and spaces !");
            printf("\033[0m");
            gotoxy(75,12);  printf("                         ");
			goto fullName;
		}
	}
    gotoxy(45,27);      printf("                                                     ");
    
    fatherName:
    gotoxy(75,13);      gets(Account.fatherName);
    gotoxy(45,27);      printf("                                                     ");
    if(strlen(Account.fatherName)>25||strlen(Account.fatherName)<5)
	{
        printf("\033[1;31m");
		gotoxy(48,27);  printf("FatherName should be less than 25 characters !");
        printf("\033[0m");
        gotoxy(75,13);  printf("                         ");
		goto fatherName;
	}
    else
	{
		for (int b=0;b<strlen(Account.fatherName);b++)
		{
			if (isalpha(Account.fatherName[b]) || Account.fatherName[b] == ' ')
			{ 
				valid=1;
			}
			else
			{
				valid=0;
				break;
			}
		}
		if(!valid)
		{
            printf("\033[1;31m");
			gotoxy(47,27);  printf("FatherName can contain only Alphabets and spaces !");
            printf("\033[0m");
            gotoxy(75,13);  printf("                         ");
			goto fatherName;
		}
	}
    gotoxy(45,27);      printf("                                                     ");

    age:
    gotoxy(75,14);      scanf("%d",&(Account.age));     fflush(stdin);
    gotoxy(45,27);      printf("                                                     ");
    if(Account.age >100 || Account.age<18)
    {
        printf("\033[1;31m");
        gotoxy(56,27);   printf("Age limit should be 18-100 !");
        printf("\033[0m");
        gotoxy(75,14);   printf("     ");
        goto age;
    }
    gotoxy(45,27);      printf("                                                     ");

    gender:
    gotoxy(75,15);      gets(Account.gender);
    gotoxy(45,27);      printf("                                                     ");
    for(int b=0;b<strlen(Account.gender);b++)
    {
        if(toupper(Account.gender[b])=='M'|| toupper(Account.gender[b])=='F' || toupper(Account.gender[b])=='O')
        {
            ok = 1;
        }
        else 
        {
            ok = 0;
            break;
        }
    }
    if(!ok)
    {
        printf("\033[1;31m");
        gotoxy(56,27);   printf("Gender can contain only M/F/O !");
        printf("\033[0m");
        gotoxy(75,15);   printf("     ");
        goto gender;
    }
    gotoxy(45,27);      printf("                                                     ");

    nationality:
    gotoxy(75,16);      gets(Account.nationality);
    gotoxy(45,27);      printf("                                                     ");
    if(strlen(Account.nationality)>25||strlen(Account.nationality)<5)
	{
        printf("\033[1;31m");
		gotoxy(48,27);  printf("Nationality should be less than 25 characters !");
        printf("\033[0m");
        gotoxy(75,16);  printf("                         ");
		goto nationality;
	}
    else
	{
		for (int b=0;b<strlen(Account.nationality);b++)
		{
			if (isalpha(Account.nationality[b]) || Account.nationality[b] == ' ')
			{ 
				valid=1;
			}
			else
			{
				valid=0;
				break;
			}
		}
		if(!valid)
		{
            printf("\033[1;31m");
			gotoxy(46,27);  printf("Nationality can contain only Alphabets and spaces !");
            printf("\033[0m");
            gotoxy(75,16);  printf("                         ");
			goto nationality;
		}
	}
    gotoxy(45,27);      printf("                                                     ");

    gotoxy(75,17);      scanf("%ld",&(Account.DOB));
    gotoxy(45,27);      printf("                                                     ");

    phoneNo:
    gotoxy(75,18);      scanf("%lld",&(Account.phoneNo));   fflush(stdin);
    char phNo[20];
    itoa(Account.phoneNo,phNo,10);
    if(strlen(phNo)>10||strlen(phNo)!=10)
    {
        printf("\033[1;31m");
        gotoxy(56,27);        printf("PhoneNo should be 10 digits !");
        printf("\033[0m");
        gotoxy(75,18);      printf("                        ");
        goto phoneNo;
    }

    gotoxy(45,27);      printf("                                                     ");

    AadhaarNo:
    gotoxy(75,19);      gets(Account.AadhaarNo);
    gotoxy(45,27);      printf("                                                     ");
    char AadNo[20];
    strcpy(AadNo,Account.AadhaarNo);
    if(strlen(AadNo)>12 || strlen(AadNo)!=12)
    {
        printf("\033[1;31m");
        gotoxy(56,27);       printf("AADHAAR NO should be 16 digits !");
        printf("\033[0m");
        gotoxy(75,19);   printf("                        ");
        goto AadhaarNo;
    }
    
    gotoxy(45,27);      printf("                                                     ");

    MaritalStatus:
    gotoxy(75,20);      gets(Account.MaritalStatus);
    gotoxy(45,27);      printf("                                                     ");
    for(int b=0;b<strlen(Account.MaritalStatus);b++)
    {
        if(toupper(Account.MaritalStatus[b])=='Y'|| toupper(Account.MaritalStatus[b])=='N')
        {
            ok = 1;
        }
        else
        {
            ok = 0;
            break;
        }
    }
    if(!ok)
    {
        printf("\033[1;31m");
        gotoxy(54,27);   printf("MaritalStatus can contain only Y/N !");
        printf("\033[0m");
        gotoxy(75,20);   printf("     ");
        goto MaritalStatus;
    }
    gotoxy(45,27);      printf("                                                     ");

    gotoxy(75,21);      gets(Account.EducationLevel);
    gotoxy(45,27);      printf("                                                     ");

    gotoxy(75,22);      gets(Account.occupation);
    gotoxy(45,27);      printf("                                                     ");
    
    accBal:
    gotoxy(75,23);      scanf("%d",&Account.accBal);
    gotoxy(45,27);      printf("                                                     ");
    if(Account.accBal<0 || Account.accBal>50000)
    {
        printf("\033[1;31m");
        gotoxy(52,27);   printf("Acc Bal should in range of 0 - 50,000 !");
        printf("\033[0m");
        gotoxy(75,23);   printf("         ");
        goto accBal;
    }

    gotoxy(45,27);      printf("                                                     ");

    fprintf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",Account.AccNo,Account.PIN,Account.fullName,Account.fatherName,Account.age,Account.gender,Account.nationality,Account.DOB,Account.phoneNo,Account.AadhaarNo,Account.MaritalStatus,Account.EducationLevel,Account.occupation,Account.accBal);
    fclose(ptr);
    gotoxy(56,25);      printf("***ACCOUNT SUCCESSFULLY CREATED***");       Sleep(500);
    gotoxy(60,26);      printf("YOUR ACCOUNT NUMBER :%ld",Account.AccNo);
    gotoxy(61,27);      printf("YOUR PASSWORD: %d",Account.PIN);
    gotoxy(43,29);      printf("PRESS ANY KEY TO GO BACK : ");    getch();
    displayWelcomePage();
}

int viewAccDetails(long int accountNo, int flagVar)
{
    clrscr();
    int choice,flag=0;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t   VIEW DETAILS\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    ptr = fopen("records.txt","r");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&Account.accBal) != EOF)
    {
        if(accountNo == traverse.AccNo)
        {
            flag = 1;
            gotoxy(58,22);  printf("GENERATING ACCOUNT DETAILS...");
            Sleep(2000);
            clrscr();
            gotoxy(40,10);
            printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t ACCOUNT DETAILS \t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
            menuBorder();
            gotoxy(45,12);  printf("1. ACCOUNT NO: ");                  gotoxy(75,12);      printf("%ld",traverse.AccNo);
            gotoxy(45,13);  printf("2. FULL NAME: ");                   gotoxy(75,13);      printf("%s",traverse.fullName);
            gotoxy(45,14);  printf("3. FATHER NAME: ");                 gotoxy(75,14);      printf("%s",traverse.fatherName);
            gotoxy(45,15);  printf("4. AGE: ");                         gotoxy(75,15);      printf("%d",traverse.age);
            gotoxy(45,16);  printf("5. GENDER (M/F): ");                gotoxy(75,16);      printf("%s",traverse.gender);
            gotoxy(45,17);  printf("6. NATIONALITY: ");                 gotoxy(75,17);      printf("%s",traverse.nationality);
            gotoxy(45,18);  printf("7. DATE OF BIRTH(DDMMYYYY): ");     gotoxy(75,18);      printf("%ld",traverse.DOB);
            gotoxy(45,19);  printf("8. PHONE NO: ");                    gotoxy(75,19);      printf("%lld",traverse.phoneNo);
            gotoxy(45,20);  printf("9. AADHAAR NUMBER: ");              gotoxy(75,20);      printf("%s",traverse.AadhaarNo);
            gotoxy(45,21);  printf("10. MARITAL STATUS(Y/N): ");        gotoxy(75,21);      printf("%s",traverse.MaritalStatus);
            gotoxy(45,22);  printf("11. EDUCATION LEVEL: ");            gotoxy(75,22);      printf("%s",traverse.EducationLevel);
            gotoxy(45,23);  printf("12. OCCUPATION: ");                 gotoxy(75,23);      printf("%s",traverse.occupation);
            gotoxy(45,24);  printf("13. ACCOUNT BALANCE: ");            gotoxy(75,24);      printf("%d",traverse.accBal);
            break;
        }
    }
    fclose(ptr);
    if(flag != 1)
    {
        gotoxy(60,21);      printf("INVALID ACCOUNT DETAILS!!!");   Sleep(1500);
        gotoxy(61,22);      printf("RETURNING TO MAINMENU!!!");     Sleep(2000);
        return -1;
    }
    if(flagVar == 1)
    {
        gotoxy(43,29);   printf("PRESS ANY KEY TO GO BACK : ");    getch();
        displayAccountHolderMenu(accountNo);
    }
}

void updateAccDetails(long int accountNo)
{
    clrscr();
    int opt;
    int x = viewAccDetails(accountNo,0);
    if( x == -1)
    {
        displayAccountHolderMenu(accountNo);
    }
    printf("\033[01;33m");
    gotoxy(42,29);      printf("Enter 0 to SKIP");
    printf("\033[0m");
    gotoxy(45,27);      printf("Enter the option number to Edit: ");     scanf("%d",&opt);  fflush(stdin);
    gotoxy(45,27);      printf("                                    ");

    if((opt==1) || (opt==9)){
        printf("\033[1;31m");
        gotoxy(44,27);      printf("Acc.No and Aadhaar.No can't be changed by Account holder");     Sleep(1500);
        printf("\033[0m");
        updateAccDetails(accountNo);
    }
    else if(opt==13){
        printf("\033[1;31m");
        gotoxy(60,28);      printf("Acc Bal is just to view.");       Sleep(1500);
        printf("\033[0m");
        updateAccDetails(accountNo);
    }
    else if(opt == 0)
    {
        //do nothing
    }
    else{
        ReadAndUpdate(accountNo,opt);
    }
    displayAccountHolderMenu(accountNo);
}

void ReadAndUpdate(long int accountNo, int opt)
{
    long long int updatedData;
    char updatedInfo[20];
    gotoxy(43,25);       printf("                                                            ");
    gotoxy(45,26);       printf("ENTER UPDATED INFO: ");
    ptr = fopen("records.txt","r");
    ptr1 = fopen("new.txt","w+");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        if(accountNo != traverse.AccNo)
        {
            fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
        }
        else
        {
            switch(opt)
            {
                case 2:
                    gotoxy(65,26);   gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,updatedInfo,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;
                
                case 3:
                    gotoxy(65,26);   gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,updatedInfo,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;

                case 4:
                    gotoxy(65,26);   scanf("%lld",&updatedData);
                    fprintf(ptr1,"%ld %d %s %s %lld %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,updatedData,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;
                
                case 5:
                    gotoxy(65,26);   gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,updatedInfo,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);  break;
                
                case 6:
                    gotoxy(65,26);   gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,updatedInfo,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;
                
                case 7:
                    gotoxy(65,26);   scanf("%lld",&updatedData);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,updatedData,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;
                
                case 8:
                    gotoxy(65,26);   scanf("%lld",&updatedData);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,updatedData,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;

                case 9:
                    gotoxy(65,26);  gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,updatedData,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;

                case 10:
                    gotoxy(65,26);   gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,updatedInfo,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    break;

                case 11:
                    gotoxy(65,26);   gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,updatedInfo,traverse.occupation,traverse.accBal);
                    break;
                case 12:
                    gotoxy(65,26);   gets(updatedInfo);
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,updatedInfo,traverse.accBal);
                    break;
            }
        }
    }
    fclose(ptr);    fclose(ptr1);
    gotoxy(43,26);       printf("                                                            ");
    remove("records.txt");
    if(rename("new.txt","records.txt") == 0)
    {
        gotoxy(65,27);      printf("CHANGES SAVED!!");      Sleep(2000);
    }
    else
    {
        gotoxy(55,27);      printf("ERROR OCCURRED..TRY AGAIN LATER!");     Sleep(2000);
    }
}

void viewAccountBalance(long int accountNo)
{
    clrscr();
    int choice,flag=0;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t   ACCOUNT BALANCE\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    ptr = fopen("records.txt","r");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        if(accountNo == traverse.AccNo)
        {
            flag = 1;
            gotoxy(45,14);      printf("ACCOUNT NUMBER: %ld",traverse.AccNo);
            gotoxy(45,15);      printf("NAME: %s",traverse.fullName);
            gotoxy(60,19);      printf("ACCOUNT BALANCE: %d",traverse.accBal);
            gotoxy(45,24);      printf("1. TO CHECK TRANSACTION HISTORY");
            gotoxy(45,25);      printf("2. TO GO TO MENU");
            gotoxy(45,26);      printf("ENTER YOUR CHOICE: ");
            fclose(ptr);
            scanf("%d",&choice);
            if(choice == 1)
            {
                viewTransactionHistory(accountNo);
            }
            else if(choice == 2)
            {
                displayAccountHolderMenu(accountNo);
            }
            else
            {
                gotoxy(45,23);      printf("             ");
                gotoxy(45,24);      printf("                               ");
                gotoxy(45,25);      printf("                 ");            
                gotoxy(45,26);      printf("                      ");
                printf("\033[1;31m");
                gotoxy(64,25); printf("INVALID ENTRY!!!");      Sleep(1500);
                printf("\033[0m");
                displayAccountHolderMenu(accountNo);
            }
        }
    }
    if(flag != 1)
    {
        fclose(ptr);
        gotoxy(58,25);      printf("UNABLE TO LOAD ACC BALANCE.");      Sleep(1500);
        displayAccountHolderMenu(accountNo);
    }
}

void viewTransactionHistory(long int accountNo)
{
    clrscr();
    FILE *fp;
    int choice, flag = 0,y = 14,i=0;
    char *token,str[1000],str1[1000],amount[10],ANo[10];
    const char delim[3]="*";
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tTRANSACTION HISTORY\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(40,11);      printf("\xDB");     gotoxy(105,11);     printf("\xDB");
    fp = fopen("transactions.txt","r");
    while(fgets(str,1000,fp) != NULL)
    {
        gotoxy(40,12);      printf("\xDB");     gotoxy(105,12);     printf("\xDB");
        gotoxy(40,13);      printf("\xDB");     gotoxy(105,13);     printf("\xDB");
        gotoxy(40,14);      printf("\xDB");     gotoxy(105,14);     printf("\xDB");
        
        strcpy(str1,str);
        itoa(accountNo,ANo,10);
        token = strtok(str1,delim);
        gotoxy(45,12);      printf("ACCOUNT NO : ");
        gotoxy(45,14);      printf("TRANSACTIONS : ");
        if(strcmp(token,ANo) == 0)
        {
            flag = 1;
            gotoxy(60,12);      printf("%s",token);
            token = strtok(NULL,delim);
            while( token != NULL )
            {
                gotoxy(40,y);      printf("\xDB");     gotoxy(105,y);     printf("\xDB");
                gotoxy(60,y++);       printf("%s",token);
                token = strtok(NULL,delim);
            }
            gotoxy(40,y);      printf("\xDB");     gotoxy(105,y++);     printf("\xDB");
            gotoxy(40,y);      printf("\xDB");     gotoxy(105,y++);     printf("\xDB");
        }
    }
    fclose(fp);
    if(flag != 1)
    {
        menuBorder();
        gotoxy(60,12);      printf("%s",ANo);
        gotoxy(60,21);      printf("NO TRANSACTIONS FOUND!!!");     Sleep(500);
        gotoxy(62,24);      printf("RETURNING TO MAINMENU");        Sleep(2000);
        displayAccountHolderMenu(accountNo);
    }
    else
    {
        gotoxy(40,y);      printf("\xDB");     gotoxy(105,y++);     printf("\xDB");
        gotoxy(40,y);      printf("\xDB");     gotoxy(105,y++);     printf("\xDB");
        gotoxy(40,y);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
        gotoxy(43,y-2);   printf("PRESS ANY KEY TO GO BACK : ");    getch();
        displayAccountHolderMenu(accountNo);
    }
    
}

void addToTransactions(long int accountNo, char transType[],long long int amt)
{
    time_t t;
    time(&t);
    FILE *fp,*fp1;
    char *token,str[1000],str1[1000],str2[1000],amount[60],ANo[10],time[50];
    fp = fopen("transactions.txt","a+");
    fp1 = fopen("newtrans.txt","a+");
    int i=0,flag=0;
    const char delim[3]="*";

    for(int i = 0;i<strlen(ctime(&t))-1;i++)
    {
        time[i] = ctime(&t)[i];
    }

    while(fgets(str,1000,fp) != NULL)
    {
        strcpy(str1,str);
        token = strtok(str1,delim);
        itoa(amt,amount,10);
        itoa(accountNo,ANo,10);
        if(strcmp(token,ANo) == 0)
        {
            flag = 1;
            for(i=0;i<strlen(str)-1;i++)
            {
                str2[i]=str[i];
            }
            str2[i] = '\0';
            strcat(amount,"(");
            strcat(amount,time);
            strcat(amount,")");
            strcat(strcat(str2,delim),strcat(transType,amount));
            fputs(str2,fp1);
            fprintf(fp1,"\n");
        }
        else
        {
            fputs(str,fp1);
        }
    }
    if(flag != 1)
    {
        itoa(accountNo,ANo,10);
        itoa(amt,amount,10);
        strcat(amount,"(");
        strcat(amount,time);
        strcat(amount,")");
        strcat(transType,amount);
        fprintf(fp1,"%s%s%s\n",ANo,delim,transType);
    }
    fclose(fp);    fclose(fp1);
    remove("transactions.txt");
    if(rename("newtrans.txt","transactions.txt") == 0)
    {
        gotoxy(61,20);  printf("TRANSACTION SUCCESSFUL");
    }
}

void depositAmount(long int accountNo)
{
    clrscr();
    int choice,transRes = 0;
    long long int amt=0,verify=0;
    long long int AtmAmount = 0;
    char transType[] = "DEPOSITED - ";
    char trans = 'D';
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t   DEPOSIT AMOUNT\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    if(ATMServices == TRUE)
    {
        gotoxy(45,13);      printf("ENTER AMOUNT TO DEPOSIT: ");    scanf("%lld",&amt);
        gotoxy(45,15);      printf("VERIFY AMOUNT: ");      scanf("%lld",&verify);        fflush(stdin);
        if(amt==verify)
        {
            ptr = fopen("records.txt","r");
            ptr1 = fopen("new.txt","w+");
            while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
            {
                if(accountNo != traverse.AccNo)
                {
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                }
                else
                {
                    AtmAmount = checkATMAmount();
                    if(AtmAmount+amt > 1000000)
                    {
                        gotoxy(58,20);      printf("--ATM AMOUNT LIMIT REACHED--");
                        gotoxy(60,21);      printf("CAN'T PROCESS DEPOSITS!!");
                        transRes = 1;
                    }
                    if(transRes == 1)
                    {
                        fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                    }
                    else
                    {
                        fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal+amt);
                        updateATMAmount(trans,verify);
                        addToTransactions(accountNo,transType,amt);
                        gotoxy(57,21);      printf("AMOUNT SUCCESFULLY DEPOSITED!!");
                    }
                }
            }
            fclose(ptr);    fclose(ptr1);
            remove("records.txt");
            if(rename("new.txt","records.txt") == 0)
            {
                gotoxy(45,24);      printf("1. CHECK ACCOUNT BALANCE");
                gotoxy(45,25);      printf("2. CHECK TRANSACTION HISTORY");
                gotoxy(45,26);      printf("3. GO BACK");
                gotoxy(62,27);      printf("ENTER YOUR CHOICE: ");      scanf("%d",&choice);    fflush(stdin);
                if(choice == 1){
                    viewAccountBalance(accountNo);
                }
                else if(choice == 2){
                    viewTransactionHistory(accountNo);
                }
                else if(choice == 3){
                    displayAccountHolderMenu(accountNo);
                }
                else{
                    gotoxy(45,27);      printf("                                       ");
                    printf("\033[1;31m");
                    gotoxy(64,27);      printf("INVALID CHOICE!");
                    printf("\033[0m");
                    Sleep(1500);
                    displayAccountHolderMenu(accountNo);
                }
            }
            else{
                gotoxy(45,27);
                printf("ERROR OCCURRED..TRY AGAIN LATER!");     Sleep(1500);
                displayAccountHolderMenu(accountNo);
            }
        }
        else
        {
            printf("\033[1;31m");
            gotoxy(60,25);  printf("VERIFICATION FAILED!!!");   Sleep(500);
            printf("\033[0m");
            gotoxy(62,26);  printf("RETURNING TO MENU");        Sleep(1500);
            Sleep(500);
            displayAccountHolderMenu(accountNo);
        }
    }
    else
    {
        printf("\033[1;31m");
        gotoxy(45,18);
        printf("OH SORRY!! ATM SERVICES ARE TEMPORARILY DISABLED!!");   Sleep(500);
        gotoxy(60,20);      printf("PLEASE TRY AGAIN LATER!!");     Sleep(1500);
        printf("\033[0m");
        gotoxy(62,26);  printf("RETURNING TO MENU");    Sleep(2000);
        displayAccountHolderMenu(accountNo);
    }
}

void withdrawAmount(long int accountNo)
{
    int amt=0,verify=0,choice;
    long long int AtmAmount;
    char transType[] = "WITHDRAWN - ";
    char trans = 'W';
    clrscr();
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t   WITHDRAW AMOUNT\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    if(ATMServices == TRUE)
    {
        gotoxy(45,13);      printf("ENTER AMOUNT TO WITHDRAW: ");    scanf("%d",&amt);
        gotoxy(45,15);      printf("VERIFY AMOUNT: ");      scanf("%d",&verify);
        if(amt==verify)
        {
            ptr = fopen("records.txt","r");
            ptr1 = fopen("new.txt","w+");
            while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
            {
                if(accountNo != traverse.AccNo)
                {
                    fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                }
                else
                {
                    AtmAmount = checkATMAmount();
                    if(amt>traverse.accBal)
                    {
                        fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                        printf("\033[1;31m");
                        gotoxy(63,22);  printf("PROCESS TERMINATED !");    Sleep(500);
                        gotoxy(60,23);  printf("ERROR: INSUFFICIENT BALANCE");  Sleep(2000);
                        printf("\033[0m");
                    }
                    else if(amt>AtmAmount)
                    {
                        fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                        printf("\033[1;31m");
                        gotoxy(61,22);  printf("PROCESS TERMINATED!!!");    Sleep(500);
                        gotoxy(51,23);  printf("ERROR : SORRY...INSUFFICIENT CASH IN ATM!!");  Sleep(2000);
                        printf("\033[0m");
                    }
                    else if(amt>50000)
                    {
                        fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                        printf("\033[1;31m");
                        gotoxy(64,22);  printf("LIMIT EXCEEDED!!");    Sleep(500);
                        gotoxy(52,23);  printf("ERROR : CAN'T WITHDRAW MORE THAN 50,000.");  Sleep(2000);
                        printf("\033[0m");
                    }
                    else
                    {
                        fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal-amt);
                        updateATMAmount(trans,verify);
                        addToTransactions(accountNo,transType,amt);
                        gotoxy(59,21);      printf("PLEASE COLLECT THE MONEY!!");
                    }
                }
            }
            fclose(ptr);    fclose(ptr1);
            remove("records.txt");
            if(rename("new.txt","records.txt") == 0)
                {
                    gotoxy(45,24);      printf("1. CHECK ACCOUNT BALANCE");
                    gotoxy(45,25);      printf("2. CHECK TRANSACTION HISTORY");
                    gotoxy(45,26);      printf("3. GO BACK");
                    gotoxy(62,28);      printf("ENTER YOUR CHOICE: ");      scanf("%d",&choice);
                    if(choice == 1){
                        viewAccountBalance(accountNo);
                    }
                    else if(choice == 2){
                        viewTransactionHistory(accountNo);
                    }
                    else if(choice == 3){
                        displayAccountHolderMenu(accountNo);
                    }
                    else{
                        gotoxy(45,27);      printf("                                       ");
                        printf("\033[1;31m");
                        gotoxy(64,27);      printf("INVALID CHOICE!");
                        printf("\033[0m");
                        Sleep(1500);
                        displayAccountHolderMenu(accountNo);
                    }
                }
            else
                {
                    gotoxy(45,27);      printf("ERROR OCCURRED..TRY AGAIN LATER!");     Sleep(1500);
                    displayAccountHolderMenu(accountNo);
                }
        }
        else
        {
            printf("\033[1;31m");
            gotoxy(60,25);  printf("VERIFICATION FAILED!!!");
            printf("\033[0m");
            gotoxy(62,26);  printf("RETURNING TO MENU");
            Sleep(1000);
            displayAccountHolderMenu(accountNo);
        }
    }
    else
    {
        printf("\033[1;31m");
        gotoxy(45,18);
        printf("OH SORRY!! ATM SERVICES ARE TEMPORARILY DISABLED!!");   Sleep(500);
        gotoxy(60,20);      printf("PLEASE TRY AGAIN LATER!!");     Sleep(1500);
        printf("\033[0m");
        gotoxy(62,26);      printf("RETURNING TO MENU");    Sleep(2000);
        displayAccountHolderMenu(accountNo);
    }
}

void changePin(long int accountNo)
{
    clrscr();
    long int Ano;   int pw,flag=0;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tVERIFY YOUR ACCOUNT\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,14);      printf("\xDB\t\xB2\xB2\xB2 ENTER ACCOUNT NUMBER: ");
    gotoxy(40,16);      printf("\xDB\t\xB2\xB2\xB2 ENTER PIN: ");
    gotoxy(75,14);      scanf("%d",&Ano);   gotoxy(75,16);      scanf("%d",&pw);
    ptr = fopen("records.txt","r");
    ptr1 = fopen("new.txt","w+");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        if(accountNo != traverse.AccNo)
        {
            fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
        }
        else
        {
            flag=1;
            if(traverse.PIN == pw)
            {
                gotoxy(58,20);      printf("******PASSWORD MATCHED******");   Sleep(1000);
                gotoxy(62,22);      printf("Enter New PIN: ");  
                int newPw;          scanf("%d",&newPw);     fflush(stdin);
                fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,newPw,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                gotoxy(59,25);      printf("PIN CHANGED SUCCESSFULLY!!!");       Sleep(1000);
                gotoxy(60,27);      printf("REDIRECTING TO LOGIN MENU");        Sleep(1500);
                fclose(ptr);    fclose(ptr1);
                remove("records.txt");    rename("new.txt","records.txt");
                displayWelcomePage();
            }
            else
            {
                gotoxy(57,21);      printf("WARNING : WRONG PASSWORD!!!!!"); Sleep(1000);
                gotoxy(50,22);      printf("ENTER 1 TO TRY AGAIN..0 TO RETURN TO MENU..");
                int opt;    gotoxy(60,24);   printf("ENTER YOUR CHOICE: ");  scanf("%d",&opt);
                if(opt==1)
                {
                    fclose(ptr);    fclose(ptr1);
                    remove("records.txt");    rename("new.txt","records.txt");
                    changePin(accountNo);
                }
                else
                {
                    fclose(ptr);    fclose(ptr1);
                    remove("records.txt");    rename("new.txt","records.txt");
                    displayAccountHolderMenu(accountNo);
                }
            }
        }
    }
    if(flag != 1)
    {
        gotoxy(60,21);      printf("INVALID ACCOUNT DETAILS!!!");   Sleep(1500);
        gotoxy(61,22);      printf("RETURNING TO MAINMENU!!!");     Sleep(1500);    displayAccountHolderMenu(accountNo);
    }
}

void closeAccount(long int accountNo)
{
    clrscr();
    long int Ano;   int pw,flag=0;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tVERIFY YOUR ACCOUNT\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,14);      printf("\xDB\t\xB2\xB2\xB2 ENTER ACCOUNT NUMBER: ");
    gotoxy(40,15);      printf("\xDB\t\xB2\xB2\xB2 ENTER PIN: ");
    gotoxy(75,14);      scanf("%d",&Ano);   gotoxy(75,15);      scanf("%d",&pw);
    ptr = fopen("records.txt","r");
    ptr1 = fopen("new.txt","w+");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        if(accountNo != traverse.AccNo)
        {
            fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
        }
        else
        {
            flag=1;
            if(traverse.PIN == pw)
            {
                gotoxy(58,21);      printf("******PASSWORD MATCHED******");   Sleep(1000);
                gotoxy(54,24);      printf("!!! ACCOUNT SUCCESSFULLY DELETED !!!");     Sleep(1000);
                gotoxy(60,27);      printf("REDIRECTING TO LOGIN MENU");        Sleep(1500);
                fclose(ptr);    fclose(ptr1);
                remove("records.txt");    rename("new.txt","records.txt");
                displayWelcomePage();
            }
            else
            {
                fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
                gotoxy(57,21);      printf("WARNING : WRONG PASSWORD!!!!!"); Sleep(1000);
                gotoxy(50,22);      printf("ENTER 1 TO TRY AGAIN..0 TO RETURN TO MENU..");
                int opt;    gotoxy(60,24);   printf("ENTER YOUR CHOICE: ");  scanf("%d",&opt);
                if(opt==1)
                {
                    fclose(ptr);    fclose(ptr1);
                    remove("records.txt");    rename("new.txt","records.txt");
                    closeAccount(accountNo);
                }
                else
                {
                    fclose(ptr);    fclose(ptr1);
                    remove("records.txt");    rename("new.txt","records.txt");
                    displayAccountHolderMenu(accountNo);
                }
            }
        }
    }
    if(flag != 1)
    {
        fclose(ptr);    fclose(ptr1);
        gotoxy(60,21);      printf("INVALID ACCOUNT DETAILS!!!");   Sleep(1500);
        gotoxy(61,22);      printf("RETURNING TO MAINMENU!!!");     Sleep(1500);
        displayAccountHolderMenu(accountNo);
    }
    
}

int generateAccNo()
{
    long int r = rand();
    ptr1 = fopen("records.txt","r");
    while(fscanf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        if(traverse.AccNo == r)
        {
            r = generateAccNo();
        }
    }
    fclose(ptr1);
    return r;
}

void loginPageEmployee()
{
    clrscr();
    int y = 75,i=0;
    char username[20],pw[20],ch;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t   ADMIN LOGIN\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,14);      printf("\xDB\t\xB2\xB2\xB2 ENTER USERNAME: ");
    gotoxy(40,16);      printf("\xDB\t\xB2\xB2\xB2 ENTER PASSWORD: ");
    gotoxy(72,14);      gets(username);     gotoxy(72,16);

    while(ch != 13)
    {
        ch = getch();
        if(ch != 13 && ch!= 8)
        {
            printf("*");
            pw[i] = ch;
            i++;
        }
        else if(ch == 8)
        {
            if(i>0)
            {
                i--;
                pw[i] = '\0';
                printf("\b \b");
            }
        }
        if(ch == 13)
        {
            break;
        }
    }

    if((strcmp(username,"bankingsystem@miniproject")==0) && (strcmp(pw,"vcestudentbank") == 0))
    {
        gotoxy(58,21);      printf("******PASSWORD MATCHED******");   Sleep(500);
        gotoxy(62,23);      printf("-----LOGGING IN-----");           Sleep(1000);
        displayEmployeeMenu();
    }
    else
    {
        gotoxy(51,22);      printf("WARNING : WRONG USERNAME OR PASSWORD!!!!!"); Sleep(2000);
        gotoxy(49,23);      printf("ENTER 1 TO TRY AGAIN..0 TO RETURN TO MAIN MENU..");
        int opt;    gotoxy(60,25);   printf("ENTER YOUR CHOICE: ");  scanf("%d",&opt);
        if(opt==1){
                fflush(stdin);
                loginPageEmployee();
            }
        else{
                displayWelcomePage();
            }
    }
}

void displayEmployeeMenu()
{
    clrscr();
    int option;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tCHOOSE ANY OPTION\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,14);  printf("\xDB\t1. VIEW ACCOUNT HOLDERS LIST ");
    gotoxy(40,15);  printf("\xDB\t2. VIEW ACCOUNT HOLDER DETAILS");
    gotoxy(40,16);  printf("\xDB\t3. EDIT ACCOUNT HOLDER DETAILS ");
    gotoxy(40,17);  printf("\xDB\t4. DELETE AN ACCOUNT ");
    gotoxy(40,18);  printf("\xDB\t5. ADD MONEY TO ATM ");
    gotoxy(40,19);  printf("\xDB\t6. DISABLE ATM SERVICES ");
    gotoxy(40,20);  printf("\xDB\t7. LOGOUT");
    gotoxy(40,21);  printf("\xDB\t8. EXIT");
    gotoxy(42,25);  printf("Enter your Choice : ");         scanf("%d",&option);        fflush(stdin);

    switch(option)
    {
        case 1:     AccountsList();                      break;
        case 2:     viewAccHolderDetails();              break;   
        case 3:     editAccHolderDetails();              break;
        case 4:     closeAccHolderAccount();             break;
        case 5:     addMoneyToATM();                     break;
        case 6:     disableATMServices();                break;
        case 7:     displayWelcomePage();                break;
        case 8:     break;
        default:    gotoxy(65,26);  printf("INVALID ENTRY!!!");     Sleep(1000);
                    displayEmployeeMenu();     break;
    }
}

void AccountsList()
{
    clrscr();
    int y=14,slNo=1;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\tLIST OF ACCOUNTS\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(40,11);   printf("\xDB");    gotoxy(105,11);     printf("\xDB");
    gotoxy(40,12);   printf("\xDB");    gotoxy(42,12);      printf("Sl.No");
    gotoxy(50,12);      printf("--Acc No--");       gotoxy(65,12);      printf("--NAME--");
    gotoxy(85,12);      printf("--Phone No--");     gotoxy(105,12);     printf("\xDB");
    gotoxy(40,13);   printf("\xDB");    gotoxy(105,13);      printf("\xDB");
    ptr = fopen("records.txt","r");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        gotoxy(40,y);   printf("\xDB");
        gotoxy(44,y);   printf("%d",slNo);
        gotoxy(53,y);   printf("%ld",traverse.AccNo);
        gotoxy(66,y);   printf("%s",traverse.fullName);
        gotoxy(87,y);   printf("%lld",traverse.phoneNo);
        gotoxy(105,y);   printf("\xDB");
        y++;        slNo++;
    }
    fclose(ptr);
    gotoxy(40,y);     printf("\xDB");     gotoxy(105,y);     printf("\xDB");
    gotoxy(40,y+1);   printf("\xDB");     gotoxy(105,y+1);   printf("\xDB");
    gotoxy(40,y+2);   printf("\xDB");     gotoxy(105,y+2);   printf("\xDB");
    gotoxy(40,y+3);   printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(43,y+2);   printf("PRESS ANY KEY TO GO BACK : ");    getch();
    displayEmployeeMenu();
}

void viewAccHolderDetails()
{
    clrscr();
    long int accountNo;
    int opt;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t   VIEW DETAILS\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(45,12);      printf("Enter Account Number: ");
    scanf("%ld",&accountNo);
    int x = viewAccDetails(accountNo,0);
    if(x == -1)
    {
        displayEmployeeMenu();
    }
    gotoxy(43,29);   printf("PRESS ANY KEY TO GO BACK : ");    getch();
    displayEmployeeMenu();
}

void editAccHolderDetails()
{
    clrscr();
    long int accountNo;
    int opt;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t   VIEW DETAILS\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(45,12);      printf("Enter Account Number: ");
    scanf("%ld",&accountNo);
    int x = viewAccDetails(accountNo,0);
    if(x == -1)
    {
        displayEmployeeMenu();
    }
    gotoxy(45,26);      printf("Enter the option number to Edit: ");     scanf("%d",&opt);  fflush(stdin);
    Sleep(100);
    if((opt==1) || (opt==13)){
        gotoxy(43,25);       printf("                                                            ");
        gotoxy(43,26);       printf("                                                            ");
        gotoxy(55,27);       printf("Acc.No and Acc.Bal can't be changed");
    }
    else{
        gotoxy(43,25);       printf("                                                            ");
        gotoxy(45,26);       printf("                                                            ");
        ReadAndUpdate(accountNo,opt);
    }
    gotoxy(43,29);   printf("PRESS ANY KEY TO GO BACK : ");    getch();
    displayEmployeeMenu();
}

void closeAccHolderAccount()
{
    clrscr();
    int flag=0;
    long int accountNo;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t DELETE ACCOUNT\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(45,12);      printf("Enter Account Number: ");
    scanf("%ld",&accountNo);
    ptr = fopen("records.txt","r");
    ptr1 = fopen("new.txt","w+");
    while(fscanf(ptr,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",&traverse.AccNo,&traverse.PIN,traverse.fullName,traverse.fatherName,&traverse.age,traverse.gender,traverse.nationality,&traverse.DOB,&traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,&traverse.accBal) != EOF)
    {
        if(accountNo != traverse.AccNo)
        {
            fprintf(ptr1,"%ld %d %s %s %d %s %s %ld %lld %s %s %s %s %d\n",traverse.AccNo,traverse.PIN,traverse.fullName,traverse.fatherName,traverse.age,traverse.gender,traverse.nationality,traverse.DOB,traverse.phoneNo,traverse.AadhaarNo,traverse.MaritalStatus,traverse.EducationLevel,traverse.occupation,traverse.accBal);
        }
        else
        {
            flag=1;
            gotoxy(55,24);      printf("!!! ACCOUNT SUCCESSFULLY DELETED !!!");     Sleep(500);
            gotoxy(55,25);      printf("RETURNING TO MENU!!!");     Sleep(500);
        }
    }
    fclose(ptr);    fclose(ptr1);
    remove("records.txt");    rename("new.txt","records.txt");
    if(flag != 1)
    {
        gotoxy(60,21);      printf("INVALID ACCOUNT DETAILS!!!");   Sleep(1000);
        gotoxy(61,22);      printf("RETURNING TO MAINMENU!!!");     Sleep(1500);    displayEmployeeMenu();
    }
    displayEmployeeMenu();
}

void addMoneyToATM()
{
    clrscr();
    int choice;
    long long int AtmAmount;
    char trans = 'D';
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(58,20);      printf("GENERATING ATM AMOUNT STATUS");
    for(int i=0;i<5;i++)
    {
        Sleep(500);  printf(".");
    }

    clrscr();
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    AtmAmount = checkATMAmount();
    gotoxy(60,15);      printf("REMAINING ATM AMOUNT : %lld",AtmAmount);
    gotoxy(53,28);      printf("Enter 1 to PROCEED and 0 to GO BACK : ");      scanf("%d",&choice);     fflush(stdin);
    if(choice == 1)
    {
        gotoxy(43,28);       printf("                                                            ");
        gotoxy(60,17);      printf("ENTER AMOUNT TO ADD : ");
        long long int add;        scanf("%lld",&add);
        if(AtmAmount+add > 1000000)
        {
            gotoxy(63,25);      printf("PROCESS FAILED...");        Sleep(500);
            gotoxy(54,26);      printf("ATM CAN'T HAVE MORE THAN 10 LAKHS...");     Sleep(2000);
        }
        else
        {
            updateATMAmount(trans,add);
            gotoxy(50,27);      printf("MONEY ADDED SUCCESSFULLY...RETURNING TO MENU!!!");      Sleep(2000);
        }
        displayEmployeeMenu();
    }
    else if(choice == 0)
    {
        displayEmployeeMenu();
    }
    else
    {
        gotoxy(50,19);      printf("INVALID ENTRY...RETURNING TO MENU!!!");     Sleep(1500);
        displayEmployeeMenu();
    }

}

void disableATMServices()
{
    clrscr();
    int i=0;
    char username[20],pw[20],option[5],ch;
    gotoxy(40,10);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t  VERIFY LOGIN\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    gotoxy(40,14);      printf("\xDB\t\xB2\xB2\xB2 ENTER USERNAME : ");
    gotoxy(40,16);      printf("\xDB\t\xB2\xB2\xB2 ENTER PASSWORD : ");
    gotoxy(75,14);      gets(username);   gotoxy(75,16);
    
    while(ch != 13)
    {
        ch = getch();
        if(ch != 13 && ch!= 8)
        {
            printf("*");
            pw[i] = ch;
            i++;
        }
        else if(ch == 8)
        {
            if(i>0)
            {
                i--;
                pw[i] = '\0';
                printf("\b \b");
            }
        }
        if(ch == 13)
        {
            break;
        }
    }

    if((strcmp(username,"bankingsystem@miniproject")==0) && (strcmp(pw,"vcestudentbank") == 0))
    {
        gotoxy(65,25);      printf("LOGIN VERIFIED");   Sleep(1000);
        gotoxy(65,25);      printf("              ");
        if(ATMServices == TRUE)
        {
            printf("\033[1;31m");
            gotoxy(82,29);     printf("NOTE : CASE SENSITIVE");
            printf("\033[0m;");
            gotoxy(50,22);      printf("DISABLE ATM SERVICES (YES/NO) : ");     scanf("%s",option);
            if(strcmp(option,"YES") == 0)
            {
                gotoxy(50,24);      printf("PRESS 'YES' TO CONFIRM : ");     scanf("%s",option);
                gotoxy(82,29);     printf("                     ");
                if(strcmp(option,"YES") == 0)
                {
                    ATMServices = FALSE;
                    gotoxy(47,26);      printf("ATM SERVICES ARE DISABLED UNTIL YOU ENABLE BACK!!!");    Sleep(2000);
                    gotoxy(43,29);   printf("PRESS ANY KEY TO GO BACK : ");    getch();
                }
            }
        }
        else
        {
            gotoxy(50,22);      printf("ENABLE ATM SERVICES (YES/NO) : ");     scanf("%s",option);
            if(strcmp(option,"YES") == 0)
            {
                gotoxy(50,24);      printf("PRESS 'YES' TO CONFIRM : ");     scanf("%s",option);
                if(strcmp(option,"YES") == 0)
                {
                    ATMServices = TRUE;
                    gotoxy(51,26);      printf("ATM SERVICES ARE ENABLED BACK FOR USERS!!");
                    gotoxy(43,29);   printf("PRESS ANY KEY TO GO BACK : ");    getch();
                }
            }
        }
        displayEmployeeMenu();
    }
    else
    {
        gotoxy(55,22);      printf("WARNING : WRONG USERNAME OR PASSWORD!!!!!"); Sleep(2000);
        gotoxy(47,23);      printf("ENTER 1 TO TRY AGAIN..0 TO RETURN TO MAIN MENU..");
        int opt;    gotoxy(60,24);   printf("ENTER YOUR CHOICE: ");  scanf("%d",&opt);
        if(opt==1){
                fflush(stdin);
                disableATMServices();
            }
        else{
                fflush(stdin);
                displayEmployeeMenu();
            }
    }
}

void updateATMAmount(char transType, long long int amount)
{
    long long int amt;
    FILE *fp = fopen("AtmBalance.txt","a+");
    while(fscanf(fp,"%lld",&amt) != EOF)
    {
        //do nothing;
    }

    FILE *fp1 = fopen("newBal.txt","w+");
    if(transType == 'D')
    {
        amt = amt + amount;
        fprintf(fp1,"%lld",amt);
    }
    else if(transType == 'W')
    {
        amt = amt - amount;
        fprintf(fp1,"%lld",amt);
    }
    else
    {
        //
    }
    fclose(fp); fclose(fp1);
    remove("AtmBalance.txt");
    rename("newBal.txt","AtmBalance.txt");
}

long long int checkATMAmount()
{
    FILE *fp = fopen("AtmBalance.txt","r");
    long long int AtmBal;
    while(fscanf(fp,"%lld",&AtmBal) != EOF)
    {
        //do nothing;
    }
    fclose(fp);
    return AtmBal;
}

void loadingPage(char message[])
{
    system("cls");
    gotoxy(40,10);      printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    menuBorder();
    int y=16,y1=18;
    for(int i=0;i<9;i++)
    {
        gotoxy(51,y++);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    }
    for(int i=0;i<5;i++)
    {
        gotoxy(52,y1++);
        printf("                                        ");
    }
    if(strcmp(message,"WELCOME TO VCE STUDENT BANK.") == 0)
    {
        gotoxy(58,y1-3);
    }
    else if(strcmp(message,"THANK YOU") == 0)
    {
        gotoxy(68,y1-3);
    }
    
    for(int i=0;i<strlen(message);i++)
    {
        printf("%c",message[i]);
        Sleep(70);
    }
    Sleep(500);

}

void menuBorder()
{
    gotoxy(40,11);  printf("\xDB");     gotoxy(105,11);  printf("\xDB");
    gotoxy(40,12);  printf("\xDB");     gotoxy(105,12);  printf("\xDB");
    gotoxy(40,13);  printf("\xDB");     gotoxy(105,13);  printf("\xDB");
    gotoxy(40,14);  printf("\xDB");     gotoxy(105,14);  printf("\xDB");
    gotoxy(40,15);  printf("\xDB");     gotoxy(105,15);  printf("\xDB");
    gotoxy(40,16);  printf("\xDB");     gotoxy(105,16);  printf("\xDB");
    gotoxy(40,17);  printf("\xDB");     gotoxy(105,17);  printf("\xDB");
    gotoxy(40,18);  printf("\xDB");     gotoxy(105,18);  printf("\xDB");
    gotoxy(40,19);  printf("\xDB");     gotoxy(105,19);  printf("\xDB");
    gotoxy(40,20);  printf("\xDB");     gotoxy(105,20);  printf("\xDB");
    gotoxy(40,21);  printf("\xDB");     gotoxy(105,21);  printf("\xDB");
    gotoxy(40,22);  printf("\xDB");     gotoxy(105,22);  printf("\xDB");
    gotoxy(40,23);  printf("\xDB");     gotoxy(105,23);  printf("\xDB");
    gotoxy(40,24);  printf("\xDB");     gotoxy(105,24);  printf("\xDB");
    gotoxy(40,25);  printf("\xDB");     gotoxy(105,25);  printf("\xDB");
    gotoxy(40,26);  printf("\xDB");     gotoxy(105,26);  printf("\xDB");
    gotoxy(40,27);  printf("\xDB");     gotoxy(105,27);  printf("\xDB");
    gotoxy(40,28);  printf("\xDB");     gotoxy(105,28);  printf("\xDB");
    gotoxy(40,29);  printf("\xDB");     gotoxy(105,29);  printf("\xDB");
    gotoxy(40,30);  printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
}

void gotoxy(int x,int y) 
{ 
    coord.X=x + 15; 
    coord.Y=y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); 
}

void clrscr(void)
{
    system("cls");
}
