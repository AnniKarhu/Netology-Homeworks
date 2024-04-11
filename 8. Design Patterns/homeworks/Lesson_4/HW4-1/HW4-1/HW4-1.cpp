#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0;
    virtual std::string printAsText() const = 0;
    virtual std::string printAsJSON() const = 0;
};

class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

void saveTo(std::ofstream& file, const Printable& printable, Data::Format format)
{
    switch (format)
    {
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}

void saveToAsHTML(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kText);
}

int main()
{
    return 0;
}

//Данный код нарушает принцип открытости/закрытости: функция SaveTo - потребуется изменение уже имеющегося кода функции в случае, если нужно будет добавить новые типы данных. 
// Кроме того, изменения придется вносить в разные части кода - и в класс Data, и в функцию SaveTo.
//Данный код нарушает принцип подстановки Барбары Лисков - существует вероятность, что созданный объект вызовет метод, который вызовет исключение, хотя в ином случае 
// (другой экземпляр объекта) отработает корректно. Здесь экземпляры наследников не всегда могут использовать метод базового класса. Data является наследником printable, но не допускает выполнение методов в некоторых случаях.
//Нарушенмпринцип разделения интерфесов - "толстый интерфейс" у базового класса - узконаправленные методы в базовом классе printable - virtual std::string printAsHTML() const = 0; , virtual std::string printAsText() const = 0; ,
// virtual std::string printAsJSON() const = 0;


//В  данном случае стоит создать наследников от класса Data, избавиться от узкоспециализированных методов в базовом классе, от switch-case, не допускать вызова методов для классов-наследников, если эти методы к ним неприменимы, 
// чтобы вместо выбрасывания исключений не допускать компиляцию такого кода.