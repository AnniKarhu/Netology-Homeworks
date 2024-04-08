
#include <iostream>
#include <vector>
#include <fstream>

#include "LogMessage.h"
#include "MessageHandler.h"


int main()
{
    auto unknown_message_handler = std::make_unique<UnknownMessageHandler>(nullptr);
    auto warning_message_handler = std::make_unique<WarningMessageHandler>(std::move(unknown_message_handler));
    auto errore_message_handler  = std::make_unique<ErrorMessageHandler>(std::move(warning_message_handler), "errors_log.txt");
    auto message_handler = std::make_unique<FatalErrorMessageHandler>(std::move(errore_message_handler));

    LogMessageWarning       new_Log_message_warning(" it is a warning message");
    LogMessageError         new_Log_message_error(" it is an error message");
    LogMessageFatalError    new_Log_message_fatalerror(" it is a fatal error message");
    LogMessageUnknown       new_Log_message_unknown(" it is an unknown message");

    try
    {
        message_handler->GetLogMessage(new_Log_message_unknown);
        std::cout << "\n";
    }
    catch (const UnknownMessageException& ex)
    {
       std::cout << ex.what() << "\n";
    }
    catch (...)
    {
        std::cout << "Unknown exception\n";
        return 1;
    }

    try
    {
        message_handler->GetLogMessage(new_Log_message_warning);
        std::cout << "\n";
        message_handler->GetLogMessage(new_Log_message_error);
        std::cout << "\n";
        message_handler->GetLogMessage(new_Log_message_fatalerror);              
    }
    catch (const FatalErrorMessageException& ex)
    {
        std::cout << "exception 2: ";
        std::cout << ex.what();
        return 2;
    }
    catch (...)
    {
        std::cout << "exception 3: ";
        std::cout << "Unknown exception\n";
        return 3;
    }


   

    return 0;

}
