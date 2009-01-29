#ifndef ____FILE_READER_HPP__
#define ____FILE_READER_HPP__

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.hpp"
#include "../exceptions/ReaderException.hpp"
#include "../utils/logger.hpp"
class File_reader{
   protected:
      std::string filename;
      std::vector< std::vector<vertex_descriptor> > peers;
      std::vector<vertex_descriptor> peersVector;
      std::vector< std::pair<vertex_descriptor, int> > ansa;
      Graph stubsGraph;
      Graph peersGraph;
   public:
      enum{P2C,C2P,PEER};
      void change_file_name(std::string);
      File_reader(std::string f):filename(f), peers(), peersVector(), ansa(), stubsGraph(){;};
      void parse(Graph &);
      inline Graph& getNonStubsGraph(){return stubsGraph;};
      inline Graph& getPeersGraph(){ return peersGraph;};
   private:
      int addEdge(vertex_descriptor &, vertex_descriptor &, std::string, bool &, edge_descriptor &, Graph &);
      void addToPeersVector(vertex_descriptor& , vertex_descriptor&);
      void stubs_testing(int&, int&, int, int&, int, vertex_descriptor &);
      void create_peers_graph(void);
};

#endif
