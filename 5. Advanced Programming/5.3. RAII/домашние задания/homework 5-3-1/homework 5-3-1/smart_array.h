#pragma once

class Smart_array
{
protected:
    int* arr = nullptr;
    int array_size = 0;  //фактический размер массива
    int add_to_array_index = 0; //указатель на индекс для добавленя следующего элемента
public:
    explicit Smart_array(const int new_size);
    virtual ~Smart_array();

    /* памятка для себя  - про запрет конструктора копирования и оператора присваивания 
    
    https://learn.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-170
    * запрет копирования, перемещения
    * способ позволяет явням образом указываться, будут ли специальные функции создаваться автоматически
    * предотвращает нежелательный вызов функции или оператора
    * конструкторы копирования, перемещения и оператор перемещения и присваивания создаются компилятором автоматически, если не были явно объявлены в классе
   
   //старый способ решения проблемы - объявление в private - недостатки метода по ссылке выше:
   struct noncopyable
    {
    noncopyable() {};
    private:
        noncopyable(const noncopyable&);
        noncopyable& operator=(const noncopyable&);
    };

    //начиная с С++11
    struct noncopyable
    {
        noncopyable() =default;
        noncopyable(const noncopyable&) =delete;
        noncopyable& operator=(const noncopyable&) =delete;
    };

    */
  
    Smart_array(const Smart_array&) = delete;
    Smart_array& operator=(const Smart_array&) = delete;

    virtual void add_element(const int new_value); //добавить элемент
    virtual int get_element(const int elem_index);   //получить элемент по индексу
};