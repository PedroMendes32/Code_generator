#include"code_gen.hpp"

int main(int agrc, char* argv[])
{
    setlocale(LC_ALL, "Portuguese");

    string nome_tabela,fields;
    short int sql_type, qtd_fields,option;
    vector<tuple<string, sql_types, bool>> table;
    char is_null;
    bool sair = false;

    while (!sair)
    {
        menu();
        fflush(stdin);
        cin >> option;

        if (cin.fail())
        {
            cout << "\nEntrada invalida!\n";
            exit(EXIT_FAILURE);
        }

        switch (option)
        {
            case 1:
            {
                try
                {
                    create_sql_class();
                    cout << "\nArquivos criados com sucesso!\n";
                }
                catch (const exception& ex)
                {
                    cerr << "Erro: " << ex.what() << "\n";
                }
            }
            break;
            case 2:
            {
                try
                {
                    cout << "\nDigite o nome da tabela: ";
                    cin >> nome_tabela;
                    cout << "\nDigite a quantidade de campos da tabela " << nome_tabela << ": ";
                    cin >> qtd_fields;

                    for (short int i = 0; i < qtd_fields; i++)
                    {
                        cout << "\nDigite o nome do " << i + 1 << " campo: ";
                        cin >> fields;
                        sql_options();
                        cin >> sql_type;
                        cout << "\nO campo pode ser nulo? (S/N): ";
                        cin >> is_null;
                        add_on_vector(table, read_row_from_table(fields, static_cast<sql_types>(sql_type), is_null == 'S' ? true : false));
                    }

                    dados = create_table(nome_tabela, table);
                    create_data_transfer_object_class(dados);
                    create_interface(dados);
                    create_service(dados);
                    cout << "Arquivos criados com sucesso!\n";
                }
                catch (const exception& ex)
                {
                    cerr << "Erro: " << ex.what() << "\n";
                }
            }
            break;
            case 3:
            {
                sair = true;
            }
            break;
            default:
            {
                cout << "\nOpcao invalida!\n";
            }
        }
        system("pause");
        system("cls");
    }

    return 0;
}

