#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include "../parser/server_parser.hpp"

// struct location_parser
// {
//     private:
//         std::vector<std::string>    accepted_requests;
//         std::string                 location_path;
//         std::string                 root_path;
//         std::vector<std::string>    index;
//         std::string                 upload_path;
//         std::string                 cgi_path;
//         std::pair<std::string, std::string> redirection;
//         bool                        auto_index;
//     public:
//         std::vector<std::string>    getAcceptedRequests() { return accepted_requests; }
//         std::string                 getLocationPath() { return location_path; }
//         std::string                 getRootPath() { return root_path; }
//         std::vector<std::string>    getIndexs() { return index; }
//         std::string                 getUploadPath() { return upload_path; }
//         std::string                 getCgiPath() { return cgi_path; }
//         std::pair<std::string, std::string> getRedirection() { return redirection; }
//         bool                        getAutoIndex() { return auto_index; }

//         void                        setAcceptedRequests(std::vector<std::string> accepted_requests) { this->accepted_requests = accepted_requests; }
//         void                        setLocationPath(std::string location_path) { this->location_path = location_path; }
//         void                        setRootPath(std::string root_path) { this->root_path = root_path; }
//         void                        setIndexs(std::vector<std::string> index) { this->index = index; }
//         void                        setUploadPath(std::string upload_path) { this->upload_path = upload_path; }
//         void                        setCgiPath(std::string cgi_path) { this->cgi_path = cgi_path; }
//         void                        setRedirection(std::pair<std::string, std::string> redirection) { this->redirection = redirection; }
//         void                        setAutoIndex(bool auto_index) { this->auto_index = auto_index; }
// };

// struct server_parser
// {
//     private:
//         int                             port;
//         std::string                     host;
//         std::string                     root_path;
//         std::vector<std::string>        names;
//         std::vector<std::string>        error_pages;
//         int                             clientMaxBodySize;
//         std::vector<location_parser>    locations;
//     public:

//         int                             getPort() { return this->port; }
//         std::string                     getHost() { return this->host; }
//         std::string                     getRootPath() { return this->root_path; }
//         std::vector<std::string>        getNames() { return this->names; }
//         std::vector<std::string>        getErrorPages() { return this->error_pages; }
//         int                             getMaxBodySize() { return this->clientMaxBodySize; }
//         std::vector<location_parser>    getLocations() { return this->locations; }

//         void                            setPort(int port) { this->port = port; }
//         void                            setHost(std::string host) { this->host = host; }
//         void                            setRootPath(std::string root_path) { this->root_path = root_path; }
//         void                            setNames(std::vector<std::string> names) { this->names = names; }
//         void                            setErrorPages(std::vector<std::string> error_pages) { this->error_pages = error_pages; }
//         void                            setMaxBodySize(int clientMaxBodySize) { this->clientMaxBodySize = clientMaxBodySize; }
//         void                            setLocations(std::vector<location_parser> locations) { this->locations = locations; }

// };

class request_parser
{
    private:
        std::string                         error;
        server_parser                       serv;
        std::string                         methode;
        std::string                         path;
        std::string                         queries;
        std::string                         version;
        std::map<std::string, std::string>  headers;
        std::string                         bodyFile;

    public:
        std::string                         getError() { return error; }
        server_parser                       getServer() { return serv; }
        std::string                         getMethode() { return methode; }
        std::string                         getPath() { return path; }
        std::string                         getQueries() { return queries; }
        std::string                         getVersion() { return version; }
        std::map<std::string, std::string>  getHeaders() { return headers; }
        std::string                         getBodyFile() { return bodyFile; }

        void                                setError(std::string error) {  this->error = error; }
        void                                setServer(server_parser serv) {  this->serv = serv; }
        void                                setMethode(std::string methode) {  this->methode = methode; }
        void                                setPath(std::string path) {  this->path = path; }
        void                                setQueries(std::string queries) {  this->queries = queries; }
        void                                setVersion(std::string version) {  this->version = version; }
        void                                setHeaders(std::map<std::string, std::string> headers) {  this->headers = headers; }
        void                                setBodyFile(std::string bodyFile) {  this->bodyFile = bodyFile; }
};
