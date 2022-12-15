#include "LogicPiece.h"
#include "Game.h"
#include "King.h"

logicPiece::logicPiece(int pos, bool black, Piece* p) {

    _pos = pos;
    _black = black;
    _name = ' ';
	_graphicPiece = p;

	//allocazione 
	_bonus = new int*[8];
	for (int i = 0; i < 8; i++)
		_bonus[i] = new int[8];
}

logicPiece::~logicPiece() 
{
	for (int i = 0; i < 8; i++)
		delete[] _bonus[i];
	delete[] _bonus;
}

int logicPiece::bonus()
{
    int x = _pos / 8;
    int y = _pos % 8;

    if (_black)
        return _bonus[7-x][y];
    else return _bonus[x][y];
}

bool logicPiece::verify_check(int move)
{
    int old_pos = _pos;
    bool check = false;
    logicPiece* eaten = nullptr;
    King* k = dynamic_cast<King*>(_black ? Game::black_king() : Game::white_king());

    // make the move corresponding to 'v'
    eaten = Game::board()[move / 8][move % 8];
    Game::board()[move / 8][move % 8] = this;
    this->setPos(move);
    Game::board()[old_pos / 8][old_pos % 8] = nullptr;

    //verify check condition
    if (k->isChecked())
        check = true;
    else check = false;

    // restore previous game state / undo the move
    Game::board()[old_pos / 8][old_pos % 8] = this;
    this->setPos(old_pos);
    if (eaten)
        Game::board()[move / 8][move % 8] = eaten;
    else  Game::board()[move / 8][move % 8] = nullptr;

    return check;
}
