#include <iostream>
#include <algorithm>
#include "graph/graph.hpp"
#include "exceptions/ReaderException.hpp"
#include "utils/logger.hpp"
#include "graph/file_reader.hpp"
#include "controler/controler.hpp"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/timer.hpp>


int main(int argc , char ** argv)
{
   std::string filename;
   Logger::createInstance(Logger::DEBUG);
   if(argc > 1)
      filename = argv[1];
   else
   {
      Logger::getInstance()->logMessage( "usage : nom_executable nom_fichier",Logger::ERR_UNEXP);
      exit(0);
   }

   Controler c(filename);
   try{
      c.parse_file();
   }catch(ReaderException & e){
      if(e.getType()==ReaderException::CRITICAL){
	 Logger::getInstance()->logMessage(e.display(),Logger::ERR_UNEXP);
	 return 1;
      }else{
	 Logger::getInstance()->logMessage(e.display(),Logger::ERR_UNEXP);
      }
   }
   c.displayCircle(1.5);
   return EXIT_SUCCESS;
}

