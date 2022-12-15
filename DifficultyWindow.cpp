#include <iostream>
#include "DifficultyWindow.h"
#include "GodWindow.h"
#include "NameWindow.h"

DifficultyWindow::DifficultyWindow(QWidget* parent) : QWidget(0)
{
	QPalette pal;
	QFont font;
    QString accent_a = QStringLiteral("à");

	_easy = new MyLabel(trUtf8("Facile"));
   	_mid  = new MyLabel(trUtf8("Normale"));
	_hard = new MyLabel(trUtf8("Difficile"));
    _chooseDiff = new QLabel("Scegli la difficolt" + accent_a);
	_ly = new QVBoxLayout();

	connect(_easy, SIGNAL(clicked()), this, SLOT(Chosen()));
	connect(_mid, SIGNAL(clicked()), this, SLOT(Chosen()));
	connect(_hard, SIGNAL(clicked()), this, SLOT(Chosen()));
	
	
	_chooseDiff->setAlignment(Qt::AlignCenter);
	_easy->setAlignment(Qt::AlignCenter);
	_mid->setAlignment(Qt::AlignCenter);
	_hard->setAlignment(Qt::AlignCenter);
	
	pal.setColor(QPalette::WindowText, QColor(41, 58, 86));

	font.setFamily("Palatina");
	font.setPointSize(font.pointSize() + 40);

	_chooseDiff->setFont(font);
	_chooseDiff->setPalette(pal);


	font.setPointSize(font.pointSize() - 20);

	_easy->setPalette(pal);
	_easy->setFont(font);
	
	_mid->setPalette(pal);
	_mid->setFont(font);

	_hard->setPalette(pal);
	_hard->setFont(font);

	pal.setColor(QPalette::Background, QColor(207, 214, 229));
	this->setPalette(pal);

	_ly->addWidget(_chooseDiff);
	_ly->addSpacing(70);
	_ly->addWidget(_easy);
	_ly->addSpacing(10);
	_ly->addWidget(_mid);
	_ly->addSpacing(10);
	_ly->addWidget(_hard);

	_ly->setAlignment(Qt::AlignCenter);

	setMinimumSize(900, 768);

	this->setLayout(_ly);
    this->setParent(GodWindow::instance());
    GodWindow::instance()->widgetStack()->addWidget(this);

}

DifficultyWindow::~DifficultyWindow()
{
	delete _easy;
	delete _ly;
	delete _mid;
	delete _hard;
	delete _chooseDiff;
    
}

void DifficultyWindow::Chosen() {

	MyLabel* d = dynamic_cast<MyLabel*> (QObject::sender());
	int diff=0;
	if (d == _easy)
		diff = 3;
	else if (d == _mid)
		diff = 5;
	else if (d == _hard)
		diff = 7;

	this->setVisible(false);

    (new NameWindow(diff))->show();

}
