#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<ctype.h> //used for characters
#include<unistd.h> //used for interacting with operating system (full form--> Unix Standard)
#include<stdlib.h> //used for memory allocation etc (full form--> Standard Library)
#include<time.h> //used to work with time and date information

int i,j;
int main_exit;
void closed();
void menu();
void new_acc();
void edit();
void transact();
void see();
void erase();
void view_list();

struct date{
    int month,day,year;
};

struct person{
    char name[60];
    int acc_no,age;
    char address[60];
    char citizenship[15];
    int phone;
    char acc_type[10];
    int amount;
    struct date dob;
    struct date deposit;
    struct date withdraw;
}add,upd,check,rem,transaction;

int main(){
    char pass[15],password[15]="thisisme";
    int i=0;
    printf("\n\n\t Enter the password to login (maximum 15 characters):");
    scanf("%s", &pass);
    if(strcmp(pass,password) == 0){
        printf("\n\n Password Matched! Loading...");
        sleep(3);
        menu();
    }
    else{
        printf("\n Wrong Password!!!");
        login_try:
            printf("\n Enter 1 to try again and 0 to exit: ");
            scanf("%d", &main_exit);
            if(main_exit == 1){
                main();
            }
            else if(main_exit == 0){
                closed();
            }
    }
}

void menu(){
    int choice;
    printf("\n");
    printf("\n\n\t\t\t CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\t\t\t             WELCOME TO THE MENU");
    printf("\n\n\t1.Create new account \n\t2.Update information of existing account \n\t3.For transaction \n\t4.Check the details of the existing account \n\t5.Remove existing account \n\t6.View customer's list \n\t7.Exit \n\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);
    switch(choice){
    case 1:
        new_acc();
        break;
    case 2:
        edit();
        break;
    case 3:
        transact();
        break;
    case 4:
        see();
        break;
    case 5:
        erase();
        break;
    case 6:
        view_list();
        break;
    case 7:
        closed();
        break;
    }
}

void new_acc(){
    int choice;
    FILE *ptr;
    ptr=fopen("record.dat","a+");
    account_no:
        printf("\t\t\t ADD RECORD");
        printf("\n\n\n Enter today's date (mm/dd/yyyy):");
        scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
        printf("\n Enter the account number:");
        scanf("%d", &check.acc_no);
        while(fscanf(ptr, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amount, &add.deposit.month, &add.deposit.day, &add.deposit.year)!=EOF){
            if(check.acc_no==add.acc_no){
                printf("\n Account number already in use!");
                goto account_no;
            }
        }
        add.acc_no=check.acc_no;
        printf("\n Enter the name:");
        scanf("%s", &add.name);
        printf("\n Enter the date of the birth(mm/dd/yyyy):");
        scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
        add.age=add.deposit.year-add.dob.year;
        printf("\n The age of the customer is: %d \n", add.age);
        printf("\n Enter the address:");
        scanf("%s", &add.address);
        printf("\n Enter the citizenship number:");
        scanf("%s", &add.citizenship);
        printf("\n Enter the phone number:");
        scanf("%d", &add.phone);
        printf("\n Type of account: \n\t #Saving \n\t #Current \n\t #Fixed1(for 1 year) \n\t #Fixed2(for 2 years) \n\t #Fixed3(for 3 years):");
        scanf("%s", &add.acc_type);
        printf("\n Enter the amount:");
        scanf("%d", &add.amount);
        fprintf(ptr, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
        fclose(ptr);
        printf("\n Account created successfully!!!");
        add_invalid:
            printf("\n\n\n\t Enter 1 to go to the main menu and 0 to exit:");
            scanf("%d", &main_exit);
            if(main_exit == 1){
                menu();
            }
            else if(main_exit == 0){
                closed();
            }
            else{
                printf("\nInvalid!!!");
                goto add_invalid;
            }
}

void edit(){
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    printf("\nEnter the account number of the customer whose information you want to change:");
    scanf("%d", &upd.acc_no);
    while(fscanf(old, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amount, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if(add.acc_no == upd.acc_no){
            test = 1;
            printf("\nWhich information do you want to change?:\n1. Address\n2. Phone number\n\nEnter your choice:");
            scanf("%d", &choice);
            // Create a new structure to hold the updated information
            struct person upd_info = add;
            if(choice == 1){
                printf("\nEnter the address:");
                scanf("%s", &upd_info.address);
            }
            else if(choice == 2){
                printf("\nEnter the phone number:");
                scanf("%d", &upd_info.phone);
            }
            // Write the updated information to the new file
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",upd_info.acc_no, upd_info.name, upd_info.dob.month, upd_info.dob.day,upd_info.dob.year, upd_info.age, upd_info.address, upd_info.citizenship,upd_info.phone, upd_info.acc_type, upd_info.amount,upd_info.deposit.month, upd_info.deposit.day, upd_info.deposit.year);
            printf("\nChanges saved!!!");
        }
        else{
            // If the account number doesn't match, copy the record as it is
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,add.age, add.address, add.citizenship, add.phone, add.acc_type,add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if(test != 1){
        printf("\nRecord not found!");
        edit_invalid:
            printf("\nEnter 0 to try again, 1 to go to the main menu, or 2 to exit:");
            scanf("%d", &main_exit);
            if(main_exit == 1){
                menu();
            }
            else if(main_exit == 2){
                closed();
            }
            else if(main_exit == 0){
                edit();
            }
            else{
                printf("\nInvalid!");
                goto edit_invalid;
            }
    }
    else{
        printf("\n\nEnter 1 to go to the main menu or 0 to exit:");
        scanf("%d", &main_exit);
        if(main_exit == 1){
            menu();
        } else if(main_exit == 0){
            closed();
        }
    }
}

void transact() {
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");  // Open in write mode
    printf("\nEnter the account number of the customer:");
    scanf("%d", &transaction.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",&add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,&add.age, add.address, add.citizenship, &add.phone, add.acc_type,&add.amount, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == transaction.acc_no){
            test = 1;
            if (strcmp(add.acc_type, "Fixed1") == 0 || strcmp(add.acc_type, "Fixed2") == 0 || strcmp(add.acc_type, "Fixed3") == 0 ) {
                printf("\nYou cannot deposit or withdraw cash in a fixed account!!!");
                // Write the fixed account information back to the new file
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,add.age, add.address, add.citizenship, add.phone, add.acc_type,add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
            }
            else{
                printf("\n\nDo you want to \n1. Deposit \n2. Withdraw? \nEnter your choice:");
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("\nEnter the amount you want to deposit: $");
                    scanf("%d", &transaction.amount);
                    add.amount += transaction.amount;
                }
                else if (choice == 2) {
                    printf("\nEnter the amount you want to withdraw: $");
                    scanf("%d", &transaction.amount);
                    add.amount -= transaction.amount;
                }
                // Write the updated information to the new file
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,add.age, add.address, add.citizenship, add.phone, add.acc_type,add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
                if (choice == 1) {
                    printf("\n\nDeposited successfully!!!");
                }
                else if (choice == 2) {
                    printf("\n\nWithdrawn successfully!!!");
                }
            }
        }
        else {
            // If the account number doesn't match, copy the record as it is
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,add.age, add.address, add.citizenship, add.phone, add.acc_type,add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test != 1) {
        printf("\nRecord not found!");
        transact_invalid:
            printf("\nEnter 0 to try again, 1 to go to the main menu, or 2 to exit:");
            scanf("%d", &main_exit);
            if (main_exit == 1) {
                menu();
            }
            else if (main_exit == 2) {
                closed();
            }
            else if (main_exit == 0) {
                transact();
            }
            else {
                printf("\nInvalid!");
                goto transact_invalid;
            }
    }
    else {
        printf("\n\nEnter 1 to go to the main menu or 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 1) {
            menu();
        }
        else if (main_exit == 0) {
            closed();
        }
    }
}

void see(){
    FILE *ptr;
    int test=0;
    int choice;
    int time, money;
    float interest;
    ptr=fopen("record.dat", "r");
    printf("\n\n Do you want to check by \n 1. Account number \n 2. Name \nEnter your choice:");
    scanf("%d", &choice);
    if(choice==1){
        printf("\n Enter the account number:");
        scanf("%d", &check.acc_no);
        while(fscanf(ptr, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amount, &add.deposit.month, &add.deposit.day, &add.deposit.year)!=EOF){
            if(check.acc_no==add.acc_no){
                test=1;
                printf("\n Account number: %d \n Name: %s \n Date of birth: %d/%d/%d \n Age: %d \n Address: %s \n Citizenship number: %s \n Phone number: %d \n Type of account: %s \n Amount deposited: $ %d \n Date of deposit: %d/%d/%d \n\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
                if(strcmp(add.acc_type, "Fixed1")==0 || strcmp(add.acc_type, "Fixed2")==0 || strcmp(add.acc_type, "Fixed3")==0 || strcmp(add.acc_type, "Current") == 0){
                    printf("\n %s will get no interest.", add.name);
                }
                else if(strcmp(add.acc_type, "Saving")==0){
                    printf("\n When does %s want to take their money (in years)?:", add.name);
                    scanf("%d", &time);
                    if(time<=3) interest = 2.5;
                    else if(time>3 && time<=5)  interest = 5.0;
                    money=add.amount*(interest/100)*time;
                    printf("\n %s will get $%d interest after %d year.", add.name, money, time);
                    //int total = money + add.amount;
                    //printf("\n Total Amount will be $%d after %d years",total,time);
                }
            }
        }
    }
    else if(choice==2){
        printf("\n Enter the name:");
        scanf("%s", &check.name);
        while(fscanf(ptr, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amount, &add.deposit.month, &add.deposit.day, &add.deposit.year)!=EOF){
            if(strcmp(check.name, add.name)==0){
                test=1;
                printf("\n Account number: %d \n Name: %s \n Date of birth: %d/%d/%d \n Age: %d \n Address: %s \n Citizenship number: %s \n Phone number: %d \n Type of account: %s \n Amount deposited: $ %d \n Date of deposit: %d/%d/%d \n\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
                if(strcmp(add.acc_type, "Fixed1")==0 || strcmp(add.acc_type, "Fixed2")==0 || strcmp(add.acc_type, "Fixed3")==0 || strcmp(add.acc_type, "Current")==0){
                    printf("\n %s will get no interest.", add.name);
                }
                else if(strcmp(add.acc_type, "Saving")==0){
                    printf("\n When does %s want to take their money (in years)?:", add.name);
                    scanf("%d", &time);
                    if(time<=3) interest = 2.5;
                    else if(time>3 && time<=5)  interest = 5.0;
                    money=add.amount*(interest/100)*time;
                    printf("\n %s will get $%d interest after %d year.", add.name, money, time);

                }
            }
        }
    }
    fclose(ptr);
    if(test != 1){
        printf("\n Record not found!");
        see_invalid:
            printf("\n Enter 0 to try again, 1 to go to the main menu or 2 to exit:");
            scanf("%d", &main_exit);
            if(main_exit==1){
                menu();
            }
            else if(main_exit==2){
                closed();
            }
            else if(main_exit==0){
                see();
            }
            else{
                printf("\n Invalid!");
                goto see_invalid;
            }
        }
        else{
            printf("\n\n Enter 1 to go to the main menu or 0 to exit:");
            scanf("%d", &main_exit);
            if(main_exit==1){
                menu();
            }
            else if(main_exit==0){
                closed();
            }
        }
}

void erase() {
    FILE *old, *newrec;
    int test = 0;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    printf("\nEnter the account number of the customer you want to delete:");
    scanf("%d", &rem.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",&add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year,&add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type,&add.amount, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (rem.acc_no != add.acc_no) {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n",add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,add.age, add.address, add.citizenship, add.phone, add.acc_type,add.amount, add.deposit.month, add.deposit.day, add.deposit.year);
        }
        else {
            test++;
            printf("\nRecord deleted successfully!!!\n\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test == 0) {
        printf("\nRecord not found!");
        erase_invalid:
            printf("\nEnter 0 to try again, 1 to go to the main menu, or 2 to exit:");
            scanf("%d", &main_exit);
            if (main_exit == 1) {
                menu();
            }
            else if (main_exit == 2) {
                closed();
            }
            else if (main_exit == 0) {
                erase();
            }
            else {
                printf("\nInvalid!");
                goto erase_invalid;
            }
    }
    else {
        printf("\n\nEnter 1 to go to the main menu or 0 to exit:");
        scanf("%d", &main_exit);
        if (main_exit == 1) {
            menu();
        }
        else if (main_exit == 0) {
            closed();
        }
    }
}

void view_list(){
    FILE *view;
    view=fopen("record.dat", "r");
    int test=0;
    printf("\n Account number \t Name \t\t Address \t\t Phone number \n");
    while(fscanf(view, "%d %s %d/%d/%d %d %s %s %d %s %d %d/%d/%d \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amount, &add.deposit.month, &add.deposit.day, &add.deposit.year)!=EOF){
        printf("\n %d \t\t\t %s \t\t %s \t\t %d", add.acc_no, add.name, add.address, add.phone);
        test++;
    }
    fclose(view);
    if(test==0){
        printf("\n NO RECORDS! \n");
    }
    view_list_invalid:
        printf("\n\n Enter 1 to go to the main menu or 0 to exit:");
        scanf("%d", &main_exit);
        if(main_exit==1){
            menu();
        }
        else if(main_exit==0){
            closed();
        }
        else{
            printf("\n Invalid! \n");
            goto view_list_invalid;
        }
}

void closed(){
    printf("\n\n\n This is a Banking Management System made by Md Afir Uddin Bhuiyan \n\n\n");
}
