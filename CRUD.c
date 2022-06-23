#include <stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>

struct user
{
	char citizenship_number[50];
    char name[30];
    char gender;
    float meter;
};

FILE *file;

void input(struct user *u)
{
    printf("\nEnter the name:");
    scanf("%s",&u->name);
    printf("Enter the citizenship_number:");
    scanf("%s",&u->citizenship_number);
    printf("Enter gender:");
    scanf(" %c",&u->gender);
    printf("Enter meter:");
    scanf("%f",&u->meter);
    fflush(stdin);
} 

void add_user()
{
	char continuation;
	struct user data;
	file = fopen("a.txt", "a+");
	while(1){
	
		system("cls");
	    printf("\n\nPlease enter the details of new user \n");
	    input(&data);
	    fwrite(&data, sizeof(data), 1, file);
	    
	    printf("\nUser Record Has Been Created ");
	    printf("\nDo you want to continue(y/n)");
	    scanf(" %c",&continuation);
	    if(continuation=='n' || continuation=='N'){
	    	fclose(file);
			break;
		}
	}
    
}

void display(struct user u)
{
    printf("\nName: %s", u.name);
    printf("\ncitizenship_number: %s", u.citizenship_number);
    printf("\ngender: %c",u.gender);
    printf("\nmeter: %f", u.meter);
    
} 
void display_all()
{
	system("cls");
    struct user data;
    char continuation;
    printf("\n\nDISPLAY ALL RECORD !!!\n");
    file = fopen("a.txt", "rb");
    while ((fread(&data, sizeof(data), 1, file)) > 0)
    {
        display(data);
        printf("\n====================================\n");
    } 
    printf("\nPress any key");
	    getch();
	fclose(file);
    	
	
		
	
}

void search_user(){

	char c[50];
	char continuation;
	file=fopen("a.txt","rb");
	struct user data;
	while(1){
		system("cls");
		printf("Enter citizenship_number:");
		scanf("%s",&c);
		int flag=0;
		
		while ((fread(&data, sizeof(data), 1, file)) > 0)
	    {
	        if (strcmp(data.citizenship_number,c)==0)
	        {
	            display(data);
	            flag = 1;
	        } 
	    }
	    
	    if (flag == 0)
	        printf("\nRecord not exist");
	        
	    printf("\nDo you want to continue(y/n)");
	    scanf(" %c",&continuation);
	    if(continuation=='n' || continuation=='N'){
	    	fclose(file);
			break;
		}
	}
	
	
}

void modify_user()
{
	system("cls");
    struct user data;
    char c[50],continuation;
    int found = 0;
	while(1){
		system("cls");
		printf("\nTo Modify ");
	    printf("\nPlease Enter citizenship_number: ");
	    scanf("%s", &c);
	    file = fopen("a.txt", "rb+");
	    while ((fread(&data, sizeof(data), 1, file)) > 0 && found == 0)
	    {
	        if (strcmp(data.citizenship_number,c)==0)
	        {
	            display(data);
	            printf("\n\nPlease enter the new details of user \n");
	            input(&data);
	            fseek(file,  - (long)sizeof(data), 1);
	            fwrite(&data, sizeof(data), 1, file);
	            printf("\n Record Updated");
	            found = 1;
	        } 
	    }
	   
	    if (found == 0)
	        printf("\n Record Not Found ");
		printf("\nDo you want to continue(y/n)");
	    scanf(" %c",&continuation);
	    if(continuation=='n' || continuation=='N'){
	    	fclose(file);
			break;	
		}	
	}
	    
}

void delete_user()
{
	
    char c[50],continuation;
    bool record_exist=false;
    struct user data;
    FILE *file2;
    while(1){
    	record_exist=false;
    	system("cls");
    	printf("\n\nDelete Record");
	    printf("\nPlease Enter citizenship number you want to delete: ");
	    scanf("%s", &c);
	    file = fopen("a.txt", "rb");
	    file2 = fopen("temp.txt", "wb");
	    rewind(file);
	    while ((fread(&data, sizeof(data), 1, file)) > 0)
	    {
	        if (strcmp(data.citizenship_number,c)!=0)
	        {
	            fwrite(&data, sizeof(data), 1, file2);
	        }
			else record_exist=true;
	    }
	    fclose(file2);
	    fclose(file);
	    remove("a.txt");
	    rename("temp.txt", "a.txt");
	    if(record_exist==true){
	    	printf("\nRecord deleted.");
		}
	    else printf("\nRecord not found");
	    printf("\nDo you want to continue(y/n)");
	    scanf(" %c",&continuation);
	    if(continuation=='n' || continuation=='N'){
			break;
		}
	    	
	}
    
}
void menu()
{
    int choice;
    system("cls");
    printf("\t\t\t\t____Welcome Water Management System_____");
	printf("\n\n\t\t1. Add user");
	printf("\n\n\t\t2. Display all users");
	printf("\n\n\t\t3. Delete users");
	printf("\n\n\t\t4. Edit user record");
	printf("\n\n\t\t5. Search users");
	printf("\n\n\t\t6. Exit\n");
    printf("\nEnter your choice (1-6): ");
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
        	system("cls");
            add_user();
            break;
        case 2:
        	display_all();
        	break;
        	
        case 3:
        	delete_user();
        	break;
        case 4:
        	modify_user();
        	break;
        	
        case 5:
        	search_user();
        	break;
        	
        case 6:
        	exit(0);
        	break;
        default:
            printf("\a");
            menu();
    }
    
}


FILE *file;

void main(){
	char username[20],password[20];
	
	
	while(1){
		printf("\nEnter you username:");
		scanf("%s",&username);
		printf("Enter your password:");
		int p=0; 
	    do{ 
	        password[p]=getch(); 
	        if(password[p]!='\r'){ 
	            printf("*"); 
	        } 
	        p++; 
	    }while(password[p-1]!='\r'); 
	    password[p-1]='\0'; 
		if(strcmp(username,"amrit")!=0 || strcmp(password,"amrit")!=0){
			system("cls");
			printf("\nPassword or username is incorrect");
			
		}else break;
	}	
	while(1){
		menu();
	}
	
}
