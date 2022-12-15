#include "Knight.h"
#include "Game.h"
#include "King.h"
#include <iostream>

Knight::Knight(int pos,bool black) : logicPiece(pos, black) {

    _name = 'c';

    int knight[8][8] = {
        {-50,-40,-30,-30,-30,-30,-40,-50},
        {-40,-20,  0,  0,  0,  0,-20,-40},
        {-30,  0, 10, 15, 15, 10,  0,-30},
        {-30,  5, 15, 20, 20, 15,  5,-30},
        {-30,  0, 15, 20, 20, 15,  0,-30},
        {-30,  5, 10, 15, 15, 10,  5,-30},
        {-40,-20,  0,  5,  5,  0,-20,-40},
        {-50,-40,-30,-30,-30,-30,-40,-50}
    };

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            _bonus[i][j] = knight[i][j];
}

std::list<int> Knight::possibleMove() {

    std::list<int> possible_move;
    int move = -1;
    int row = _pos / 8;
    int col = _pos % 8;

    for (int i = -1; i <= 1; i = i + 2)
        for (int j = -1; j <= 1; j = j + 2)
        {
            move = _pos + i * 16 + j;
            if (move / 8 >= 0 && move / 8 <= 7 && move % 8 >= 0 && move % 8 <= 7)
                if (move / 8 == row + i * 2 && move % 8 == col + j)
                {
                    if (Game::board()[move / 8][move % 8] != nullptr && _black == Game::board()[move / 8][move % 8]->check_color())
                        ;
                    else
                        if(!verify_check(move))
                            possible_move.push_back(move);
                }
            move = _pos + i*8 +2*j;
            if (move / 8 == row + i  && move % 8 == col + j*2)
                if (move / 8 >= 0 && move / 8 <= 7 && move % 8 >= 0 && move % 8 <= 7)
                {
                    if (Game::board()[move / 8][move % 8] != nullptr && _black == Game::board()[move / 8][move % 8]->check_color())
                        ;
                    else
                        if (!verify_check(move))
                            possible_move.push_back(move);

                }
        }

    return possible_move;
}

std::list<int> Knight::pseudo_moves()
{

    std::list<int> possible_move;
    int move = -1;
    int row = _pos / 8;
    int col = _pos % 8;

    for (int i = -1; i <= 1; i = i + 2)
        for (int j = -1; j <= 1; j = j + 2)
        {
            move = _pos + i * 16 + j;
            if (move / 8 >= 0 && move / 8 <= 7 && move % 8 >= 0 && move % 8 <= 7)
                if (move / 8 == row + i * 2 && move % 8 == col + j)
                {
                    if (Game::board()[move / 8][move % 8] != nullptr && _black == Game::board()[move / 8][move % 8]->check_color())
                        ;
                    else possible_move.push_back(move);
                }
            move = _pos + i * 8 + 2 * j;
            if (move / 8 == row + i && move % 8 == col + j * 2)
                if (move / 8 >= 0 && move / 8 <= 7 && move % 8 >= 0 && move % 8 <= 7)
                {
                    if (Game::board()[move / 8][move % 8] != nullptr && _black == Game::board()[move / 8][move % 8]->check_color())
                        ;
                    else possible_move.push_back(move);

                }
        }

    return possible_move;
}
