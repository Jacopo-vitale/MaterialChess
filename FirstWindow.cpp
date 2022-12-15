#include <QFont>
#include <iostream>
#include "FirstWindow.h"
#include "GodWindow.h"
#include "DifficultyWindow.h"
#include "MainWindow.h"

FirstWindow::FirstWindow(QWidget* parent) : QWidget(parent)
{
	_newGame   = new QPushButton(QIcon(":/graphics/kingB.png"), "   Nuova Partita\t    ", this);
	_continue  = new QPushButton(QIcon(":/graphics/knightB.png"), "   Continua Partita\t\t", this);
	_ranking   = new QPushButton(QIcon(":/graphics/queenB.png"), "   Classifica\t\t\t\t\t\t\t\t\t\t\t", this);
	_startText = new QLabel(this);
	_layout    = new QVBoxLayout(this);
	
	QPalette pal = palette();
	QFont font   = _startText->font();

	font.setPointSize(70);
	font.setFamily("Avenir");
	pal.setColor(QPalette::WindowText, QColor(238, 255, 65));
	

	_startText->setPalette(pal);
	_startText->setFont(font);

	_startText->setText("CHESS GAME");
    _startText->setAlignment(Qt::AlignCenter);

	pal.setBrush(QPalette::ButtonText, QBrush(QColor(41, 58, 86)));
	font = _newGame->font();
	font.setPointSize(font.pointSize() + 10);
	_newGame->setIconSize(QSize(100, 100));
	_newGame->setFixedWidth(550);
	_newGame->setPalette(pal);
	_newGame->setFont(font);
	_newGame->setStyleSheet("* { background-color: rgb(207, 214, 229); border-radius: 10px; border-width: 3px; border-style: solid; border-color: rgb(238, 255, 65) }");
	_continue->setIconSize(QSize(100, 100));
	_continue->setFixedWidth(550);
	_continue->setPalette(pal);
	_continue->setFont(font);
	_continue->setStyleSheet("* { background-color: rgb(207, 214, 229);  border-radius: 10px;  border-width: 3px; border-style: solid; border-color: rgb(238, 255, 65) }");
	_ranking->setIconSize(QSize(100, 100));
	_ranking->setFixedWidth(550);
	_ranking->setPalette(pal);
	_ranking->setFont(font);
	_ranking->setStyleSheet("* { background-color: rgb(207, 214, 229); border-radius: 10px; border-width: 3px; border-style: solid; border-color: rgb(238, 255, 65) }");


	connect(_newGame, SIGNAL(clicked()), this, SLOT(NewGame()));
	connect(_continue, SIGNAL(clicked()), this, SLOT(ResumeGame()));
	connect(_ranking, SIGNAL(clicked()), this, SLOT(ResumeGame()));

	setMinimumSize(900, 768);
	
	pal.setColor(QPalette::Background, QColor(41, 58, 86));
	setAutoFillBackground(true);
	setPalette(pal);

	pal.setColor(QPalette::Text, QColor(248, 226, 93));
	_startText->setPalette(pal);

	_layout->setContentsMargins(0, 0, 0, 100);
	_layout->setSpacing(0);
	_layout->addWidget(_startText);
	_layout->addSpacing(50);
	_layout->addWidget(_newGame);
	_layout->addSpacing(30);
	_layout->addWidget(_continue);
	_layout->addSpacing(20);
	_layout->addWidget(_ranking);
	

	_layout->setAlignment(Qt::AlignCenter);

	setLayout(_layout);

    this->setParent(parent);
}

FirstWindow::~FirstWindow()
{
	delete _newGame;
	delete _ranking;
	delete _continue;
	delete _layout;
	delete _startText;

}

void FirstWindow::NewGame() {

	this->setVisible(false);
    (new DifficultyWindow())->show();
}
void FirstWindow::ResumeGame() 
{
	this->setVisible(false);
	(new MainWindow(3, false,"Ci"))->show();
}
