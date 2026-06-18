//
// Created by int0 on 15.06.2026.
//

#pragma once
#include "models/user.h"
#include "db/db.h"

#include <vector>

namespace queries {
    std::vector<User> getUsers(Database &db);

    void addUser(Database &db, const User &user);
}
