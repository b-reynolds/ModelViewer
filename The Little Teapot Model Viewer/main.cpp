#include "frmmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    FrmMain frmMain;

    frmMain.show();
    return application.exec();
}
