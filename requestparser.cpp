#include "requestparser.h"

RequestParser::RequestParser(boost::asio::streambuf* request)
{

    std::istream stream(request);

    string temp_str;
    stream>>temp_str;

    header["method"] = temp_str;
    cout<<"Method: "<<temp_str<<endl;
    temp_str = " ";
    stream>>temp_str;
    header["path"] = temp_str;
    cout<<"Path: "<<temp_str<<endl;
    temp_str = " ";
    stream>>temp_str;
    header["version"] = temp_str;
    cout<<"Version: "<<temp_str<<endl;
    temp_str = readNextBlock(&stream);
    if(temp_str == "Host:")
    {
        temp_str = readNextBlock(&stream);
        header["host"] = temp_str;
        cout<<"Host: "<<header["host"]<<endl;
    }
    temp_str = readNextBlock(&stream);
    if(temp_str == "User-Agent:")
    {
        char reqbuff[512] = " ";
        stream.getline(reqbuff, 1024, '\n');
        string tstr(reqbuff);

        header["user_agent"] = tstr;
        cout<<"User-Agent: "<<header["user_agent"]<<endl;
    }
    temp_str = readNextBlock(&stream);
    if(temp_str == "Accept:")
    {
        temp_str = readNextBlock(&stream);
        header["accept"] = temp_str;
        cout<<"Accept: "<<header["accept"]<<endl;
    }
    temp_str = readNextBlock(&stream);
    if(temp_str == "Accept-Language:")
    {
        temp_str = readNextBlock(&stream);
        header["accept_lang"] = temp_str;
        cout<<"Accept-Language: "<<header["accept_lang"]<<endl;
    }
    temp_str = readNextBlock(&stream);
    if(temp_str == "Accept-Encoding:")
    {
        char reqbuff[512] = " ";
        stream.getline(reqbuff, 1024, '\n');
        string tstr(reqbuff);

        header["accept_encoding"] = tstr;
        cout<<"Accept-Encoding: "<<header["accept_encoding"]<<endl;
    }
    temp_str = readNextBlock(&stream);
    if(temp_str == "DNT:")
    {
        temp_str = readNextBlock(&stream);
        header["DNT"] = temp_str;
        cout<<"DNT: "<<header["DNT"]<<endl;
    }
    temp_str = readNextBlock(&stream);
//    char reqbuff[512] = " ";
//    stream.readsome(reqbuff, 512);
//    for(int i = 0; i < 512;i++)
//    {
//        cout<<reqbuff[i];
//    }




}


string RequestParser::readNextBlock(std::istream* stream)
{
    string temp_string = " ";
    *stream>>temp_string;
   // cout<<"Temp string in func: "<<temp_string<<endl;
    return temp_string;
}
