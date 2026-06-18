//
// Created by int0 on 14.06.2026.
//

#pragma once
#include "db/db.h"

#include <crow.h>
#include <crow/middlewares/cors.h>

namespace controller {

    void setupRoute(crow::App<crow::CORSHandler>& app, Database &db);

}