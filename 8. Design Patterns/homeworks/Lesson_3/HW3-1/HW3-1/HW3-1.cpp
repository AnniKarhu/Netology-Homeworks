
#include <iostream>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class LogCommandConsole : public LogCommand {
public:
    LogCommandConsole() {};
    void print(const std::string& message) override
    {
        std::cout << message;
    }
};

class LogCommandFile : public LogCommand {
public:
    explicit LogCommandFile (std::string file_name) : file_name_(file_name) {};
    void print(const std::string& message) override
    {
        std::ofstream file_(file_name_, std::ios::app);
        if (file_.is_open())
        {
            file_ << message;
        }

        file_.close();
    }
private:
    std::string file_name_;
};

int main()
{
    std::cout << "Hello World!\n";

    LogCommand* LogConsole = new LogCommandConsole();
    LogConsole->print("Some messsage 1\n");

    LogCommand* LogFile = new LogCommandFile("log.txt");
    LogFile->print("Some messsage 2\n");
    LogFile->print("Some messsage 3\n");

}

