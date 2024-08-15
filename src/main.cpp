#include <CPPVersus.hpp>

#include <CPPVersus-CLI.hpp>

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

    CPPVersus::CLI cli(apiKey);
    cli.run();

    return 0;
}