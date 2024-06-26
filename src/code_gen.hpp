#pragma once

#include<tuple>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<clocale>

using namespace std; // Não é uma boa pratica mas não faz diferença nessa aplicação 

enum class sql_types : short int 
{
    INT,
    BIGINT,
    CHAR,
    VARCHAR,
    NVARCHAR,
    DATE,
    TIME,
    DATETIME,
    DECIMAL,
    SMALLINT,
    TINYINT,
    NUMERIC,
    FLOAT,
    REAL,
    TEXT,
    NTEXT,
    NCHAR,
    BIT,
    BINARY,
    VARBINARY,
    IMAGE,
    UNIQUEIDENTIFIER
};

static pair<string, vector<tuple<string, sql_types, bool>>> dados;

tuple<string, sql_types, bool> read_row_from_table(string field_name, sql_types field_type, bool is_null);
void add_on_vector(vector<tuple<string, sql_types, bool>>& table, tuple<string, sql_types, bool> row);
pair<string, vector<tuple<string, sql_types, bool>>> create_table(string table_name, const vector<tuple<string, sql_types, bool>>& table);
void import_header_files(ofstream& file);
void create_data_transfer_object_class(const pair<string, vector<tuple<string, sql_types, bool>>>& table);
void menu(void);
void sql_options(void);
void create_interface(const pair<string, vector<tuple<string, sql_types, bool>>>& table);
void create_service(const pair<string, vector<tuple<string, sql_types, bool>>>& table);
void create_business_entity_class(const pair<string, vector<tuple<string, sql_types, bool>>>& table);
void create_data_access_object(const pair<string, vector<tuple<string, sql_types, bool>>>& table);
void create_sql_class(void);
string return_convert_sql(const sql_types& type, const string& field_name);

