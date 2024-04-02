-- Создание пользователя
CREATE USER capybara_user WITH PASSWORD 'iamcapybara';

-- Выдача пользователю привилегий на текущую БД
DO $$
    BEGIN
        EXECUTE
            'GRANT ALL PRIVILEGES ON DATABASE ' || current_database() || ' TO capybara_user';
    END;
$$;

-- Создание таблицы с данными владельцев авто
CREATE TABLE IF NOT EXISTS owners_data (
    owner_id        SERIAL   PRIMARY KEY,               -- Идентификатор владельца - уникальное целое число
    last_name       text     NOT NULL,                  -- Фамилия
    first_name      text     NOT NULL,                  -- Имя
    patronymic      text     NOT NULL,                  -- Отчество
    pass_series     char(4)  NOT NULL,                  -- Серия паспорта
    pass_number     char(6)  NOT NULL,                  -- Номер паспорта
    phone_number    char(11) NOT NULL UNIQUE,           -- Номер телефона
                                                        -- Ряд проверок:
    UNIQUE( pass_series, pass_number ),                 -- Комбинация "серия + номер" паспорта должна быть уникальной
    CHECK(    last_name ~* '^[А-ЯЁа-яё \-'']+$' ),      -- Фамилия состоит из символов кириллицы, пробелов, апострофов, дефисов и не пуста
    CHECK(   first_name ~* '^[А-ЯЁа-яё \-'']+$' ),      -- аналогично Имя
    CHECK(   patronymic ~* '^[А-ЯЁа-яё \-'']*$' ),      -- аналогично Отчество
    CHECK(  pass_series ~* '^\d\d\d\d$' ),              -- Серия паспорта - 4 цифры
    CHECK(  pass_number ~* '^\d\d\d\d\d\d$' ),          -- Номер паспорта - 6 цифр
    CHECK( phone_number ~* '^8\d\d\d\d\d\d\d\d\d\d$' )  -- Номер телефона - 11 цифр, где первая - "8". При указании городского писать в виде 8-*код города*-*номер телефона*
);

-- Множество категорий водительских прав
CREATE TYPE cars_categories AS ENUM (
    'A',
    'A1',
    'B',
    'BE',
    'B1',
    'C',
    'CE',
    'C1',
    'C1E',
    'D',
    'DE',
    'D1',
    'D1E',
    'M',
    'Tm',
    'Tb'
);

-- Таблица с данными об автомобилях
CREATE TABLE IF NOT EXISTS cars_data(
    car_id          SERIAL              PRIMARY KEY,                                -- Идентификатор авто - уникально ецелое число
    car_number      VARCHAR(12)            NOT NULL UNIQUE,                            -- Номер авто - формат "X123XX123RUS"
    car_mark        TEXT                NOT NULL,                                   -- Марка авто
    car_color       TEXT                NOT NULL,                                   -- Цвет авто
    car_category    cars_categories     NOT NULL,                                   -- Категория прав из множества cars_categories
    car_vin         char(17)            NOT NULL UNIQUE,                            -- VIN номер авто 
    owner_id        INTEGER             NOT NULL,                                   -- Ссылка на владельца авто
                                                                                -- Ряд проверок:
    CHECK( car_number ~ '^[АВЕКМНОРСТУХ]\d\d\d[АВЕКМНОРСТУХ]{2}\d\d\d?RUS$' ),  -- Формат номера авто - допустимая буква, три цифры, две буквы, 2-3 цифры, "RUS": А123ВЕ36RUS
    CHECK( NOT car_mark = '' ),                                                 -- 
    CHECK( NOT car_color = '' ),                                                --
    CHECK( car_vin ~ '^[A-HJ-NPR-Z\d]{17}$' ),                                  --
    FOREIGN KEY (owner_id) REFERENCES owners_data(owner_id)                     --
        ON DELETE NO ACTION                                                     --
        ON UPDATE CASCADE                                                       --
);

GRANT ALL PRIVILEGES ON owners_data TO capybara_user;
GRANT ALL PRIVILEGES ON cars_data   TO capybara_user;
GRANT ALL ON ALL SEQUENCES IN SCHEMA public TO capybara_user;

-- Команды для удаления таблиц и пользователя
/*
DROP TABLE IF EXISTS owners_data CASCADE;       --
DROP TABLE IF EXISTS cars_data CASCADE;         --

DROP TYPE  IF EXISTS cars_categories CASCADE;   --

REASSIGN OWNED BY capybara_user TO postgres;    --
DROP OWNED BY capybara_user;                    --

DROP ROLE  IF EXISTS capybara_user;             --
*/