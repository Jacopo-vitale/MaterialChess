#include "Pawn.h"
#include "King.h"
#include "Game.h"
#include "Queen.h"
#include <iostream>

Pawn::Pawn(int pos, bool black) :logicPiece(pos, black)
{
    _name = 'p';

    int pawn[8][8] = {
        {0,  0,  0,  0,  0,  0,  0,  0},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {10, 10, 20, 30, 30, 20, 10, 10},
        {5,  5, 10, 25, 25, 10,  5,  5},
        {0,  0,  0, 20, 20,  0,  0,  0},
        {5, -5,-10,  0,  0,-10, -5,  5},
        {5, 10, 10,-20,-20, 10, 10,  5},
        {0,  0,  0,  0,  0,  0,  0,  0}
    };

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            _bonus[i][j] = pawn[i][j];

}

std::list<int> Pawn::possibleMove()
{
    std::list<int> possible_move;
    int move = _pos;

    for (int i = -1; i <= 1; i++)
    {
        if (!_black)
            move = _pos - 8 + i;
        else move = _pos + 8 + i;

		if (move < 0 || move > 63)
			continue;
		
        if (!_black && move / 8 != (_pos / 8) - 1)
            continue;
        if (_black && move / 8 != (_pos / 8) + 1)
            continue;
		
        if (i == 0 && Game::board()[move / 8][move % 8] != nullptr)
            continue;

        if (i == 0 && Game::board()[move / 8][move % 8] == nullptr)
            if (!verify_check(move))
                possible_move.push_back(move);

        if (i == -1 || i == 1)
        {
            if (move / 8 >= 0 && move / 8 <= 7 && move % 8 >= 0 && move % 8 <= 7)
                if (Game::board()[move / 8][move % 8] != nullptr && Game::board()[move / 8][move % 8]->check_color() != _black)
                    if(!verify_check(move))
                        possible_move.push_back(move);
        }
    }

	if (_pos / 8 == 1 && _black)
	{
		move = _pos + 16;
		if (Game::board()[(_pos + 8) / 8][(_pos + 8) % 8] == nullptr)
			if (Game::board()[move / 8][move % 8] == nullptr)
				if (!verify_check(move))
					possible_move.push_back(move);
	}
	else if (_pos / 8 == 6 && !_black)
	{
		move = _pos - 16;
		if (Game::board()[(_pos - 8) / 8][(_pos - 8) % 8] == nullptr)
			if (Game::board()[move / 8][move % 8] == nullptr)
				if (!verify_check(move))
					possible_move.push_back(move);
	}


    return possible_move;
}

std::list<int> Pawn::pseudo_moves()
{
    std::list<int> possible_move;
    int move = _pos;

    for (int i = -1; i <= 1; i++)
    {
        if (!_black)
            move = _pos - 8 + i;
        else move = _pos + 8 + i;

        if (!_black && move / 8 != (_pos / 8) - 1)
            continue;
        if (_black && move / 8 != (_pos / 8) + 1)
            continue;

        if (i == 0 && Game::board()[move / 8][move % 8] != nullptr)
            continue;
        else if (i == 0 && Game::board()[move / 8][move % 8] == nullptr)
                possible_move.push_back(move);


        if (i == -1 || i == 1)
        {
            if (move / 8 >= 0 && move / 8 <= 7 && move % 8 >= 0 && move % 8 <= 7)
                if (Game::board()[move / 8][move % 8] != nullptr && Game::board()[move / 8][move % 8]->check_color() != _black)
                        possible_move.push_back(move);
        }
    }

    

    return possible_move;
}
