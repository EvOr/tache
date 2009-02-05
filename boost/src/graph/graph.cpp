#include "graph.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include <map>
void full_mesh_detector(Graph * peers){
  // Algo = retirer les noeuds avec un seul truc voisin... esperer que ca fasse beaucoup, si possible compter et verifier l'utilite avant
  // 1 2 3 prendre la liste des voisin (out_edges je crois) 
  // 2 1 3 prendre la liste des voisins comparer avec 2
  // 3 1 2 prendre la liste des voisin comparer avec 1
  // on part du principe que tout le monde a au moins n voisins (n définis par l'appel à la fonction... 
  // coup en np pas coool ... trouver un fucking algo plus efficace !!
//   graph_traits<PeerGraph>::vertex_iterator vi, vi_end, next;
 //  tie(vi, vi_end)= vertices(peers);
  // for(next = vi ; vi != vi_end; vi=next){
    //    ++next;
//	*vi.out_edges();
	//remove_vertex(*vi, peers);
//   }
}


void copyGraph(const Graph & g, WUGraph & wug)
{
   boost::graph_traits<Graph>::vertex_iterator vit, vend;
   Graph::edge_iterator it,end;
   edge_descriptor_wu e;
   bool found = false;
   boost::property_map<WUGraph, boost::edge_weight_t>::type weightMap = get(boost::edge_weight, wug);
	std::map< Graph::vertex_descriptor , WUGraph::vertex_descriptor > mapping;


   //copie des sommets
   for( boost::tie ( vit,vend)  = boost::vertices( g ); vit != vend; ++vit)
   {
      Graph::vertex_descriptor vertex = *vit;
      WUGraph::vertex_descriptor v1 = boost::add_vertex(wug);
		mapping[vertex] = v1;
		//std::cout << vertex << "->" << v1 << std::endl;
   }

   std::cout << "graphe WUG, nodes=" << boost::num_vertices(wug) << std::endl;

   //copie des aretes
   for( boost::tie ( it,end)  = boost::edges( g ); it != end; ++it)
   {
      edge_descriptor edge = *it;
      vertex_descriptor source = boost::source(edge,g);
      vertex_descriptor target = boost::target(edge,g);
	//	std::cout << source << "," << target << " -> " <<   mapping[source] << "," << mapping[target] << std::endl;
		found = false;
      boost::tie(e,found) = boost::add_edge( mapping[source],mapping[target], wug);
//       //initialisation du poids a 1
      if(found)
         boost::put(weightMap, e, rand() % 10);
//         wug[e].weight = 1;
   }

   
}


