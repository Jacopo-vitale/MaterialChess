#pragma once
#include <list>
#include <QChar>
#include "Piece.h"

class logicPiece
{
protected:
    int _pos;
    bool _black;
    QChar _name;
	int ** _bonus;
	Piece* _graphicPiece;
public:
    logicPiece(int pos,bool black, Piece* p=nullptr);
    virtual ~logicPiece();

    virtual void setPos(int pos) { _pos = pos; }
    int pos() { return _pos; }
    virtual std::list<int> possibleMove() = 0;
    virtual std::list<int> pseudo_moves() = 0;
    virtual bool verify_check(int move);
    QChar name() { return _name; }

    bool check_color() { return _black; }

    virtual int bonus();

	void setGraphicPiece(Piece* p) { _graphicPiece = p; }
	Piece* GraphicPiece() { return _graphicPiece; }

};

/*
CODIFICA SCACCHIERA

(x,y) -> i
i=y*8+x


i -> (x,y)
y = i%8
x=i/8
*/
