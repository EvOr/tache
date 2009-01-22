#include "graph.hpp"
#include "utils/logger.hpp"
#include <sstream>
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

void centrality(const Graph & g, Graph & g2, std::vector<vertex_descriptor> vd)
{
   std::vector<vertex_descriptor>::iterator it;
   int i = 0;
std::cout << "il y a " << vd.size() << " feuilles a retirer" << std::endl;

   g2 = g;


}



