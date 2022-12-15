#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include "ChessBoard.h"

class MainWindow :public QWidget{
    
	Q_OBJECT

private:
    QWidget * _window;
    ChessBoard *_chessboard;
    QVBoxLayout *_layout;
    QMenuBar *_menuBar;
    QMenu* _game;
    QMenu* _options;
    QMenu* _info;

    QAction* _newGame;
    QAction* _quit;
    QAction* _infoAction;
	QAction* _setGrid;
    QAction* _difficulty;

	QString _name;

public:
    
    MainWindow(int diff, bool _newgame, QString name, QWidget* parent = nullptr);
	~MainWindow();

	virtual void resizeEvent(QResizeEvent *event) override;

	void loadName();

signals:
	void changed(int);

public slots:
    void grid(bool state);
	void game_ended(QString time);
	void saveName();
};
