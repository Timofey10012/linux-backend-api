# Linux Backend API

Backend-сервис на C++ с REST API, подключённый к PostgreSQL и полностью контейнеризированный через Docker Compose.

Проект реализует базовую архитектуру серверного приложения с разделением на слои (controller / service / queries / db) и использует libpq для работы с PostgreSQL без ORM.

## Содержание
- [Возможности](#возможности)
- [Архитектура](#архитектура)
- [Docker](#docker)
- [API](#api)
- [Технологии](#технологии)
- [Особенности реализации](#особенности-реализации)
- [Запуск](#запус)
- [Лицензия](#Лицензия)

## Возможности
- REST API на базе Crow
- PostgreSQL как основная база данных
- Работа с БД через libpq
- Безопасная передача параметров (защита от SQL-инъекций)
- RAII-обёртка над подключением к БД
- Docker Compose для полного запуска проекта
- Автоматическая инициализация БД через init.sql

## Архитектура
controller → service → queries → db → PostgreSQL
- controller — HTTP слой (Crow)
- service — бизнес-логика
- queries — SQL-запросы
- db — RAII-обёртка над libpq

## Docker
Проект полностью запускается через Docker Compose:
```
docker-compose up -d
```

Поднимается:
backend API (C++)

PostgreSQL (18)

## API
Получить пользователей
```
GET /users
```

Добавить пользователя
```
POST /users
Content-Type: application/json
```
body:
```
{
  "name": "name",
  "email": "email@example.com"
}
```

## Технологии
- C++23
- Crow (HTTP framework)
- PostgreSQL
- libpq
- CMake
- Docker / Docker Compose

## Особенности реализации
- Используется `std::expected` для обработки ошибок
- RAII для управления соединением с БД
- Параметризованные SQL-запросы
- Изоляция инфраструктуры через Docker
- `.env` конфигурация через переменные окружения

## Запуск
### Клонировать репозитори
```
git clone https://github.com/Timofey10012/linux-backend-api.git
cd linux-backend-api
```

### Создать файлы конфигурации

Скопировать `.env.example` в `.env` и заполнить необходимые значения.

Для backend:
```
backend/
```

Для PostgreSQL:
```
infra/db/
```

### Запустить проект
```
infra/docker/
docker-compose up -d
```

После запуска:

API: http://localhost:8080

PostgreSQL: localhost:5432

## Лицензия

[MIT](LICENSE)

Проект распространяется под лицензией MIT.
Вы можете свободно использовать, копировать, изменять
и распространять данный код, включая коммерческое использование,
при условии сохранения уведомления об авторских правах.
