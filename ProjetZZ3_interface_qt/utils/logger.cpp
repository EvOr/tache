#include "logger.hpp"
Logger * Logger::logger = NULL;
///\return l'instance de logger courante 
Logger * Logger::getInstance(){
   if(Logger::logger==NULL){
      createInstance(INFO);
   }
   return Logger::logger;
}
///\brief cree l'instance
///\param debugLevel le niveau d'affichage souhaite
void Logger::createInstance(int debugLevel){
   if(Logger::logger==NULL){
      Logger::logger=new Logger(debugLevel);
   }
}
///\brief Log le message
///\param message message
///\param level niveau de debug du message a logger
void Logger::logMessage(std::string message, int level){
   if(debugLevel<=level){
      switch(level){
	 case DEBUG:
	    std::cout << message << std::endl;
	    break;
	 case INFO:
	    std::cout << ansi::set_foreground(ansi::GREEN);
	    std::cout << message << std::endl;
	    break;
	 case ERR_UNEXP:
	    std::cerr << ansi::set_foreground(ansi::RED);
	    std::cerr << message << std::endl;
	    break;
	 default:
	    break;
      }
      std::cout << ansi::reset_textstyle();

   }
}

