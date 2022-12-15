#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QKeyEvent>
#include "MyLabel.h"

class NameWindow : public QWidget
{
	Q_OBJECT

private:
	QLineEdit*   _line;
	QLabel*      _insertName;
	MyLabel*     _apply;
	QVBoxLayout* _lay;
	int _diff;

public:
	NameWindow(int diff, QWidget* parent = nullptr);
	~NameWindow();
    virtual void keyPressEvent(QKeyEvent* e);
    
signals:
    void Pressed_enter();
    
public slots:
	void ApplyClicked();
};
