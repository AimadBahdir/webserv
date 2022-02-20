#include "./response.hpp"

Response::Response(std::string path) : _inFile(path, std::ios::out|std::ios::binary), _readLen(0), _fileSize(0), _headSent(false)
{
    if (this->_inFile.is_open())
    {
        this->_inFile.seekg(this->_readLen,  this->_inFile.end);
        this->_fileSize = this->_inFile.tellg();
        this->_inFile.seekg(this->_readLen,  this->_inFile.beg);
    }
    std::cout << this->_fileSize << std::endl;
}

Response::~Response()
{
    this->_inFile.close();
}

std::pair<bool, std::string> Response::Read(size_t _bufferSize)
{
    if (this->_headSent)
    {
        char* _buffer = new char [_bufferSize];
        if (this->_inFile.is_open())
        {
            this->_inFile.seekg(this->_readLen,  this->_inFile.beg);
            this->_inFile.read(_buffer, _bufferSize);
            this->_readLen += this->_inFile.gcount();
        }
        std::string _buff(_buffer, this->_inFile.gcount());
        delete [] _buffer;
        return (std::make_pair(this->_inFile.eof(), _buff));
    }
    else
    {
        this->_headSent = true;
        return (std::make_pair(false, this->_getHeaders()));
    }
}

std::string Response::_getHeaders(void)
{
    return ("HTTP/1.1 200 OK\r\n");
}