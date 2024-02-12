#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX 10000


typedef struct node
{
    struct node *prev;
    struct node *next;
    char name[MAX];
    char countrycode[4];
    char phoneno[20];
    char mailid[MAX];
    int birthMonth;
    int birthDay;
    int isFavorite;

} node;

node *head = NULL;

void importdata() {
    FILE* fp = fopen("data.csv", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[100000];
    char *token;
    fgets(line, sizeof(line), fp); 

    node *temp = NULL;
    node *parse = NULL;
    head = NULL;

    while (fgets(line, sizeof(line), fp) != NULL) {
        temp = (node*)malloc(sizeof(node));
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        token = strtok(line, ",");
        if (token != NULL) {
            strcpy(temp->name, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(temp->countrycode, token);
            printf("%s \n",token);

        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(temp->phoneno, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            temp->birthMonth = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            temp->birthDay = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(temp->mailid, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            temp->isFavorite = atoi(token);
        }

        temp->prev = NULL;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
            parse = temp;
        } else {
            parse->next = temp;
            temp->prev = parse;
            parse = parse->next;
        }
    }

    fclose(fp);
}


void exportdata()
{
    FILE *file = fopen("data.csv", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    node *temp = head;
    fprintf(file, "name, country-code, mobilenumber, birth month, birth day,emailid, favourite\n");

    while (temp != NULL)
    {
        fprintf(file, "%s, %s, %s, %d, %d, %s, %d\n", temp->name, temp->countrycode, temp->phoneno, temp->birthMonth, temp->birthDay, temp->mailid, temp->isFavorite);
        temp = temp->next;
    }

    fclose(file);
    printf("Contact data exported to data.csv successfully.\n");
}

int countContacts()
{
    int count = 0;
    node *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    printf("Total no of contacts are %d\n", count);
}

void displayContacts()
{
    printf("\n--- Contact List ---\n");

    node *temp = head;
    int contactCount = 0;

    while (temp != NULL)
    {
        printf("%d. %s\n", contactCount + 1, temp->name);
        temp = temp->next;
        contactCount++;
    }

    if (contactCount == 0)
    {
        printf("No contacts found.\n");
    }
}

void displayFavorites()
{
    printf("--- Favorite Contacts ---\n");

    node *temp = head;
    int favoriteCount = 0;

    while (temp != NULL)
    {
        if (temp->isFavorite)
        {
            printf("%d. %s\n", favoriteCount + 1, temp->name);
            favoriteCount++;
        }

        temp = temp->next;
    }

    if (favoriteCount == 0)
    {
        printf("No favorite contacts found.\n");
    }
}

void addToFavorites()
{
    printf("--- Add to Favorites ---\n");

    displayContacts();

    int contactIndex;
    printf("Enter the index of the contact you want to add to favorites: ");
    scanf("%d", &contactIndex);

    node *temp = head;
    int currentIndex = 1;
    int found = 0;

    while (temp != NULL)
    {
        if (currentIndex == contactIndex)
        {
            temp->isFavorite = 1;
            printf("%s has been added to favorites.\n", temp->name);
            found = 1;
            break;
        }

        temp = temp->next;
        currentIndex++;
    }

    if (!found)
    {
        printf("Invalid contact index.\n");
    }
}

void adddetail(char *newName)
{
    char mailid[MAX];
    char phone[20];
    char countrycode[10];
    int k = 0;

    k = 0;
    while (k == 0) {
        printf("Enter phone number: ");
        scanf("%s", phone);

        // Check if the input contains only digits
        int valid = 1;
        for (int i = 0; i < strlen(phone); i++) {
            if (!isdigit(phone[i])) {
                valid = 0;
                break;
            }
        }

        if (strlen(phone) != 10 || !valid) {
            printf("Enter a valid 10-digit mobile number.\n");
        } else {
            k = 1;
        }
    }
    k = 0;
    while (k == 0)
    {
        printf("Enter country code: ");
        scanf("%s", countrycode);
        int valid = 1;
        for (int i = 0; i < strlen(countrycode); i++) {
            if (!isdigit(countrycode[i])) {
                valid = 0;
                break;
            }
        }

        if (strlen(countrycode) >3 || !valid) {
            printf("Enter a valid country code.\n");
        } else {
            k = 1;
        }
    }

    int birthMonth, birthDay;
    k=0;
    while(k==0){
        printf("Enter birth month (1-12): ");
        scanf("%d", &birthMonth);
        if(birthMonth>12|| birthMonth<0){
            printf("Enter a valid month!!\n");
        }
        else{
            k=1;
        }

    }
    k=0;
    while(k==0){
    printf("Enter birth day (1-31): ");
    scanf("%d", &birthDay);
        if((birthMonth == 2 && birthDay > 29)||(birthDay>31|| birthDay<0)||((birthMonth == 4 || birthMonth == 6 || birthMonth == 9 || birthMonth == 11) && birthDay > 30)){
            printf("Enter a valid dayy!!\n");
        }
        else{
            k=1;
        }

    }

    printf("Enter mail id: ");
    scanf("%s", mailid);
    node *newNode = (node *)malloc(sizeof(node));
    node *next;
    strcpy(newNode->name, newName);
    strcpy(newNode->phoneno, phone);
    strcpy(newNode->countrycode, countrycode);
    strcpy(newNode->mailid, mailid);
    newNode->birthMonth = birthMonth;
    newNode->birthDay = birthDay;
    newNode->next = NULL;

    if (head == NULL || strcmp((head)->name, newName) > 0)
    {
        if (head != NULL)
            head->prev = newNode;
        newNode->next = head;
        newNode->prev = NULL;
        head = newNode;
    }
    else if (strcmp((head)->name, newName) == 0)
    {
        printf("Name already present");
    }
    else
    {
        node *current = head;
        while (current->next != NULL && strcmp(current->next->name, newName) < 0)
        {
            current = current->next;
        }
        if (current->next == NULL)
        {
            newNode->next = current->next;
            newNode->prev = current;
            current->next = newNode;
        }
        else if (strcmp(current->next->name, newName) == 0)
        {
            printf("Name already present \n");
        }
        else
        {
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next != NULL)
                current->next->prev = newNode;
            current->next = newNode;
        }
    }
}

void deletebyname(char name[])
{
    node *current = head;
    node *prev = NULL;
    node *next = NULL;

    if (current != NULL && strcmp(current->name, name) == 0)
    {
        head = current->next;
        if (head != NULL)
            head->prev = NULL;
        free(current);
        return;
        
    }
    while (current != NULL && strcmp(current->name, name) != 0)
    {
        current = current->next;
    }
    if (current != NULL)
    {
        prev = current->prev;
        next = current->next;

        if (prev != NULL)
            prev->next = next;
        if (next != NULL)
            next->prev = prev;

        free(current);
    }
    else
    {
        printf("\n Name not found \n");
    }
}

void emptyDirectory()
{
    node *current = head;
    node *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    head = NULL;
}

void display()
{
    printf("\n");
    node *temp;
    temp = head;
    while (temp != NULL)
    {
        printf("%s \t %s \t %s \n", temp->name, temp->countrycode, temp->phoneno);
        temp = temp->next;
    }
}

void printnodedata(node *temp)
{
    printf("\n Name: %s\n", temp->name);
    printf("Phone: %s", temp->countrycode);
    printf(" %s \n", temp->phoneno);
}

void searchbyname(char inname[])
{
    node *temp = head;
    if (head == NULL)
    {
        printf("Directory is Empty");
    }
    else
    {
        while (temp != NULL)
        {
            if (checkOccurrence(temp->name, inname) != 0)
            {
                printnodedata(temp);
            }
            temp = temp->next;
        }
    }
}


int checkOccurrence(const char* haystack, const char* needle) {
    int haystackLength = strlen(haystack);
    int needleLength = strlen(needle);

    if (needleLength > haystackLength) {
        return 0; 
    }

    for (int i = 0; i <= haystackLength - needleLength; i++) {
        int j;
        for (j = 0; j < needleLength; j++) {
            if (haystack[i + j] != needle[j]) {
                break; 
            }
        }

        if (j == needleLength) {
            return 1;
        }
    }

    return 0;
}

void searchByNumber(char innumber[])
{
    node *temp = head;
    int found = 0;

    if (head == NULL)
    {
        printf("Directory is Empty\n");
    }

    else
    {
        while (temp != NULL)
        {
            if (checkOccurrence(temp->phoneno, innumber) != 0)
            {
                printnodedata(temp);
                found = 1;
            }
            temp = temp->next;
        }
    }
    if (!found)
    {
        printf("No results found.\n"); // search not found case
    }
}

void modifyNumber(char inname[])
{
    node *temp = head;
    int found = 0;

    while (temp != NULL)
    {
        if (strcmp(temp->name, inname) == 0)
        {
            found = 1;

            printf("Enter new phone number: ");
            scanf("%s", temp->phoneno);

            printf("Phone number has been modified successfully.\n");
        }
        temp = temp->next;
    }
    if (!found)
    {
        printf("No results found.\n");
    }
}

void checkUpcomingBirthdays()
{
    time_t now = time(NULL);
    struct tm *currentTime = localtime(&now);
    int currentMonth = currentTime->tm_mon + 1;
    int currentDay = currentTime->tm_mday;

    node *temp = head;
    int found = 0;

    while (temp != NULL)
    {
        if (temp->birthMonth == currentMonth && temp->birthDay >= currentDay)
        {
            printf("Upcoming Birthday: %s\n", temp->name);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
    {
        printf("No upcoming birthdays.\n");
    }
}

void removefav(){
    node *temp = head;

    while(temp!=NULL){
        if(temp->isFavorite==1){
            temp->isFavorite=0;
        }
        temp=temp->next;
    }
}


void main()
{
    int k, opt;
    int length;
    k = 1;
    char name[MAX];
    while (k == 1)
    {
        printf("------PHONE DIRECTORY------\n");
        printf("    1. Add in details\n");
        printf("    2. Display\n");
        printf("    3. Delete by name\n");
        printf("    4. Search by name\n");
        printf("    5. Search by number\n");
        printf("    6. Update new number\n");
        printf("    7. Check upcoming birthdays in this month\n");
        printf("    8. Empty Directory\n");
        printf("    9. Contacts count\n");
        printf("    10. Add to Favorites\n");
        printf("    11. Display Favorites\n");
        printf("    12. Export Data to a CSV file\n");
        printf("    13.Remove all favourites\n");
        printf("    14. Import Data\n");
        printf("    15.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &opt);
        getchar();

        switch (opt)
        {
        case (1):
            printf("Enter name: ");
            gets(name);
            adddetail(name);
            break;
        case (2):
            display();
            break;
        case (3):
            printf("Enter name: ");
            fgets(name, sizeof(name), stdin);
            deletebyname(name);
            break;
        case (4):
            printf("Enter name or substring: ");
            scanf("%s",name);
            searchbyname(name);
            break;
        case (5):
            printf("Enter number or substring: ");
            scanf("%s",name);
            searchByNumber(name);
            break;
        case (6):
            printf("Enter name: ");
            scanf("%s",name);
            modifyNumber(name);
            break;
        case (7):
            checkUpcomingBirthdays();
            break;
        case (8):
            emptyDirectory();
            printf("Directory Emptied");
            break;
        case (9):
            countContacts();
            break;
        case (10):
            addToFavorites();
            break;
        case (11):
            displayFavorites();
            break;
        case (12):
            exportdata();
            break;
        case(13):
            removefav();
            break;
        case(14):
            importdata();
            break;
        default:
            k = 0;
            break;
        }
    }
}