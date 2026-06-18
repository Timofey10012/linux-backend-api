//
// Created by int0 on 14.06.2026.
//
#include "service.h"
#include "queries/queries.h"

namespace service {

    std::expected<std::vector<User>, ErrorCode> getUsers(Database &db) {
        try {
            std::vector<User> users = queries::getUsers(db);
            return users;
        } catch (std::exception& e) {
            std::cerr<< "Error: " << e.what() << std::endl;
            return std::unexpected(ErrorCode::InternalError);
        }
    }

    std::expected<void, ErrorCode> addUser(Database &db, const User &user) {
        try {
            if (user.name.empty()) {
                std::cerr << "Error: username is empty\n";
                return std::unexpected(ErrorCode::ValidationError);
            }

            if (user.email.empty()) {
                std::cerr << "Error: email is empty\n";
                return std::unexpected(ErrorCode::ValidationError);
            }

            queries::addUser(db, user);

            return {};

        } catch (std::exception& e) {
            std::cerr<< "Error: " << e.what() << std::endl;
            return std::unexpected(ErrorCode::InternalError);
        }
    }

}