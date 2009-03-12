#include "controler.hpp"
///\brief change le nom du fichier
///\param name nom du fichier
void Controler::change_file_name(std::string name){
   filename=name;
   graph.clear();
   mescoords.clear();
   clique.clear();
   mespoids.clear();
   // position.clear();
}

///\brief parse le fichier
void Controler::parse_file()
{
   parse(filename, graph); 

   //parcours pour voir le nombre max d'AS
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   int n = 0;
   nbAS = 0;
   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      n = graph[*vit].asn;
      if(n > nbAS)
         nbAS = n;
   }
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
   // bool retour;

   // WUGraph wug;
   //   copyGraph(getNonStubsGraph(), wug);

   //copyGraph_noStub(graph,wug);
   //   circle_graph_layout( wug, boost::get(vertex_position, wug), 1.0);

   // retour = boost::kamada_kawai_spring_layout(wug, boost::get(vertex_position, wug), boost::get(boost::edge_weight, wug), boost::side_length(50.0));

   //remplissage de la map de coordonnées
   // mescoords.clear();
   // boost::graph_traits<WUGraph>::vertex_iterator vi, vi_end; 
   // boost::property_map<WUGraph, vertex_position_t>::type positionMap = get(vertex_position, wug);
   // for (boost::tie(vi, vi_end) = boost::vertices(wug); vi != vi_end; ++vi)
   // {
   //   coordonnes c;
   //  c.x = positionMap[*vi].x;
   // c.y = positionMap[*vi].y;
   // std::pair< vertex_descriptor , coordonnes> p(get(boost::vertex_index, wug, *vi), c);
   //  mescoords.insert(p);
   // }

   //   return retour;
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
   int i=0;
   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      v=*vit;
      //      int asnumber=graph[].as
      found=transit_as.find(graph[v].asn);
      //Affectation de la propriété transit
      graph[v].is_transit=(found == transit_as.end())?false:true; 

      if(graph[v].is_transit)
	 i++;
   }
   std::cout<< i << std::endl;
}

void Controler::getNonStubsGraph(Graph & g2)
{
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::edge_iterator it,end;
   edge_descriptor e;
   bool found;

   //mapping
   typedef  std::map< int ,  Graph::vertex_descriptor> as_number_to_vertex_type;
   as_number_to_vertex_type as_number_to_vertex;
   std::map< Graph::vertex_descriptor , Graph::vertex_descriptor > mapping;

   //copie des sommets
   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      Graph::vertex_descriptor vertex = *vit;
      if(graph[vertex].is_transit == true)
      {
	 Graph::vertex_descriptor v1 = boost::add_vertex(g2);
	 //mise a jour infos pour nouveau sommet
	 g2[v1].asn = graph[vertex].asn;
	 g2[v1].is_transit = graph[vertex].is_transit;
	 //on garde trace des AS ajoutés nouveau graph pour pouvoir ensuite ajouter que les aretes qui les relient
	 as_number_to_vertex[graph[vertex].asn] = vertex;
	 //on garde trave des correspondances de sommet pour pouvoir faire les aretes car bien qu'étant de meme type, les vertex descriptor appartiennent a leur graphe respectif
	 mapping[vertex] = v1;
      }
   }

   //copie des aretes
   for( boost::tie ( it,end)  = boost::edges( graph ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,graph);
      vertex_descriptor target = boost::target(edge,graph);
      //si les deux sommets ont été ajouté précédémment, on ajoute l'arete qui les relie
      as_number_to_vertex_type::const_iterator found_i1 =  as_number_to_vertex.find(graph[source].asn);
      as_number_to_vertex_type::const_iterator found_i2 =  as_number_to_vertex.find(graph[target].asn);
      if(found_i1 != as_number_to_vertex.end() && found_i2 != as_number_to_vertex.end())
      {
	 boost::tie(e,found) = boost::add_edge(mapping[source], mapping[target], g2);
	 g2[e].link_type = graph[edge].link_type;
	 g2[e].weight = graph[edge].weight;
      }
   }

   noStubGraph = g2;
}

