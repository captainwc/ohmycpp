#include "log.h"

int main() {
    CONSOLE->info("Welcome to spdlog!");
    CONSOLE->error("Some error message with arg: {}", 1);

    LOGGER->error("Some error message");
    return 0;
}