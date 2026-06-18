//
// Created by int0 on 14.06.2026.
//
#include "server.h"
#include "controller/controller.h"

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <iostream>

void run_server(Database &db) {
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests", "Content-Type", "Authorization")
        .methods("POST"_method, "GET"_method, "PATCH"_method, "DELETE"_method, "OPTIONS"_method)
        .origin("*");

    controller::setupRoute(app, db);

    std::cout << "Server started at http://localhost:8080\n";

    app.port(8080).multithreaded().run();
}