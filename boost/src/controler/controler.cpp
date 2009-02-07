#include "controler.hpp"
///\brief change le nom du fichier
///\param name nom du fichier
void Controler::change_file_name(std::string name){
   filename=name;
   graph.clear();
   mescoords.clear();
   // position.clear();
}

///\brief parse le fichier
void Controler::parse_file(){
   std::cout << "parse file " << filename  << "..." << std::endl;
   parse(filename, graph); 
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

///\brief Parse le fichier de triplet afin d'affecter si oui ou non un AS(vertex) est un transit
///\param filename nom du fichier de triplet
void Controler::load_triplet(std::string const & filename){
   std::set<std::size_t> transit_as;
   std::set<std::size_t>::iterator it;
   Graph::vertex_descriptor v;
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   std::set<std::size_t>::const_iterator found; 
   
   read_triplet(filename,transit_as);
   //Parcours du graph
   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      found=transit_as.find(*vit);
      v=*vit;
      //Affectation de la propriété transit
      graph[v].is_transit=(found == transit_as.end())?false:true; 
   }
}

