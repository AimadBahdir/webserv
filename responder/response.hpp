#pragma once
#include <iostream>
#include <fstream>
#include <utility>
#include <map>

class Response
{
    public:
        typedef std::map<std::string, std::string> headersType;

        Response(std::string path, headersType headers);
        Response(Response const & r);
        Response& operator=(Response const & r);
        ~Response();
        std::pair<bool, std::string> Read(size_t _bufferSize);

    private:
        std::ifstream   _inFile;
        headersType     _headers;
        size_t          _readLen;
        size_t          _fileSize;
        bool            _headSent;

        std::string     _getHeaders(void);
};