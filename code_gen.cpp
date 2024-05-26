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
    file << "using System.Runtime.Serialization;\n";
    file << "using System.Data.SqlClient;\n\n";
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
            case sql_types::DECIMAL:
            {
                file << "double";
            }
            break;
        }
        if (get<2>(row) && (get<1>(row) != sql_types::VARCHAR) && get<1>(row) != sql_types::NVARCHAR)
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
        file << "      this."+ get<0>(row) << " = obj." + get<0>(row) << ";\n";
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
    cout << "\n8 - DECIMAL";
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
    file << "    public " << table.first << "_DTO GetById(int id) \n";
    file << "    {\n";
    file << "        using ("<< table.first <<"_BE" << " be = new " << table.first <<"_BE())\n";
    file << "        {\n";
    file << "            return be.GetById(id);\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public List<" << table.first << "_DTO> GetAll() \n";
    file << "    {\n";
    file << "        using (" << table.first << "_BE" << " be = new " << table.first << "_BE())\n";
    file << "        {\n";
    file << "            return be.GetAll();\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Insert(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "        using (" << table.first << "_BE" << " be = new " << table.first << "_BE(item))\n";
    file << "        {\n";
    file << "            be.Insert(item);\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Update(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "        using (" << table.first << "_BE" << " be = new " << table.first << "_BE(item))\n";
    file << "        {\n";
    file << "            be.Update(item);\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Delete(int id) \n";
    file << "    {\n";
    file << "        using (" << table.first << "_BE" << " be = new " << table.first << "_BE())\n";
    file << "        {\n";
    file << "            be.Delete(id);\n";
    file << "        }\n";
    file << "    }\n";
    file << "} \n";
}

void create_business_entity_class(const pair<string, vector<tuple<string, sql_types, bool>>>& table)
{
    string file_name = table.first + "_BE" + ".cs";
    ofstream file(file_name);

    import_header_files(file);

    file << "public class " << table.first << "_BE : " << table.first << "_DTO, IDisposable \n";
    file << "{ \n";
    file << "    public " << table.first << "_BE()\n";
    file << "    {\n\n";
    file << "    }\n";

    file << "    public " << table.first << "_BE( " << table.first << "_DTO" << " obj " << ")\n";
    file << "    {\n";
    for (const auto& row : table.second)
    {
        file << "       this." + get<0>(row) << " = obj." + get<0>(row) << ";\n";
    }
    file << "    }\n\n";

    file << "    public " << table.first << "_DTO GetById(int id) \n";
    file << "    {\n";
    file << "        using (" << table.first << "_DAO" << " dao = new " << table.first << "_DAO())\n";
    file << "        {\n";
    file << "            return dao.GetById(id);\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public List<" << table.first << "_DTO> GetAll() \n";
    file << "    {\n";
    file << "        using (" << table.first << "_DAO" << " dao = new " << table.first << "_DAO())\n";
    file << "        {\n";
    file << "            return dao.GetAll();\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Insert(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "        using (" << table.first << "_DAO" << " dao = new " << table.first << "_DAO())\n";
    file << "        {\n";
    file << "            dao.Insert(item);\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Update(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "        using (" << table.first << "_DAO" << " dao = new " << table.first << "_DAO())\n";
    file << "        {\n";
    file << "            dao.Update(item);\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Delete(int id) \n";
    file << "    {\n";
    file << "        using (" << table.first << "_DAO" << " dao = new " << table.first << "_DAO())\n";
    file << "        {\n";
    file << "            dao.Delete(id);\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Dispose() \n";
    file << "    {\n";
    file << "        throw new NotImplementedException();\n";
    file << "    }\n";
    file << "} \n";
}

