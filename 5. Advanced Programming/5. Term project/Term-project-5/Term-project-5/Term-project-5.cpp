// Term-project-5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>

#include "ini_parser.h"

int main()
{
    setlocale(LC_ALL, "rus");
    
    //несуществующий файл
    std::cout << "Чтение из несуществующего файла\n";
    ini_parser parser_0("settingss.ini");
    try
    {
        std::cout << "Sec1.var2 = " << parser_0.get_value<std::string>("Sec1.var2") << "\n";
    }
    catch (const ParserException_no_file& ex)
    {
        std::cout << ex.what() << "\n";
    }
    std::cout << "***************************\n\n";

    std::cout << "Чтение из хорошего файла\n";
    //рабочий файл settings.ini
    ini_parser parser("settings.ini");    

    std::cout << "существующие переменные типа string: \n";
    std::vector<std::string> requests_array_string_1 = {
        "Section1.var1", //существующая переменная 
        "Section1.var2", //существующая переменная 
        "Section1.var3", //существующая переменная 
        "Section2.var1", //существующая переменная 
        "Section2.var2", //существующая переменная 
        "Section4.Mode", //существующая переменная 
        "Section4.Vid",  //существующая переменная 
    };

    for (auto& item : requests_array_string_1)
    {
        try
        {
            std::cout << item << " = " << parser.get_value<std::string>(item) << "\n";
        }
        catch (...)
        {
            std::cout << "Произошла ошибка получения переменной\n"; //в данном примере в эту строку кода попадать не будем
        }
        
    }

    std::cout << "\nсуществующие переменные типа double: \n";
    std::vector<std::string> requests_array_double_1 = {
        "Section1.var1", //существующая переменная 
        "Section2.var1", //существующая переменная        
    };

    for (auto& item : requests_array_double_1) 
    {
        try
        {
            std::cout << item << " = " << std::fixed << std::setprecision(3) << parser.get_value<double>(item) << "\n";
        }
        catch (...)
        {
            std::cout << "Произошла ошибка получения переменной\n"; //в данном примере в эту строку кода попадать не будем
        }
        
    }

    std::cout << "\nсуществующие переменные типа int: \n";
    std::vector<std::string> requests_array_int_1 = {
        "Section1.var1", //существующая переменная 
        "Section2.var1", //существующая переменная        
    };

    for (auto& item : requests_array_int_1) 
    {
        try
        {
            std::cout << item << " = " << parser.get_value<int>(item) << "\n";
        }
        catch (...)
        {
            std::cout << "Произошла ошибка получения переменной\n"; //в данном примере в эту строку кода попадать не будем
        }
        
    }    
   
    std::cout << "\nНесуществующие переменные типа string: \n";
    std::vector<std::string> requests_array_string_2 = {
        "Sectio1.var1", //секция не существует 
        "Section1.var22", //переменная не существует        
    };

    for (auto& item : requests_array_string_2)
    {
        try
        {
            std::cout << item << " = " << parser.get_value<std::string>(item) << "\n";
        }
        catch (const ParserException_no_section& ex)
        {
            std::cout << ex.what() << "\n";
            parser.print_all_sections();
            std::cout << "\n";
        }
        catch (const ParserException_no_variable& ex)
        {
            std::string section_name = parser.get_section_from_request(item); //получить из строки запроса название секции
            std::cout << "Секция " << section_name << ": " << ex.what() << "\n";            
            parser.print_all_variables(section_name);
            std::cout << "\n";
        }
        catch(...)
        {
            std::cout << "Произошла ошибка получения переменной\n"; //в данном примере в эту строку кода попадать не будем
        }
    }

    std::cout << "***************************\n\n";

    std::cout << "Запрос информации из файла с ошибками\n";
    
    //файл с ошибками settings2.ini
    ini_parser parser3("settings2.ini");
    
    try
    {
        if (!parser3.print_all_sections_info())
        {
            std::cout << "Парсер содержит некорретные данные. Выведенная информация может содержать некорректные или неполные данные.\n";
            parser3.print_incorrect_info();	//вывести информацию о некорректных данных в файле
            std::cout << "\n";
        }
    }
    catch (const ParserException_error& ex)
    {
        std::cout << "Не удалось вывести информацию. " << ex.what() << "\n";
    }
    catch (const ParserException_no_file& ex)
    {
        std::cout << "Не удалось вывести информацию. " << ex.what() << "\n"; //в этом примере сюда не попадаем, так как файл существует
    }
    catch (const ParserException_incorrect_data& ex)
    {
        std::cout << "Не удалось вывести информацию. " << ex.what() << "\n"; //сюда не попадаем, ошибка обрабатывается раньше
        parser3.print_incorrect_info();	//вывести информацию о некорректных данных в файле
    }
    catch (...)
    {
        std::cout << "Не удалось вывести информацию. Неизвестная ошибка.\n"; 
    }
   

    std::cout << "\nпеременные типа string из файла с ошибками: \n";
    std::vector<std::string> requests_array_string_3 = {
        "Section1.var1", //существующая переменная 
        "Section1.var2", //существующая переменная 
        "Section1.var3", //переменная не существует
        "Section1.Mode", //существующая переменная 
        "Section1.Vid", //переменная не существует
        "Section2.var1", //существующая переменная 
        "Section2.var2", //существующая переменная 
        "Section4.Mode", //секция не существует 
        "Section4.Vid", //секция не существует  
    };

    for (auto& item : requests_array_string_3)
    {
        try
        {
            std::cout << item << " = " << parser3.get_value<std::string>(item) << "\n";
        }
        catch (const ParserException_incorrect_request& ex)
        {
            std::cout << ex.what() << "\n";
        }
        catch (const ParserException_no_section& ex)
        {
            std::cout << "Строка запроса: " << item << "\n";
            std::cout << ex.what() << "\n";
            if (!parser3.print_all_sections())
            {
                std::cout << "Парсер содержит некорретные данные. Выведенная информация может содержать некорректные или неполные данные.\n";
                parser3.print_incorrect_info();	//вывести информацию о некорректных данных в файле
            }
            std::cout << "\n";
        }
        catch (const ParserException_no_variable& ex)
        {
            std::cout << "Строка запроса: " << item << "\n";
            std::string section_name = parser3.get_section_from_request(item); //получить из строки запроса название секции
            std::cout << "Секция " << section_name << ": " << ex.what() << "\n";

            if (!parser3.print_all_variables(section_name))
            {
                std::cout << "Парсер содержит некорретные данные. Выведенная информация может содержать некорректные или неполные данные.\n";
                parser3.print_incorrect_info();	//вывести информацию о некорректных данных в файле
            }
        }
        catch (const ParserException_error& ex)
        {
            
            std::cout << ex.what() << "\n";
           
        }
        catch (const ParserException_no_file& ex)
        {
            std::cout << ex.what() << "\n";
        }
        catch (const ParserException_incorrect_data& ex)
        {
            std::cout << ex.what() << "\n";
        }
        
        std::cout << "\n\n";

    }
    

    std::cout << "************************************\n\n";
    std::cout << "конструктор копирования - копирование валидного парсера\n";
    ini_parser parser_copy_valid(parser);
    try
    {
        if (!parser_copy_valid.print_all_sections_info())
        {
            std::cout << "Скопированный парсер содержит некорректную информацию\n";
            parser_copy_valid.print_incorrect_info();	//вывести информацию о некорректных данных в файле
        }
    }
    catch (...)
    {
        std::cout << "Произошла ошибка 1\n";
    }

    std::cout << "************************************\n\n";
    std::cout << "конструктор копирования - копирование невалидного парсера\n";
    ini_parser parser_copy_invalid(parser3);
    try
    {
        if (!parser_copy_invalid.print_all_sections_info())
        {
            std::cout << "Скопированный парсер содержит некорректную информацию\n";
            parser_copy_invalid.print_incorrect_info();	//вывести информацию о некорректных данных в файле
        }
    }
    catch (...)
    {
        std::cout << "Произошла ошибка 2\n";
    }
    
    std::cout << "************************************\n\n";
    std::cout << "Оператор копирования - копирование валидного парсера\n";
    ini_parser parser_copy_valid2 = parser;
    try
    {
        if (!parser_copy_valid2.print_all_sections_info())
        {
            std::cout << "Скопированный парсер содержит некорректную информацию\n";
            parser_copy_valid2.print_incorrect_info();	//вывести информацию о некорректных данных в файле
        }
    }
    catch (...)
    {
        std::cout << "Произошла ошибка 3\n";
    }

    std::cout << "************************************\n\n";
    std::cout << "Оператор копирования - копирование невалидного парсера\n";
    ini_parser parser_copy_invalid2 = parser3;
    try
    {
        if (!parser_copy_invalid2.print_all_sections_info())
        {
            std::cout << "Скопированный парсер содержит некорректную информацию\n";
            parser_copy_invalid2.print_incorrect_info();	//вывести информацию о некорректных данных в файле
        }
    }
    catch (...)
    {
        std::cout << "Произошла ошибка 4\n";
    }

    std::cout << "************************************\n\n";
    std::cout << "конструктор перемещения\n";
    ini_parser parser_move = std::move(parser);
    try
    {
        if (!parser_move.print_all_sections_info())
        {
            std::cout << "Скопированный парсер содержит некорректную информацию\n";
            parser_move.print_incorrect_info();	//вывести информацию о некорректных данных в файле
        }
    }
    catch (...)
    {
        std::cout << "Произошла ошибка 5\n";
    }

    try
    {
        if (!parser.print_all_sections_info())
        {
            std::cout << "Скопированный парсер содержит некорректную информацию\n";
            parser.print_incorrect_info();	//вывести информацию о некорректных данных в файле
        }
    }
    catch (...)
    {
        std::cout << "Произошла ошибка 6. Попытка обращения к невалидному объекту.\n";
    }

}

