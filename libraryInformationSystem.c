#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define BOOLEAN int
#define TRUE 1
#define FALSE 0

typedef struct
{
    int book_no, edition, no_of_books, no_of_rent, balance;
    char title[25], author[25];
} Book;

void menu();

// 1
void bookDataEntry(Book[], int *);
// 2
void computeBalance(Book[], int);
// 3
void displayBookInfoDetail(Book[], int);
// 4
void displayBooksByNoOfBookInDesOrder(Book[], int);
void sort1(Book[], int);
// 5
void displayBooksByBalanceInDesOrder(Book[], int);
void sort2(Book[], int);
// 6
void BookEnquiry(Book[], int);
void searchByBookNo(Book[], int);
void searchByTitle(Book[], int);
void searchByAuthor(Book[], int);
// 7
void saveBookData(Book[], int);

// 8
void terminate();
// an explicit display function for reusability sake
void display(Book[], int);

// For printing main menu
void menu()
{
    printf("\n");
    printf("Library Infomation System\n");
    printf("\n");
    printf("************************\n");
    printf("\n");
    printf("1. Book Data Entry\n");
    printf("2. Compute Balance of Book\n");
    printf("3. Display Book Information in Detail\n");
    printf("4. Display Book List by no_of_book (Descending order)\n");
    printf("5. Display Book List by Balance(Descending order)\n");
    printf("6. Book Enquiry\n");
    printf("7. Save Book Data into File named library.dat\n");
    printf("8. Exit\n");
}

void main()
{
    int choice;
    char ans;
    Book books[100];
    int p = 0;
    do
    {
        system("clear");
        menu();

        do
        {
            printf("Select option number: (1-8)\t");
            scanf("%d", &choice);
        } while (!(choice >= 1 && choice <= 9));

        switch (choice)
        {
        case 1:
            bookDataEntry(books, &p);
            break;
        case 2:
            computeBalance(books, p);
            break;
        case 3:
            displayBookInfoDetail(books, p);
            break;
        case 4:
            displayBooksByNoOfBookInDesOrder(books, p);
            break;
        case 5:
            displayBooksByBalanceInDesOrder(books, p);
            break;
        case 6:
            BookEnquiry(books, p);
            break;
        case 7:
            saveBookData(books, p);
            break;
        case 8:
            terminate();
            break;
        default:
            printf("Invalid!");
            break;
        }

        getchar();
        printf("press Enter to go back to main menu\n");
        ans = getchar();

    } while (ans == '\n');
}

void bookDataEntry(Book books[], int *p)
{
    char ans;

    do
    {
        printf("Book No\t:");
        scanf("%d", &books[*p].book_no);
        getchar();

        printf("Title\t:");
        scanf("%[^\n]s", books[*p].title);
        getchar();

        printf("Author\t:");
        scanf("%[^\n]s", books[*p].author);
        getchar();

        printf("Edition\t:");
        scanf("%d", &books[*p].edition);

        printf("No of books\t:");
        scanf("%d", &books[*p].no_of_books);

        printf("No of rent\t:");
        scanf("%d", &books[*p].no_of_rent);
        getchar();

        *p += 1;
        printf("Anymore data?(Y/N)");
        ans = getchar();
    } while (ans == 'y');
}

void computeBalance(Book books[], int length)
{
    for (int i = 0; i < length; i++)
    {
        books[i].balance = books[i].no_of_books - books[i].no_of_rent;
    }
    printf("Balance is calculated.\n");
}

void displayBookInfoDetail(Book books[], int length)
{
    printf("\nDisplaying books\n");
    printf("\nBook Information in Detail\n");
    printf("******************************\n\n");
    display(books, length);
}

void displayBooksByNoOfBookInDesOrder(Book books[], int length)
{
    sort1(books, length);
    printf("\nDisplaying Books by No. of books in descending order\n");
    printf("******************************\n\n");
    display(books, length);
}

void displayBooksByBalanceInDesOrder(Book books[], int length)
{
    sort2(books, length);
    printf("\nDisplaying Books by Balance in descending order\n");
    printf("******************************\n\n");
    display(books, length);
}

void BookEnquiry(Book books[], int length)
{
    int choice;
    system("clear");
    printf("\nBook Enquiry\n");
    printf("*************\n");
    printf("1. Search by Book No.\n");
    printf("2. Search by Title\n");
    printf("3. Search by Author\n");

    do
    {
        printf("Select option number: (1 or 2 or 3): ");
        scanf("%d", &choice);
    } while (!(choice >= 1 && choice <= 3));
    getchar();

    switch (choice)
    {
    case 1:
        searchByBookNo(books, length);
        break;
    case 2:
        searchByTitle(books, length);
        break;
    case 3:
        searchByAuthor(books, length);
        break;
    default:
        printf("Invalid!");
        break;
    }
}

