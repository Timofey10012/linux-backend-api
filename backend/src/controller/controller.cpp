//
// Created by int0 on 14.06.2026.
//
#include "controller/controller.h"
#include "service/service.h"
#include "models/user.h"
#include "common/errors.h"

namespace controller {

    void setupRoute(crow::App<crow::CORSHandler>& app, Database &db) {
        CROW_ROUTE(app, "/users").methods(crow::HTTPMethod::GET) (
            [&db](const crow::request& req) {
                try {
                    auto result = service::getUsers(db);

                    if (!result) {
                        return common::errors::makeError(result.error());
                    }

                    crow::json::wvalue arr(crow::json::type::List);
                    size_t i = 0;
                    for (auto& user : *result) {
                        if (auto id = user.id) arr[i]["id"] = *id;
                        else throw std::runtime_error("user id not found");
                        arr[i]["name"] = user.name;
                        arr[i]["email"] = user.email;
                        i++;
                    }

                    crow::json::wvalue respJson;
                    respJson["users"] = std::move(arr);

                    return crow::response(respJson);

                } catch (const std::exception& e) {
                    std::cerr << "Controller error: " << e.what() << std::endl;
                    return common::errors::makeError(common::errors::ErrorCode::InternalError);
                }
            });

        CROW_ROUTE(app, "/users").methods(crow::HTTPMethod::POST) (
            [&db](const crow::request& req) {
                try {
                    auto jsonBody = crow::json::load(req.body);

                    if (!jsonBody ||
                        jsonBody["name"].t() == crow::json::type::Null ||
                        jsonBody["email"].t() == crow::json::type::Null) {
                        return common::errors::makeError(common::errors::ErrorCode::ValidationError);
                    }

                    User user;
                    user.name = jsonBody["name"].s();
                    user.email = jsonBody["email"].s();

                    auto result = service::addUser(db, user);

                    if (!result) {
                        return common::errors::makeError(result.error());
                    }

                    return crow::response(201);
                } catch (const std::exception& e) {
                    std::cerr << "Controller error: " << e.what() << std::endl;
                    return common::errors::makeError(common::errors::ErrorCode::InternalError);
                }
            });
    }

}
