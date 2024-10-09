#pragma once

#include <string>

class HttpClient
{
   public:
    static std::string get(const std::string& host, const std::string& path);
    static std::string get(const std::string& url);
};
