
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY_Piece
};

// Define the different players
enum Player
{
    BLACK,
    WHITE,
    EMPTY_Player
};

// Define a struct to represent a chess piece
struct Piece
{
    char name[3];
    enum PieceType t_piece;
    enum Player player;
    bool moved;
    bool captured;
    bool enpass;
};

// Define a struct to represent a chess move
struct Move
{
    struct Location* location_src;
    struct Location* location_dest;
    struct Piece* captured_piece;
    bool castling;
    bool enpassmove;
};

// Define a struct to store a list of moves
struct Moves
{
    int size;
    struct Move moveList[300];
};

// define a struct to represent chessboard location
struct Location
{
    int rank;
    int file;
};

// Define the chess board as an 8x8 array of Piece structs
struct Board
{
    struct Piece* board[8][8];
    bool whiteHasCastled;
    bool blackHasCastled;
};

extern void initialize(struct Board* board);
extern void print_moves(struct Moves* moves, struct Board* position);
extern void endgame();
extern int inCheck(struct Board* board, enum Player playerColor);
extern void generatemoves(struct Board* position, struct Moves* p_list, enum Player playerturn);
extern void move_piece(struct Move* move, struct Board* board);
extern void draw(struct Board* board);
extern bool isLegal(struct Board* board, struct Move* move, struct Moves* moves, enum Player playerColor);
extern void recordMove(struct Move* move, enum Player curr_player, FILE* fp);
extern void get_user_move(struct Move* move);
extern bool isGameOver(struct Board* board, struct Moves* moves, enum Player playerColor);
#endif // CHESS_GAME_H