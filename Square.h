#pragma once
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsEffect>


class Square :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
protected:
    int _x, _y;
    bool _black;
    bool _movable;
	QGraphicsTextItem text;
public:
    static int cell_size;

    Square(int x, int y, bool black);

	QGraphicsTextItem* t() { return &text; }

    bool black() { return _black; }
    void setMovable(bool movable) { _movable = movable; }
    bool movable() { return _movable; }

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* e);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* e);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* e);

	void colorized(bool col);
	void ai_colorized(bool col, bool from);
	void check_colorized(bool color);

signals:
    void clicked(int, int);

public slots:
	void visible_text(bool visible);
};
