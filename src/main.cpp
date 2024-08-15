#include <CPPVersus.hpp>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    CLI::App app("Multiversus CLI Test Utility", "CPPVersus CLI");
    argv = app.ensure_utf8(argv);

    std::string apiKey = "";
    app.add_option("-k,--key", apiKey, "Steam key for authentication (REQUIRED).");

    CLI11_PARSE(app, argc, argv);
    if(apiKey == "") {
        spdlog::critical("No Steam key specified.");
        return 1;
    }

    std::unique_ptr<CPPVersus::DokkenAPI> dokkenAPI;
    try {
        dokkenAPI = std::unique_ptr<CPPVersus::DokkenAPI>(new CPPVersus::DokkenAPI(apiKey));
    }
    catch(std::runtime_error const&) {
        return 1;
    }

    std::optional<CPPVersus::PlayerInfo> playerInfoOpt = dokkenAPI->getPlayerInfo("6289bfe8213b6d574354d9fc");
    if(!playerInfoOpt.has_value()) {
        spdlog::warn("No player found.");
        return 1;
    }

    CPPVersus::PlayerInfo playerInfo = playerInfoOpt.value();

    spdlog::info("Player found.");

    spdlog::info("ID: {}", playerInfo.id);
    spdlog::info("publicID: {}", playerInfo.publicID);

    spdlog::info("createdAt: {}", playerInfo.createdAt);
    spdlog::info("updatedAt: {}", playerInfo.updatedAt);
    spdlog::info("lastLogin: {}", playerInfo.lastLogin);

    spdlog::info("username: {}", playerInfo.username);

    spdlog::info("lastLoginPlatform: {}", (int)playerInfo.lastLoginPlatform);

    spdlog::info("openBetaPlayer: {}", playerInfo.openBetaPlayer);
    spdlog::info("profileIconPath: {}", playerInfo.profileIconPath);

    return 0;
}