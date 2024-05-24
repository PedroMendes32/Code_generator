#include"code_gen.hpp"

int main(int agrc, char* argv[])
{
    setlocale(LC_ALL, "Portuguese");

    string nome_tabela,fields;
    short int sql_type,qtd_fields;
    vector<tuple<string, sql_types, bool>> table;
    char is_null;

    cout << "Digite o nome da tabela: ";
    cin >> nome_tabela;
    cout << "\nDigite a quantidade de campos da tabela " << nome_tabela << ": ";
    cin >> qtd_fields;
    
    for (short int i = 0; i < qtd_fields; i++)
    {
        cout << "\nDigite o nome do " << i+1  << " campo: ";
        cin >> fields;
        sql_options();
        cin >> sql_type;
        cout << "\nO campo pode ser nulo? (S/N): ";
        cin >> is_null;
        add_on_vector(table, read_row_from_table(fields, static_cast<sql_types>(sql_type), is_null == 'S' ? true : false));
    }

    dados = create_table(nome_tabela,table);
    create_data_transfer_object_class(dados);
    create_interface(dados);
    create_service(dados);
    
    return 0;
}

