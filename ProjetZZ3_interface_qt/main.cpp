#include "./ihm/mainWindow.hpp"
#include <iostream>
#include <ctime>

int main(int argc, char ** argv)
{
 QApplication app(argc, argv);

   mainWindow f;
   int nb = 0;
   Logger::createInstance(Logger::DEBUG);

   Logger::getInstance()->logMessage( "Lancement de l'application",Logger::INFO);
   f.init();

   Logger::getInstance()->logMessage( "Lancement fenetre...",Logger::INFO);
   f.show();

   return app.exec();
}

