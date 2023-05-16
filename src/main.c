#include "structures.h"
#include <time.h>
#include <signal.h>
#define MAXMOVES 300
FILE* log_file;

void print_move(struct Move* move)
{
    printf("%c ", move->location_src->file + 'a');
    printf("%c ", move->location_src->rank + '1');
    printf("%c ", move->location_dest->file + 'a');
    printf("%c ", move->location_dest->rank + '1');
    printf("\n");
}
void endgame()
{
    printf("end game\n");
}

void sigint_handler(int sig)
{
    fclose(log_file);
    printf("File saved and closed.\n");
    exit(0);
}
// above for the test
int main()
{
    srand(time(NULL));
    int random_int;
    struct Board* my_board = (struct Board*)malloc(sizeof(struct Board));
    if (my_board == NULL)
    {
        printf("Error: failed to create my_board.\n");
        exit(1);
    }
    initialize(my_board);

    printf("MAIN MENU\n------------------------------------------------\n");
    printf("1)play against computer\n");
    printf("2)computer vs computer\n");
    printf("choose mode:(1\\2)\n");
    int mode;
    scanf("%d", &mode);
    getchar();
    // Initialize the game
    bool is_game_over = false;
    enum Player human_player, computer_player;
    printf("Choose your side (B for Black, W for White): ");
    char side;
    scanf("%c", &side);
    getchar();
    if (side == 'B')
    {
        human_player = BLACK;
        computer_player = WHITE;
    }
    else
    {
        human_player = WHITE;
        computer_player = BLACK;
    }
    enum Player curr_player = WHITE;

    // Allocate memory for struct Moves
    struct Moves* p_list = (struct Moves*)malloc(sizeof(struct Moves));
    if (p_list == NULL)
    {
        printf("Error: failed to create my_board.\n");
        exit(1);
    }
    p_list->size = 0; // Set initial size of moveList to 0
    for (int i = 0; i < MAXMOVES; i++)
    {
        p_list->moveList[i].location_src = (struct Location*)malloc(sizeof(struct Location));
        p_list->moveList[i].location_dest = (struct Location*)malloc(sizeof(struct Location));
        p_list->moveList[i].captured_piece = (struct Piece*)malloc(sizeof(struct Piece));
        if (p_list->moveList[i].location_src == NULL || p_list->moveList[i].location_dest == NULL || p_list->moveList[i].captured_piece == NULL)
        {
            printf("Error: failed to create move %d in p_list.\n", i);
            exit(1);
        }
    }
    for (int i = 0; i < MAXMOVES; i++)
    {
        p_list->moveList[i].location_src->rank = 0; // initialize location_src
        p_list->moveList[i].location_dest->rank = 0; // initialize location_dest
        p_list->moveList[i].location_src->file = 0; // initialize location_src
        p_list->moveList[i].location_dest->file = 0; // initialize location_dest
    }

    log_file = fopen("chess_game.txt", "w");
    if (log_file == NULL)
    {
        printf("Error: failed to create log file.\n");
        exit(1);
    }
    signal(SIGINT, sigint_handler);
    //reload(log_file, my_board);
    // test
    int count = 0;
    // Game loop
    while (!is_game_over)
    {
        printf("count = %d \n", count);
        draw(my_board);
        const char* turn = (curr_player == WHITE) ? "WHITE" : "BLACK";
        printf("It's %s player's turn.\n", turn);
        generatemoves(my_board, p_list, curr_player);
        printf("moves generated\n");

        // print_moves(p_list, my_board);
        if (p_list->size == 0)
        {
            const char* str = (curr_player == human_player) ? "You" : "Computer";
            printf("%s have no legal moves left. Game over.\n", str);
            endgame();
            is_game_over = true;
            break;
        }
        // Human player's turn
        if (human_player == curr_player)
        {
            struct Move *move = p_list->moveList;
           

            if (move == NULL || move->location_dest == NULL || move->location_src == NULL)
            {
                printf("Error: failed to create move .\n");
                exit(1);
            }
            bool is_move_legal = false;
            while (!is_move_legal)
            {
                if (mode == 2)
                {
                    random_int = rand() % (p_list->size);
                    move = &(p_list->moveList[random_int]);
                }
                else
                {
                    get_user_move(move);
                   
                }
                is_move_legal = isLegal(my_board,move, p_list, curr_player);
                //is_move_legal = isLegal(move, p_list);
                if (!is_move_legal)
                {
                    printf("Illegal move. Try again.\n");
                }
            }
            print_move(move);
            move_piece(move, my_board);
            recordMove(move, human_player, log_file);
            curr_player = computer_player;
        }
        // Computer's turn
        else
        {
            struct Move* computer_move;
            // generatemoves(my_board, p_list, computer_player);
            random_int = rand() % (p_list->size);
            computer_move = &(p_list->moveList[random_int]);
            print_move(computer_move);
            move_piece(computer_move, my_board);
            recordMove(computer_move, computer_player, log_file);
            curr_player = human_player;
        }
        count++;
        // Check if game is over
        if (isGameOver(my_board, p_list, curr_player) || count == 500)
        {
            is_game_over = true;
            endgame();
            break;
        }
    }
    free(my_board);
    free(p_list);

    fclose(log_file);
    return 0;
}
