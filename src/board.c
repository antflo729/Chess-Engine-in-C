#include "structures.h"
#include <stdio.h>

void draw(struct Board* board) {
    printf(" +----+----+----+----+----+----+----+----+\n");
    for (int i = 7; i >= 0; i--) {
        printf("%d|", i + 1);
        for (int j = 0; j < 8; j++) {
            struct Piece* p = board->board[i][j];
            if (p == NULL) {
                printf("    |");
            }
            else {
                printf(" %s |", p->name);
            }
        }
        printf("\n");
        printf(" +----+----+----+----+----+----+----+----+\n");
    }
    printf("    A    B    C    D    E    F    G    H  \n");
}

// void move_piece(struct Move *move, struct Board *board) {
//   struct Piece *src_piece = board->board[move->location_src->rank][move->location_src->file];
//   struct Piece *dst_piece = board->board[move->location_dest->rank][move->location_dest->file];
//   enum PieceType t1 = EMPTY_Piece;
//   enum Player t2 = EMPTY_Player;
//   if((dst_piece->t_piece != t1) && (dst_piece->player != t2)){
//       strncpy(dst_piece->name, "  ", 3);
//       dst_piece->t_piece = EMPTY_Piece; 
//       dst_piece->player = EMPTY_Player;
//       dst_piece->captured = true; 

//       board->board[move->location_src->rank][move->location_src->file] = dst_piece;
//       board->board[move->location_dest->rank][move->location_dest->file] = src_piece;
//     }
//     else{
//       board->board[move->location_src->rank][move->location_src->file] = dst_piece;
//       board->board[move->location_dest->rank][move->location_dest->file] = src_piece;

//     }
//   if (!src_piece->moved){
//     src_piece->moved=true;
//   }
// }
void move_piece(struct Move* move, struct Board* board) {

    struct Piece* src_piece = board->board[move->location_src->rank][move->location_src->file];
    struct Piece* dst_piece = board->board[move->location_dest->rank][move->location_dest->file];
    enum PieceType t1 = EMPTY_Piece;
    enum Player t2 = EMPTY_Player;
    enum PieceType t3 = PAWN;
    enum Player t4 = WHITE;
    enum Player t5 = BLACK;

    if ((dst_piece->t_piece != t1) && (dst_piece->player != t2)) {
        strncpy(dst_piece->name, "  ", 3);
        dst_piece->t_piece = EMPTY_Piece;
        dst_piece->player = EMPTY_Player;
        dst_piece->moved = NULL;
        dst_piece->captured = true;
        dst_piece->enpass = NULL;

        board->board[move->location_src->rank][move->location_src->file] = dst_piece;
        board->board[move->location_dest->rank][move->location_dest->file] = src_piece;
    }
    else if ((src_piece->t_piece == t3) && ((move->location_dest->rank == 7) || (move->location_dest->rank == 0))) {
        if (src_piece->player == t4) {
            strncpy(dst_piece->name, "wQ", 3);
            dst_piece->t_piece = QUEEN;
            dst_piece->player = WHITE;
            dst_piece->moved = true;
            dst_piece->captured = false;
            dst_piece->enpass = false;
        }
        else if (src_piece->player == t5) {
            strncpy(dst_piece->name, "bQ", 3);
            dst_piece->t_piece = QUEEN;
            dst_piece->player = BLACK;
            dst_piece->moved = true;
            dst_piece->captured = false;
            dst_piece->enpass = false;
        }
        board->board[move->location_src->rank][move->location_src->file] = dst_piece;
        board->board[move->location_dest->rank][move->location_dest->file] = src_piece;
    }
    else if ((src_piece->t_piece == t3) && (move->location_dest->file != move->location_src->file) && (dst_piece->t_piece == t1)) {
        int delta_rank = move->location_dest->rank - move->location_src->rank;
        int delta_file = move->location_dest->file - move->location_src->file;
        int capture_rank = move->location_src->rank + delta_rank;
        int capture_file = move->location_src->file + delta_file;
        struct Piece* captured_piece = board->board[capture_rank][capture_file];

        captured_piece->captured = true;
        captured_piece->t_piece = EMPTY_Piece;
        captured_piece->player = EMPTY_Player;
        captured_piece->moved = NULL;
        captured_piece->enpass = NULL;

        board->board[capture_rank][capture_file] = captured_piece;
        board->board[move->location_src->rank][move->location_src->file] = dst_piece;
        board->board[move->location_dest->rank][move->location_dest->file] = src_piece;
    }
    else {
        board->board[move->location_src->rank][move->location_src->file] = dst_piece;
        board->board[move->location_dest->rank][move->location_dest->file] = src_piece;
    }

    if (!src_piece->moved) {
        src_piece->moved = true;
    }
}

