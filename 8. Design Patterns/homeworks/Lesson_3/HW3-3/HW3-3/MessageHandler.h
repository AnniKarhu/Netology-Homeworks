#pragma once

#include "LogMessage.h"

class FatalErrorMessageException : public std::exception
{
public:
    const char* what() const override { return "Fatal error exception"; }
};

class UnknownMessageException : public std::exception
{
public:
    const char* what() const override { return "Exception - unknown message was not handled"; }
};



class MessageHandler
{
public:
    explicit MessageHandler(std::unique_ptr<MessageHandler> NextHandler) : NextHandler_(std::move(NextHandler)) {};

    virtual ~MessageHandler() = default;
    void GetLogMessage(const LogMessage& log_message)
    {
        if (HandleMessage(log_message))
        {
            return;
        }
        else
            NextHandler_->GetLogMessage(log_message);
    }

private:

    virtual bool HandleMessage(const LogMessage& log_message) = 0;
    std::unique_ptr<MessageHandler> NextHandler_ = nullptr;
};

class WarningMessageHandler : public MessageHandler
{
public:
    explicit WarningMessageHandler(std::unique_ptr<MessageHandler> NextHandler) : MessageHandler(std::move(NextHandler)) {};

private:

    bool HandleMessage(const LogMessage& log_message) override
    {
        //std::cout << "go through WarningMessageHandler. Message_str = " << log_message.message() << "\n";

        if (log_message.msg_type() == MsgType::msg_type_warning)            
        {
            std::string temp_str = log_message.message();
            std::cout << log_message.message() << "\n";
            return true;
        }
        else
            return false;
    }

};

class ErrorMessageHandler : public MessageHandler
{
public:
    explicit ErrorMessageHandler(std::unique_ptr<MessageHandler> NextHandler, const std::string& file_name) : MessageHandler(std::move(NextHandler))
    {
        file_name_ = file_name;
    }

private:
    bool HandleMessage(const LogMessage& log_message) override
    {
       // std::cout << "go through ErrorMessageHandler. Message_str = " << log_message.message() << "\n";
        
        if (log_message.msg_type() == MsgType::msg_type_error)
        {
            std::ofstream file_(file_name_, std::ios::app);
            if (file_.is_open())
            {
                file_ << log_message.message() << "\n";
            }
            file_.close();
            return true;
        }
        else
            return false;
    }


    std::string file_name_;
};

class FatalErrorMessageHandler : public MessageHandler
{
public:
    FatalErrorMessageHandler(std::unique_ptr<MessageHandler> NextHandler) : MessageHandler(std::move(NextHandler)) {};

private:
    bool HandleMessage(const LogMessage& log_message) override
    {
       // std::cout << "go through FatalErrorMessageHandler. Message_str = " << log_message.message() << "\n";
        
        if (log_message.msg_type() == MsgType::msg_type_fatalerror)
        {

            throw FatalErrorMessageException();
            // return true;
        }
        else
            return false;
    }

    std::string file_name_;
};

class UnknownMessageHandler : public MessageHandler
{
public:
    UnknownMessageHandler(std::unique_ptr<MessageHandler> NextHandler) : MessageHandler(std::move(NextHandler)) {};
private:

    bool HandleMessage(const LogMessage& log_message) override
    {
       // std::cout << "go through UnknownMessageHandler. Message_str = " << log_message.message() << "\n";
        
        if (log_message.msg_type() == MsgType::msg_type_unknown)
        {
            throw UnknownMessageException();
            //return true;
        }
        else
            return false;
    }
};