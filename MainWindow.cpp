#include <QString>
#include <QMessageBox>
#include <QSettings>
#include <QChar>
#include <qpalette.h>
#include <iostream>
#include "Square.h"
#include "MainWindow.h"
#include "GodWindow.h"

MainWindow::MainWindow(int diff, bool _newgame, QString name, QWidget* parent):QWidget(parent){
    
	QPalette pal;
    _window=new QWidget();
    _chessboard=new ChessBoard(diff, _newgame);
    _layout=new QVBoxLayout();
	_window->setAcceptDrops(true);

    _menuBar=new QMenuBar();
    _game=new QMenu("Partita");
    _options=new QMenu("Opzioni");
    _info=new QMenu("?");
  
    _menuBar->addMenu(_game);
    _menuBar->addMenu(_options);
    _menuBar->addMenu(_info);
    
    _newGame=new QAction("Nuova partita",0);
    _quit=new QAction("Esci",0);
    _infoAction=new QAction("Info",0);
    _difficulty=new QAction("Seleziona difficoltà...",0);
	_setGrid = new QAction("Griglia", 0);
	_setGrid->setCheckable(true);
	_setGrid->setChecked(true);

	connect(_setGrid, SIGNAL(toggled(bool)), this, SLOT(grid(bool)));

    _game->addAction(_newGame);
    _game->addAction(_quit);
    
    _options->addAction(_difficulty);
	_options->addAction(_setGrid);
    _info->addAction(_infoAction);
    
    //checkbox    
	pal.setColor(QPalette::WindowText, QColor(255, 255, 255));
//    connect(checkbox, SIGNAL(toggled(bool)), this, SLOT(grid(bool)));

	//adding to layout...
	_layout->addWidget(_menuBar);
	_layout->addWidget(_chessboard);
	_layout->setContentsMargins(0,0,0,0);
	
	//window settings...
    setLayout(_layout);
	setWindowTitle(QString("ChessGame"));

	//set name player
	if(_newgame)
		_name = name;
	else loadName();

	connect(_chessboard, SIGNAL(human_wins(QString)), this, SLOT(game_ended(QString)));
	connect(_chessboard, SIGNAL(toSave()), this, SLOT(saveName()));
    
    this->setParent(GodWindow::instance());
    
    GodWindow::instance()->widgetStack()->addWidget(this);
	GodWindow::instance()->setChessBoard(_chessboard);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}

void MainWindow::grid(bool state){

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_chessboard->square()[i][j]->visible_text(state);
}

MainWindow::~MainWindow() {
	this->destroy();
}

void MainWindow::game_ended(QString time)
{
	QString newWinner = _name + ' ' + time;
	QMessageBox::information(this, "Hai vinto", newWinner);
}

void MainWindow::saveName()
{
	QSettings setting;

	setting.setValue("name", _name);
}

void MainWindow::loadName()
{
	QSettings setting;

	_name = setting.value("name", " ").toString();
}
