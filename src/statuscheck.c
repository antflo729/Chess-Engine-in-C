
#include "structures.h"

int inCheck(struct Board* board, enum Player playerColor) {

    //initialize struct
   // struct Piece* piece = board->board[0][0];

    int kingRank, kingFile;
    int numChecks = 0;
    int knightChecks[8][2] = { {2,1}, {2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1} };
    int pluxDirec[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    int XDirec[4][2] = { {1,1}, {1,-1}, {-1,-1}, {-1,1} };
    int rankOffset, fileOffset;

    //initialize numChecks
    numChecks = 0;

    //finding king position
    for (int i = 0; i < 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board->board[i][j]->t_piece == KING) {
                if (playerColor == BLACK && board->board[i][j]->player == BLACK) {
                    kingRank = i;
                    kingFile = j;
                    //if king is black check for white pieces

                        //check for pawn checks
                    if ((board->board[kingRank - 1][kingFile + 1]->t_piece == PAWN) && (board->board[kingRank - 1][kingFile + 1]->player == WHITE)) {
                        numChecks++;
                    }
                    if ((board->board[kingRank - 1][kingFile - 1]->t_piece == PAWN) && (board->board[kingRank - 1][kingFile - 1]->player == WHITE)) {
                        numChecks++;
                    }

                    //checking for checks from knights
                    for (int i = 0; i < 8; i++) {
                        rankOffset = knightChecks[i][0];
                        fileOffset = knightChecks[i][1];

                        //check if coordinate is out of bounds
                        int file = kingFile + fileOffset;
                        int rank = kingRank + rankOffset;
                        if (rank >= 0 && rank < 8 && file >= 0 && file < 8) {
                            if ((board->board[rank][file]->t_piece == KNIGHT) && (board->board[rank][file]->player == WHITE))
                                numChecks++;
                        }
                    }

                    //checking for rooks and queens
                    //checking for checks above the king
                    //Loop through all directions
                    for (int d = 0; d < 4; d++) {
                        int rank = kingRank;
                        int file = kingFile;
                        while (1) {
                            //Move in the current direction
                            rank += pluxDirec[d][0];
                            file += pluxDirec[d][1];

                            //Check if we're off the board
                            if (rank < 0 || rank > 7 || file < 0 || file > 7) {
                                break;
                            }

                            //Check if there's a piece here
                            if (board->board[rank][file]->player != EMPTY_Piece) {
                                if (board->board[rank][file]->player == WHITE && (board->board[rank][file]->t_piece == ROOK || board->board[rank][file]->t_piece == QUEEN)) {
                                    numChecks++;
                                }
                                break;
                            }
                        }
                    }

                    //Checking for bishops and queens
                    //Loop through all diagonal directions
                    for (int d = 0; d < 4; d++) {
                        int rank = kingRank;
                        int file = kingFile;
                        while (1) {
                            //Move in the current direction
                            rank += XDirec[d][0];
                            file += XDirec[d][1];

                            //Check if we're off the board
                            if (rank < 0 || rank > 7 || file < 0 || file > 7) {
                                break;
                            }

                            //Check if there's a piece here
                            if (board->board[rank][file]->player != EMPTY_Piece) {
                                if (board->board[rank][file]->player == WHITE && (board->board[rank][file]->t_piece == BISHOP || board->board[rank][file]->t_piece == QUEEN)) {
                                    numChecks++;
                                }
                                break;
                            }
                        }
                    }

                }
                if (playerColor == WHITE && board->board[i][j]->player == WHITE) {
                    kingRank = i;
                    kingFile = j;
                    if (board->board[i][j]->player == WHITE) {

                        //check for pawn checks
                        if ((board->board[kingRank + 1][kingFile + 1]->t_piece == PAWN) && (board->board[kingRank + 1][kingFile + 1]->player == BLACK)) {
                            numChecks++;
                        }
                        if ((board->board[kingRank + 1][kingFile - 1]->t_piece == PAWN) && (board->board[kingRank + 1][kingFile - 1]->player == BLACK)) {
                            numChecks++;
                        }

                        //checking for checks from knights
                        for (int x = 0; x < 8; x++) {
                            rankOffset = knightChecks[x][0];
                            fileOffset = knightChecks[x][1];

                            //check if coordinate is out of bounds
                            int file = kingFile + fileOffset;
                            int rank = kingRank + rankOffset;
                            if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
                                if ((board->board[rank][file]->t_piece == KNIGHT) && (board->board[rank][file]->player == BLACK))
                                    numChecks++;
                            }
                        }

                        //Checking for rooks and queens
                        //Loop through all vertical and horizontal directions
                        for (int d = 0; d < 4; d++) {
                            int rank = kingRank;
                            int file = kingFile;
                            while (1) {
                                //Move in the current direction
                                rank += pluxDirec[d][0];
                                file += pluxDirec[d][1];

                                //Check if we're off the board
                                if (rank < 0 || rank > 7 || file < 0 || file > 7) {
                                    break;
                                }

                                //Check if there's a piece here
                                if (board->board[rank][file]->player != EMPTY_Piece) {
                                    if (board->board[rank][file]->player == BLACK && (board->board[rank][file]->t_piece == ROOK || board->board[rank][file]->t_piece == QUEEN)) {
                                        numChecks++;
                                    }
                                    break;
                                }
                            }
                        }

                        //Checking for bishops and queens
                        //Loop through all diagonal directions
                        for (int d = 0; d < 4; d++) {
                            int rank = kingRank;
                            int file = kingFile;
                            while (1) {
                                //Move in the current direction
                                rank += XDirec[d][0];
                                file += XDirec[d][1];

                                //Check if we're off the board
                                if (rank < 0 || rank > 7 || file < 0 || file > 7) {
                                    break;
                                }

                                //Check if there's a piece here
                                if (board->board[rank][file]->player != EMPTY_Piece) {
                                    if (board->board[rank][file]->player == BLACK && (board->board[rank][file]->t_piece == BISHOP || board->board[rank][file]->t_piece == QUEEN)) {
                                        numChecks++;
                                    }
                                    break;
                                }
                            }
                        }


                    }





                }
            }
        }
    }
    return numChecks;
}

    
bool isGameOver(struct Board* board, struct Moves* moves, enum Player playerColor) {

    int numLegalMoves = 0;


    for (int i = 0; i < moves->size; i++)
    {
        if (isLegal(board, &(moves->moveList[i]), moves, playerColor))
        {
            numLegalMoves++;
        }
    }

    if (numLegalMoves == 0)
        return true;

    return false;


}


