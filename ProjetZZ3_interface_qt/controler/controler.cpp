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
  file_reader.parse(graph); 

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

   //remplissage des liens
   Graph::edge_iterator it,end;

   for( boost::tie ( it,end)  = boost::edges( graph ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,graph);
      vertex_descriptor target = boost::target(edge,graph);
      std::pair<vertex_descriptor, vertex_descriptor> p(source, target);
      liens.push_back(p);
   }

   return 0;

}

/// \brief permet d'obtenir une position map pour placer les points selon KamadaKawaiSpringLayout
bool Controler::displayKamada()
{
   bool retour;

   WUGraph wug;
   copyGraph(getNonStubsGraph(), wug);

   circle_graph_layout( wug, boost::get(vertex_position, wug), 1.0);

   retour = boost::kamada_kawai_spring_layout(wug, boost::get(vertex_position, wug), boost::get(boost::edge_weight, wug), boost::side_length(50.0));

   //remplissage de la map de coordonnées
   mescoords.clear();
   boost::graph_traits<WUGraph>::vertex_iterator vi, vi_end; 
   boost::property_map<WUGraph, vertex_position_t>::type positionMap = get(vertex_position, wug);
   for (boost::tie(vi, vi_end) = boost::vertices(wug); vi != vi_end; ++vi)
   {
      coordonnes c;
      c.x = positionMap[*vi].x;
      c.y = positionMap[*vi].y;
      std::pair< vertex_descriptor , coordonnes> p(get(boost::vertex_index, wug, *vi), c);
      mescoords.insert(p);
   }

   return retour;
}

