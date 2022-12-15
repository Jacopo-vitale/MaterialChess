#include "NameWindow.h"
#include "MainWindow.h"
#include "GodWindow.h"
#include <iostream>

NameWindow::NameWindow(int diff, QWidget* parent) : QWidget(0)
{
	_line       = new QLineEdit();
	_insertName = new QLabel();
	_apply      = new MyLabel("Invio");
	_lay        = new QVBoxLayout();
	_diff = diff;

	QFont    font;
	QPalette pal;

	this->setMinimumSize(800, 600);

	connect(_apply, SIGNAL(clicked()), this, SLOT(ApplyClicked()));
    connect(this,SIGNAL(Pressed_enter()),this,SLOT(ApplyClicked()));

	pal.setColor(QPalette::Background, QColor(207, 214, 229));
	this->setPalette(pal);

	font.setFamily("Palatina");
	font.setPointSize(30);

	pal.setColor(QPalette::WindowText, QColor(41, 58, 86));

	
	_insertName->setFixedHeight(50);
	_insertName->setAlignment(Qt::AlignCenter);
	_insertName->setText("Inserisci il nome: ");
	_insertName->setFont(font);
	_insertName->setPalette(pal);
	
	font.setPointSize(30);
	pal.setColor(QPalette::Text, QColor(41, 58, 86));
	_line->setAlignment(Qt::AlignCenter);
	_line->setMaxLength(20);
	_line->setFixedWidth(550);
	_line->setPalette(pal);
	_line->setFont(font);

	_apply->setFont(font);
	_apply->setPalette(pal);
	_apply->setAlignment(Qt::AlignCenter);

	pal.setColor(QPalette::ButtonText, QColor(41, 58, 86));

	_lay->setContentsMargins(0,0,0,30);
	_lay->addWidget(_insertName);
	_lay->addSpacing(10);
	_lay->addWidget(_line);
	_lay->setSpacing(50);
	_lay->addWidget(_apply);
	_lay->setAlignment(Qt::AlignCenter);

	this->setLayout(_lay);

	this->setWindowTitle("Chess Game");

	this->setVisible(false);

    this->setParent(GodWindow::instance());
    
    GodWindow::instance()->widgetStack()->addWidget(this);

}

NameWindow::~NameWindow()
{
	this->destroy();

}

void NameWindow::ApplyClicked() {

	if (_line->text() != "") {
		QString name = _line->text();
		this->setVisible(false);
        (new MainWindow(_diff,true, name))->show();
	}
	else return;
}


void NameWindow::keyPressEvent(QKeyEvent* e)
{
    
        if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
            emit(Pressed_enter());
}
