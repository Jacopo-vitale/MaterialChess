#include "MyLabel.h"

MyLabel::MyLabel(QString str) : QLabel(str)
{
	_sound = new QSound(":/sounds/SelectMenu.wav");
	setText(str);

}

void MyLabel::mousePressEvent(QMouseEvent* e) {
		
		emit clicked();
	
	
}

void MyLabel::enterEvent(QEvent* e) {

	QPalette pal = this->palette();

	pal.setColor(QPalette::WindowText, QColor(238, 255, 65));

	_sound->play();

	this->setPalette(pal);

	
	
}

void MyLabel::leaveEvent(QEvent* e) {

	QPalette pal = this->palette();

	pal.setColor(QPalette::WindowText, QColor(41, 58, 86));

	this->setPalette(pal);

}

MyLabel::~MyLabel()
{
}
