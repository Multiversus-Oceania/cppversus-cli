#ifndef __CPPVERSUS_CLI_HPP__
#define __CPPVERSUS_CLI_HPP__

#include <string>
#include <memory>

#include <spdlog/spdlog.h>

#include <CPPVersus.hpp>

namespace CPPVersus {

class CLI {
private:
    std::string _apiKey;
    std::unique_ptr<DokkenAPI> _dokkenAPI;

public:
    CLI(std::string key) : _apiKey(key) {
        try {
            _dokkenAPI = std::unique_ptr<CPPVersus::DokkenAPI>(new CPPVersus::DokkenAPI(_apiKey));
        }
        catch(std::runtime_error const&) {
            spdlog::critical("Invalid API Key, Exiting.");
            exit(1);
        }
    }

    ~CLI() {

    }
    

    void run() {
        std::optional<CPPVersus::PlayerInfo> playerInfoOpt = _dokkenAPI->getPlayerInfo("6289bfe8213b6d574354d9fc");
        if(!playerInfoOpt.has_value()) {
            spdlog::warn("No player found.");
            return;
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

        spdlog::info("");
        spdlog::info("---- Stats ----");

        spdlog::info("highestDamageDealt: {}", playerInfo.stats.highestDamageDealt);
        spdlog::info("totalDamage: {}", playerInfo.stats.totalDamage);
        spdlog::info("totalRingoutLeader: {}", playerInfo.stats.totalRingoutLeader);
        spdlog::info("totalRingouts: {}", playerInfo.stats.totalRingouts);
        spdlog::info("totalWins: {}", playerInfo.stats.totalWins);
        spdlog::info("totalAssists: {}", playerInfo.stats.totalAssists);
        spdlog::info("totalAttacksDodged: {}", playerInfo.stats.totalAttacksDodged);
        spdlog::info("totalDoubleRingouts: {}", playerInfo.stats.totalDoubleRingouts);
        spdlog::info("totalMaxedCharacters: {}", playerInfo.stats.totalMaxedCharacters);

        spdlog::info("---------------");
    }
};

};

#endif