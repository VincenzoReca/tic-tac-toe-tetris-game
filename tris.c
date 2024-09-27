#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 3

void start_game();                                          // function to start the game
void stampa_tabella(char matrice[SIZE][SIZE]);              // function to print the game board
void get_input(char matrice[SIZE][SIZE]);                   // function to handle player inputs
int is_character(int x, int y, int flagInput);              // check if input is valid
int is_occupato(char matrice[SIZE][SIZE], int x, int y);    // check if cell is occupied
int checkTris(char matrice[SIZE][SIZE]);                    // check if there's a winning condition

int main()
{
    start_game();                                           // start the game
    return 0;
}

void start_game()
{
    int flagContinue = 0;
    do
    {
        char tabella[SIZE][SIZE];
        for (size_t i = 0; i < SIZE; i++)                   // initialize the board
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                tabella[i][j] = ' ';
            }
        }
        stampa_tabella(tabella);                            // print the board
        get_input(tabella);                                 // get player input
        system("cls");
        printf("1 for new game, 0 to exit: ");
        scanf("%d", &flagContinue);                         // ask to continue
        while (flagContinue != 1 && flagContinue != 0)
        {
            printf("Enter a valid value: ");
            scanf("%d", &flagContinue);
        }
    } while (flagContinue);                                 // loop until player chooses to exit
    printf("Game exited\n");
}

void stampa_tabella(char matrice[SIZE][SIZE])               // prints the game board
{
    system("cls || clear");
    printf("\t0     1\t    2\t\n");
    printf("\t   %c     %c  \n", 186, 186);
    printf("0\t%c  %c  %c  %c  %c\n", matrice[0][0], 186, matrice[1][0], 186, matrice[2][0]);
    printf("       %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205);
    printf("1\t%c  %c  %c  %c  %c\n", matrice[0][1], 186, matrice[1][1], 186, matrice[2][1]);
    printf("       %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205);
    printf("2\t%c  %c  %c  %c  %c\n", matrice[0][2], 186, matrice[1][2], 186, matrice[2][2]);
    printf("\t   %c     %c  \n", 186, 186);
}

// return 1 if the character input is valid
int is_character(int x, int y, int flagInput)
{
    if ((x >= 0 && x <= 2) && (y >= 0 && y <= 2) && flagInput)
    {
        return 1;
    }
    return 0;
}

// return 1 if the cell is occupied
int is_occupato(char matrice[SIZE][SIZE], int x, int y)
{
    if (matrice[x][y] != ' ')
    {
        return 1;
    }

    return 0;
}

void get_input(char matrice[SIZE][SIZE])                    // handle player input and turns
{
    int x, y;
    static int turno = 0;
    int flagInput = 0, flag = 0;
    while (!checkTris(matrice) && turno < 9)                // check if game is ongoing
    {
        if (turno % 2 == 0)
        {
            stampa_tabella(matrice);
            printf("\nPlayer X's turn\n");
            printf("Insert row and column: ");
            flagInput = scanf("%d %d", &x, &y);
            while (!is_character(x, y, flagInput) || is_occupato(matrice, x, y))
            {
                printf("Invalid or occupied coordinates, retry: ");
                fflush(stdin);
                x = 0, y = 0;
                flagInput = scanf("%d %d", &x, &y);
            }

            matrice[x][y] = 'X';                           // mark X on the board
            stampa_tabella(matrice);
            if (checkTris(matrice) == 1)
            {
                printf("Player X wins!\n");
                system("pause");
                system("cls");
            }
            else
            {
                turno++;                                    // change turn
            }
        }
        else
        {
            system("cls");
            stampa_tabella(matrice);
            printf("\nPlayer O's turn\n");
            printf("Insert row and column: ");
            flagInput = scanf("%d %d", &x, &y);
            while (!is_character(x, y, flagInput) || is_occupato(matrice, x, y))
            {
                printf("Invalid or occupied coordinates, retry: ");
                fflush(stdin);
                x = 0, y = 0;
                flagInput = scanf("%d %d", &x, &y);
            }

            matrice[x][y] = 'O';                           // mark O on the board
            stampa_tabella(matrice);
            if (checkTris(matrice))
            {
                printf("Player O wins!\n");
                system("pause");
                system("cls");
            }
            else
            {
                turno++;                                    // change turn
            }
        }
    }
    if (turno == 9 && !checkTris(matrice))                 // if no one wins, it's a draw
    {
        printf("It's a draw!\n");
        turno = 0;
        system("pause");
    }
}

int checkTris(char matrice[SIZE][SIZE])                    // check for winning condition
{
    // check diagonals
    if ((matrice[0][0] == matrice[1][1]) && (matrice[1][1] == matrice[2][2]) && matrice[1][1] != ' ')
    {
        return 1;
    }
    if ((matrice[2][2] == matrice[1][1]) && (matrice[1][1] == matrice[0][2]) && matrice[1][1] != ' ')
    {
        return 1;
    }

    // check rows
    for (int x = 0; x < 3; x++)
    {
        int y = 0;
        if ((matrice[x][y] == matrice[x][y + 1]) && matrice[x][y] != ' ')
        {
            y++;
            if ((matrice[x][y] == matrice[x][y + 1]))
            {
                return 1;
            }
        }
    }
    // check columns
    for (int y = 0; y < 3; y++)
    {
        int x = 0;
        if ((matrice[x][y] == matrice[x + 1][y]) && matrice[x][y] != ' ')
        {
            x++;
            if ((matrice[x][y] == matrice[x + 1][y]))
            {
                return 1;
            }
        }
    }

    return 0;
}
