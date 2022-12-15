#include "King.h"
#include "Pawn.h"
#include "Game.h"
#include "Rook.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include <iostream>

King::King(int pos, bool black) :logicPiece(pos, black)
{
    _name = 'k';

    int king[8][8] = {
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-20,-30,-30,-40,-40,-30,-30,-20},
        {-10,-20,-20,-20,-20,-20,-20,-10},
        {20, 20,  0,  0,  0,  0, 20, 20},
        {20, 30, 10,  0,  0, 10, 30, 20}
    };

    int king2[8][8] = {
        {-50, -40, -30, -20, -20, -30, -40, -50},
        {-30, -20, -10, 0, 0, -10, -20, -30},
        {-30, -10, 20, 30, 30, 20, -10, -30},
        {-30, -10, 30, 40, 40, 30, -10, -30},
        {-30, -10, 30, 40, 40, 30, -10, -30},
        {-30, -10, 20, 30, 30, 20, -10, -30},
        {-30, -30, 0, 0, 0, 0, -30, -30},
        {-50, -30, -30, -30, -30, -30, -30, -50}
    };

	_end_game = false;

	_bonus_end_game = new int*[8];
	for (int i = 0; i < 8; i++)
		_bonus_end_game[i] = new int[8];

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            _bonus[i][j] = king[i][j];
            _bonus_end_game[i][j] = king2[i][j];
        }
}

std::list<int> King::possibleMove()
{
    std::list<int> possible_move;
    int move = -1;


    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            move = _pos + j * 8 + i;
            if (move < 0 || move >= 64)
                continue;
            if (move / 8 != (_pos / 8) + j)
                continue;
            if (Game::board()[move / 8][move % 8] != nullptr &&
                Game::board()[move / 8][move % 8]->check_color() == _black)
                continue;

			if (verify_king(move))
				continue;

            int old_pos = _pos;

            _pos = move;
            if (!isChecked())
                possible_move.push_back(move);

            _pos = old_pos;
        }

    return possible_move;
}

