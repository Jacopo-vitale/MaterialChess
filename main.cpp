#include <QApplication>
#include "GodWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    app.setWindowIcon(QIcon(":/graphics/knightB.png"));
    app.setOrganizationName("Team Scacchi");
    app.setOrganizationDomain("MyDomain");
    app.setApplicationName("Chess Game");
    
    (GodWindow::instance())->show();

    return app.exec();
}
