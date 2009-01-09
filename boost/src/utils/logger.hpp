#ifndef LOGGER_hpp
#define LOGGER_hpp 

#include <iostream>
#include <string>
#include <fstream>
#include "ansi.h"
// Objet Pattern Singleton
// Cr�er par l'instance principale du programme
// Ecrit dans un fichier .log et en console l'�volution du programme
// Il prendre � chaque fois en param�tre une constante qui d�finit l'importance du message
// Celle-ci permet d'afficher les messages en couleurs en fonction et de fixer des niveaux de debugging
class Logger{
   public:
      static Logger * getInstance();
      static void createInstance(int debugLevel);
      enum {DEBUG,INFO,ERR_UNEXP};
      void logMessage(std::string message, int debug);
   protected:
      static Logger * logger;
      int debugLevel;
      std::ofstream file; 
   private:
      Logger(int dl):debugLevel(dl),file(".log"){;};
      //      logMessage(Exception exception, int debug);

};

#endif
