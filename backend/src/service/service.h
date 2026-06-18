//
// Created by int0 on 14.06.2026.
//

#pragma once

#include "models/user.h"
#include "common/errors.h"
#include "db/db.h"

#include <expected>
#include <vector>

namespace service {
    using common::errors::ErrorCode;

    std::expected<std::vector<User>, ErrorCode> getUsers(Database &db);

    std::expected<void, ErrorCode> addUser(Database &db, const User &user);

}
