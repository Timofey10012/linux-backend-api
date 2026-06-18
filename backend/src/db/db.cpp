//
// Created by int0 on 14.06.2026.
//

#include "db.h"

#include <iostream>
#include <stdexcept>

Database::Database(const std::string &connectionString) {
    connection_ = PQconnectdb(connectionString.c_str());

    if (PQstatus(connection_) != CONNECTION_OK) {
        std::string error = PQerrorMessage(connection_);

        PQfinish(connection_);
        connection_ = nullptr;

        throw std::runtime_error(error);
    }
}

Database::~Database() {
    if (connection_ != nullptr) {
        PQfinish(connection_);
    }
}

Database::Result Database::exec(const std::string &query) {
    PGresult* res = PQexec(connection_, query.c_str());

    auto status = PQresultStatus(res);

    if (status != PGRES_TUPLES_OK && status != PGRES_COMMAND_OK) {
        std::string error = PQresultErrorMessage(res);
        PQclear(res);
        throw std::runtime_error(error);
    }

    return Result(res);
}

Database::Result Database::execParams(const std::string &query, const std::vector<const char*> &params) {
    PGresult* res = PQexecParams(
        connection_,
        query.c_str(),
        params.size(),
        nullptr,
        params.data(),
        nullptr,
        nullptr,
        0);

    auto status = PQresultStatus(res);

    if (status != PGRES_TUPLES_OK && status != PGRES_COMMAND_OK) {
        std::string error = PQresultErrorMessage(res);
        PQclear(res);
        throw std::runtime_error(error);
    }

    return Result(res);
}

int Database::Result::rowCount() const {
    return PQntuples(result_);
}

int Database::Result::columnCount() const {
    return PQnfields(result_);
}

std::string Database::Result::get(int row, int column) const {
    return PQgetvalue(result_, row, column);
}