/*
    FINDING CHECKMATE
        check all moves
        find if king is in check
        find all pieces checking the king
        if 2 pieces are checking the king and king has no legal moves
            then checkmate
        if only 1 piece checking the king
            1. check if king has any legal moves
                if no
            2. check if attacking piece can be captured
                if no
            3. check if attack can be blocked by another piece
                if knight then checkmate
                for QUEEN ROOK BISHOP
                    check its coordinate in relation to king
                    loop through each square in between piece and the king
                        find any piece that has destination rank and file on those pieces
                        if there are
                        then not checkmate

            if not then checkmate


    finding if king is in check
        1. find king position
        2. find most recent move's coordinate, and piece
        3. depending on the piece we check all possible check positions
        4. if king position is one of those positions
            then check
        5. Also check king has any pieces attacking vertically, horizontally, or diagonally.

    brute force
    CHECKING FOR PAWN CHECK
        1. Check two squares diagonally in front of the king
            if enemy pawn is there then CHECK

    CHECKING FOR KNIGHT CHECK
        2. Check L squares away from the king
            if enemy kinght is there then CHECK

    CHECKING FOR ROOK/QUEEN CHECK
        3. Check in front of the king
            3.5 if there is either a rook or queen there
                    then check
                if it is a piece other than a rook or queen
                    then number 3 done
                else
                    move foreward one square and repeat 3.5
                end once we reach the end of the board
        4. Check behind the king
            repeat steps from 3.5
        5. Check to the left of the king
            repeat steps from 3.5
        6. Check to the right of the king
            repeat steps from 3.5

    CHECKING FOR BISHOP/QUEEN CHECK
        7. Check up one square and right one square
            7.5 if there is either a bishop or queen there
                    then check
                if it is a piece other than a bishop or a queen
                    then number 7 check done
                else
                    move foreward one square and right one square and repeat 7.5
                end once til square we are checking is out of bounds.
        8. Check up one square and left one square
            repeat steps from 7.5
        8. Check up down square and right one square
            repeat steps from 7.5
        8. Check up down square and left one square
            repeat steps from 7.5

    We increment number of checks every time one is found
        int numOfChecks


    */