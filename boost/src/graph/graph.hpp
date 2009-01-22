#ifndef ____GRAPH_HPP__
#define ____GRAPH_HPP__

#include <algorithm>
#include <vector>
#include <utility>
#include <stdexcept>
#include <boost/operators.hpp>
#include <boost/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/circle_layout.hpp>
#include <boost/graph/betweenness_centrality.hpp>
struct AS : boost::totally_ordered< AS >
{
   typedef int value_type;
   typedef int key_type;
   typedef int reference;
   typedef int category;

   value_type value;
   AS(int _asn = 0) : value(_asn){}

   inline bool operator<(AS const & o) const
   {
      return this->value < o.value;
   }

   inline bool operator==(AS const & o) const
   {
      return this->value == o.value;
   } 
};

struct ASLink
{
   ASLink( std::size_t myw = 0) 
      : weight(myw)
   {}	
   std::size_t weight;
};

//graphe par liste d'adjacence
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, AS, ASLink> Graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, AS, ASLink> PeerGraph;
//TODO
//typedef boost::adjacency_list<boost::listS, boost::listS, boost::undirectedS, AS, ASLink> PeerGraph;
typedef Graph::vertex_descriptor vertex_descriptor;
typedef Graph::edge_descriptor edge_descriptor;

//graphe par matrice d'adjacence
typedef boost::adjacency_matrix<boost::directedS> AMatrix;

//positionmap pour les algo de placement automatique
// typedef boost::property_map<AMatrix, boost::vertex_index_t> PositionMap;
struct coordonnes	
{
   coordonnes() : x(0),y(0) {}
   double x;
   double y;
};

struct tableau_de_coordonnees
: public boost::put_get_helper< coordonnes &,tableau_de_coordonnees >
{
   typedef std::map< vertex_descriptor , coordonnes>  C;
   public:

   typedef  C::key_type key_type;
   typedef  C::value_type::second_type value_type;
   typedef  C::value_type::second_type & ref;
   typedef const   C::value_type::second_type & const_ref;
   typedef boost::lvalue_property_map_tag category;

   tableau_de_coordonnees() : m_p(0) { }
   tableau_de_coordonnees( C & c) : m_p(&c) {}

   inline ref operator[] (const key_type & k) const {
      assert(m_p!=0);
      if(m_p == 0) throw std::runtime_error("no matrix");
      return (*m_p)[k];
   }
   private:
   C * m_p;
};


struct tableau_de_poids
: public boost::put_get_helper< double&,tableau_de_poids >
{
   typedef std::map< vertex_descriptor , double>  C;
   public:

   typedef  C::key_type key_type;
   typedef  C::value_type::second_type value_type;
   typedef  C::value_type::second_type & ref;
   typedef C::value_type::second_type & reference;
   typedef const   C::value_type::second_type & const_ref;
   typedef boost::lvalue_property_map_tag category;

   tableau_de_poids() : m_p(0) { }
   tableau_de_poids( C & c) : m_p(&c) {}

   inline ref operator[] (const key_type & k) const {
      assert(m_p!=0);
      if(m_p == 0) throw std::runtime_error("no matrix");
      return (*m_p)[k];
   }
   private:
   C * m_p;
};



//fonction de file_reader_boost.cpp
//int retrieveNbPointFile(std::ifstream & inIf);
//void reader(std::string inFile, AMatrix ** m, Graph ** g);
//void initVertex(Graph * g, int i);
//void addEdge(int i1, int i2, std::string linkType, bool & found, edge_descriptor & e, Graph ** g, std::vector<int> * peers);
//void addToPeersVector(std::vector<int> * peers, int i1, int i2);
//fonction de graph.cpp

void centrality(const Graph & g, Graph & g2, std::vector<vertex_descriptor> vd);

#endif
