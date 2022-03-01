#include "./responder.hpp"

Responder::Responder(request req) : _req(req)
{
    if (req.error.compare("200") == 0)
    {
        location l = this->_getLocation(req.path, req.serv.locations);
        std::cout << l.location_path << std::endl;
    }
}

Responder::Responder(Responder const & r)
{
    (*this) = r;
}

Responder& Responder::operator=(Responder const & r)
{
    this->_req = r._req;
    return (*this);
}

Responder::~Responder() {}


std::string Responder::_cgiResponse() 
{
    return ("Res");
}

std::string Responder::_getMethode() 
{
    return ("Res");
}

std::string Responder::_postMethode() 
{
    return ("Res");
}

std::string Responder::_deleteMethode() 
{
    return ("Res");
}

std::string Responder::_uploadFile() 
{
    return ("Res");
}

std::string Responder::_indexOfPage(std::string _root, std::string _dir)
{
    DIR *dp;
    struct dirent *dirp;
    std::string _html = "<html><head><title>Index of "+_dir+"</title></head><body><h1>Index of "+_dir+"</h1><hr><pre>";
    if((dp  = opendir(std::string(_root+""+_dir).c_str())) != NULL)
    {
        while ((dirp = readdir(dp)) != NULL)
            _html += "<a href='"+ std::string(dirp->d_name) +"/'>" + std::string(dirp->d_name) + "/</a>\n";
        closedir(dp);
    }
    _html += "</pre><hr></body></html>";
    return (_html);
}

size_t  Responder::_cmpath(std::string path, std::string cmval)
{
    size_t res = 0;
    size_t i = 0;

    for (; i < path.length(); i++)
    {
        if (path[i] != cmval[i])
            return (res * (cmval[i] == '\0'));
        res += (path[i] == cmval[i] && cmval[i] == '/');
    }
    return (res * (cmval[i] == '\0'));
}

location Responder::_getLocation(std::string _reqPath, std::vector<location> _locations)
{
    size_t _bestPath = 0;
    location _loc;
    _loc.location_path = "";
    _loc.auto_index = true;
    _loc.cgi_path = "";
    _loc.index.push_back("index.html");
    _loc.root_path = "/goinfre/abahdir/webserv";
    _loc.upload_path = "default";
    _loc.redirection = std::make_pair(1, "/");

    for (size_t i = 0; i < _locations.size(); i++)
    {
        size_t _cmp = this->_cmpath(_reqPath, _locations[i].location_path);
        _loc = (_cmp > _bestPath) ?  _locations[i] : _loc;
        _bestPath = (_cmp > _bestPath) ? _cmp : _bestPath;
    }
    return (_loc);
}

std::string Responder::_getError(std::string errorCode)
{
    std::map<std::string, std::string> statusCodes;

    statusCodes["100"] = "Continue";
    statusCodes["101"] = "Switching protocols";
    statusCodes["102"] = "Processing";
    statusCodes["103"] = "Early Hints";
    statusCodes["200"] = "OK";
    statusCodes["201"] = "Created";
    statusCodes["202"] = "Accepted";
    statusCodes["203"] = "Non-Authoritative Information";
    statusCodes["204"] = "No Content";
    statusCodes["205"] = "Reset Content";
    statusCodes["206"] = "Partial Content";
    statusCodes["207"] = "Multi-Status";
    statusCodes["208"] = "Already Reported";
    statusCodes["226"] = "IM Used";
    statusCodes["300"] = "Multiple Choices";
    statusCodes["301"] = "Moved Permanently";
    statusCodes["302"] = "Found (Previously \"Moved Temporarily\")";
    statusCodes["303"] = "See Other";
    statusCodes["304"] = "Not Modified";
    statusCodes["305"] = "Use Proxy";
    statusCodes["306"] = "Switch Proxy";
    statusCodes["307"] = "Temporary Redirect";
    statusCodes["308"] = "Permanent Redirect";
    statusCodes["400"] = "Bad Request";
    statusCodes["401"] = "Unauthorized";
    statusCodes["402"] = "Payment Required";
    statusCodes["403"] = "Forbidden";
    statusCodes["404"] = "Not Found";
    statusCodes["405"] = "Method Not Allowed";
    statusCodes["406"] = "Not Acceptable";
    statusCodes["407"] = "Proxy Authentication Required";
    statusCodes["408"] = "Request Timeout";
    statusCodes["409"] = "Conflict";
    statusCodes["410"] = "Gone";
    statusCodes["411"] = "Length Required";
    statusCodes["412"] = "Precondition Failed";
    statusCodes["413"] = "Payload Too Large";
    statusCodes["414"] = "URI Too Long";
    statusCodes["415"] = "Unsupported Media Type";
    statusCodes["416"] = "Range Not Satisfiable";
    statusCodes["417"] = "Expectation Failed";
    statusCodes["418"] = "I'm a Teapot";
    statusCodes["421"] = "Misdirected Request";
    statusCodes["422"] = "Unprocessable Entity";
    statusCodes["423"] = "Locked";
    statusCodes["424"] = "Failed Dependency";
    statusCodes["425"] = "Too Early";
    statusCodes["426"] = "Upgrade Required";
    statusCodes["428"] = "Precondition Required";
    statusCodes["429"] = "Too Many Requests";
    statusCodes["431"] = "Request Header Fields Too Large";
    statusCodes["451"] = "Unavailable For Legal Reasons";
    statusCodes["500"] = "Internal Server Error";
    statusCodes["501"] = "Not Implemented";
    statusCodes["502"] = "Bad Gateway";
    statusCodes["503"] = "Service Unavailable";
    statusCodes["504"] = "Gateway Timeout";
    statusCodes["505"] = "HTTP Version Not Supported";
    statusCodes["506"] = "Variant Also Negotiates";
    statusCodes["507"] = "Insufficient Storage";
    statusCodes["508"] = "Loop Detected";
    statusCodes["510"] = "Not Extended";
    statusCodes["511"] = "Network Authentication Required";

    return (statusCodes[errorCode]);
}

