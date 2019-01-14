#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <sstream>
namespace crz {

std::string getCurrentTimeStr();
std::string gzipCompress(const std::string&);

}





#endif // UTILS_H
