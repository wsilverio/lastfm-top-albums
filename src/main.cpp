#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>

#include <cstdint>
#include <format>
#include <opencv2/opencv.hpp>
#include <ranges>
#include <vector>

#include "http_client.hpp"
#include "image_utils.hpp"
#include "lastfm_client.hpp"

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;

class App : public Application
{
   protected:
    void initialize(Application& self) override
    {
        Application::initialize(self);
    }

    void uninitialize() override
    {
        Application::uninitialize();
    }

    void reinitialize(Application& self) override
    {
        Application::reinitialize(self);
    }

    void defineOptions(OptionSet& options) override
    {
        Application::defineOptions(options);
        options.addOption(Option("api-key", "k", "Last.fm API key").required(true).argument("api-key").binding("apiKey"));
        options.addOption(Option("username", "u", "Last.fm username").required(true).argument("username").binding("username"));
    }

    int main(const std::vector<std::string>& args) override
    {
        if (apiKey = config().getString("apiKey", ""); apiKey.empty())
        {
            logger().error("API key not provided.");
            return Application::EXIT_USAGE;
        }

        if (username = config().getString("username", ""); username.empty())
        {
            logger().error("Username not provided.");
            return Application::EXIT_USAGE;
        }

        auto albums = LastFmClient::extractTopAlbums(LastFmClient(apiKey).fetchTopAlbums(username, 9));
        auto urls = albums | std::views::transform([](const LastFmClient::Album& album) { return album.image_url; }) | std::ranges::to<std::vector<std::string>>();
        auto covers = fetchAlbumCovers(urls);
        auto grid = ImageUtils::makeGrid(covers);

        auto filename = std::format("{}.jpg", username);
        ImageUtils::saveFile(grid, filename);

        logger().information(std::format("{} written", filename));

        return Application::EXIT_OK;
    }

   private:
    static std::vector<cv::Mat> fetchAlbumCovers(const std::vector<std::string> urls)
    {
        // clang-format off
        return urls
               // fetch raw image
               | std::views::transform(
                    [](const std::string& url)
                    {
                        std::string raw = HttpClient::get(url);
                        return std::vector<std::uint8_t>(raw.begin(), raw.end());
                    })
               // decode
               | std::views::transform(
                    [](const std::vector<std::uint8_t>& raw_image)
                    {
                        return cv::imdecode(raw_image, cv::IMREAD_COLOR);
                    })
               // append to vector
               | std::ranges::to<std::vector<cv::Mat>>();
        // clang-format on
    }

    std::string apiKey;
    std::string username;
};

int main(int argc, char** argv)
{
    Poco::AutoPtr<App> app = new App;

    try
    {
        app->init(argc, argv);
    }
    catch (Poco::Exception& ex)
    {
        app->logger().log(ex);
        return Application::EXIT_CONFIG;
    }

    return app->run();
}