std::string Responder::_generateErrorPage(std::string errorMessage)
{
    return (std::string("<html><head><title>"+errorMessage+"</title></head><body><center><h1>"+errorMessage+"</h1></center><hr><center>webserv/1.0.0</center></body></html>"));
}

std::string Responder::_getMimeType(std::string path)
{
    std::map<std::string, std::string> mimeTypes;

    mimeTypes["html"] = "text/html";
    mimeTypes["htm"] = "text/html";
    mimeTypes["shtml"] = "text/html";
    mimeTypes["css"] = "text/css";
    mimeTypes["xml"] = "text/xml";
    mimeTypes["gif"] = "image/gif";
    mimeTypes["jpeg"] = "image/jpeg";
    mimeTypes["jpg"] = "image/jpeg";
    mimeTypes["js"] = "application/javascript";
    mimeTypes["atom"] = "application/atom+xml";
    mimeTypes["rss"] = "application/rss+xml";
    mimeTypes["mml"] = "text/mathml";
    mimeTypes["txt"] = "text/plain";
    mimeTypes["jad"] = "text/vnd.sun.j2me.app-descriptor";
    mimeTypes["wml"] = "text/vnd.wap.wml";
    mimeTypes["htc"] = "text/x-component";
    mimeTypes["avif"] = "image/avif";
    mimeTypes["png"] = "image/png";
    mimeTypes["svg"] = "image/svg+xml";
    mimeTypes["svgz"] = "image/svg+xml";
    mimeTypes["tif"] = "image/tiff";
    mimeTypes["tiff"] = "image/tiff";
    mimeTypes["wbmp"] = "image/vnd.wap.wbmp";
    mimeTypes["webp"] = "image/webp";
    mimeTypes["ico"] = "image/x-icon";
    mimeTypes["jng"] = "image/x-jng";
    mimeTypes["bmp"] = "image/x-ms-bmp";
    mimeTypes["woff"] = "font/woff";
    mimeTypes["woff2"] = "font/woff2";
    mimeTypes["jar"] = "application/java-archive";
    mimeTypes["war"] = "application/java-archive";
    mimeTypes["ear"] = "application/java-archive";
    mimeTypes["json"] = "application/json";
    mimeTypes["hqx"] = "application/mac-binhex40";
    mimeTypes["doc"] = "application/msword";
    mimeTypes["pdf"] = "application/pdf";
    mimeTypes["ps"] = "application/postscript";
    mimeTypes["eps"] = "application/postscript";
    mimeTypes["ai"] = "application/postscript";
    mimeTypes["rtf"] = "application/rtf";
    mimeTypes["m3u8"] = "application/vnd.apple.mpegurl";
    mimeTypes["kml"] = "application/vnd.google-earth.kml+xml";
    mimeTypes["kmz"] = "application/vnd.google-earth.kmz";
    mimeTypes["xls"] = "application/vnd.ms-excel";
    mimeTypes["eot"] = "application/vnd.ms-fontobject";
    mimeTypes["ppt"] = "application/vnd.ms-powerpoint";
    mimeTypes["odg"] = "application/vnd.oasis.opendocument.graphics";
    mimeTypes["odp"] = "application/vnd.oasis.opendocument.presentation";
    mimeTypes["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    mimeTypes["odt"] = "application/vnd.oasis.opendocument.text";
    mimeTypes["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mimeTypes["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mimeTypes["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypes["wmlc"] = "application/vnd.wap.wmlc";
    mimeTypes["wasm"] = "application/wasm";
    mimeTypes["7z"] = "application/x-7z-compressed";
    mimeTypes["cco"] = "application/x-cocoa";
    mimeTypes["jardiff"] = "application/x-java-archive-diff";
    mimeTypes["jnlp"] = "application/x-java-jnlp-file";
    mimeTypes["run"] = "application/x-makeself";
    mimeTypes["pl"] = "application/x-perl";
    mimeTypes["pm"] = "application/x-perl";
    mimeTypes["prc"] = "application/x-pilot";
    mimeTypes["pdb"] = "application/x-pilot";
    mimeTypes["rar"] = "application/x-rar-compressed";
    mimeTypes["rpm"] = "application/x-redhat-package-manager";
    mimeTypes["sea"] = "application/x-sea";
    mimeTypes["swf"] = "application/x-shockwave-flash";
    mimeTypes["sit"] = "application/x-stuffit";
    mimeTypes["tcl"] = "application/x-tcl";
    mimeTypes["tk"] = "application/x-tcl";
    mimeTypes["der"] = "application/x-x509-ca-cert";
    mimeTypes["pem"] = "application/x-x509-ca-cert";
    mimeTypes["crt"] = "application/x-x509-ca-cert";
    mimeTypes["xpi"] = "application/x-xpinstall";
    mimeTypes["xhtml"] = "application/xhtml+xml";
    mimeTypes["xspf"] = "application/xspf+xml";
    mimeTypes["zip"] = "application/zip";
    mimeTypes["bin"] = "application/octet-stream";
    mimeTypes["exe"] = "application/octet-stream";
    mimeTypes["dll"] = "application/octet-stream";
    mimeTypes["deb"] = "application/octet-stream";
    mimeTypes["dmg"] = "application/octet-stream";
    mimeTypes["iso"] = "application/octet-stream";
    mimeTypes["img"] = "application/octet-stream";
    mimeTypes["msi"] = "application/octet-stream";
    mimeTypes["msp"] = "application/octet-stream";
    mimeTypes["msm"] = "application/octet-stream";
    mimeTypes["mid"] = "audio/midi";
    mimeTypes["midi"] = "audio/midi";
    mimeTypes["kar"] = "audio/midi";
    mimeTypes["mp3"] = "audio/mpeg";
    mimeTypes["ogg"] = "audio/ogg";
    mimeTypes["m4a"] = "audio/x-m4a";
    mimeTypes["ra"] = "audio/x-realaudio";
    mimeTypes["3gpp"] = "video/3gpp";
    mimeTypes["3gp"] = "video/3gpp";
    mimeTypes["ts"] = "video/mp2t";
    mimeTypes["mp4"] = "video/mp4";
    mimeTypes["mpeg"] = "video/mpeg";
    mimeTypes["mpg"] = "video/mpeg";
    mimeTypes["mov"] = "video/quicktime";
    mimeTypes["webm"] = "video/webm";
    mimeTypes["flv"] = "video/x-flv";
    mimeTypes["m4v"] = "video/x-m4v";
    mimeTypes["mng"] = "video/x-mng";
    mimeTypes["asx"] = "video/x-ms-asf";
    mimeTypes["asf"] = "video/x-ms-asf";
    mimeTypes["wmv"] = "video/x-ms-wmv";
    mimeTypes["avi"] = "video/x-msvideo";

    size_t ppos =  path.find_last_of(".");
    if (ppos == std::string::npos)
        return (mimeTypes["bin"]);

    std::map<std::string, std::string>::iterator it = mimeTypes.find(path.substr(++ppos));
    if (it == mimeTypes.end())
        return (mimeTypes["bin"]);

    return (it->second);
}

