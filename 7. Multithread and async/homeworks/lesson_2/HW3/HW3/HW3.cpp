#include<iostream>
#include<mutex>

class Data
{
public:
    int int_value;
    std::string str_value;
    std::mutex data_mutex;

    Data(int a, std::string b) { int_value = a; str_value = b; };
    
    void print_data()
    {
        std::cout << int_value << "\t" << "str_value" << "\n";
    }
    
};

void swap_data1(Data& data_1, Data& data_2);
void swap_data2(Data& data_1, Data& data_2);
void swap_data3(Data& data_1, Data& data_2);

int main()
{
    Data data_1(1, "string_1");
    Data data_2(2, "string_2");

    data_1.print_data();
    data_2.print_data();
    std::cout << "\n";

    swap_data1(data_1, data_2);

    data_1.print_data();
    data_2.print_data();
    std::cout << "\n";

    swap_data2(data_1, data_2);

    data_1.print_data();
    data_2.print_data();
    std::cout << "\n";

    swap_data3(data_1, data_2);

    data_1.print_data();
    data_2.print_data();
    std::cout << "\n";

    return 0;
}

void swap_data1(Data& data_1, Data& data_2)
{
    
    
    std::lock(data_1.data_mutex, data_2.data_mutex);
    std::lock_guard lk1(data_1.data_mutex, std::adopt_lock);
    std::lock_guard lk2(data_2.data_mutex, std::adopt_lock);

   // data_1.data_mutex.lock();
   // data_2.data_mutex.lock();

    int temp_int = data_1.int_value;
    data_1.int_value = data_2.int_value;
    data_2.int_value = temp_int;

    std::string temp_str = data_1.str_value;
    data_1.str_value = data_2.str_value;
    data_2.str_value = temp_str;

    
   // data_1.data_mutex.unlock();
  //  data_2.data_mutex.unlock();
}


void swap_data2(Data& data_1, Data& data_2)
{
    std::unique_lock<std::mutex> lk1(data_1.data_mutex, std::defer_lock);
    std::unique_lock<std::mutex> lk2(data_2.data_mutex, std::defer_lock);
    std::lock(lk1, lk2);

    int temp_int = data_1.int_value;
    data_1.int_value = data_2.int_value;
    data_2.int_value = temp_int;

    std::string temp_str = data_1.str_value;
    data_1.str_value = data_2.str_value;
    data_2.str_value = temp_str;
}

void swap_data3(Data& data_1, Data& data_2)
{
    std::scoped_lock(data_1.data_mutex, data_2.data_mutex);

    int temp_int = data_1.int_value;
    data_1.int_value = data_2.int_value;
    data_2.int_value = temp_int;

    std::string temp_str = data_1.str_value;
    data_1.str_value = data_2.str_value;
    data_2.str_value = temp_str;   
}