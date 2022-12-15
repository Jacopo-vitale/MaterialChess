#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QChar>
#include <QGraphicsEffect>

class Piece :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int _x, _y;
    bool _black;
    QChar _name;				//ruolo del pezzo nel gioco degli scacchi (re, pedone, etc)
	bool _died;
	QGraphicsEffect* _colorize;

    /* Codifica per il nome dei pezzi
        k=re
        q=regina
        t=torre
        a=alfiere
        p=pedone
        c=cavallo
    */

public:
    Piece(int x, int y, bool black, QChar name);

    bool black() { return _black; }
    QChar name() {return _name;}

    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

	void setDied(bool died) { _died = died; }

	void colorized(bool col) { _colorize->setEnabled(col); }

signals:
    void checked();
};
