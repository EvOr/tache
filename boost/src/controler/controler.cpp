#include "controler.hpp"
///\brief change le nom du fichier
///\param name nom du fichier
void Controler::change_file_name(std::string name){
   filename=name;
   graph.clear();
   file_reader.change_file_name(name);
   mescoords.clear();
  // position.clear();
}

///\brief parse le fichier
void Controler::parse_file(){
	std::cout << "parse file " << filename  << "..." << std::endl;
  file_reader.parse(graph); 
	std::cout << "num_vertices:" << boost::num_vertices(graph) << std::endl;

}

///\brief permet d'obtenir une position map en forme de cercle depuis une matrice d'adjacence en vue de l'affichage du graphe avec QT
///\param r rayon du cercle
int Controler::displayCircle(double r)
{
   std::ostringstream nb;
   nb << num_vertices(graph);
   Logger::getInstance()->logMessage( "nombre de sommets : " + nb.str(), Logger::DEBUG);
   //fonction boost pour generer la position map
   circle_graph_layout( graph, position, r);
   std::map<vertex_descriptor, double> v_centrality;
   tableau_de_poids vc_map(v_centrality);
//   brandes_betweenness_centrality(graph, vc_map);
   return 0;

}

