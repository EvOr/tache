#include "file_reader.hpp"

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

typedef  std::map< int ,  Graph::vertex_descriptor> as_number_to_vertex_type;

/// \brief Ajoute une arette
/// \param v vertex_descriptor du premier noeud a ajouter 
/// \param vv vertex_descriptor du deuxieme noeud a ajouter
/// \param type type d'arrete
/// \param linkType descripteur du type d'arrete
/// \param found booleen resultat
/// \param e edge_descriptor de l'arrete
/// \param g Graph ou il faut ajouter la relation
/// \return le type de point
int add_edge(vertex_descriptor const & v, vertex_descriptor const & vv, int & type, std::string const & linkType, bool & found, edge_descriptor & e, Graph & g){
   // found a false permet si erreur de typage sur le type de l'un des nodes de throw l'exception en fin de boucle...
   found=false;
   //si on veut mettre des poids
   // 		if(found) (**g)[e].weight = xx%13 * 2 + 5;
   if(linkType=="PEER"){
      // Pas besoin d'ajouter deux fois parce que les arcs en PEER sont presents en double
      boost::tie(e,found) = boost::add_edge( v,vv,g);
      type=PEER;
      //  boost::tie(e,found) = boost::add_edge(vv,v,g);
      // Peer vers Client
   }else if(linkType=="C2P"){
      boost::tie(e,found) = boost::add_edge(vv,v,g);
      type=C2P;
   }else if(linkType=="P2C"){
      boost::tie(e,found) = boost::add_edge(v,vv,g);
      type=P2C;
   }
   // Ajout a l'adjacence du currentVertex -> NON vous avez ça grace à la structure du graphe, suffit d'iterer dessus
}


/// \brief Creation des noeuds si ceux-ci n'existent pas, sinon mise à jour des vertex_descriptor en fonction de l'index au prealable enregistre
/// \param parts ensemble des chaines consitant la ligne parsee
/// \param v vertex_descriptor a mettre a jour en fonction de parts[0]
/// \param vv vertex_descriptor a mettre a jour en fonction de parts[1]
/// \param as_number_to_vertex map contenant la correspondance index -> numero d'AS
/// \param g graph sur lequel les vertices seront rajouter
void create_vertices_from_line(std::vector<std::string> const & parts, vertex_descriptor & v, vertex_descriptor & vv, as_number_to_vertex_type & as_number_to_vertex, Graph & g){
   int i1,i2;
   
   i1 = boost::lexical_cast<int>( parts.at(0) );
   i2 = boost::lexical_cast<int>( parts.at(1) );
   
   as_number_to_vertex_type::const_iterator found_i1 =  as_number_to_vertex.find(i1);
   if( found_i1 == as_number_to_vertex.end())
   {
      v = boost::add_vertex(g);
      as_number_to_vertex[i1] = v;
      g[v].asn=i1;
   }
   else v = found_i1->second;

   as_number_to_vertex_type::const_iterator found_i2 =  as_number_to_vertex.find(i2);
   if( found_i2 == as_number_to_vertex.end())
   {
      vv = boost::add_vertex(g);
      as_number_to_vertex[i2] = vv;
      g[vv].asn=i2;
   }
   else vv = found_i2->second;

}

/// \brief Fonction de lecture du fichier d'adjacence
/// \param g Matrice d'adjacence Ã  remplir
/// \throws ReaderException when an error occurs
void parse(std::string const & filename, Graph & g)
{
   bool line_error = false, found= false;
   edge_descriptor e;
   std::string line;
   vertex_descriptor v,vv ;
   int type;
   //mapping
   as_number_to_vertex_type as_number_to_vertex;
   typedef boost::tokenizer< boost::char_separator<char> >   tokenizer;
   boost::char_separator<char> sep("\t");

   try
   {
      std::ifstream file(filename.c_str());

      if( file.is_open() )
      {
	 //remplissage de la matrice
	 while(std::getline(file, line)) {
	    tokenizer tokens(line, sep);
	    std::vector<std::string> parts(tokens.begin(), tokens.end());
	    if( parts.size() == 3)
	    {
	       create_vertices_from_line(parts, v, vv, as_number_to_vertex, g);
	       add_edge(v, vv, type, parts.at(2), found, e, g);
	       if(found) g[e].link_type = type;
	       else line_error=true;
	    }
	    else line_error=true;
	 }
	 file.close();
      }
      else{
	 throw ReaderException("Fichier inexistant ou non lisible", filename,ReaderException::CRITICAL);
      }
   }
   catch(const std::exception & e)
   {
      throw ReaderException("Erreur lors de la lecture du fichier", filename, ReaderException::CRITICAL);
   }

   if(line_error)
   {
      throw ReaderException("Erreur lors de la lecture d'une ou plusieurs ligne", filename, ReaderException::NON_BLOCKING);
   }
   std::cout << "num vertex:" << boost::num_vertices(g) << std::endl;

}

/// \brief Lit le fichier de triplets et remplit la correspondance numero d'AS/transit
/// \param filename nom du fichier
/// \param transit_as set de correspondance entre n° d'AS et transit/stub
void read_triplet(std::string const & filename,std::set<std::size_t> &  transit_as)
{
   typedef boost::tokenizer< boost::char_separator<char> >   tokenizer;
   boost::char_separator<char> sep("\t");
   try
   {
      std::ifstream file(filename.c_str());

      if( file.is_open() )
      {
	 std::string line;
	 //remplissage de la matrice
	 while(std::getline(file, line))
	 {
	    tokenizer tokens(line, sep);
	    std::vector<std::string> parts(tokens.begin(), tokens.end());
	    if( parts.size() == 3)
	    {
	       transit_as.insert( boost::lexical_cast<std::size_t>( parts.at(1) ) );
	    }
	 }
      }
      file.close();
   }
   catch(const std::exception & e)
   {
      throw ReaderException("Erreur lors de la lecture du fichier", filename, ReaderException::CRITICAL);
   }
}
