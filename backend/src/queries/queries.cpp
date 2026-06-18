//
// Created by int0 on 15.06.2026.
//

#include "queries.h"

#include <iostream>

namespace queries {
    std::vector<User> getUsers(Database &db) {
        std::string query = "SELECT id, name, email FROM users";

        auto result = db.exec(query);

        int rowCount = result.rowCount();

        std::vector<User> users;
        users.reserve(rowCount);

        for (int i = 0; i < rowCount; i++) {
            User user;

            user.id = std::stoi(result.get(i, 0));
            user.name = result.get(i, 1);
            user.email = result.get(i, 2);

            users.emplace_back(user);
        }

        return users;
    }

    void addUser(Database &db, const User &user) {
        std::string query = "INSERT INTO users (name, email) VALUES ($1, $2);";

        std::vector<const char*> params;
        params.reserve(2);

        params.emplace_back(user.name.c_str());
        params.emplace_back(user.email.c_str());

        db.execParams(query, params);
    }



}
