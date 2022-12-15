#include "Piece.h"
#include "Square.h"
#include <iostream>

Piece::Piece(int x, int y, bool black, QChar name):QObject(), QGraphicsPixmapItem()
{
    _x = x;
    _y = y;
    _black = black;
    _name = name;

    if (black)
    {
        if (name == 'k')
            setPixmap(QPixmap(":/graphics/kingB.png"));
        else if (name == 'q')
            setPixmap(QPixmap(":/graphics/queenB.png"));
        else if (name == 'p')
            setPixmap(QPixmap(":/graphics/pawnB.png"));
        else if (name == 't')
            setPixmap(QPixmap(":/graphics/rookB.png"));
        else if (name == 'a')
            setPixmap(QPixmap(":/graphics/bishopB.png"));
        else if (name == 'c')
            setPixmap(QPixmap(":/graphics/knightB.png"));
        setZValue(2);
    }
    else
    {
        if (name == 'k')
            setPixmap(QPixmap(":/graphics/kingW.png"));
        else if (name == 'q')
            setPixmap(QPixmap(":/graphics/queenW.png"));
        else if (name == 'p')
            setPixmap(QPixmap(":/graphics/pawnW.png"));
        else if (name == 't')
            setPixmap(QPixmap(":/graphics/rookW.png"));
        else if (name == 'a')
            setPixmap(QPixmap(":/graphics/bishopW.png"));
        else if (name == 'c')
            setPixmap(QPixmap(":/graphics/knightW.png"));
        setZValue(3);
    }

    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setPos(_x, _y);
	_died = false;

	_colorize = new QGraphicsColorizeEffect();
	_colorize->setEnabled(false);
	setGraphicsEffect(_colorize);
}



void Piece::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (_died)
		return;

    emit checked();
}
