// homework 4-5-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

enum user_actions { user_action_invalid = 0, user_action_up, user_action_left, user_action_right, user_action_exit };

void print_pyramid(int* arr, const int size); //вывод пирамиды на консоль
int get_level_by_index(const int index); //определение уровня по индексу элемента
std::string get_index_info(const int index, int* arr, const int size); //описание элемента по его индексу
user_actions get_next_action(); //какое действие выполнить
int get_parent_index(const int index); //определить индекс родителя по индексу ребенка
int get_left_index(const int index, const int size); //определить индекс левого ребенка
int get_right_index(const int index, const int size); //определить индекс правого ребенка

int main()
{
    setlocale(LC_ALL, "rus");

    const int size_4 = 6;
    int test_array_4[size_4] = { 1, 3, 6, 5, 9, 8 };

    const int size_2 = 8;
    int test_array_2[size_2] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    
    const int size_3 = 10;
    int test_array_3[size_3] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
       
    
    int* test_array = test_array_3;
    int size = size_3;

    print_pyramid(test_array, size); //вывод пирамиды на консоль - print_pyramid работает быстрее, чем вывод циклом get_index_info
    std::cout << "\n\n";

    //вывод пирамиды
    //for (int i = 0; i < size; ++i)
    //{
    //   std::cout << get_index_info(i, test_array, size) << "\n";
    //}

    int current_index = 0; //текущий индекс - начинаем с корня

    user_actions new_user_action = user_action_invalid;
    while (new_user_action != user_action_exit)
    {
        std::cout << "Вы находитесь здесь: " << get_index_info(current_index, test_array, size) << "\n";
        new_user_action = user_action_invalid;

        //узнать, что хочет пользователь
        while (!new_user_action)
        {
           // new_user_action = user_action_invalid;
            std::cout << "Введите команду: ";
            new_user_action = get_next_action(); //какое действие выполнить
            
            int new_possible_index;

            switch (new_user_action)
            {
            case user_action_up: 
                new_possible_index = get_parent_index(current_index);
                if (new_possible_index < 0)
                {
                   std::cout << "Ошибка! Отсутствует родитель\n";
                   break;
                }

                std::cout << "ok\n";   
                current_index = new_possible_index;
                break;

            case user_action_left:
                new_possible_index = get_left_index(current_index, size);
                if (new_possible_index < 0)
                {
                    std::cout << "Ошибка! Отсутствует левый потомок\n";
                    break;
                }
                std::cout << "ok\n";
                current_index = new_possible_index;
                break;

            case user_action_right:
                new_possible_index = get_right_index(current_index, size);
                if (new_possible_index < 0)
                {
                    std::cout << "Ошибка! Отсутствует правый потомок\n";
                    break;
                }
                std::cout << "ok\n";
                current_index = new_possible_index;
                break;

            }

           // current_index = new_possible_index;
            std::cout << get_index_info(current_index, test_array, size) << "\n";
            
        }
        
        //зввершить программу
        if (new_user_action == user_action_exit)
        {
            return 0;
        }

    }    

}

void print_pyramid(int* arr, const int size) //вывод пирамиды на консоль
{
    std::cout << "Исходный массив: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << "\nПирамида:\n";

    //корень пирамиды - нулевой элемент массива
    int level = 0;
    std::string role_str = "root";
    int parent_index = 0;
    int index = 0;
    int max_level_index = 0; //максимальный индекс на уровне. 0-й уровень - один элемент с индексом 0

    std::cout << level << " " << role_str << arr[index] << "\n";
    while (index < size - 1) //вывести информацию по всем элементам массива
    {
        ++index;

        //определить уровень элемента по его индексу
        if (index > max_level_index) //если текущий индекс больше максимального индекса для текущего уровня
        {
            ++level; //увеличить номер уровня
            max_level_index += pow(2, level); //максимальный индекс на новом уровне = макс. индекс на предыдущем уровне + 2 в степени уровень
        }

        int temp_div = index % 2; //temp_div определяет, четный или нечетный индекс  
        switch (temp_div)
        {
        case 0:
            role_str = "right";//четные индексы - right
            parent_index = (index - 2) / 2; //индекс родителя
            break;

        case 1:
            role_str = "left";//нечетные индексы - left   
            parent_index = (index - 1) / 2; //индекс родителя
            break;
        }
        std::cout << level << " " << role_str << "(" << arr[parent_index] << ") " << arr[index] << "\n";
    }
}

int get_level_by_index(const int index) //определение уровня по индексу элемента
{
    
    int max_level_index = 0;
    int level = 0;
    while (index > max_level_index)
    {
        ++level;
        max_level_index +=  pow(2, level);        
    }

    return level;
}

std::string get_index_info(const int index, int* arr, const int size) //описание элемента по его индексу
{
    if ((index == 0) && (size > 0))
    {
        return "0 root " + std::to_string(arr[0]); // +"\n";
    }  

    std::string res_str = std::to_string(get_level_by_index(index)) + " ";

    std::string role_str = "";
    int parent_index = 0;

    int temp_div = index % 2; //temp_div определяет, четный или нечетный индекс  
    switch (temp_div)
    {
    case 0:
        role_str = "right";//четные индексы - right
        parent_index = (index - 2) / 2; //индекс родителя
        break;

    case 1:
        role_str = "left";//нечетные индексы - left   
        parent_index = (index - 1) / 2; //индекс родителя
        break;
    }
   
    res_str += role_str;
    res_str += "("; 
    res_str += std::to_string(arr[parent_index]);
    res_str += +") ";
    res_str += std::to_string(arr[index]); // +"\n";
    return res_str;
}

user_actions get_next_action() //какое действие выполнить
{
    std::string user_str = "";
    std::cin >> user_str;

    //if (user_str == "up")
    if (user_str == "up")
    {
        return user_action_up;
    }

    //if (user_str == "left")
    if (user_str == "left")
    {
        return user_action_left;
    }

    //if (user_str == "righ")
    if (user_str == "right")
    {
        return user_action_right;
    }

    //if (user_str == "exit")
    if (user_str == "exit")
    {
        return user_action_exit;
    }

    return user_action_invalid; 
}

int get_parent_index(const int index) //определить индекс родителя по индексу ребенка
{
    int temp_div = index % 2;
    int temp_res = -1;

    if (temp_div == 1) //это был левый ребенок
    {
        temp_res = (index - 1) / 2;
    }

    if (temp_div == 0) //это был правый ребенок
    {
        temp_res = (index - 2) / 2;
    }

    if (temp_res < 0)
    {
        return -1;
    }

    return temp_res;

}

int get_left_index(const int index, const int size) //определить индекс левого ребенка
{
   int temp_index = index * 2 + 1;
    if (temp_index >= size)
    {
        temp_index = -1;       
    }
    return temp_index;
}

int get_right_index(const int index, const int size) //определить индекс правого ребенка
{
    int temp_index = index * 2 + 2;
    if (temp_index >= size)
    {
        temp_index = -1;
    }
    return temp_index;
}
