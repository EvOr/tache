#ifndef ____CONTROLLER_HPP_
#define ____CONTROLLER_HPP_
#include "../graph/file_reader.hpp"
#include "../graph/graph.hpp"
#include <string>

class Controler{
   protected:
      Graph graph;
      std::string filename;
      std::map< vertex_descriptor , coordonnes> mescoords;
      tableau_de_coordonnees position;
      
   public:
      Controler(std::string fn):graph(),filename(fn),mescoords(),position(mescoords){;};
      void change_file_name(std::string fn);
      void parse_file();
      int displayCircle(double r);
      Graph & getGraph(){return graph;}
      Graph const & getGraph() const {return graph;}
      inline std::map< vertex_descriptor , coordonnes> get_position(){return mescoords;};
      void load_triplet(std::string const & filename);
      //inline Graph & getNonStubsGraph(){return file_reader.getNonStubsGraph();};
      //inline Graph & getPeersGraph(){return file_reader.getPeersGraph();};
};

#endif
