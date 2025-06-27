#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 100
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define MAX_SIZE_EMAIL 50
#define MAX_CITIES 5
#include <ctype.h>
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
#define MAX_PASSENGERS 100

typedef struct CityNode{
    char city[30];
    struct CityNode *next;
} CityNode;

typedef struct{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
    char email[MAX_SIZE_EMAIL];
} sFileHeader;

typedef struct {
    int customer_id;
    char name[50];
    char passport[20];
} Customer;
typedef struct TreeNode {
    Customer customer;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

static int last_assigned_customer_id = 0;

TreeNode* createnode(Customer customer) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->customer = customer;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(TreeNode** root, Customer customer) {
    if (*root == NULL) {
        *root = createnode(customer);
        return;
    }

    if (customer.customer_id < (*root)->customer.customer_id) {
        insert(&((*root)->left), customer);
    } else {
        insert(&((*root)->right), customer);
    }
}

void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("\n\n\t\t\tPassenger %d details:\n\t\t\tName: %s\n\t\t\tPassport Number: %s\n",
                root->customer.customer_id, root->customer.name, root->customer.passport);
        inorderTraversal(root->right);
    }
}
void menu();
void destination();


CityNode* createNode(const char *cityName){
    CityNode *newNode = (CityNode*)malloc(sizeof(CityNode));
    if (newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->city, cityName);
    newNode->next = NULL;
    return newNode;
}

