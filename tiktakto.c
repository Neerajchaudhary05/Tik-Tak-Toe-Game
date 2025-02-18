#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define board_size 3
#define X 'X'
#define O 'O'

typedef struct
{
    int PlayerWon;
    int computerWon;
    int drow;
} Score;

int difficulty;
Score score = {.PlayerWon = 0, .computerWon = 0, .drow = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[board_size][board_size]);
int check_win(char board[board_size][board_size], char player);
int Check_draw(char board[board_size][board_size]);
void play_game();
void player_move(char board[board_size][board_size]);
void computer_move(char board[board_size][board_size]);
int is_valid_move(char board[board_size][board_size], int row, int col);

int main()
{
    srand(time(NULL));
    int choice;
    input_difficulty();
    do
    {
        play_game();
        printf("\nPlay again? (1 for yes, 0 for No):");
        scanf("%d", &choice);
    } while (choice == 1);
    printf("Bye Bye, Thanks for play!");
    return 0;
}

int is_valid_move(char board[board_size][board_size], int row, int col)
{
    return !(row < 0 || col < 0 ||
             row > 2 || col > 2 ||
             board[row][col] != ' ');
}

void computer_move(char board[board_size][board_size])
{
    // 1.Play for Immediate win
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (check_win(board, O))
                {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    // 2.Play for Immediate Block
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = X;
                if (check_win(board, X))
                {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // God mode
    if (difficulty == 2)
    {
        // 3.play center ifavailable
        if (board[1][1] == ' ')
        {
            board[1][1] = O;
            return;
        }

        // 4.play for corner
        int corner[4][2] = {
            {0, 0},
            {0, 2},
            {2, 0},
            {2, 2}};

        for (int i = 0; i < 4; i++)
        {
            if (board[corner[i][0]][corner[i][1]] == ' ')
            {
                board[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }

    // 5.Play first Available move
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                return;
            }
        }
    }
}

void player_move(char board[board_size][board_size])
{
    int count = 0, x, y;
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == ' ')
            {
                x = i;
                y = j;
                count++;
            }
        }
    }
    if (count == 1)
    {
        board[x][y]=X;
        return;
    }

    int row, col;
    do
    {
        printf("\nPlayer X's Turn.");
        printf("\nEnter row and column (1-3) for X: ");
        scanf("%d", &row);
        scanf("%d", &col);
        // Converting to zero Base
        row--;
        col--;
    } while (!is_valid_move(board, row, col));
    board[row][col] = X;
}

void play_game()
{
    char board[board_size][board_size] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    char current_player = rand() % 2 == 0 ? X : O;
    print_board(board);
    while (1)
    {
        if (current_player == X)
        {
            player_move(board);
            print_board(board);
            if (check_win(board, X))
            {
                score.PlayerWon++;
                print_board(board);
                printf("\nCongratulation You have won.!!!\n");
                break;
            }
            current_player = O;
        }
        else
        {
            computer_move(board);
            print_board(board);
            if (check_win(board, O))
            {
                score.computerWon++;
                print_board(board);
                printf("\nComputer wins.!!\n");
                break;
            }
            current_player = X;
        }
        if (Check_draw(board))
        {
            score.drow++;
            print_board(board);
            printf("\nIt's a drow!");
            break;
        }
    }
}

int check_win(char board[board_size][board_size], char player)
{
    for (int i = 0; i < board_size; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[2][0] == player && board[1][1] == player && board[0][2] == player))
        return 1;

    return 0;
}
int Check_draw(char board[board_size][board_size])
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

void print_board(char board[board_size][board_size])
{
    clear_screen();
    printf("Score - Player X: %d ,Computer : %d , Drows : %d", score.PlayerWon,
           score.computerWon, score.drow);
    printf("\nTik-Tak-Toe\n");
    for (int i = 0; i < board_size; i++)
    {
        printf("\n");
        for (int j = 0; j < board_size; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < board_size - 1)
                printf("|");
        }
        if (i < board_size - 1)
            printf("\n---+---+---");
    }
    printf("\n");
}

void clear_screen()
{
#ifdef _Win32
    system("cls");
#else
    system("clear");
#endif
}

void input_difficulty()
{

    while (1)
    {
        printf("\nSelect difficulty Level:");
        printf("\n1 - Human(Standard)");
        printf("\n2 - God (Impossible to win)");
        printf("\nEnter your choice :");
        scanf("%d", &difficulty);
        if (difficulty != 1 && difficulty != 2)
        {
            printf("\nIncorrect choice enter (1 or 2) :");
        }
        else
        {
            break;
        }
    }
}