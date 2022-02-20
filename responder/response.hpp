#pragma once
#include <iostream>
#include <fstream>
#include <utility>

class Response
{
    private:
        std::ifstream   _inFile;
        size_t          _readLen;
        size_t          _fileSize;
        bool            _headSent;

        std::string     _getHeaders(void);
    public:
        Response(std::string path);
        ~Response();
        std::pair<bool, std::string> Read(size_t _bufferSize);
};