void create_data_access_object(const pair<string, vector<tuple<string, sql_types, bool>>>& table)
{
    string file_name = table.first + "_DAO" + ".cs";
    ofstream file(file_name);
    int i = 1,count = table.second.size();

    import_header_files(file);

    file << "public class " << table.first << "_DAO : Database\n";
    file << "{ \n";
    file << "    public " << table.first << "_DTO GetById(int id) \n";
    file << "    {\n";
    file << "        " << table.first << "_DTO result = null;\n";
    file << "        try\n";
    file << "        {\n";
    file << "           using (SqlCommand cmd = new SqlCommand())\n";
    file << "           {\n";
    file << "               cmd.Connection = conn;\n";
    file << "               cmd.CommandText = @\"SELECT * FROM " << table.first << "\n";
    file << "               WHERE id = @id\"; //Implemente sua lógica aqui!" << "\n\n";
    file << "               cmd.Parameters.AddWithValue(\"@id\", id);\n";
    file << "               using (SqlDataReader reader = cmd.ExecuteReader())\n";
    file << "               {\n";
    file << "                   if (reader.Read())\n";
    file << "                   {\n";
    file << "                       result = new "<< table.first << "_DTO()\n";
    file << "                       {\n";
    for (const auto& row : table.second)
    {
        file << "                            " << get<0>(row) << " = ";
        file << "reader[\"" << get<0>(row) << "\"] != DBNull.Value ? " << return_convert_sql(get<1>(row), get<0>(row));
        file << " : " << return_default_values_sql(get<1>(row),get<2>(row)) << ",\n";
    }
    file << "                       };\n";
    file << "                   }\n";
    file << "               }\n";
    file << "           }\n";
    file << "        }\n";
    file << "        catch (SqlException ex)\n";
    file << "        {\n";
    file << "           throw ex;\n";
    file << "        }\n";
    file << "        return result;\n";
    file << "    }\n\n";
    file << "    public List<" << table.first << "_DTO> GetAll() \n";
    file << "    {\n";
    file << "        List<" << table.first << "_DTO> result = null;\n";
    file << "        try\n";
    file << "        {\n";
    file << "           using (SqlCommand cmd = new SqlCommand())\n";
    file << "           {\n";
    file << "               cmd.Connection = conn;\n";
    file << "               cmd.CommandText = @\"SELECT * FROM " << table.first << "\";\n\n";
    file << "               using (SqlDataReader reader = cmd.ExecuteReader())\n";
    file << "               {\n";
    file << "                   while (reader.Read())\n";
    file << "                   {\n";
    file << "                       result.Add(new " << table.first << "_DTO()\n";
    file << "                       {\n";
    for (const auto& row : table.second)
    {
        file << "                            " << get<0>(row) << " = ";
        file << "reader[\"" << get<0>(row) << "\"] != DBNull.Value ? " << return_convert_sql(get<1>(row), get<0>(row));
        file << " : " << return_default_values_sql(get<1>(row), get<2>(row)) << ",\n";
    }
    file << "                       });\n";
    file << "                   }\n";
    file << "               }\n";
    file << "           }\n";
    file << "        }\n";
    file << "        catch (SqlException ex)\n";
    file << "        {\n";
    file << "           throw ex;\n";
    file << "        }\n";
    file << "        return result;\n";
    file << "    }\n\n";
    file << "    public void Insert(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "        try\n";
    file << "        {\n";
    file << "           using (SqlCommand cmd = new SqlCommand())\n";
    file << "           {\n";
    file << "               cmd.Connection = conn;\n";
    file << "               cmd.CommandText = @\"INSERT INTO " << table.first << "\n";
    file << "               (\n";
    for (const auto& row : table.second)
    {
        file <<"\t\t\t\t" << get<0>(row);
        if (i < count) file << ",\n";
        else  file << ")\n";
        i++;
    }
    file << "               VALUES\n";
    file << "               (\n";
    i = 1;
    for (const auto& row : table.second)
    {
        file << "\t\t\t\t@" << get<0>(row);
        if (i < count) file << ",\n";
        else file << ")\";\n\n";
        i++;
    }
    for (const auto& row : table.second)
    {
        file << "               cmd.Parameters.AddWithValue(\"@"<< get<0>(row) << "\", item." << get<0>(row) << " != null ? item." << get<0>(row) << " : " << return_default_values_sql(get<1>(row),get<2>(row)) << "); \n";
    }
    file << "               cmd.ExecuteNonQuery();\n";
    file << "           }\n";
    file << "        }\n";
    file << "        catch (SqlException ex)\n";
    file << "        {\n";
    file << "           throw ex;\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Update(" << table.first << "_DTO item) \n";
    file << "    {\n";
    file << "        try\n";
    file << "        {\n";
    file << "           using (SqlCommand cmd = new SqlCommand())\n";
    file << "           {\n";
    file << "               cmd.Connection = conn;\n";
    file << "               cmd.CommandText = @\"UPDATE " << table.first << "\n";
    file << "               SET\n";
    i = 1;
    for (const auto& row : table.second)
    {
        file << "\t\t\t\t" << get<0>(row) << " = @" << get<0>(row);
        if (i < count) file << ",\n";
        else  file << "\n";
        i++;
    }
    file << "               WHERE 1 = 1\";// Implemente sua lógica aqui! \n\n";
    file << "               \n";
    for (const auto& row : table.second)
    {
        file << "               cmd.Parameters.AddWithValue(\"@" << get<0>(row) << "\", item." << get<0>(row) << " != null ? item." << get<0>(row) << " : " << return_default_values_sql(get<1>(row), get<2>(row)) << "); \n";
    }
    file << "               cmd.ExecuteNonQuery();\n";
    file << "           }\n";
    file << "        }\n";
    file << "        catch (SqlException ex)\n";
    file << "        {\n";
    file << "           throw ex;\n";
    file << "        }\n";
    file << "    }\n\n";
    file << "    public void Delete(int id) \n";
    file << "    {\n";
    file << "        try\n";
    file << "        {\n";
    file << "           using (SqlCommand cmd = new SqlCommand())\n";
    file << "           {\n";
    file << "               cmd.Connection = conn;\n";
    file << "               cmd.CommandText = @\"DELETE FROM " << table.first << "\n";
    file << "               WHERE id = @id\"; //Implemente sua lógica aqui!" << "\n\n";
    file << "               cmd.Parameters.AddWithValue(\"@id\", id);\n";
    file << "               cmd.ExecuteNonQuery();\n";
    file << "           }\n";
    file << "        }\n";
    file << "        catch (SqlException ex)\n";
    file << "        {\n";
    file << "           throw ex;\n";
    file << "        }\n";
    file << "    }\n";
    file << "} \n";
}

