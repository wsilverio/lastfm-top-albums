#pragma once

#include <Poco/JSON/Object.h>

#include <string>
#include <vector>

struct LastFmClient
{
    struct Album
    {
        enum class CoverSize : unsigned
        {
            SMALL,
            MEDIUM,
            LARGE,
            EXTRA_LARGE,
        };

        std::string name;
        std::string artist;
        unsigned plays;
        std::string image_url;
    };

    LastFmClient(const std::string& apiKey);
    std::string fetchTopAlbums(const std::string& username, unsigned limit) const;
    static std::vector<Album> extractTopAlbums(const std::string jsonStr);

   private:
    static Album parseAlbum(Poco::JSON::Object::Ptr jsonObj);

    static constexpr std::string API_VERSION = "2.0";
    std::string apiKey;
};
