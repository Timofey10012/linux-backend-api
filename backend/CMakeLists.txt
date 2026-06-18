cmake_minimum_required(VERSION 3.20)
project(linux_backend_api)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG v1.3.2
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(crow)

find_package(PostgreSQL REQUIRED)

add_executable(linux_backend_api src/main.cpp
        src/server/server.cpp
        src/controller/controller.cpp
        src/service/service.cpp
        src/db/db.cpp
        src/queries/queries.cpp
)

target_include_directories(linux_backend_api PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(linux_backend_api PRIVATE
    PostgreSQL::PostgreSQL
    Crow::Crow
)