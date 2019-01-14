#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/read_until.hpp>
#include "requestparser.h"
#include <fstream>

#include "crz_utils.h"
using boost::asio::ip::tcp;
vector<string> content_types;

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
      cout<<"Error, need some arguments"<<endl;
      cout<<"Usage: WebServer -path_to_working_dir"<<endl;
      return 1;
  }


  cout<<"Working dir path: "<<argv[1]<<endl;
  string WORKING_DIR = argv[1];

  try
  {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));

    for (;;)//Main loop
    {
      tcp::socket socket(io_service);
      acceptor.accept(socket);


      boost::asio::streambuf request;
      boost::asio::read_until(socket, request, "\r\n\r\n");
      RequestParser request_parser(&request);

      boost::asio::streambuf response;
      std::ostream response_stream(&response);

      response_stream<<"HTTP/1.1 200 OK\r\n";
      response_stream<<"Date: "<<crz::getCurrentTimeStr()<<"GMT\r\n";
      response_stream<<"Server: Craserve/0.0.1 (Linux)\r\n";
      response_stream<<"Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n";
      response_stream<<"Connection: keep-alive\r\n\r\n";

      if(request_parser.header.at("method") == "GET")
      {
          string line;
          std::string file_path = WORKING_DIR + request_parser.header.at("path");
          std::string file_ext = file_path.substr(file_path.find_last_of(".")+1);
          std::ifstream myFile;

          myFile.seekg(ios_base::end);
          long int file_size = 105078;//myFile.tellg();
          myFile.seekg(ios_base::beg);
          std::cout<<"File size: "<<file_size<<std::endl;
          char* buffer = new char[file_size];

          if(file_ext == "html" || file_ext == "htm" || file_ext == "css" || file_ext == "js")
          {
               if(file_ext == "css") response_stream<<"Content-Type: text/css\r\n";
               else if(file_ext == "js")response_stream<<"Content-Type: application/javascript\r\n";
               response_stream<<"Content-Type: text/html\r\n";
               myFile.open(file_path);
               if(myFile.is_open())
               {
                   myFile.read(buffer, file_size);
                   response_stream.write(buffer, file_size);
                   myFile.close();
               }
               else
               {
                   cout<<"Could not open file!"<<endl;
               }
          }
          if (file_ext == "jpg" || file_ext == "jpeg" || file_ext == "giff" || file_ext == "png")
          {
              if(file_ext == "jpg") response_stream<<"Content-Type: image/jpeg\r\n";
              else if(file_ext == "jpeg")response_stream<<"Content-Type: image/jpeg\r\n";
              else if(file_ext == "gif")response_stream<<"Content-Type: image/gif\r\n";
              else if(file_ext == "png")response_stream<<"Content-Type: image/png\r\n";

              myFile.open(file_path, ios_base::in | ios_base::binary);
              if(myFile.is_open())
              {
                  myFile.read(buffer, file_size);
                  response_stream.write(buffer, file_size);
                  myFile.close();
              }
              else
              {

                  cout<<"Could not open file!"<<endl;
              }
          }

      }

      boost::system::error_code ignored_error;
      boost::asio::write(socket, response, ignored_error);

      socket.cancel();
      socket.close();
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
