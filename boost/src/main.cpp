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

   std::map<vertex_descriptor, double> v_centrality;
   tableau_de_poids vc_map(v_centrality);

   std::map< vertex_descriptor , coordonnes> mescoords;
   tableau_de_coordonnees position(mescoords);

   brandes_betweenness_centrality(c.getNonStubsGraph(), vc_map);

    //std::cout << num_vertices(g2) << std::endl;
   std::cout << "temps de calcul " << time(0) - t << std::endl;

//    std::map<vertex_descriptor, double>::iterator it;
//    int i = 0;
//    for(it = v_centrality.begin(); it != v_centrality.end(); ++it)
//    {
//       ++i;
//       if((*it).second != 0)
//          std::cout << "Vertex : " << (*it).first << ", poids : " << (*it).second << std::endl;
//    }
//    std::cout << i << " vertices classées." << std::endl;

   std::cout << "kamada spring layout" << std::endl;

   bool ok = boost::kamada_kawai_spring_layout(c.getNonStubsGraph(),position, vc_map, boost::side_length(10.0));

   if(!ok)
      std::cout << "probleme de kamada !!" << std::endl;


   return EXIT_SUCCESS;
}

