#pragma once
#include "LogicPiece.h"
#include <list>

class King : public logicPiece
{
private:
    int** _bonus_end_game;
    bool _end_game;
public:
    King(int pos, bool black);
	~King();
    virtual std::list<int> possibleMove();
    virtual std::list<int> pseudo_moves();
    virtual int bonus();
    bool isChecked();
	bool verify_king(int pos);
    void setEndGame(bool end_game) { _end_game = end_game; }
};
