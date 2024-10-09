#include "lastfm_client.hpp"

#include <Poco/Dynamic/Struct.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>

#include <format>
#include <utility>

#include "http_client.hpp"

LastFmClient::LastFmClient(const std::string& apiKey) : apiKey(apiKey)
{
}

std::string LastFmClient::fetchTopAlbums(const std::string& username, unsigned limit) const
{
    return HttpClient::get(
        "ws.audioscrobbler.com",
        std::format(
            "/{}/"
            "?method=user.gettopalbums"
            "&api_key={}"
            "&user={}"
            "&format=json"
            "&period=1month"
            "&limit={}",
            API_VERSION,
            apiKey,
            username,
            limit));
}

std::vector<LastFmClient::Album> LastFmClient::extractTopAlbums(const std::string jsonStr)
{
    Poco::JSON::Parser parser;
    auto result = parser.parse(jsonStr);
    auto root = result.extract<Poco::JSON::Object::Ptr>();
    auto top_albums = root->getObject("topalbums");
    auto albums = top_albums->getArray("album");

    std::vector<LastFmClient::Album> album_list;

    // TODO: use range-based for loop
    for (unsigned i = 0; i < albums->size(); ++i)
    {
        album_list.push_back(parseAlbum(albums->getObject(i)));
    }

    return album_list;
}

LastFmClient::Album LastFmClient::parseAlbum(Poco::JSON::Object::Ptr jsonObj)
{
    Poco::Dynamic::Struct<std::string> obj = *jsonObj;

    return {
        obj["name"],
        obj["artist"]["name"],
        obj["playcount"],
        obj["image"][std::to_underlying(LastFmClient::Album::CoverSize::EXTRA_LARGE)]["#text"],
    };
}
