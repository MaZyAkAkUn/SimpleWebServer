#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H
#include <iostream>
#include <boost/asio/streambuf.hpp>
#include <map>
using namespace std;
class RequestParser
{
public:
    RequestParser(boost::asio::streambuf* request);
    map <string, string> header = {{"version", ""},              //main header structure
                                   {"method", ""},
                                   {"absolute_path", ""},
                                   {"relative_path", ""},
                                   {"host", ""},
                                   {"user_agent", ""},
                                   {"accept", ""},
                                   {"accept_charset", ""},
                                   {"accept_encoding", ""},
                                   {"accept_lang", ""},
                                   {"connection", ""},
                                   {"data", ""},
                                   {"DNT", ""},
                                   {"pragma", ""},
                                   {"trailer", ""},
                                   {"transfer_encoding", ""},
                                   {"upgrade", ""},
                                   {"VIA", ""},
                                   {"authorization", ""},
                                   {"cookie", ""},
                                   {"expect", ""},
                                   {"from", ""},
                                   {"if_match", ""},
                                   {"if_non_match", ""},
                                   {"if_modifed_since", ""},
                                   {"if_unmodifed_since", ""},
                                   {"if_range", ""},
                                   {"max_forwards", ""},
                                   {"proxy_authorization", ""},
                                   {"range", ""},
                                   {"referer", ""},
                                   {"TE", ""},
                                   {"allow", ""},
                                   {"content_encoding", ""},
                                   {"content_lang", ""},
                                   {"content_lenght", ""},
                                   {"content_location", ""},
                                   {"coontent_md5", ""},
                                   {"content_range", ""},
                                   {"content_type", ""},
                                   {"expires", ""},
                                   {"last_modified", ""}
                                  };

protected:
    const string END_LINE = "\r\n";
    const string EMPTY_LINE = "\r\n\r\n";
private:
    void parse(std::istream*);
    std::string readNextBlock(std::istream* stream);


};

#endif // REQUESTPARSER_H
