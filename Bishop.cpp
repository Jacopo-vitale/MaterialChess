#include "Bishop.h"
#include "Game.h"
#include "King.h"
#include <iostream>

Bishop::Bishop(int pos, bool black) : logicPiece(pos,black) {

    _name = 'a';

    int bishop[8][8] = {
        {-20,-10,-10,-10,-10,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5, 10, 10,  5,  0,-10},
        {-10,  5,  5, 10, 10,  5,  5,-10},
        {-10,  0, 10, 10, 10, 10,  0,-10},
        {-10, 10, 10, 10, 10, 10, 10,-10},
        {-10,  5,  0,  0,  0,  0,  5,-10},
        {-20,-10,-10,-10,-10,-10,-10,-20}
    };

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            _bonus[i][j] = bishop[i][j];
}

std::list<int> Bishop::possibleMove() {

    std::list<int> possible_move;

    int move = -1;
    bool flag = false;
    int y = _pos / 8;

    //std::cout << _pos << std::endl;
    move = _pos + 7;
    y++;
    while (move  >= y * 8  && flag==false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag=true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                        if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                        }
                }

            else
                if (!verify_check(move))
                    possible_move.push_back(move);
        }
        move = move + 7;
        y++;
    }

    flag = false;
    move = _pos - 7;
    y = _pos / 8;
    y--;

    while (move <= (y * 8) + 7 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                        if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                if (!verify_check(move))
                    possible_move.push_back(move);
        }
        move = move - 7;
        y--;

    }

    flag = false;
    move = _pos + 9;
    y = _pos / 8;
    y++;

    while (move <= (y * 8) + 7 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                        if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                if (!verify_check(move))
                    possible_move.push_back(move);
        }
        move = move + 9;
        y++;
    }

    flag = false;
    move = _pos - 9;
    y = _pos / 8;
    y--;

    while (move >= y * 8 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                        if(!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                if (!verify_check(move))
                    possible_move.push_back(move);
        }
        move = move -9;
        y--;
    }

    return possible_move;
}

std::list<int> Bishop::pseudo_moves() {

    std::list<int> possible_move;
    int move = -1;
    bool flag = false;
    int y = _pos / 8;

    //std::cout << _pos << std::endl;
    move = _pos + 7;
    y++;
    while (move >= y * 8 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else possible_move.push_back(move);
        }
        move = move + 7;
        y++;
    }

    flag = false;
    move = _pos - 7;
    y = _pos / 8;
    y--;

    while (move <= (y * 8) + 7 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else possible_move.push_back(move);
        }
        move = move - 7;
        y--;

    }

    flag = false;
    move = _pos + 9;
    y = _pos / 8;
    y++;

    while (move <= (y * 8) + 7 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else possible_move.push_back(move);
        }
        move = move + 9;
        y++;
    }

    flag = false;
    move = _pos - 9;
    y = _pos / 8;
    y--;

    while (move >= y * 8 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (Game::board()[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == Game::board()[move / 8][move % 8]->check_color() && Game::board()[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != Game::board()[move / 8][move % 8]->check_color()) {
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else possible_move.push_back(move);
        }
        move = move - 9;
        y--;
    }

    return possible_move;
}
