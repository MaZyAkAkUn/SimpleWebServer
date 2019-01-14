#include "crz_utils.h"

std::string crz::getCurrentTimeStr()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(nullptr);
  string curr_time =ctime(&now);
  cout<<curr_time;
  return curr_time;
}

std::string crz::gzipCompress(const std::string& data)
    {
        namespace bio = boost::iostreams;

        std::stringstream compressed;
        std::stringstream origin(data);

        bio::filtering_streambuf<bio::input> out;
        out.push(bio::gzip_compressor(bio::gzip_params(bio::gzip::best_compression)));
        out.push(origin);
        bio::copy(out, compressed);

        return compressed.str();
}
