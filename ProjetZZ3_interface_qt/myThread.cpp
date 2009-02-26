
#include "myThread.hpp"

void MyThread::run()
{
   QMessageBox::warning(_mainWin, QString::fromStdString("Info"), QString::fromStdString("Calcul en cours..."), QMessageBox::NoButton, QMessageBox::NoButton);

   exec();
}
