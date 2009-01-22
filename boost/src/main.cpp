#include <iostream>
#include <algorithm>
#include "graph/graph.hpp"
#include "exceptions/ReaderException.hpp"
#include "utils/logger.hpp"
#include "graph/file_reader.hpp"
#include "controler/controler.hpp"
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/timer.hpp>
#include <ctime>


int main(int argc , char ** argv)
{
   std::string filename;
   Graph g2;
   double t = time(0);
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

   //centrality(c.getGraph(), g2, c.getStubsVector());

    //std::cout << num_vertices(g2) << std::endl;
   std::cout << "temps de calcul " << time(0) - t << std::endl;

   return EXIT_SUCCESS;
}

