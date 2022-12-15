#pragma once

#include <QString>
#include <QSound>
#include <QMouseEvent>
#include <QLabel>

class MyLabel : public QLabel
{
	Q_OBJECT

private:
	QSound* _sound;
public:
	MyLabel(const QString str);
	~MyLabel();

	virtual void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
	virtual void enterEvent(QEvent* e) override;
	virtual void leaveEvent(QEvent* e) override;

signals:
	void clicked();

};