#include"code_gen.hpp"

tuple<string, sql_types, bool> read_row_from_table(string field_name, sql_types field_type, bool is_null)
{
    tuple<string, sql_types, bool> row(field_name, field_type, is_null);
    return row;
}

void add_on_vector(vector<tuple<string, sql_types, bool>>& table, tuple<string, sql_types, bool> row)
{
    table.push_back(row);
}

pair<string, vector<tuple<string, sql_types, bool>>> create_table(string table_name, const vector<tuple<string, sql_types, bool>>& table)
{
    return make_pair(table_name, table);
}

void import_header_files(ofstream& file)
{
    file << "using System;\n";
    file << "using System.Collections.Generic;\n";
    file << "using System.Linq;\n";
    file << "using System.Text;\n";
    file << "using System.Threading.Tasks;\n";
    file << "using System.Runtime.Serialization;\n\n";
}

void create_data_transfer_object_class(const pair<string, vector<tuple<string, sql_types, bool>>>& table)
{
    string file_name = table.first + "_DTO" + ".cs";
    ofstream file(file_name);

    import_header_files(file);

    file << "[DataContract]\n";
    file << "public class " << table.first << "_DTO \n";
    file << "{ ";
    for (const auto& row : table.second)
    {
        file << "\n";
        file << "   [DataMember]\n";
        file << "   public ";
        switch (get<1>(row))
        {
        case sql_types::INT:
        {
            file << "int";
        }
        break;
        case sql_types::BIGINT:
        {
            file << "long int";
        }
        break;
        case sql_types::CHAR:
        {
            file << "char";
        }
        break;
        case sql_types::VARCHAR:
        case sql_types::NVARCHAR:
        {
            file << "string";
        }
        break;
        case sql_types::DATETIME:
        {
            file << "DateTime";
        }
        break;
        }
        if (get<2>(row))
        {
            file << "? ";
        }
        else
        {
            file << " ";
        }
        file << get<0>(row) << " { get; set; }\n";
    }
    file << "\n   public " << table.first << "_DTO()\n";
    file << "   {\n\n";
    file << "   }\n";

    file << "\n   public " << table.first << "_DTO( "<< table.first <<"_DTO" << " obj " <<")\n";
    file << "   {\n";
    for (const auto& row : table.second)
    {
        file << "      this."+ get<0>(row) << " = obj." + get<0>(row) << "\n";
    }
    file << "   }\n";
    file << "}\n";
}

void menu(void)
{
    cout << "***********************\n";
    cout << "* .NET Code Generator *\n";
    cout << "***********************\n";
    cout << "\n - 1 Gerar classe de conexao com o banco.";
    cout << "\n - 2 Gerar DTO, Interface, Service, BE e DAO de uma tabela.";
    cout << "\n - 3 Sair do programa.";
    cout << "\nDigite a sua escolha: ";
}


void sql_options(void)
{
    cout << "\nDigite o tipo de dado do campo: ";
    cout << "\n0 - INT";
    cout << "\n2 - CHAR";
    cout << "\n3 - VARCHAR";
    cout << "\n7 - DATETIME";
    cout << "\n: ";
}

void create_interface(const pair<string, vector<tuple<string, sql_types, bool>>>& table)
{
    string file_name = table.first + "_Interface" + ".cs";
    ofstream file(file_name);

    import_header_files(file);

    file << "public interface I" << table.first << "_Repository \n";
    file << "{ \n";
    file << "    " << table.first << "_DTO GetById(int id); \n";
    file << "    List<" << table.first << "_DTO> GetAll(); \n";
    file << "    void Insert(" << table.first << "_DTO item); \n";
    file << "    void Update(" << table.first << "_DTO item); \n";
    file << "    void Delete(int id); \n";
    file << "} \n";
}

void create_service(const pair<string, vector<tuple<string, sql_types, bool>>>& table)
{
    string file_name = table.first + "_Service" + ".cs";
    ofstream file(file_name);

    import_header_files(file);

    file << "public class " << table.first << "_Service : " << "I" << table.first << "_Repository \n";
    file << "{ \n";
    file << "    " << table.first << "_DTO GetById(int id) \n";
    file << "    {\n";
    file << "    }\n";//TODO -> fazer a chamada à business entity (terminar de escrever ela também)
    file << "    List<" << table.first << "_DTO> GetAll() \n";
    file << "    {\n";
    file << "    }\n";
    file << "    void Insert(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "    }\n";
    file << "    void Update(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "    }\n";
    file << "    void Delete(int id) \n";
    file << "    {\n";
    file << "    }\n";
    file << "} \n";
}

void create_business_entity_class(const pair<string, vector<tuple<string, sql_types, bool>>>& table)
{

}

void create_data_access_object(const pair<string, vector<tuple<string, sql_types, bool>>>& table)
{

}

void create_sql_class(void)
{
    string file_name = "Database.cs";
    ofstream file(file_name);

    file << "using System;\n";
    file << "using System.Text;\n";
    file << "using System.Data.SqlClient;\n\n";

    file << "public abstract class Database : IDisposable\n";
    file << "{\n";
    file << "   protected SqlConnection conn;\n";
    file << "   private bool disposed = false;\n\n";
    file << "   public Database()\n";
    file << "   {\n";
    file << "      string connectionString = \"Coloque_sua_string_aqui\";\n";
    file << "      conn = new SqlConnection(connectionString);\n";
    file << "      conn.Open();\n";
    file << "   }\n\n";
    file << "   protected virtual void Dispose(bool disposing)\n";
    file << "   {\n";
    file << "      if (!disposed)\n";
    file << "      {\n";
    file << "         if (disposing)\n";
    file << "         {\n";
    file << "            if (conn != null)\n";
    file << "            {\n";
    file << "               conn.Close();\n";
    file << "               conn = null;\n";
    file << "            }\n";
    file << "         }\n";
    file << "         disposed = true;\n";
    file << "      }\n";
    file << "   }\n\n";
    file << "   public void Dispose()\n";
    file << "   {\n";
    file << "      Dispose(true);\n";
    file << "      GC.SuppressFinalize(this);\n";
    file << "   }\n\n";
    file << "   ~Database()\n";
    file << "   {\n";
    file << "      Dispose(false);\n";
    file << "   }\n";
    file << "}\n";
}
