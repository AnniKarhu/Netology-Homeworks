
#include <iostream>
#include <vector>
#include <fstream>

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
       std::cout << message;
   };
};

class ObserverError : public Observer
{
public:
    explicit ObserverError(std::string file_name) : file_name_(file_name) {};
    void onError(const std::string& message) override
    {
        std::ofstream file_(file_name_, std::ios::app);
        if (file_.is_open())
        {
            file_ << message;
        }

        file_.close();
    };
private:
    std::string file_name_;
};

class ObserverFatalError : public  ObserverError, public ObserverWarning
{
public:
    explicit ObserverFatalError(std::string file_name) : ObserverError(file_name) {};
    void onFatalError(const std::string& message) override
    {
        ObserverError::onError(message);
        ObserverWarning::onWarning(message);
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
            // if (observer != nullptr)
           // observer->onWarning(message);
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
            // if (observer != nullptr)
           // observer->onError(message);
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
            // if (observer != nullptr)
           // observer->onFatalError(message);
        }
    }

    void AddObserver(std::weak_ptr<Observer> observer) 
    {
        observes_.push_back(observer);
    }
private:
    std::vector<std::weak_ptr<Observer>> observes_;
    //std::vector<Observer*> observes_;
};

int main()
{
    Observer* ObserverWarningObj    = new ObserverWarning;
    auto ObserverWarningObj1 = std::make_shared <ObserverWarning>();
    auto ObserverWarningObj2 = std::make_shared <ObserverWarning>();

    Observer* ObserverErrorObj      = new ObserverError("ObserverErrorObj.txt");
    auto ObserverErrorObj1 = std::make_shared <ObserverError>("ObserverErrorObj1.txt");
    auto ObserverErrorObj2 = std::make_shared <ObserverError>("ObserverErrorObj2.txt");

    //при создании объекта ObserverFatalErrorObj - использование static_cast<ObserverError> - не уверена, что это хорошо. 
    // Но и писать дважды один и тот же код (методы onError и onWarning) не хотелось, чтобы избежать дублирования кода.
    // или здесь стоит наследовать так же от Observer и прописать две отдельные глобальрые функции - для печати в консоль и для печати в файл - и использовать их внутри методов  onError, onWarning и onFatalError?
    //без static_cast компилятор не может привести ObserverFatalError к Observer 
    Observer* ObserverFatalErrorObj = static_cast<ObserverError*> (new ObserverFatalError("ObserverFatalError.txt"));
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
    // observed_obj.AddObserver(ObserverFatalErrorObj1);
    observed_obj.AddObserver(static_cast<std::shared_ptr<ObserverError>>(ObserverFatalErrorObj1));
    observed_obj.AddObserver(static_cast<std::shared_ptr<ObserverError>>(ObserverFatalErrorObj2));

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
