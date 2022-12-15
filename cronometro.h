#pragma once

#include <QLCDNumber>
#include <QTimer>
#include <QString>

class Cronometro:public QLCDNumber{
    Q_OBJECT

private:

    QTimer *timer;
    int ore;
    int minuti;
    int secondi;

public:
    Cronometro(QString init_time, QWidget *parent=0);
    void reset();
    QString getOra();
    void setOra(QString newOra);
    void start();
    void stop();
    
    
private slots:
    void showTime();
    
};