void Controler::getGraphWeightInf(int i, Graph & g2)
{
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::edge_iterator it,end;
   edge_descriptor e;
   bool found;

   //mapping
   typedef  std::map< int ,  Graph::vertex_descriptor> as_number_to_vertex_type;
   as_number_to_vertex_type as_number_to_vertex;
   std::map< Graph::vertex_descriptor , Graph::vertex_descriptor > mapping;

   //copie des sommets
   for( boost::tie ( vit,vend)  = boost::vertices( noStubGraph ); vit != vend; ++vit)
   {
      std::map<vertex_descriptor, double>::iterator it = mespoids.find(*vit);
      if(it->second < i)
      {
         Graph::vertex_descriptor vertex = *vit;
         Graph::vertex_descriptor v1 = boost::add_vertex(g2);
         //mise a jour infos pour nouveau sommet
         g2[v1].asn = noStubGraph[vertex].asn;
         g2[v1].is_transit = noStubGraph[vertex].is_transit;
         //on garde trace des AS ajoutés nouveau graph pour pouvoir ensuite ajouter que les aretes qui les relient
         as_number_to_vertex[noStubGraph[vertex].asn] = vertex;
         //on garde trave des correspondances de sommet pour pouvoir faire les aretes car bien qu'étant de meme type, les vertex descriptor appartiennent a leur graphe respectif
         mapping[vertex] = v1;
      }
   }

   //copie des aretes
   for( boost::tie ( it,end)  = boost::edges( noStubGraph ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,noStubGraph);
      vertex_descriptor target = boost::target(edge,noStubGraph);
      //si les deux sommets ont été ajouté précédémment, on ajoute l'arete qui les relie
      as_number_to_vertex_type::const_iterator found_i1 =  as_number_to_vertex.find(noStubGraph[source].asn);
      as_number_to_vertex_type::const_iterator found_i2 =  as_number_to_vertex.find(noStubGraph[target].asn);
      if(found_i1 != as_number_to_vertex.end() && found_i2 != as_number_to_vertex.end())
      {
	 boost::tie(e,found) = boost::add_edge( mapping[source], mapping[target], g2);
	 g2[e].link_type = noStubGraph[edge].link_type;
	 g2[e].weight = noStubGraph[edge].weight;
      }
   }
std::cout << num_vertices(g2) << " " << num_edges(g2) << std::endl;
}

void Controler::getGraphWeightSup(int i, Graph & g2)
{
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::edge_iterator it,end;
   edge_descriptor e;
   bool found;

   //mapping
   typedef  std::map< int ,  Graph::vertex_descriptor> as_number_to_vertex_type;
   as_number_to_vertex_type as_number_to_vertex;
   std::map< Graph::vertex_descriptor , Graph::vertex_descriptor > mapping;

   //copie des sommets
   for( boost::tie ( vit,vend)  = boost::vertices( noStubGraph ); vit != vend; ++vit)
   {  
      std::map<vertex_descriptor, double>::iterator it = mespoids.find(*vit);
      if(it->second >= i)
      {
         Graph::vertex_descriptor vertex = *vit;
         Graph::vertex_descriptor v1 = boost::add_vertex(g2);
         //mise a jour infos pour nouveau sommet
         g2[v1].asn = noStubGraph[vertex].asn;
         g2[v1].is_transit = noStubGraph[vertex].is_transit;
         //on garde trace des AS ajoutés nouveau graph pour pouvoir ensuite ajouter que les aretes qui les relient
         as_number_to_vertex[noStubGraph[vertex].asn] = vertex;
         //on garde trave des correspondances de sommet pour pouvoir faire les aretes car bien qu'étant de meme type, les vertex descriptor appartiennent a leur graphe respectif
         mapping[vertex] = v1;
      }
   }

   //copie des aretes
   for( boost::tie ( it,end)  = boost::edges( noStubGraph ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,noStubGraph);
      vertex_descriptor target = boost::target(edge,noStubGraph);
      //si les deux sommets ont été ajouté précédémment, on ajoute l'arete qui les relie
      as_number_to_vertex_type::const_iterator found_i1 =  as_number_to_vertex.find(noStubGraph[source].asn);
      as_number_to_vertex_type::const_iterator found_i2 =  as_number_to_vertex.find(noStubGraph[target].asn);
      if(found_i1 != as_number_to_vertex.end() && found_i2 != as_number_to_vertex.end())
      {
	 boost::tie(e,found) = boost::add_edge( mapping[source], mapping[target], g2);
	 g2[e].link_type = noStubGraph[edge].link_type;
	 g2[e].weight = noStubGraph[edge].weight;
      }
   }
std::cout << num_vertices(g2) << " " << num_edges(g2) << std::endl;
}

