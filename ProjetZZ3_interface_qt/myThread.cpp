
#include "myThread.hpp"

void myThread::init(QWidget * parent)
{
   _fenetre.init(parent);
}


void myThread::run()
{
   //QMessageBox::warning(_mainWin, QString::fromStdString("Info"), QString::fromStdString("Calcul en cours..."), QMessageBox::NoButton, QMessageBox::NoButton);

   //calculWindow win;

   //win.init();
   _fenetre.afficher();

   std::cout << "Un petit coup dans le thread..." << std::endl;

   exec();
}


//void myThread::exit()
//{
//   _fenetrecacher();
//
//   std::cout << "fin du thread" << std::endl;
//}
