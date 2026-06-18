//
// Created by int0 on 14.06.2026.
//

#pragma once

#include <string>
#include <optional>

struct User {
    std::optional<int> id;
    std::string name;
    std::string email;
};