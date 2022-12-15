#pragma once

#include <QWidget>
#include <QStackedLayout>
#include "FirstWindow.h"
#include "ChessBoard.h"

class GodWindow : public QWidget
{
	Q_OBJECT

private:
	
	QStackedLayout* _widgetStack;
    FirstWindow *_first;
	ChessBoard *_chess;
    static GodWindow* uniqueinstance;
    GodWindow();


public:
    static GodWindow* instance();
	~GodWindow();
    QStackedLayout* widgetStack(){ return _widgetStack; }
	void closeEvent(QCloseEvent *event);
	void setChessBoard(ChessBoard* p) { _chess = p; }
	void end_game(QString time, bool turn);
};
