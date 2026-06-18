//
// Created by int0 on 14.06.2026.
//

#pragma once

#include <string>
#include <crow.h>

namespace common::errors {
    enum class ErrorCode {
        ValidationError,
        InternalError
    };

    inline crow::response makeError(ErrorCode code) {
        crow::json::wvalue json;

        if (code == ErrorCode::ValidationError) {
            json["error"]["code"] = "VALIDATION_ERROR";
            return crow::response(400, json);
        }
        else {
            json["error"]["code"] = "INTERNAL_ERROR";
            return crow::response(500, json);
        }
    }
}