void saveBookData(Book books[], int length)
{
    FILE *fp = fopen("./library.dat", "wb");
    for (int i = 0; i < length; i++)
    {
        fwrite(&books[i], sizeof(books[i]), 1, fp);
    }
    printf("Book information is saving into file.\n");
    fclose(fp);
}

void sort1(Book books[], int length)
{
    Book temp;
    BOOLEAN isSwap = TRUE;

    while (isSwap)
    {
        isSwap = FALSE;

        for (int i = 0; i < length - 1; i++)
        {
            if (books[i].no_of_books < books[i + 1].no_of_books)
            {
                temp = books[i];
                books[i] = books[i + 1];
                books[i + 1] = temp;
                isSwap = TRUE;
            }
        }
    }
}

void sort2(Book books[], int length)
{
    Book temp;
    BOOLEAN isSwap = TRUE;

    while (isSwap)
    {
        isSwap = FALSE;

        for (int i = 0; i < length - 1; i++)
        {
            if (books[i].balance < books[i + 1].balance)
            {
                temp = books[i];
                books[i] = books[i + 1];
                books[i + 1] = temp;
                isSwap = TRUE;
            }
        }
    }
}

void searchByBookNo(Book books[], int length)
{
    int bookNo;
    printf("Enter Book No:\t");
    scanf("%d", &bookNo);

    for (int i = 0; i < length; i++)
    {
        if (books[i].book_no == bookNo)
        {
            printf("Book No\t:\t%d\n", books[i].book_no);
            printf("Title\t:\t%s\n", books[i].title);
            printf("Author\t:\t%s\n", books[i].author);
            printf("Edition\t:\t%d\n", books[i].edition);
            printf("No. of Books\t:\t%d\n", books[i].no_of_books);
            printf("No. of Rent\t:\t%d\n", books[i].no_of_rent);
            printf("Balance\t:\t%d\n", books[i].balance);
            return;
        }
    }
    printf("Book not found!\n");
}

void searchByTitle(Book books[], int length)
{
    char title[25];
    printf("Enter Title:\t");
    gets(title);
    for (int i = 0; i < length; i++)
    {
        if (strcmp(title, books[i].title) == 0)
        {
            printf("Book No\t:\t%d\n", books[i].book_no);
            printf("Title\t:\t%s\n", books[i].title);
            printf("Author\t:\t%s\n", books[i].author);
            printf("Edition\t:\t%d\n", books[i].edition);
            printf("No. of Books\t:\t%d\n", books[i].no_of_books);
            printf("No. of Rent\t:\t%d\n", books[i].no_of_rent);
            printf("Balance\t:\t%d\n", books[i].balance);
            return;
        }
    }
    printf("Book not found!\n");
}

void searchByAuthor(Book books[], int length)
{
    char author[25];
    printf("Enter Author:\t");
    gets(author);
    for (int i = 0; i < length; i++)
    {
        if (strcmp(author, books[i].author) == 0)
        {
            printf("Book No\t:\t%d\n", books[i].book_no);
            printf("Title\t:\t%s\n", books[i].title);
            printf("Author\t:\t%s\n", books[i].author);
            printf("Edition\t:\t%d\n", books[i].edition);
            printf("No. of Books\t:\t%d\n", books[i].no_of_books);
            printf("No. of Rent\t:\t%d\n", books[i].no_of_rent);
            printf("Balance\t:\t%d\n", books[i].balance);
            return;
        }
    }
    printf("Book not found!\n");
}

void display(Book books[], int length)
{
    printf("Book_No\tTitle\t\t\tAuthor\t\t\tEdition\t\tNo. of Books\tNo. of Rent\tBalance\n");

    for (int k = 0; k < 7; k++)
    {
        if (k == 0 || k == 6)
        {
            printf("*****\t");
        }
        else if (k == 1 || k == 2)
        {
            printf("*****\t\t\t");
        }
        else
        {

            printf("*****\t\t");
        }
    }

    printf("\n");
    for (int i = 0; i < length; i++)
    {
        printf("%-8d", books[i].book_no);
        printf("%-24s", books[i].title);
        printf("%-24s", books[i].author);
        printf("%-16d", books[i].edition);
        printf("%-16d", books[i].no_of_books);
        printf("%-16d", books[i].no_of_rent);
        if (books[i].balance)
        {
            printf("%-16d\n", books[i].balance);
        }
        else
        {
            printf("%-16c\n", '-');
        }
    }
}

void terminate()
{
    printf("Terminating the program...");
    Sleep(5);
    exit(1);
}