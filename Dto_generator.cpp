#include<tuple>
#include<iostream>
#include<vector>
#include<fstream>
//#include<pair>
#include<string>

using namespace std;

enum class sql_types //TODO -> Adicionar mais tipos, pelo menos os princiapis
{
    INT,BIGINT,CHAR,VARCHAR,NVARCHAR,DATE,TIME,DATETIME
};

pair<string,vector<tuple<string,sql_types,bool>>> dados; //TODO -> Talvez bool não seja necessário aqui ou trocar pra map<>

tuple<string,sql_types,bool> read_row_from_table (string field_name, sql_types field_type, bool is_null)
{
    tuple<string,sql_types,bool> row(field_name,field_type,is_null);
    return row;
}
/* Método que lê o nome do campo, tipo e nulidade do campo de uma tabela e devolve a estrutura em uma tupla<string,sql_types,bool> do campo*/

void add_on_vector (vector<tuple<string,sql_types,bool>>& table,tuple<string,sql_types,bool> row )
{
    table.push_back(row);
}
/* Método que adiciona um campo da tabela (no formato correto) na tabela*/

pair<string,vector<tuple<string,sql_types,bool>>> create_table (string table_name,const vector<tuple<string,sql_types,bool>>& table)
{
    return make_pair(table_name,table);
}

void import_header_files (ofstream& file)
{
    file << "using System;\n"; 
    file << "using System.Collections.Generic;\n"; 
    file << "using System.Linq;\n"; 
    file << "using System.Text;\n";
    file << "using System.Threading.Tasks;\n\n"; 
}

void create_data_transfer_object_class (const pair<string,vector<tuple<string,sql_types,bool>>>& table)
{
    string file_name = table.first + ".cs";
    ofstream file(file_name);

    import_header_files(file);

    file << "public class " << table.first << "DTO \n";
    file << "{ " << "\n";
    for (const auto& row : table.second)
    {
        file << "public ";
        switch (get<1>(row))
        {
            case sql_types::INT:
            {
                file << "int ";
            }
            break;
            case sql_types::BIGINT:
            {
                file << "long int ";
            }
            break;
            case sql_types::CHAR:
            {
                file << "char ";
            }
            break;
            case sql_types::VARCHAR:
            case sql_types::NVARCHAR:
            {
                file << "string ";
            }
            break;
            case sql_types::DATETIME:
            {
                file << "DateTime ";
            }
            break;
        }
        file << get<0>(row) << " { get; set; }\n";
    }
    file << "}" << "\n";
}

void create_interface (const pair<string,vector<tuple<string,sql_types,bool>>>& table) 
{
    string file_name = table.first + ".cs";
    ofstream file(file_name);

    import_header_files(file);

    file << "public interface I" << table.first << "Repository \n";
    file << "{ \n";
    file << "    " << table.first << "DTO GetById(int id); \n";
    file << "    List<" << table.first << "DTO> GetAll(); \n";
    file << "    void Insert(" << table.first << "DTO item); \n";
    file << "    void Update(" << table.first << "DTO item); \n";
    file << "    void Delete(int id); \n";
    file << "} \n";      
}

void create_service (const pair<string,vector<tuple<string,sql_types,bool>>>& table)
{
    string file_name = table.first + ".cs";
    ofstream file(file_name);

    import_header_files(file);

    file << "public class " << table.first << "Service : " << "I" << table.first << "Repository \n";
    file << "{ \n";
    file << "    " << table.first << "DTO GetById(int id) \n";
    file << "    {\n";
    file << "    }\n";//TODO -> fazer a chamada à business entity (terminar de escrever ela também)
    file << "    List<" << table.first << "DTO> GetAll() \n";
    file << "    {\n";
    file << "    }\n";
    file << "    void Insert(" << table.first << "DTO item) \n";
    file << "    {\n";
    file << "    }\n";
    file << "    void Update(" << table.first << "DTO item) \n";
    file << "    {\n";
    file << "    }\n";
    file << "    void Delete(int id) \n";
    file << "    {\n";
    file << "    }\n";
    file << "} \n";   
}

void create_business_entity_class(const pair<string,vector<tuple<string,sql_types,bool>>>& table)
{

}

void create_data_access_object (const pair<string,vector<tuple<string,sql_types,bool>>>& table)
{

}

int main(int agrc, char *argv[])
{
    //TODO -> Fazer a rotina
    return 0;
}


/*
file << "public interface I" << table.first << "Repository \n";
file << "{ \n";
file << "    " << table.first << "DTO GetById(int id); \n";
file << "    List<" << table.first << "DTO> GetAll(); \n";
file << "    void Insert(" << table.first << "DTO item); \n";
file << "    void Update(" << table.first << "DTO item); \n";
file << "    void Delete(int id); \n";
file << "} \n";
*/
/*
file << "public " << table.first << "DTO GetById(int id) \n";
file << "{ \n";
file << "    // Implementação para recuperar um registro por ID \n";
file << "} \n";
*/