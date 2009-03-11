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
      std::map< vertex_descriptor , coordonnes> mescoords_tmp;
      std::vector< std::pair<vertex_descriptor , vertex_descriptor> > liens;
      std::vector< std::pair<vertex_descriptor , vertex_descriptor> > liens_tmp;
      tableau_de_coordonnees position;
      tableau_de_coordonnees position_tmp;

   public:
      Controler(std::string fn):graph(),filename(fn),mescoords(),position(mescoords),mescoords_tmp(),position_tmp(mescoords_tmp){;};
      void change_file_name(std::string fn);
      void parse_file();
      int displayCircle(double r);
      bool displayKamada();
      Graph const & getGraph() const {return graph;}
      inline std::map< vertex_descriptor , coordonnes> get_position(){return mescoords;};
      inline std::vector< std::pair<vertex_descriptor , vertex_descriptor> > get_liens() { return liens; }
      inline std::map< vertex_descriptor , coordonnes> get_position_tmp(){return mescoords_tmp;};
      inline std::vector< std::pair<vertex_descriptor , vertex_descriptor> > get_liens_tmp() { return liens_tmp; }
      int getNumberOfAs();
      void load_triplet(std::string const & filename);
      Graph & getNonStubsGraph();
      Graph & getGraphWeightInf(int i);
      Graph & getGraphWeightSup(int i);
      Graph & getGraphAsNumInf(int i);
      Graph & getGraphAsNumSup(int i);
      Graph & getFirstNeighbors(int i);
      Graph::vertex_descriptor findAS(int i);


      //inline Graph & getPeersGraph(){return file_reader.getPeersGraph();};
};

#endif