void insertCity(CityNode **head, const char *cityName){
    CityNode *newNode = createNode(cityName);
    CityNode *temp = *head;
    if (*head == NULL || strcmp((*head)->city, cityName) > 0){
        newNode->next = *head;
        *head = newNode;
    }else{
        while (temp->next != NULL && strcmp(temp->next->city, cityName) < 0){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void freeList(CityNode *head){
    CityNode *temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

int searchCity(CityNode *head, const char *searchCityName){
    int d=1;
    CityNode *temp = head;
    FILE *file = fopen("Reservation_Details.txt", "a");
    if (file == NULL){
        printf("Error opening file.\n");
        exit(1);
    }

    while (temp != NULL){
            if(d==1)

            if (strcmp(temp->city, searchCityName) == 0){
                fprintf(file, "\n\t\t\t%s", searchCityName);
                fclose(file);
                return 1;
            }

        temp = temp->next;
    }
    fclose(file);
    printf(" \n\n\t\t\t%s is not found in the list.\n", searchCityName);
    return 0;
}

void signup(sFileHeader users[], int *userCount);
int signIn(sFileHeader users[], int userCount);
int isDuplicate(sFileHeader users[], int userCount, const char *username);
void saveUsersToFile(sFileHeader users[], int userCount);
void loadUsersFromFile(sFileHeader users[], int *userCount);
void welcomeMessage();
void resetPassword(sFileHeader users[], int userCount);
void forgotPassword(sFileHeader users[], int userCount);

void printMessageCenter(const char* message){
    int len =0;
    int pos = 0;
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++){

        printf(" ");
    }

    printf("%s",message);
}
void headMessage(const char *message){
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############           Flight Reservation System in C          ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t---------------------------------------------------------------------------");
}

void welcomeMessage(){
    headMessage("Homepage");
    printf("\n\n");
    printf("\n\n\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    printf("\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    printf("\n\t\t* * %87s \n\t\t* * %87s","* *","* *");

    printf("\n\t\t* *                                                          \t\t\t        * *");
    printf("\n\t\t* *                                       Welcome to\t\t\t                * *");
    printf("\n\t\t* *                                Flight Reservation System\t\t\t        * *");
    printf("\n\t\t* *                              =============================\t\t\t        * *");
    printf("\n\t\t* * %87s \n\t\t* * %87s","* *","* *");
    printf("\n\t\t* *\t   Enter any key to continue.....\t\t\t\t                * *");
    printf("\n\t\t* * %87s \n\t\t* * %87s","* *","* *");
    printf("\n\t\t* * %87s \n\t\t* * %87s","* *","* *");
    printf("\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    printf("\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
    getchar();
}
void dateValid(int day, int month, int year){
    int V;
    FILE *filePtr;

    filePtr = fopen("Reservation_Details.txt", "a");

    if (filePtr == NULL){
        printf("Error opening file.");
        return 1;
    }
    scanf("%d / %d / %d", &day, &month, &year);

    while (V == 0){
        if (year >= 1000 && year <= 9999 && month >= 1 && month <= 12){
            if ((month == 4 || month == 6 || month == 9 || month == 11) && (day >= 1 && day <= 30))
                V++;
            else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day >= 1 && day <= 31))
                V++;
            else if (month == 2 && (day >= 1 && day <= 28))
                V++;
            else if ((month == 2 && day == 29) && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
                V++;
        }

        if (V==0){
            printf("\n\n\n\t\t\t You have entered wrong date.");
            printf("\n\n\t\t\t Enter your date of journey:");
            scanf("%d / %d / %d", &day, &month, &year);

        }
    }
    if (V != 0){
        fprintf(filePtr, "\n\n\t\t\tDate: %d/%d/%d\n", day, month, year);
    }


    fclose(filePtr);
    return;
}

void classSelect(int selection){
    FILE *file;
    file = fopen("Reservation_Details.txt", "a");
    if (file == NULL){
        printf("Error opening file!");
        return;
    }
    printf("\n\n\n\t\t\tPlease choose your travel class: ");
    printf("\n\n\t\t\t1. First-Class\n\n\t\t\t2. Business\n\n\t\t\t3. Economy");
    printf("\n\n\t\t\tEnter your choice: ");
    scanf("%d", &selection);


    switch (selection){
    case 1:
        fprintf(file, "\n\t\t\tTravel clas: First-Class");
        break;
    case 2:
        fprintf(file, "\n\t\t\tTravel clas: Business");
        break;
    case 3:
        fprintf(file, "\n\t\t\tTravel clas: Economy");
        break;
    }

    fclose(file);

}
void airlines(int select){
    FILE *file;
    file = fopen("Reservation_Details.txt", "a");
    if (file == NULL){
        printf("Error opening file!");
        return;
    }
    printf("\n\n\n\t\t\t Please choose a suitable time period for your flight:-");
    printf("\n\n\n\t\t\t       %s%25s%25s%19s", "Airlines", "Flight No", "Departure", "Arrival");
    printf("\n\t\t\t       %s%25s%25s%19s", "========", "=========", "=========", "=======");
    printf("\n\n\n\t\t\t 1.US Bangla Airlines  %15s%26s%20s", "FL-101"," 9.00 PM", "3.00 AM");
    printf("\n\n\n\t\t\t 2.Saudia  %27s%26s%20s","FL-313", "8.50 AM", "2.50 PM");
    printf("\n\n\n\t\t\t 3.American Airlines  %16s%26s%20s","FL-216", "10.30 AM", "5.30 PM");
    printf("\n\n\n\t\t\t 4.Emirates %26s%26s%20s","FL-235", "7.50 PM", "2.50 AM");
    printf("\n\n\n\n\t\t\tEnter your choice: ");
    scanf("%d", &select);


    switch (select){
    case 1:
        fprintf(file, "\n\n\t\t\tAirlines: US Bangla Airlines\n\n\t\t\tFlight No: FL-101\n\n\t\t\tDeparture: 9.00 PM\n\n\t\t\tArrival: 3.00 AM");
        break;
    case 2:
        fprintf(file, "\n\n\t\t\tAirlines: Saudia\n\n\t\t\tFlight No: FL-313\n\n\t\t\tDeparture: 8.50 AM\n\n\t\t\tArrival: 2.50 PM");
        break;
    case 3:
        fprintf(file, "\n\n\t\t\tAirlines: American Airlines\n\n\t\t\tFlight No: FL-216\n\n\t\t\tDeparture: 10.30 AM\n\n\t\t\tArrival: 5.30 PM");
        break;
    case 4:
        fprintf(file, "\n\n\t\t\tAirlines: Emirates\n\n\t\t\tFlight No: FL-235\n\n\t\t\tDeparture: 7.50 PM\n\n\t\t\tArrival: 2.50 AM");
        break;
    }
    fclose(file);
}

void saveToTextFile(TreeNode* root, FILE* fp) {
    if (root != NULL) {
        saveToTextFile(root->left, fp);
        fprintf(fp, "\n\n\t\t\tPassenger ");
        fprintf(fp, "%d ", root->customer.customer_id);
        fprintf(fp, "details:");
        fprintf(fp, "\n\t\t\tName: ");
        fprintf(fp, "%s", root->customer.name);
        fprintf(fp, "\n\t\t\tPassport Number: ");
        fprintf(fp, "%s\n", root->customer.passport);
        saveToTextFile(root->right, fp);
    }
}
void loadFromFile(TreeNode** root, FILE* fp) {
    Customer customer;
    while (fread(&customer, sizeof(Customer), 1, fp) == 1) {
        insert(root, customer);
    }
}
void option(){
    int opt;
    printf("\n\n\n\n\t\t\tHow do you want to proceed?\n\n\t\t\t1. Add more reservation\n\t\t\t2. Delete all reservation\n\t\t\t3. Return to Profile page");
    printf("\n\n\t\t\tEnter your choice: ");
    scanf("%d", &opt);
    switch (opt){
    case 1:
        menu();
        break;
    case 2:
        delete();
        break;
    case 3:
        login();
        break;
    }
}
void delete(){
    int y;
    FILE *file = fopen("Reservation_Details.txt", "w");
        if (file == NULL){
            printf("Error opening file for writing.\n");
            return;
        }
        printf("\n\n\t\t\tAre you sure?\n\t\t\t1. Yes\n\t\t\t2. No");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &y);
        if(y==1){
            fprintf(file, "");
            printf("\n\n\t\t\tAll reservation deleted.");
        }
        fclose(file);
}
void menu(){
    TreeNode* root = NULL;
    FILE* fp;
    int day, month, year, selection, number, select;
    headMessage("MAIN MENU");
    destination();
    printf("\n\n\n\t\t\tDeparture date(dd/mm/yyyy): ");
    dateValid(day, month, year);
    classSelect(selection);
    airlines(select);
    printf("\n\n\n\t\t	Number of passengers: ");
    scanf("%d", &number);

    for (int i = 0; i < number; i++) {
        printf("\n\n\t\t\tEnter details for passenger %d:\n", i + 1);
        Customer customer;

        customer.customer_id = ++last_assigned_customer_id;

        printf("\t\t\tName: ");
        scanf("%s", customer.name);
        printf("\t\t\tPassport Number: ");
        scanf("%s", customer.passport);

        insert(&root, customer);
    }
    last_assigned_customer_id = 0;
    fp = fopen("Reservation_Details.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    saveToTextFile(root, fp);
    fclose(fp);
    reservation();
    option();
}

void login(){
    headMessage("Profile Setup");
    sFileHeader users[MAX_USERS];
    int userCount = 0, choice;

    loadUsersFromFile(users, &userCount);

    do{
        printf("\n\n\n\n\n\t\t\tPlease select an option: \t\t\t\t\t\t\t");
        printf("\n\n\t\t\t1. Sign Up \t\t\t\t\t\t\t\t\t");
        printf("\n\n\t\t\t2. Sign In \t\t\t\t\t\t\t\t\t");
        printf("\n\n\t\t\t3. Reset Password \t\t\t\t\t\t\t\t\t");
        printf("\n\n\t\t\t4. Forgot Password \t\t\t\t\t\t\t\t\t");
        printf("\n\n\t\t\t5. Exit \t\t\t\t\t\t\t\t\t");
        printf("\n\n\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice){
        case 1:
            signUp(users, &userCount);
            saveUsersToFile(users, userCount);
            break;
        case 2:
            if (signIn(users, userCount)){
                printf("\n\n\t\t\tLogin successful!\n");
                menu();
            }
            else printf("\n\n\t\t\tLogin failed.\n");
            break;
        case 3:
            resetPassword(users, userCount);
            break;
        case 4:
            forgotPassword(users, userCount);
            break;
        case 5:
            saveUsersToFile(users, userCount);
            printf("\n\n\t\t\tExiting...\n");
            break;
        default:
            printf("\n\n\t\t\tInvalid choice. Please try again.\n");
        }
    }while (choice != 5);
}
void reservation(){
    int reserve;
    printf("\n\n\n\t\t\tDo you want to see your reservation details?\n\n\t\t\t1. Yes\n\t\t\t2. No");
    printf("\n\n\t\t\tEnter your choice: ");
    scanf("%d", &reserve);
    switch (reserve){
        case 1:
            read();
            break;
        case 2:
            option();
            break;


    }
}
void read(){

    printf("\n\n\n\n\t\t\t %50s", "Reservation details");
    printf("\n\t\t\t %50s", "~~~~~~~~~~~~~~~~~~~");
    printf("\n\n\n\n\n\t\t\tDestination: ");
    int c;
    FILE *file = fopen("Reservation_Details.txt", "r");
            if (file == NULL){
                printf("Error opening file for writing.\n");
            return;
            }
            while((c=getc(file))!=EOF){
                putchar(c);
            }
            fclose(file);
            printf("\n\n\n\t\t\t\t\t   Thank you for choosing our service \n\t\t\t\t\t\t    Have a nice day\n\n");
            option();
}
void destination(sFileHeader users[], int *userCount){
    CityNode *head = NULL;

    char cityNames[][30] = {"DHAKA(BANGLADESH)", "TOKYO(JAPAN)", "VANCOUVER(CANADA)", "GENEVA(SWITZERLAND)", "SYDNEY(AUSTRALIA)",
                            "JAKARTA(INDONESIA)", "EDINBURGH(SCOTLAND)", "OSLO(NORWAY)", "ZURICH(SWITZERLAND)", "CHICAGO(US)", "KATHMANDU(NEPAL)",
                            "ISTANBUL(TURKEY)", "WARSAW(POLAND)", "ULAANBAATAR(MONGOLIA)", "LONDON(UK)", "QUITO(ECUADOR)", "BERLIN(GERMANY)",
                            "PARIS(FRANCE)", "NEW_YORK(US)", "AMSTERDAM(NETHERLANDS)", "ROME(ITALY)", "FRANKFURT(GERMANY)", "YANGON(MYANMAR)",
                            "MADRID(SPAIN)", "HELSINKI(FINLAND)", "XI'AN(CHINA)"
                           };

    for (int i = 0; i < sizeof(cityNames) / sizeof(cityNames[0]); i++){
        insertCity(&head, cityNames[i]);
    }

    char searchCityName1[30], searchCityName2[30];
    int found;
    do{
        printf("\n\n\n\t\t\tEnter the city name(country) to search: \n\n\t\t\tFrom: ");
        scanf("%s", searchCityName1);
        for(int i = 0; i < strlen(searchCityName1); i++){
            searchCityName1[i] = toupper(searchCityName1[i]);
        }
        printf("\t\t\tTo: ");
        scanf("%s", searchCityName2);
        for (int i = 0; i < strlen(searchCityName2); i++){
            searchCityName2[i] = toupper(searchCityName2[i]);
        }
        if(strcmp(searchCityName1, searchCityName2) == 0){
            printf("\n\t\t\tBoth destination cannot be the same. Please try again.\n");
            continue;
        }

        int fromCityFound = searchCity(head, searchCityName1);
        int toCityFound = searchCity(head, searchCityName2);

        if (!fromCityFound || !toCityFound) {
            printf("\n\n\n\t\t\tOne or more cities are not found. Available city options:\n\n");
            CityNode *temp = head;
            while (temp != NULL) {
                printf("\t\t\t- %s\n", temp->city);
                temp = temp->next;
            }
            continue;
        }

        break;

    } while (1);

    freeList(head);

    return;
}

void signUp(sFileHeader users[], int *userCount){
    if (*userCount >= MAX_USERS){
        printf("\n\n\t\t\tCannot sign up. Maximum user limit reached.\n");
        return;
    }

    char username[MAX_SIZE_USER_NAME], password[MAX_SIZE_PASSWORD], email[MAX_SIZE_EMAIL];
    printf("\n\n\t\t\tName: ");
    scanf("%s", username);

    if (isDuplicate(users, *userCount, username)){
        printf("\n\n\t\t\tUsername already exists. Please choose a different one.\n");
        return;
    }
    printf("\n\t\t\tEmail: ");
    scanf("%s", email);
    printf("\n\t\t\tPassword: ");
    scanf("%s", password);
    strcpy(users[*userCount].username, username);
    strcpy(users[*userCount].password, password);
    strcpy(users[*userCount].email, email);
    (*userCount)++;
    printf("\n\n\t\t\t\e[1mUser signed up successfully!\e[m\n");
}

int signIn(sFileHeader users[], int userCount) {
    char username[MAX_SIZE_USER_NAME], password[MAX_SIZE_PASSWORD];
    getchar();
    printf("\n\n\t\t\tName: ");
    if (fgets(username, MAX_SIZE_USER_NAME, stdin) == NULL) {
        printf("\n\n\t\t\tError reading username.\n");
        return 0;
    }
    username[strcspn(username, "\n")] = '\0';

    printf("\n\t\t\tPassword: ");
    if (fgets(password, MAX_SIZE_PASSWORD, stdin) == NULL) {
        printf("\n\n\t\t\tError reading password.\n");
        return 0;
    }
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int isDuplicate(sFileHeader users[], int userCount, const char *username){
    for (int i = 0; i < userCount; i++)
        if (strcmp(users[i].username, username) == 0)
            return 1;
    return 0;
}
void saveUsersToFile(sFileHeader users[], int userCount){
    FILE *file = fopen("Profile.txt", "w");
    if (file != NULL){
        for (int i = 0; i < userCount; i++){
            fprintf(file, "%s\n%s\n%s\n\n", users[i].username, users[i].email, users[i].password);
        }
        fclose(file);
    }else{
        printf("Error: Unable to save user data.\n");
    }
}

void loadUsersFromFile(sFileHeader users[], int *userCount){
    FILE *file = fopen("Profile.txt", "r");
    if (file != NULL){
        while (fscanf(file, "%s %s %s", users[*userCount].username, users[*userCount].email, users[*userCount].password) != EOF){
            (*userCount)++;
        }
        fclose(file);
    }
}

void resetPassword(sFileHeader users[], int userCount){
    char username[MAX_SIZE_USER_NAME], password[MAX_SIZE_PASSWORD], newPassword[MAX_SIZE_PASSWORD];
    printf("\n\n\t\t\tUsername: ");
    scanf("%s", username);
    printf("\n\n\t\t\tPrevious Password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++){
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("\n\t\t\tEnter new password: ");
            scanf("%s", newPassword);
            strcpy(users[i].password, newPassword);
            printf("\n\n\t\t\tPassword reset successfully!\n");
            return;
        }
    }
    printf("\n\n\t\t\tUser not found.\n");
}

void forgotPassword(sFileHeader users[], int userCount){
    char email[MAX_SIZE_EMAIL];
    printf("\n\n\t\t\tEnter your email: ");
    scanf("%s", email);

    for (int i = 0; i < userCount; i++){
        if (strcmp(users[i].email, email) == 0){
            printf("\n\t\t\tYour password is: %s\n", users[i].password);
            return;
        }
    }
    printf("\n\n\t\t\tEmail not found.\n");
}

int isFileExists(const char *path){

    FILE *fp = fopen(path, "rb");
    int status = 0;

    if (fp != NULL){
        status = 1;

        fclose(fp);
    }
    return status;
}

void init(){
    FILE *fp = NULL;
    int status = 0;
    sFileHeader fileHeaderInfo = {0};
}

int main(){
    init();
    welcomeMessage();
    login();

    return 0;
}
