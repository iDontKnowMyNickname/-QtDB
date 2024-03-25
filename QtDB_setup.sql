-- PostgreSQL 14.11
-- Скрипт, который создаст пользователя и таблицы для работы программы


-- Администратор базы данных
CREATE ROLE capybara
    PASSWORD 'IamCapybara'
    SUPERUSER
    CREATEDB
    CREATEROLE
    INHERIT
    LOGIN;

-- Переключение роли на админобару
SET ROLE capybara;

-- Следующее описание в целом срисовано с определения базы данных postgres
CREATE DATABASE 'QtDB'              -- Создание базы QtDB
    WITH                            -- с параметрами:
               OWNER = capybara     -- Владелец базы данных
            ENCODING = 'UTF8'       -- Кодировка базы данных
          LC_COLLATE = 'C.UTF-8'    -- 
            LC_CTYPE = 'C.UTF-8'    --
    CONNECTION LIMIT = -1           -- Неограниченное число подключений
         IS_TEMPLATE = False;       -- Клонировать базу могут только владелец базы и суперпользователи

-- Комментарий к QtDb
COMMENT ON DATABASE 'QtDB'
    IS 'База данных проекта QtDB с данными о владельцах авто и автомобилях'

-- Подключиться к QtDB пользователем capybara
/connect 'QtDB';

CREATE TABLE owners_data (
    owner_id        SERIAL PRIMARY KEY UNIQUE,
    last_name       text NOT NULL CHECK(last_name SIMILAR TO E'^[А-Яа-яЁе]+[А-Яа-яЁе\ \-\']*[А-Яа-яЁе]+$'),
    first_name      text NOT NULL CHECK(first_name SIMILAR TO E'^[А-Яа-яЁе]+[А-Яа-яЁе\ \-\']*[А-Яа-яЁе]+$'),
    patronymic      text CHECK(patronymic SIMILAR TO E'^[А-Яа-яЁе]*[А-Яа-яЁе\ \-\']*[А-Яа-яЁе]*$'),
    pass_series     char( 4 ) NOT NULL CHECK(pass_series SIMILAR TO E'^\d\d\d\d$'),
    pass_number     char( 8 ) NOT NULL CHECK(pass_number SIMILAR TO E'^\d\d\d\d\d\d$'),
    phone_number    char(11 ) NOT NULL UNIQUE CHECK(phone_number SIMILAR TO '^8\d\d\d\d\d\d\d\d\d\d$'),
    email           text UNIQUE CHECK(email SIMILAR TO '[A-Za-z]+@[A-Za-z]+\.[A-Za-z]+')
)

CREATE TYPE category AS ENUM ('A', 'A1', 'B', 'BE', 'B1', 'C', 'CE', 'C1', 'C1E', 'D', 'DE', 'D1', 'D1E', 'M', 'Tm', 'Tb')

--CREATE TABLE cars_data (
--    car_id         SERIAL PRIMARY KEY UNIQUE,
--    car_mark       text NOT NULL,
--    car_model      text NOT NULL,
--    car_color      text NOT NULL,
--    car_category   category NOT NULL,
--    car_vin        ...,
--    owner_id       integer REFERENCES owners_data (owner_id)
--)