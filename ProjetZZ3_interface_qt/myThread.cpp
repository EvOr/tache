
#include "myThread.hpp"

void myThread::run()
{
   //QMessageBox::warning(_mainWin, QString::fromStdString("Info"), QString::fromStdString("Calcul en cours..."), QMessageBox::NoButton, QMessageBox::NoButton);

   calculWindow win;

   win.init();
   win.afficher();

   std::cout << "Un petit coup dans le thread..." << std::endl;

   exec();
}
