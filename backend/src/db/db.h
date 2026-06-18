//
// Created by int0 on 14.06.2026.
//

#pragma once

#include <vector>
#include <string>
#include <libpq-fe.h>

class Database {
    public:
    explicit Database(const std::string& connectionString);
    ~Database();

    class Result {
        public:
        explicit Result(PGresult *result) : result_(result) {};
        ~Result() {
            if (result_ != nullptr) {
                PQclear(result_);
            }
        };

        int rowCount() const;
        int columnCount() const;
        std::string get(int row, int column) const;

        private:
        PGresult *result_ = nullptr;
    };

    Result exec(const std::string& query);
    Result execParams(const std::string& query, const std::vector<const char*>& params);

    private:
    PGconn *connection_ = nullptr;
};