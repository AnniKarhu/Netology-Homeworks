// homework-5-9-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "big_integer.h"


int main()
{
    setlocale(LC_ALL, "rus");
        
    big_integer big_int1("100000000");
    big_integer big_int2("9999");
    big_integer big_int3("100000000");
    big_integer big_invalid("99-99");

   
    std::cout << "******************" << "\n\n";
    std::cout << "big_int1 \n";
    std::cout << "big_int1.get_size = " << big_int1.get_size() << "\n";
    std::cout << "big_int1 = " << big_int1 << "\n";
    //std::cout << "big_int1.get_elements() = " << big_int1.get_elements() << "\n";
    
    std::cout << "******************" << "\n\n";
    std::cout << "big_int2 \n";
    std::cout << "big_int2.get_size = " << big_int2.get_size() << "\n";
    std::cout << "big_int2 = " << big_int2 << "\n";
    //std::cout << "big_int2.get_elements() = " << big_int2.get_elements() << "\n";
    
    std::cout << "******************" << "\n\n";
    std::cout << "big_invalid \n";
    std::cout << "big_invalid.get_size = " << big_invalid.get_size() << "\n";
    std::cout << "big_invalid = " << big_invalid << "\n";
    
    std::cout << "******************" << "\n\n";
    std::cout << "оператор = \n";
     big_integer big_copy1 = big_int1; //работает как конструктор копирования
     std::cout << "big_copy1.get_size = " << big_copy1.get_size() << "\n";
     std::cout << "big_copy1 = " << big_copy1 << "\n";
     std::cout << "******************" << "\n\n";

     std::cout << "конструктор копирования \n";
     big_integer big_copy2(big_int1);  //работает как конструктор копирования
     std::cout << "big_copy2.get_size = " << big_copy2.get_size() << "\n";
     std::cout << "big_copy2 = " << big_copy1 << "\n";
     std::cout << "******************" << "\n\n";

     std::cout << "конструктор копирования невалидного числа\n";
     big_integer big_copy_invalid(big_invalid);  //конструктор копирования для невалидного числа
     std::cout << "big_copy_invalid.get_size = " << big_copy_invalid.get_size() << "\n";
     std::cout << "big_copy_invalid = " << big_copy_invalid << "\n";
     std::cout << "******************" << "\n\n";

     std::cout << "конструктор перемещения \n";
     big_integer big_move = std::move(big_int3); //работает как конструктор перемещения
     std::cout << "big_move.get_size = " << big_move.get_size() << "\n";
     std::cout << "big_move = " << big_move << "\n";
     std::cout << "******************" << "\n\n";

     std::cout << "конструктор перемещения ревалидного числа \n";
     big_integer big_move_invalid = std::move(big_invalid); // конструктор перемещения для невалидного числа
     std::cout << "big_move_invalid.get_size = " << big_move_invalid.get_size() << "\n";
     std::cout << "big_move_invalid = " << big_move_invalid << "\n";
     std::cout << "******************" << "\n\n";
     
  
    std::cout << "******************" << "\n\n";
    std::cout << "сложение \n";
    big_integer big_sum = big_int1 + big_int2; //сложение
    std::cout << "big_sum.get_size = " << big_sum.get_size() << "\n";
    std::cout << "big_sum = " << big_sum << "\n";
   
    std::cout << "******************" << "\n\n";
    std::cout << "сложение с невалидным\n";
    big_integer big_sum_invalid = big_int1 + big_invalid; //сложение с невалидным числом
    std::cout << "big_sum_invalid.get_size = " << big_sum_invalid.get_size() << "\n";
    std::cout << "big_sum_invalid = " << big_sum_invalid << "\n";

    std::cout << "******************" << "\n\n";
    std::cout << "вычитание 1 \n";
    big_integer big_sub = big_int1 - big_int2;
    std::cout << "big_sub.get_size = " << big_sub.get_size() << "\n";
    std::cout << "big_sub = " << big_sub << "\n";
  
    std::cout << "******************" << "\n\n";
    std::cout << "вычитание 2 \n";
    big_integer big_sub2 = big_int2 - big_int1;
    std::cout << "big_sub2.get_size = " << big_sub2.get_size() << "\n";
    std::cout << "big_sub2 = " << big_sub2 << "\n";
    
    std::cout << "******************" << "\n\n";
    std::cout << "умножение \n";
    big_integer big_mult = big_int1 * 9999;
    std::cout << "big_mult.get_size = " << big_mult.get_size() << "\n";
    std::cout << "big_mult = " << big_mult << "\n";

    big_integer big_int4("345853257980");
    std::cout << "умножение 2\n";
    big_integer big_mult2 = big_int4 * -9999;
    std::cout << "big_mult2.get_size = " << big_mult2.get_size() << "\n";
    std::cout << "big_mult2 = " << big_mult2 << "\n";

}