void Controler::getGraphAsNumInf(int i, Graph & g2)
{
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::edge_iterator it,end;
   edge_descriptor e;
   bool found;

   //mapping
   typedef  std::map< int ,  Graph::vertex_descriptor> as_number_to_vertex_type;
   as_number_to_vertex_type as_number_to_vertex;
   std::map< Graph::vertex_descriptor , Graph::vertex_descriptor > mapping;

   //copie des sommets
   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      Graph::vertex_descriptor vertex = *vit;
      if(graph[vertex].asn < i)
      {
	 Graph::vertex_descriptor v1 = boost::add_vertex(g2);
	 //mise a jour infos pour nouveau sommet
	 g2[v1].asn = graph[vertex].asn;
	 g2[v1].is_transit = graph[vertex].is_transit;
	 //on garde trace des AS ajoutés nouveau graph pour pouvoir ensuite ajouter que les aretes qui les relient
	 as_number_to_vertex[graph[vertex].asn] = vertex;
	 //on garde trave des correspondances de sommet pour pouvoir faire les aretes car bien qu'étant de meme type, les vertex descriptor appartiennent a leur graphe respectif
	 mapping[vertex] = v1;
      }
   }

   //copie des aretes
   for( boost::tie ( it,end)  = boost::edges( graph ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,graph);
      vertex_descriptor target = boost::target(edge,graph);
      //si les deux sommets ont été ajouté précédémment, on ajoute l'arete qui les relie
      as_number_to_vertex_type::const_iterator found_i1 =  as_number_to_vertex.find(graph[source].asn);
      as_number_to_vertex_type::const_iterator found_i2 =  as_number_to_vertex.find(graph[target].asn);
      if(found_i1 != as_number_to_vertex.end() && found_i2 != as_number_to_vertex.end())
      {
	 boost::tie(e,found) = boost::add_edge( mapping[source], mapping[target], g2);
	 g2[e].link_type = graph[edge].link_type;
	 g2[e].weight = graph[edge].weight;
      }
   }
}

void Controler::getGraphAsNumSup(int i, Graph & g2)
{
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::edge_iterator it,end;
   edge_descriptor e;
   bool found;

   //mapping
   typedef  std::map< int ,  Graph::vertex_descriptor> as_number_to_vertex_type;
   as_number_to_vertex_type as_number_to_vertex;
   std::map< Graph::vertex_descriptor , Graph::vertex_descriptor > mapping;

   //copie des sommets
   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      Graph::vertex_descriptor vertex = *vit;
      if(graph[vertex].asn >= i)
      {
	 Graph::vertex_descriptor v1 = boost::add_vertex(g2);
	 //mise a jour infos pour nouveau sommet
	 g2[v1].asn = graph[vertex].asn;
	 g2[v1].is_transit = graph[vertex].is_transit;
	 //on garde trace des AS ajoutés nouveau graph pour pouvoir ensuite ajouter que les aretes qui les relient
	 as_number_to_vertex[graph[vertex].asn] = vertex;
	 //on garde trave des corrnespondances de sommet pour pouvoir faire les aretes car bien qu'étant de meme type, les vertex descriptor appartiennent a leur graphe respectif
	 mapping[vertex] = v1;
      }
   }

   //copie des aretes
   for( boost::tie ( it,end)  = boost::edges( graph ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,graph);
      vertex_descriptor target = boost::target(edge,graph);
      //si les deux sommets ont été ajouté précédémment, on ajoute l'arete qui les relie
      as_number_to_vertex_type::const_iterator found_i1 =  as_number_to_vertex.find(graph[source].asn);
      as_number_to_vertex_type::const_iterator found_i2 =  as_number_to_vertex.find(graph[target].asn);
      if(found_i1 != as_number_to_vertex.end() && found_i2 != as_number_to_vertex.end())
      {
      	boost::tie(e,found) = boost::add_edge( mapping[source], mapping[target], g2);
      	g2[e].link_type = graph[edge].link_type;
	      g2[e].weight = graph[edge].weight;
      }
   }
}

