
#include <iostream>
#include <vector>
#include <fstream>

void PrintMsgToFile(const std::string& message, const std::string& file_name)
{
std::ofstream file_(file_name, std::ios::app);
        if (file_.is_open())
        {
            file_ << message;
        }
        file_.close();
}

void PrintMsgToConsole(const std::string& message)
{
    std::cout << message;
}

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {};
    virtual void onError(const std::string& message) {};
    virtual void onFatalError(const std::string& message) {};
};

class ObserverWarning : public Observer
{
public:
   void onWarning(const std::string& message)  override
   {
       PrintMsgToConsole(message);
   };
};

class ObserverError : public Observer
{
public:
    explicit ObserverError(std::string file_name) : file_name_(file_name) {};
    void onError(const std::string& message) override
    {
        PrintMsgToFile(message, file_name_);
    };
private:
    std::string file_name_;
};

class ObserverFatalError : public  Observer
{
public:
    explicit ObserverFatalError(std::string file_name) : file_name_(file_name) {};
    void onFatalError(const std::string& message) override
    {
        PrintMsgToFile(message, file_name_);
        PrintMsgToConsole(message);
    };
private:
    std::string file_name_;
};

class Observed
{
public:
    Observed() {};
    void warning(const std::string& message) const
    {
        std::cout << "Observed object warning: " << message;
        for (auto observer : observes_)
        {
            if (auto strong_ptr = observer.lock())
            {
                strong_ptr->onWarning(message);
            }           
        }
    }
    void error(const std::string& message) const
    {
        std::cout << "Observed object error: " << message;
        for (auto observer : observes_)
        {
            if (auto strong_ptr = observer.lock())
            {
                strong_ptr->onError(message);
            }
         }
    }
    void fatalError(const std::string& message) const
    {
        std::cout << "Observed object fatal error: " << message;
        for (auto observer : observes_)
        {
            if (auto strong_ptr = observer.lock())
            {
                strong_ptr->onFatalError(message);
            }
            
        }
    }

    void AddObserver(std::weak_ptr<Observer> observer) 
    {
        observes_.push_back(observer);
    }
private:
    std::vector<std::weak_ptr<Observer>> observes_;
    
};

int main()
{
    Observer* ObserverWarningObj    = new ObserverWarning;
    auto ObserverWarningObj1 = std::make_shared <ObserverWarning>();
    auto ObserverWarningObj2 = std::make_shared <ObserverWarning>();

    Observer* ObserverErrorObj      = new ObserverError("ObserverErrorObj.txt");
    auto ObserverErrorObj1 = std::make_shared <ObserverError>("ObserverErrorObj1.txt");
    auto ObserverErrorObj2 = std::make_shared <ObserverError>("ObserverErrorObj2.txt");

    
    Observer* ObserverFatalErrorObj = new ObserverFatalError("ObserverFatalError.txt");
    auto ObserverFatalErrorObj1 = std::make_shared<ObserverFatalError>("ObserverFatalError1.txt");
    auto ObserverFatalErrorObj2 = std::make_shared<ObserverFatalError>("ObserverFatalError2.txt");

    ObserverWarningObj->onWarning("simple onWarning \n");
    ObserverErrorObj->onError("simple onError\n");
    ObserverFatalErrorObj->onFatalError("simple onFatalError\n");

    Observed observed_obj;
    
    observed_obj.AddObserver(ObserverWarningObj1);
    observed_obj.AddObserver(ObserverWarningObj2);
    observed_obj.AddObserver(ObserverErrorObj1);
    observed_obj.AddObserver(ObserverErrorObj2);
    observed_obj.AddObserver(ObserverFatalErrorObj1);
    observed_obj.AddObserver(ObserverFatalErrorObj2);

    observed_obj.error("observed error 1\n");
    observed_obj.warning("observed warning 1\n");
    observed_obj.fatalError("observed fatal error 1\n");

    delete ObserverWarningObj;
    delete ObserverErrorObj;
    delete ObserverFatalErrorObj;

    ObserverWarningObj1.reset();
    ObserverErrorObj1.reset();
    ObserverFatalErrorObj1.reset();

    observed_obj.error("observed error 2\n");
    observed_obj.warning("observed warning 2\n");
    observed_obj.fatalError("observed fatal error 2\n");
}
