#include "./responder.hpp"

RSP::Responder::Responder(server srv) : _server(srv) {}

RSP::Responder::Responder(RSP::Responder const & r)
{
    (*this) = r;
}

RSP::Responder& RSP::Responder::operator=(RSP::Responder const & r)
{
    this->_server = r._server;
    return (*this);
}

RSP::Responder::~Responder() {}

RSP::Response RSP::Responder::Respond(request_map request)
{
    RSP::Response::headersType headers;
    headers.insert(std::make_pair("Status", "200"));
    // if (request["Methode"] == "GET")
        
    return (RSP::Response(request["URI"], headers));
}

std::string RSP::Responder::CGI_Response() 
{
    return ("Res");
}

std::string RSP::Responder::GET_Methode() 
{
    return ("Res");
}

std::string RSP::Responder::POST_Methode() 
{
    return ("Res");
}

std::string RSP::Responder::DELTE_Methode() 
{
    return ("Res");
}

std::string RSP::Responder::UploadFile() 
{
    return ("Res");
}

std::string RSP::Responder::GetErrorPage() 
{
    return ("Res");
}

std::string RSP::Responder::GetError(std::string errorCode)
{
    std::map<std::string, std::string> errorsList;

    errorsList["100"] = "Continue";
    errorsList["101"] = "Switching protocols";
    errorsList["102"] = "Processing";
    errorsList["103"] = "Early Hints";
    errorsList["200"] = "OK";
    errorsList["201"] = "Created";
    errorsList["202"] = "Accepted";
    errorsList["203"] = "Non-Authoritative Information";
    errorsList["204"] = "No Content";
    errorsList["205"] = "Reset Content";
    errorsList["206"] = "Partial Content";
    errorsList["207"] = "Multi-Status";
    errorsList["208"] = "Already Reported";
    errorsList["226"] = "IM Used";
    errorsList["300"] = "Multiple Choices";
    errorsList["301"] = "Moved Permanently";
    errorsList["302"] = "Found (Previously \"Moved Temporarily\")";
    errorsList["303"] = "See Other";
    errorsList["304"] = "Not Modified";
    errorsList["305"] = "Use Proxy";
    errorsList["306"] = "Switch Proxy";
    errorsList["307"] = "Temporary Redirect";
    errorsList["308"] = "Permanent Redirect";
    errorsList["400"] = "Bad Request";
    errorsList["401"] = "Unauthorized";
    errorsList["402"] = "Payment Required";
    errorsList["403"] = "Forbidden";
    errorsList["404"] = "Not Found";
    errorsList["405"] = "Method Not Allowed";
    errorsList["406"] = "Not Acceptable";
    errorsList["407"] = "Proxy Authentication Required";
    errorsList["408"] = "Request Timeout";
    errorsList["409"] = "Conflict";
    errorsList["410"] = "Gone";
    errorsList["411"] = "Length Required";
    errorsList["412"] = "Precondition Failed";
    errorsList["413"] = "Payload Too Large";
    errorsList["414"] = "URI Too Long";
    errorsList["415"] = "Unsupported Media Type";
    errorsList["416"] = "Range Not Satisfiable";
    errorsList["417"] = "Expectation Failed";
    errorsList["418"] = "I'm a Teapot";
    errorsList["421"] = "Misdirected Request";
    errorsList["422"] = "Unprocessable Entity";
    errorsList["423"] = "Locked";
    errorsList["424"] = "Failed Dependency";
    errorsList["425"] = "Too Early";
    errorsList["426"] = "Upgrade Required";
    errorsList["428"] = "Precondition Required";
    errorsList["429"] = "Too Many Requests";
    errorsList["431"] = "Request Header Fields Too Large";
    errorsList["451"] = "Unavailable For Legal Reasons";
    errorsList["500"] = "Internal Server Error";
    errorsList["501"] = "Not Implemented";
    errorsList["502"] = "Bad Gateway";
    errorsList["503"] = "Service Unavailable";
    errorsList["504"] = "Gateway Timeout";
    errorsList["505"] = "HTTP Version Not Supported";
    errorsList["506"] = "Variant Also Negotiates";
    errorsList["507"] = "Insufficient Storage";
    errorsList["508"] = "Loop Detected";
    errorsList["510"] = "Not Extended";
    errorsList["511"] = "Network Authentication Required";

    return (errorsList[errorCode]);
}

std::string RSP::Responder::GenerateErrorPage(std::string errorMessage)
{
    return (std::string("<html><head><title>"+errorMessage+"</title></head><body><center><h1>"+errorMessage+"</h1></center><hr><center>webserv/1.0.0</center></body></html>"));
}

std::string RSP::Responder::GetMimeType(std::string path)
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