void Controler::getFirstNeighbors(int i, Graph & g2)
{
   Graph::edge_iterator it,end;
   edge_descriptor e;
   bool found;
   //int k = 0;


   //ajout de l'AS
   Graph::vertex_descriptor myVertex = findAS(i);
   Graph::vertex_descriptor v1 = boost::add_vertex(g2);
   //mise a jour infos pour nouveau sommet
   g2[v1].asn = graph[myVertex].asn;
   g2[v1].is_transit = graph[myVertex].is_transit;

   for( boost::tie ( it,end)  = boost::edges( graph ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,graph);
      vertex_descriptor target = boost::target(edge,graph);     
 
      if(graph[source].asn == i)
      {
         //ajout du sommet
         Graph::vertex_descriptor v2 = boost::add_vertex(g2);
         g2[v2].asn = graph[target].asn;
         g2[v2].is_transit = graph[target].is_transit;
         //ajout du lien
	      boost::tie(e,found) = boost::add_edge( v1, v2, g2);
	      g2[e].link_type = graph[edge].link_type;
	      g2[e].weight = graph[edge].weight;
      }
      else if(graph[target].asn == i)
      {
         //ajout du sommet
         Graph::vertex_descriptor v2 = boost::add_vertex(g2);
         g2[v2].asn = graph[source].asn;
         g2[v2].is_transit = graph[source].is_transit;
         //ajout du lien
	      boost::tie(e,found) = boost::add_edge( v2, v1, g2);
	      g2[e].link_type = graph[edge].link_type;
	      g2[e].weight = graph[edge].weight;
      }
   }
}

Graph::vertex_descriptor Controler::findAS(int i)
{
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::vertex_descriptor ret = -1;

   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      //Graph::vertex_descriptor vertex = *vit;
      if(graph[*vit].asn == i)
      {
         //std::cout << "trouve" << std::endl;
         ret = *vit;
         break;
      }
   }

   return ret;
}

void Controler::getSubGraph(int i, int j)
{
   Graph g2;
   switch(j)
   {
      case 0 : getNonStubsGraph(g2); break;
      case 1 : getGraphWeightInf(i, g2); break;
      case 2 : getGraphWeightSup(i, g2); break;
      case 3 : getGraphAsNumInf(i, g2); break;
      case 4 : getGraphAsNumSup(i, g2); break;
      case 5 : getFirstNeighbors(i, g2); break;
   }

   
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::edge_iterator it,end;
   edge_descriptor e;

   liens_tmp.clear();
   mescoords_tmp.clear();

   //stockage des arêtes
   circle_graph_layout( g2, position_tmp, 1.5);

   //stockage des liens
   for( boost::tie ( it,end)  = boost::edges( g2 ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,g2);
      vertex_descriptor target = boost::target(edge,g2);
      std::pair<vertex_descriptor, vertex_descriptor> p(source, target);
      liens_tmp.push_back(p);
   }
}


void Controler::computeClique()
{
   if(clique.size() == 0)
   {
   	mickael::graph::bron_kerbosch_max_cliques(noStubGraph, clique);
   }
}


void Controler::computeCentrality()
{
   tableau_de_poids vc_map(mespoids);
//std::cout << "calcul centrality" << std::endl;
   brandes_betweenness_centrality(noStubGraph, vc_map);
//std::cout << mespoids.size() << std::endl;
//std::map<vertex_descriptor, double>::iterator it;
//for(it = mespoids.begin(); it != mespoids.end(); ++it)
//{
//   std::cout << it->first << " " << it->second << std::endl;
//}   
}

std::string Controler::getInfoAS(int i)
{
   std::string s = "";

   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::vertex_descriptor vd1 = -1, vd2 = -1;

   std::ostringstream out;
   out << i;

   for( boost::tie ( vit,vend)  = boost::vertices( graph ); vit != vend; ++vit)
   {
      if(graph[*vit].asn == i)
      {
         vd1 = *vit;
         break;
      }
   }

   for( boost::tie ( vit,vend)  = boost::vertices( noStubGraph ); vit != vend; ++vit)
   {
      if(graph[*vit].asn == i)
      {
         vd2 = *vit;
         break;
      }
   }

   if(vd1 != -1)
   {
      s += "As number :\t" + out.str() + "\n";
      if(vd2 != -1)
      {
         s += "type :\t" + (graph[vd1].is_transit)?"\ttransit\n":"\tstub\n";  
         std::ostringstream out2;
         out2 << mespoids[vd2];
         s += "Centrality :\t" + out2.str();
      }
      else
         s += "type :\tunknown"; 
      }
   else
      s = "No such AS " + out.str();
   
return s;
}


