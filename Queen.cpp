#include "Queen.h"
#include "Game.h"
#include "King.h"

Queen::Queen(int pos, bool black) : logicPiece(pos,black) {

    _name = 'q';

    int queen[8][8] = {
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5,  5,  5,  5,  0,-10},
        {-5,  0,  5,  5,  5,  5,  0, -5},
        {0,  0,  5,  5,  5,  5,  0, -5},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}
    };

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            _bonus[i][j] = queen[i][j];
}

std::list<int> Queen::possibleMove() {

    std::list<int> possible_move;

    int move = -1;
    bool flag = false;
    int y = _pos / 8;

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
                        if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                if (!verify_check(move))
                    possible_move.push_back(move);
        }
        move = move - 9;
        y--;
    }

    move = _pos;
    int riga = _pos / 8;
    int i = 1;
    int j = 8;
    bool finished = false;

    //spostamento a sinistra
    while ((move) >= (riga * 8) && finished == false) {

        if (Game::board()[move / 8][move % 8] != 0 && _black != Game::board()[move / 8][move % 8]->check_color()) {
            if (!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (Game::board()[move / 8][move % 8] != 0 && Game::board()[move / 8][move % 8] != this && _black == Game::board()[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        else if (Game::board()[move / 8][move % 8] == 0 && move >= (riga * 8)) {
            if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos - i;
        i++;
    }

    i = 1;
    finished = false;
    move = _pos;

    //spostamento a destra
    while ((move) < (riga + 1) * 8 && finished == false) {

        if (Game::board()[move / 8][move % 8] != 0 && _black != Game::board()[move / 8][move % 8]->check_color()) {
            if (!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (Game::board()[move / 8][move % 8] != 0 && Game::board()[move / 8][move % 8] != this && _black == Game::board()[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        if (Game::board()[move / 8][move % 8] == 0 && move < (riga + 1) * 8) {
            if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos + i;
        i++;
    }

    finished = false;
    move = _pos;

    //spostamento verso l'alto
    while ((move) >= 0 && finished == false) {

        if (Game::board()[move / 8][move % 8] != 0 && _black != Game::board()[move / 8][move % 8]->check_color()) {
            if (!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (Game::board()[move / 8][move % 8] != 0 && Game::board()[move / 8][move % 8] != this && _black == Game::board()[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        if (Game::board()[move / 8][move % 8] == 0 && move >= 0) {
            if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos - j;
        j = j + 8;
    }

    j = 8;
    finished = false;
    move = _pos;

    //spostamento verso il basso
    while ((move) <= 63 && finished == false) {

        if (Game::board()[move / 8][move % 8] != 0 && _black != Game::board()[move / 8][move % 8]->check_color()) {
            if(!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (Game::board()[move / 8][move % 8] != 0 && Game::board()[move / 8][move % 8] != this && _black == Game::board()[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        if (Game::board()[move / 8][move % 8] == 0 && move <= 63) {
            if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos + j;
        j = j + 8;
    }

    return possible_move;
}

std::list<int> Queen::pseudo_moves()
{

    std::list<int> possible_move;

    logicPiece*** board = Game::board();

    int move = -1;
    bool flag = false;
    int y = _pos / 8;

    move = _pos + 7;
    y++;
    while (move >= y * 8 && flag == false) {
        if (move >= 0 && move <= 63) {	//Inside board?
            if (board[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == board[move / 8][move % 8]->check_color() && board[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != board[move / 8][move % 8]->check_color()) {
                        //if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                //if (!verify_check(move))
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
            if (board[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == board[move / 8][move % 8]->check_color() && board[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != board[move / 8][move % 8]->check_color()) {
                        //if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                //if (!verify_check(move))
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
            if (board[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == board[move / 8][move % 8]->check_color() && board[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != board[move / 8][move % 8]->check_color()) {
                        //if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                //if (!verify_check(move))
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
            if (board[move / 8][move % 8] != 0) {		//Is there a piece?
                if (_black == board[move / 8][move % 8]->check_color() && board[move / 8][move % 8] != this) {	//is color different?, am i different to me?

                    flag = true;
                }
                else
                    if (_black != board[move / 8][move % 8]->check_color()) {
                        //if (!verify_check(move))
                            possible_move.push_back(move);
                        flag = true;
                    }
            }

            else
                //if (!verify_check(move))
                    possible_move.push_back(move);
        }
        move = move - 9;
        y--;
    }

    move = _pos;
    int riga = _pos / 8;
    int i = 1;
    int j = 8;
    bool finished = false;

    //spostamento a sinistra
    while ((move) >= (riga * 8) && finished == false) {

        if (board[move / 8][move % 8] != 0 && _black != board[move / 8][move % 8]->check_color()) {
            //if (!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (board[move / 8][move % 8] != 0 && board[move / 8][move % 8] != this && _black == board[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        else if (board[move / 8][move % 8] == 0 && move >= (riga * 8)) {
            //if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos - i;
        i++;
    }

    i = 1;
    finished = false;
    move = _pos;

    //spostamento a destra
    while ((move) < (riga + 1) * 8 && finished == false) {

        if (board[move / 8][move % 8] != 0 && _black != board[move / 8][move % 8]->check_color()) {
            //if (!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (board[move / 8][move % 8] != 0 && board[move / 8][move % 8] != this && _black == board[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        if (board[move / 8][move % 8] == 0 && move < (riga + 1) * 8) {
            //if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos + i;
        i++;
    }

    finished = false;
    move = _pos;

    //spostamento verso l'alto
    while ((move) >= 0 && finished == false) {

        if (board[move / 8][move % 8] != 0 && _black != board[move / 8][move % 8]->check_color()) {
            //if (!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (board[move / 8][move % 8] != 0 && board[move / 8][move % 8] != this && _black == board[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        if (board[move / 8][move % 8] == 0 && move >= 0) {
            //if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos - j;
        j = j + 8;
    }

    j = 8;
    finished = false;
    move = _pos;

    //spostamento verso il basso
    while ((move) <= 63 && finished == false) {

        if (board[move / 8][move % 8] != 0 && _black != board[move / 8][move % 8]->check_color()) {
            //if (!verify_check(move))
                possible_move.push_back(move);
            finished = true;
        }
        else if (board[move / 8][move % 8] != 0 && board[move / 8][move % 8] != this && _black == board[move / 8][move % 8]->check_color()) {
            finished = true;
        }

        if (board[move / 8][move % 8] == 0 && move <= 63) {
            //if (!verify_check(move))
                possible_move.push_back(move);
        }

        move = _pos + j;
        j = j + 8;
    }

    return possible_move;
}