void create_sql_class(void)
{
    string file_name = "Database.cs";
    ofstream file(file_name);

    import_header_files(file);

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

string return_convert_sql(const sql_types& type,const string& field_name)
{
    string str = "";
    switch (type)
    {
        case sql_types::INT:
        {
            str = "Convert.ToInt32(reader[\"" + field_name + "\"])";
        }
        break;
        case sql_types::BIGINT:
        {
            str = "Convert.ToInt64(reader[\"" + field_name + "\"])";
        }
        break;
        case sql_types::CHAR:
        {
            str = "Convert.ToChar(reader[\"" + field_name + "\"])";
        }
        break;
        case sql_types::VARCHAR:
        case sql_types::NVARCHAR:
        {
            str = "Convert.ToString(reader[\"" + field_name + "\"])";
        }
        break;
        case sql_types::DATETIME:
        {
            str = "Convert.ToDateTime(reader[\"" + field_name + "\"])";
        }
        break;
        case sql_types::DECIMAL:
        {
            str = "Convert.ToDouble(reader[\"" + field_name + "\"])";
        }
        break;
    }
    return str;
}

string return_default_values_sql(const sql_types& type, const bool& is_null)
{
    string str = "";
    switch (type)
    {
        case sql_types::INT:
        {
            str = "default(int";
        }
        break;
        case sql_types::BIGINT:
        {
            str = "default(long";
        }
        break;
        case sql_types::CHAR:
        {
            str = "default(char";
        }
        break;
        case sql_types::VARCHAR:
        case sql_types::NVARCHAR:
        {
            str = "default(string";
        }
        break;
        case sql_types::DATETIME:
        {
            str = "default(DateTime";
        }
        break;
        case sql_types::DECIMAL:
        {
            str = "default(double";
        }
        break;
    }
    is_null == true && (type != sql_types::VARCHAR && type != sql_types::NVARCHAR) ? str += "?)" : str += ")";
    return str;
}

