
#include "myThread.hpp"

void myThread::run()
{
   QMessageBox::warning(_mainWin, QString::fromStdString("Info"), QString::fromStdString("Calcul en cours..."), QMessageBox::NoButton, QMessageBox::NoButton);

   exec();
}
