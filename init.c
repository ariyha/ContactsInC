#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000000

typedef struct node
{
    struct node *prev;
    struct node *next;
    char name[MAX];
    char countrycode[4];
    char phoneno[10];

} node;

node *head = NULL;

void adddetail(char newName[])
{
    char phone[20];
    char countrycode[10];
    int k = 0;

    while (k == 0)
    {
        printf("Enter phone no: ");
        scanf("%s", phone);
        if (strlen(phone) != 10)
        {
            printf("Enter a valid mobile number \n");
        }
        else
        {
            k = 1;
        }
    }
    k = 0;
    while (k == 0)
    {
        printf("Enter country code: ");
        scanf("%s", countrycode);
        if (strlen(countrycode) > 3)
        {
            printf("Enter valid code \n");
        }
        else
        {
            k = 1;
        }
    }
    node *newNode = (node *)malloc(sizeof(node));
    node *next;
    strcpy(newNode->name, newName);
    strcpy(newNode->phoneno, phone);
    strcpy(newNode->countrycode, countrycode);
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
            printf("%s", current->name);
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
            if (strstr(temp->name, inname) == NULL)
            {
                printnodedata(temp);
            }
            temp = temp->next;
        }
    }
}

void main()
{
    int k, opt;
    k = 1;
    char name[100];
    while (k == 1)
    {
        printf("Enter choice: ");
        scanf("%d", &opt);
        getchar();

        switch (opt)
        {
        case (1):
            printf("Enter name: ");
            fgets(name, sizeof(name), stdin);
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
            fgets(name, sizeof(name), stdin);
            searchbyname(name);
            break;
        default:
            k = 0;
            break;
        }
    }
}