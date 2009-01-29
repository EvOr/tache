#ifndef ____CONTROLLER_HPP_
#define ____CONTROLLER_HPP_
#include "../graph/file_reader.hpp"
#include "../graph/graph.hpp"
#include <string>

class Controler{
   protected:
      File_reader file_reader;
      Graph graph;
      std::string filename;
      std::map< vertex_descriptor , coordonnes> mescoords;
      std::vector< std::pair<vertex_descriptor , vertex_descriptor> > liens;
      tableau_de_coordonnees position;
      
   public:
      Controler(std::string fn):file_reader(fn),graph(),filename(fn),mescoords(),position(mescoords){;};
      void change_file_name(std::string fn);
      void parse_file();
      int displayCircle(double r);
      bool displayKamada();
      Graph & getGraph(){return graph;};
      inline std::map< vertex_descriptor , coordonnes> get_position(){return mescoords;};
      inline std::vector< std::pair<vertex_descriptor , vertex_descriptor> > get_liens() { return liens; }
      inline Graph & getNonStubsGraph(){return file_reader.getNonStubsGraph();};
      inline Graph & getPeersGraph(){return file_reader.getPeersGraph();};
};

#endif