bool King::isChecked()
{
    logicPiece*** b = Game::board();
    int k_x = _pos / 8;
    int k_y = _pos % 8;

    //controlla se un pedone mette scacco al re
    for(int i=-1; i<=1; i = i+2)
        for (int j = -1; j <= 1; j = j + 2)
            if (((k_x + i) >= 0 && (k_x + i) <= 7) && ((k_y + j) >= 0 && (k_y + j) <= 7))
                if (b[k_x + i][k_y + j] != nullptr && b[k_x + i][k_y + j]->check_color() != _black)
                {
                    Pawn* p = dynamic_cast<Pawn*>(b[k_x + i][k_y + j]);
                    if (p)
                    {
						if (i > 0 && p->check_color() == false)
							return true;
						if (i < 0 && p->check_color() == true)
							return true;
                    }
                }

    //controlla se una torre mette scacco al re (oppure regina)
    //controllo verso l'alto
    int h = k_x - 1;
    while (h >= 0 && (b[h][k_y] == 0 || b[h][k_y] == this))
        h--;

    if (h >= 0 && b[h][k_y]->check_color() != _black)
    {
        Tower* p = dynamic_cast<Tower*>(b[h][k_y]);
        Queen* q = dynamic_cast<Queen*>(b[h][k_y]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }

    //controllo verso il basso
    h = k_x + 1;
    while (h <= 7 && (b[h][k_y] == nullptr || b[h][k_y] == this))
        h++;

    if (h <=7  && b[h][k_y]->check_color() != _black)
    {
        Tower* p = dynamic_cast<Tower*>(b[h][k_y]);
        Queen* q = dynamic_cast<Queen*>(b[h][k_y]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }

    //controllo verso destra
    h = k_y + 1;
    while (h <= 7 && (b[k_x][h] == nullptr || b[k_x][h] == this))
        h++;

    if (h <= 7 && b[k_x][h]->check_color() != _black)
    {
        Tower* p = dynamic_cast<Tower*>(b[k_x][h]);
        Queen* q = dynamic_cast<Queen*>(b[k_x][h]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }

    //controllo verso sinistra
    h = k_y - 1;
    while (h >=0 && (b[k_x][h] == nullptr || b[k_x][h] == this))
        h--;

    if (h >= 0 && b[k_x][h]->check_color() != _black)
    {
        Tower* p = dynamic_cast<Tower*>(b[k_x][h]);
        Queen* q = dynamic_cast<Queen*>(b[k_x][h]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }


    //controllo se un alfiere mette scacco al re
    //controllo diagonale verso l'alto (-1) e verso destra (+1)
    h = k_x - 1;
    int l = k_y + 1;
    while (h >= 0 && l <= 7 && (b[h][l] == nullptr || b[h][l] == this))
    {
        h--;
        l++;
    }

    if (h >= 0 && l <= 7 && b[h][l]->check_color() != _black)
    {
        Bishop* p = dynamic_cast<Bishop*>(b[h][l]);
        Queen* q = dynamic_cast<Queen*>(b[h][l]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }

    //controllo diagonale verso l'alto (-1) e verso sinistra (-1)
    h = k_x - 1;
    l = k_y - 1;
    while (h >= 0 && l >= 0 && (b[h][l] == 0 || b[h][l] == this))
    {
        h--;
        l--;
    }

    if (h >= 0 && l >=0 && b[h][l]->check_color() != _black)
    {
        Bishop* p = dynamic_cast<Bishop*>(b[h][l]);
        Queen* q = dynamic_cast<Queen*>(b[h][l]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }

    //controllo diagonale verso il basso (+1) e verso sinistra (-1)
    h = k_x + 1;
    l = k_y - 1;
    while (h <= 7 && l >= 0 && (b[h][l] == nullptr || b[h][l] == this))
    {
        h++;
        l--;
    }

    if (h <= 7 && l >= 0 && b[h][l]->check_color() != _black)
    {
        Bishop* p = dynamic_cast<Bishop*>(b[h][l]);
        Queen* q = dynamic_cast<Queen*>(b[h][l]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }

    //controllo diagonale verso il basso (+1) e verso destra (+1)
    h = k_x + 1;
    l = k_y + 1;
    while (h <= 7 && l <= 7 && (b[h][l] == nullptr || b[h][l] == this))
    {
        h++;
        l++;
    }

    if (h <= 7 && l <= 7 && b[h][l]->check_color() != _black)
    {
        Bishop* p = dynamic_cast<Bishop*>(b[h][l]);
        Queen* q = dynamic_cast<Queen*>(b[h][l]);
        if (p != nullptr || q != nullptr)
        {
            return true;
        }
    }


    //controllo se un cavallo mette sotto scacco il re
    for(int i=-1; i<=1; i = i + 2)
        for (int j = -1; j <= 1; j = j + 2)
        {
            h = k_x + i;
            l = k_y + 2 * j;

            if ((h <= 7 && h >= 0) && (l >= 0 && l <= 7) && b[h][l] != nullptr && b[h][l]->check_color() != _black)
            {
                Knight* p = dynamic_cast<Knight*>(b[h][l]);
                if (p)
                {
                    return true;
                }
            }

            h = k_x + 2 * i;
            l = k_y + j;
            if ((h <= 7 && h >= 0) && (l >= 0 && l <= 7) && b[h][l] != nullptr && b[h][l]->check_color() != _black)
            {
                Knight* p = dynamic_cast<Knight*>(b[h][l]);
                if (p)
                {
                    return true;
                }
            }
        }

    return false;

}

int King::bonus()
{
    int x = _pos / 8;
    int y = _pos % 8;

    if (_black)
    {
        if (_end_game)
            return _bonus_end_game[7 - x][y];
        else return _bonus[7 - x][y];
    }
    else
    {
        if (_end_game)
            return _bonus_end_game[x][y];
        else return _bonus[x][y];
    }
}

std::list<int> King::pseudo_moves()
{
    std::list<int> possible_move;
    int move = -1;

    logicPiece*** b = Game::board();

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            move = _pos + j * 8 + i;
            if (move < 0 || move >= 64)
                continue;
            if (move / 8 != (_pos / 8) + j)
                continue;
            if (b[move / 8][move % 8] != nullptr && b[move / 8][move % 8]->check_color() == _black)
                continue;
        }

    return possible_move;
}

King::~King()
{
	for (int i = 0; i < 8; i++)
		delete[] _bonus[i];
	delete[] _bonus;

	for (int i = 0; i < 8; i++)
		delete[] _bonus_end_game[i];
	delete[] _bonus_end_game;
}

bool King::verify_king(int move)
{
	int old_pos = _pos;
	bool check = false;
	int appo = 0;
	logicPiece* eaten = nullptr;

	// make the move corresponding to 'v'
	eaten = Game::board()[move / 8][move % 8];
	Game::board()[move / 8][move % 8] = this;
	this->setPos(move);
	Game::board()[old_pos / 8][old_pos % 8] = nullptr;

	//verify the presence of a king
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			appo = _pos + j * 8 + i;
			if (appo < 0 || appo >= 64)
				continue;
			if (appo / 8 != (_pos / 8) + j)
				continue;
			if (Game::board()[appo / 8][appo % 8] == nullptr)
				continue;
			King* k = dynamic_cast <King*> (Game::board()[appo / 8][appo % 8]);
			if (k)
			{
				check = true;
				break;
			}
		}

	// restore previous game state / undo the move
	Game::board()[old_pos / 8][old_pos % 8] = this;
	this->setPos(old_pos);
	if (eaten)
		Game::board()[move / 8][move % 8] = eaten;
	else  Game::board()[move / 8][move % 8] = nullptr;

	return check;
}