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
    owner_id        ...,
    last_name       ...,
    first_name      ...,
    patronymic      ...,
    pass_series     ...,
    pass_number     ...,
    phone_number    ...,
    email           ...
)

CREATE TABLE cars_data (
    car_id         ...,
    car_mark       ...,
    car_model      ...,
    car_color      ...,
    car_category   ...,
    car_vin        ...,
    owner_id       ...
)