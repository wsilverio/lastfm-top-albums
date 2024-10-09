#include "http_client.hpp"

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>

#include <sstream>

using namespace Poco::Net;
using namespace Poco;

std::string HttpClient::get(const std::string& host, const std::string& path)
{
    HTTPClientSession session(host);
    HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);

    session.sendRequest(request);

    HTTPResponse response;
    std::istream& rs = session.receiveResponse(response);

    std::ostringstream oss;
    StreamCopier::copyStream(rs, oss);

    return oss.str();
}

std::string HttpClient::get(const std::string& url)
{
    Poco::URI uri(url);

    std::string path(uri.getPathAndQuery());

    if (path.empty())
        path = "/";

    return get(uri.getHost(), path);
}
