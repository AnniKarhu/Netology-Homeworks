#include <fstream>

enum class Format
{
    kText,
    kHTML,
    kJSON
};

class Printable
{
public:
    virtual ~Printable() = default;

    
    virtual std::string print() const = 0;
    virtual std::string get_plain_text() const = 0;
    virtual Format get_format() const = 0;
   
protected:
    Printable(std::string data) : data_(std::move(data)) {};
    std::string data_;

};

class Data_HTML : public Printable
{
public:
    Data_HTML(std::string data)  : Printable(data) {}
    std::string print() const override
    {
        return "<html>" + data_ + "<html/>";
    }
    std::string get_plain_text() const override
    {
        return  data_ ;
    };
    Format get_format() const {
        return Format::kHTML;  
    }
};

class Data_Text : public Printable
{
public:
    Data_Text(std::string data) : Printable(data) {}
    std::string print() const override
    {
        return data_;
    }
    std::string get_plain_text() const override
    {
        return  data_;
    };
    Format get_format() const {
        return Format::kText;  
    }
};

class Data_JSON : public Printable
{
public:
    Data_JSON(std::string data) : Printable(data) {}
    std::string print() const override
    {
        return "{ \"data\": \"" + data_ + "\"}";
    }
    std::string get_plain_text() const override
    {
        return  data_;
    };
    Format get_format() const {
        return Format::kJSON;  
    }
};


void saveTo(std::ofstream& file, const Printable& printable)
{
     file << printable.print();       
}


void saveToAsHTML(std::ofstream& file, const Printable& printable) {
    Data_HTML data_html_obj(printable.get_plain_text());
    saveTo(file, data_html_obj);
}

void saveToAsJSON(std::ofstream& file, const Printable& printable) {
        
    Data_JSON data_json_obj(printable.get_plain_text());
    saveTo(file, data_json_obj);
}

void saveToAsText(std::ofstream& file, const Printable& printable) {
    Data_Text data_text_obj(printable.get_plain_text());
    saveTo(file, data_text_obj);   
}

void saveToAsHTML_2(std::ofstream& file, const Printable& printable) {

    if (printable.get_format() != Format::kHTML)
    {
        throw std::runtime_error("Invalid format!");
    }
    Data_HTML data_html_obj(printable.get_plain_text());
    saveTo(file, data_html_obj);
}

void saveToAsJSON_2(std::ofstream& file, const Printable& printable) {

    if (printable.get_format() != Format::kJSON)
    {
        throw std::runtime_error("Invalid format!");
    }
    Data_JSON data_json_obj(printable.get_plain_text());
    saveTo(file, data_json_obj);
}

void saveToAsText_2(std::ofstream& file, const Printable& printable) {
    if (printable.get_format() != Format::kText)
    {
        throw std::runtime_error("Invalid format!");
    }
    Data_Text data_text_obj(printable.get_plain_text());
    saveTo(file, data_text_obj);
}

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    Data_HTML data_html_obj("some data for HTML object");
    std::cout << data_html_obj.print() << "\n";

    Data_JSON data_json_obj("some data for JSON object");
    std::cout << data_json_obj.print() << "\n";

    Data_Text data_text_obj("some data for text object");
    std::cout << data_text_obj.print() << "\n";

    std::ofstream file_("sample_file.txt", std::ios::app);
    if (file_.is_open())
    {
        saveTo(file_, data_html_obj);
        file_ <<  "\n"; 
        saveToAsHTML(file_, data_html_obj);
        file_ << "\n";
        saveToAsJSON(file_, data_html_obj);
        file_ << "\n";
        saveToAsText(file_, data_html_obj);
        file_ << "\n";
        file_ << "*********************\n\n";


        saveTo(file_, data_json_obj);
        file_ << "\n";
        saveToAsHTML(file_, data_json_obj);
        file_ << "\n";
        saveToAsJSON(file_, data_json_obj);
        file_ << "\n";
        saveToAsText(file_, data_json_obj);
        file_ << "\n";
        file_ << "*********************\n\n";

        saveTo(file_, data_text_obj);
        file_ << "\n";
        saveToAsHTML(file_, data_text_obj);
        file_ << "\n";
        saveToAsJSON(file_, data_text_obj);
        file_ << "\n";
        saveToAsText(file_, data_text_obj);
        file_ << "\n";
        file_ << "*********************\n\n";

        try
        {
            saveToAsHTML_2(file_, data_json_obj);
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << "\n";
        }
    }
    file_.close();

}

