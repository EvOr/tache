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
	  
  //    std::vector< std::pair<vertex_descriptor, int> > ansa;

   public:
      enum{P2C,C2P,PEER};
      void change_file_name(std::string);
      File_reader(std::string f)
			: filename(f) 
			{}

      void parse(Graph &);
   private:
      int addEdge(vertex_descriptor &, vertex_descriptor &, std::string, bool &, edge_descriptor &, Graph &);
};

#endif
