#include "server/server.h"
#include "db/db.h"

#include <iostream>
#include <string>

int main() {
    try {
        auto getRequiredEnv = [](const char* name) -> std::string {
            const char* value = std::getenv(name);

            if (!value) {
                throw std::runtime_error(
                    std::string("Environment variable not found: ") + name
                );
            }

            return value;
        };

        std::string host = getRequiredEnv("DB_HOST");
        std::string port = getRequiredEnv("DB_PORT");
        std::string name = getRequiredEnv("DB_NAME");
        std::string user = getRequiredEnv("DB_USER");
        std::string pass = getRequiredEnv("DB_PASSWORD");

        if (host.empty() || port.empty() || name.empty() || user.empty() || pass.empty()) {
            throw std::runtime_error("Invalid environment variables");
        }

        std::string connectionString =
            "host=" + host +
            " port=" + port +
            " dbname=" + name +
            " user=" + user +
            " password=" + pass;

        Database db(connectionString);

        run_server(db);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}