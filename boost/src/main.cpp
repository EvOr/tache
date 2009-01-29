#include <iostream>
#include <algorithm>
#include "graph/graph.hpp"
#include "exceptions/ReaderException.hpp"
#include "utils/logger.hpp"
#include "graph/file_reader.hpp"
#include "graph/bron_kerbosch.hpp"
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

<<<<<<< HEAD:boost/src/main.cpp
   std::map<vertex_descriptor, double> v_centrality;
   tableau_de_poids vc_map(v_centrality);

   std::map< vertex_descriptor , coordonnes> mescoords;
   tableau_de_coordonnees position(mescoords);
   std::cout << boost::num_vertices(c.getNonStubsGraph()) << std::endl;
//   brandes_betweenness_centrality(c.getNonStubsGraph(), vc_map);
   std::vector< std::vector<vertex_descriptor> > cliques;
   mickael::graph::bron_kerbosch_max_cliques(c.getPeersGraph(), cliques);

   std::vector< std::vector<vertex_descriptor> >::iterator it;
   std::vector<vertex_descriptor>::iterator vertex;
   int i=0;
   for( it=cliques.begin(); it != cliques.end() ; it++){
      std::vector<vertex_descriptor>::iterator adjV;
      std::cout << "------" << i++ << "------" << std::endl;
      for(adjV=(*it).begin();adjV != (*it).end(); adjV++){
	 std::cout<< *adjV << ",";
      }
      std::cout << std::endl;
   }
=======
      //test de centrality
//    std::map<vertex_descriptor, double> v_centrality;
//    tableau_de_poids vc_map(v_centrality);
// 
//    std::map< vertex_descriptor , coordonnes> mescoords;
//    tableau_de_coordonnees position(mescoords);
// 
//    brandes_betweenness_centrality(c.getNonStubsGraph(), vc_map);

>>>>>>> d0e51758dbee4f854bd0c62448936a94c72d6c9d:boost/src/main.cpp
    //std::cout << num_vertices(g2) << std::endl;
//    std::cout << "temps de calcul " << time(0) - t << std::endl;

//    std::map<vertex_descriptor, double>::iterator it;
//    int i = 0;
//    for(it = v_centrality.begin(); it != v_centrality.end(); ++it)
//    {
//       ++i;
//       if((*it).second != 0)
//          std::cout << "Vertex : " << (*it).first << ", poids : " << (*it).second << std::endl;
//    }
//    std::cout << i << " vertices classées." << std::endl;

      //test de kamada
   std::cout << "kamada spring layout" << std::endl;

<<<<<<< HEAD:boost/src/main.cpp
//   bool ok = boost::kamada_kawai_spring_layout(c.getNonStubsGraph(),position, vc_map, boost::side_length(10.0));

  // if(!ok)
    //  std::cout << "probleme de kamada !!" << std::endl;
=======

   WUGraph wug;
   copyGraph(c.getNonStubsGraph(), wug);

   circle_graph_layout( wug, boost::get(vertex_position, wug), 1.0);
   boost::graph_traits<WUGraph>::vertex_iterator vi1, vi_end1; 
   boost::property_map<WUGraph, vertex_position_t>::type positionMap1 = get(vertex_position, wug);
   for (boost::tie(vi1, vi_end1) = boost::vertices(wug); vi1 != vi_end1; ++vi1)
   {
      std::cout << " n" << get(boost::vertex_index, wug, *vi1) << "[ pos=\"" << positionMap1[*vi1].x << ", " << positionMap1[*vi1].y << "\" ];" << std::endl;
   }

>>>>>>> d0e51758dbee4f854bd0c62448936a94c72d6c9d:boost/src/main.cpp


   bool ok = boost::kamada_kawai_spring_layout(wug, boost::get(vertex_position, wug), boost::get(boost::edge_weight, wug), boost::side_length(50.0));

//    if(!ok)
//       std::cout << "probleme de kamada !!" << std::endl;
//    else
//    {
      boost::graph_traits<WUGraph>::vertex_iterator vi, vi_end; 
      boost::property_map<WUGraph, vertex_position_t>::type positionMap = get(vertex_position, wug);
      for (boost::tie(vi, vi_end) = boost::vertices(wug); vi != vi_end; ++vi)
      {
         std::cout << " n" << get(boost::vertex_index, wug, *vi) << "[ pos=\"" << positionMap[*vi].x << ", " << positionMap[*vi].y << "\" ];" << std::endl;
      }
//    }

   return EXIT_SUCCESS;
}

