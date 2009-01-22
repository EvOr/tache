#ifndef MICKAEL_GRAPH___BRON_KERBOSCH__HPP
#define MICKAEL_GRAPH___BRON_KERBOSCH__HPP

#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/utility.hpp>

// La classe DetectClique (trouvee sur la mailing-list boost) implemente 
// l'algorithme 457 de Bron&Kerbosch. Cette classe ne doit pas etre utilisee
//  directement, passer par la fonction bron_kerbosch_max_cliques qui 
// respecte un peu plus la genericite du Graphe (vertex_descriptor plutot 
// que int). 

// Restriction sur le graphe: les vertex_descriptor doivent etre des entiers
//  (typiquement adjacency_list<vecS, vecS).

// TODO: modifier la classe DetectClique pour adaptation a un graphe quelconque
//       parametres de la fonction bron_kerbosch_max_cliques ?

namespace mickael { namespace graph {

   template <class Graph> class DetectClique;

   template <typename Graph>
      std::size_t 
      bron_kerbosch_max_cliques(
	    const Graph& g, 
	    std::vector< std::vector<typename Graph::vertex_descriptor> > & cliques,
	    std::size_t max = 0,
	    bool check = true)
      {
	 if(max == 0)
	    max = num_vertices(g);
	 DetectClique<Graph> clique_finder(g, max, check);
	 clique_finder.start_detection();

	 std::size_t total = clique_finder.get_max_cliques().size();
	 cliques.resize(total);
	 for(std::size_t i=0; i<total; i++)
	 {
	    cliques[i].assign(clique_finder.get_max_cliques()[i].begin(), 
		  clique_finder.get_max_cliques()[i].end());
	 }

	 return total;
      }

   //----------------------------------------------------------------------

   template <class Graph>
      class DetectClique : boost::noncopyable
   {
      public:
	 typedef std::size_t size_type;

	 // Constructor
	 DetectClique(const Graph& graph, size_type max_, bool check_) 
	    : G(graph), 
	    max_count(max_),
	    check_max(check_) {};

	 // Methode to start the clique detection
	 void start_detection() {
	    reached_max_count = false;
	    count = 0;
	    Cmax = 0;
	    size_type N = num_vertices(G);

	    // Initialize the array 'all'
	    std::vector<size_type> all (N, 0); // 1..N
	    for (size_type i = 0; i < N; i++) all [i] = i;
	    extend(all, 0, N);
	 }

	 // Get all maximal cliques of graph G
	 const std::vector< std::vector<size_type> >& get_max_cliques() {
	    return Cliques;
	 }

      private:
	 // Check if two vertices are connected
	 bool is_connected(size_type a, size_type b) {
	    // In the Bron/Kerbosch Algorithm identical
	    // vertices are connected!!!
	    if (a == b) {
	       return true;
	    }
	    // Check if connection between vertex a and b exists
	    if ((edge(a,b,G)).second) {
	       return true;
	    }
	    return false;
	 }

	 // Recursive extension of a clique
	 void extend(std::vector<size_type> old_set, size_type ne, size_type ce) {
	    if (reached_max_count) {
	       return;
	    }
	    size_type fixp = 0;
	    size_type s;
	    size_type minnod = ce;
	    size_type nod = 0;

	    // Determine each counter value and look for minimum
	    for (size_type i = 0; i < ce && minnod != 0; i++) {
	       size_type p = old_set[i];
	       size_type count = 0;
	       size_type pos;

	       // Count disconnections of the vertices
	       for (size_type j = ne; j < ce && count < minnod; j++) {
		  if (!is_connected(p,old_set[j])) {
		     count++;
		     // Save position of potential candidate
		     pos = j;
		  }
	       }

	       // Test new minimum
	       if (count < minnod) {
		  minnod = count;
		  fixp = p;

		  if (i < ne) {
		     s = pos;
		  } else {
		     s = i;
		     // Preincrement nod
		     nod = 1;
		  }
	       }
	    }

	    // If fixed point initially chosen from 'candidates' then
	    // number of disconnections will be preincreased by one

	    // Backtrackcycle
	    for (nod += minnod; nod >= 1; nod--) {
	       // Interchange
	       size_type p = old_set[s];
	       old_set[s] = old_set[ne];
	       old_set[ne] = p;

	       size_type sel = old_set[ne];

	       // Fill new set 'not'
	       std::vector<size_type> new_set; // 1..ce
	       new_set.reserve(ce);
	       size_type new_ne = 0;
	       for (size_type i = 0; i < ne; i++) {
		  if (is_connected(sel,old_set[i])) {
		     new_set.push_back(old_set[i]);
		     new_ne++;
		  }
	       }

	       // Fill new set 'candidates'
	       size_type new_ce = new_ne;
	       for (size_type i = ne + 1; i < ce; i++) {
		  if (is_connected(sel,old_set[i])) {
		     new_set.push_back(old_set[i]);
		     new_ce++;
		  }
	       }

	       // Add to 'complete_subgraph'
	       complete_subgraph.push_back(sel);

	       if (new_ce == 0) {
		  // Handle found clique
		  count++;
		  if (complete_subgraph.size() > Cmax) { 
		     // New maximal clique found
		     Cmax = complete_subgraph.size();
		     Cliques.clear();
		     Cliques.push_back(complete_subgraph);
		  } else if (complete_subgraph.size() == Cmax) {
		     // Clique with equal size of old clique found
		     Cliques.push_back(complete_subgraph);
		  }

		  // Number of maximum iterations exceeded
		  if (check_max && count >= max_count) {
		     reached_max_count = true;
		     return;
		  }
	       } else {
		  if (new_ne < new_ce) {
		     extend(new_set, new_ne, new_ce);
		  }
	       }

	       // Remove vertex from 'complete_subgraph'
	       complete_subgraph.pop_back();

	       // Add to 'not'
	       ne++;

	       // Select a candidate disconnected to the fixed point
	       if (nod > 1) {
		  s = ne;
		  while (is_connected(fixp,old_set[s])) {
		     s++;
		  }
	       }
	    } // end of backtrackcycle
	 }

	 // Vector which contains the actual clique
	 std::vector<size_type> complete_subgraph; // behaves like a stack

	 // Graph to detect cliques
	 const Graph& G;
	 bool reached_max_count; // Flag to signal if the maximal count is reached
	 size_type Cmax;         // Size of maximum clique
	 size_type count;        // Clique counter
	 size_type max_count;    // Maximum number of cliques to detect
	 bool check_max;         // Check for a maximum number if check_max is true
	 std::vector<std::vector<size_type> > Cliques; // Cliques with maximum
	 // number of vertices

   };

   //----------------------------------------------------------------------

} } // namespace graph, namespace mickael

#endif /* MICKAEL_GRAPH___BRON_KERBOSCH__HPP */
