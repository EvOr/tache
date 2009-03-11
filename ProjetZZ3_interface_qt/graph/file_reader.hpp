#ifndef ____FILE_READER_HPP__
#define ____FILE_READER_HPP__

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.hpp"
#include "../exceptions/ReaderException.hpp"
#include "../utils/logger.hpp"
enum {P2C,C2P,PEER};
void parse(std::string const & filename, Graph &);
void read_triplet(std::string const & input_file,std::set<std::size_t> &  transit_as);
#endif
