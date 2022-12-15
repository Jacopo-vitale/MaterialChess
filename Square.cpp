#include "Square.h"
#include <QBrush>
#include <QChar>
#include <QFont>
#include <iostream>


int Square::cell_size = 300;

Square::Square(int x, int y, bool black) : QGraphicsRectItem()
{
    _x = x;
    _y = y;
    _black = black;
    _movable = false;

    if (black)
        setBrush(QBrush(QColor(41, 58, 86)));

    else
        setBrush(QBrush(QColor(207, 214, 229)));

    setRect(0, 0, cell_size, cell_size);

    setPos(x, y);
    setZValue(1);
    setAcceptHoverEvents(true);

	//text
	QChar row, col;
	if (x == 0)
		row = 'a';
	else if (x == cell_size)
		row = 'b';
	else if (x == 2*cell_size)
		row = 'c';
	else if (x == 3*cell_size)
		row = 'd';
	else if (x == 4*cell_size)
		row = 'e';
	else if (x == 5*cell_size)
		row = 'f';
	else if (x == 6*cell_size)
		row = 'g';
	else if (x == 7*cell_size)
		row = 'h';

	QString textline = row + QString::number(y / cell_size + 1);
	text.setPlainText(textline);
	QFont font;
	font.setFamily("Arial Bound");
	font.setPointSize(30);
	text.setDefaultTextColor(black ? QColor(207, 214, 229) : QColor(41, 58, 86));
	text.setPos(this->x() + 10, this->y() + 10);
	text.setFont(font);
	text.setVisible(true);
	text.setParent(this);
	text.setZValue(6);
}

void Square::hoverEnterEvent(QGraphicsSceneHoverEvent* e)
{
	if (e->type() == QEvent::GraphicsSceneHoverEnter)
		setOpacity(0.5);
}

void Square::hoverLeaveEvent(QGraphicsSceneHoverEvent* e)
{
    if (e->type() == QEvent::GraphicsSceneHoverLeave)
		setOpacity(1.0);
}
void Square::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    emit clicked(_x, _y);
}

void Square::visible_text(bool visible)
{
	if (visible)
		text.setVisible(true);
	else text.setVisible(false);
}

void Square::colorized(bool col)
{
	if (col)
	{
		if (_black)
			setBrush(QColor(255,235,59));
		else
			setBrush(QColor(255,241,118));
	}
	else
	{
		if (_black)
			setBrush(QBrush(QColor(41, 58, 86)));

		else
			setBrush(QBrush(QColor(207, 214, 229)));
	}	
}

void Square::ai_colorized(bool col, bool from)
{
	if (col)
	{
		if (!from)
			setBrush(QBrush(QColor(3, 218, 198)));

		else
			setBrush(QBrush(QColor(1, 135, 134)));
	}
	else
	{	
		if (_black)
			setBrush(QBrush(QColor(41, 58, 86)));

		else
			setBrush(QBrush(QColor(207, 214, 229)));
	}
}

void Square::check_colorized(bool color)
{
	if (color)
		setBrush(QColor(176, 0, 32));
	else
	{
		if (_black)
			setBrush(QBrush(QColor(41, 58, 86)));

		else
			setBrush(QBrush(QColor(207, 214, 229)));
	}
}