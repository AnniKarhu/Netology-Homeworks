#pragma once

#include <iostream>

enum class MsgType
{
    msg_type_warning,
    msg_type_error,
    msg_type_fatalerror,
    msg_type_unknown
};

class LogMessage {
public:
    virtual MsgType msg_type()  const = 0;
    virtual const std::string& message() const  = 0;
    virtual ~LogMessage() = default;
};

class LogMessageWarning : public LogMessage
{
public:
    explicit LogMessageWarning(const  std::string& message_str) noexcept : message_str_(message_str)   {  };
    MsgType msg_type() const override
    {
        return MsgType::msg_type_warning;
    };
    const std::string& message() const override
    {
        return message_str_;        
    }
private:
    std::string message_str_;
};

class LogMessageError : public LogMessage
{
public:
    explicit LogMessageError(const  std::string& message_str)  noexcept : message_str_(message_str) { };
    MsgType msg_type() const override
    {
        return MsgType::msg_type_error;
    };
    const std::string& message() const  override
    {
        return message_str_;  
    }
private:
    std::string message_str_;
};

class LogMessageFatalError : public LogMessage
{
public:
    explicit LogMessageFatalError(const  std::string& message_str) noexcept : message_str_(message_str) { };
    MsgType msg_type() const override
    {
        return MsgType::msg_type_fatalerror;
    };
    const  std::string& message() const override
    {
        return message_str_; 
    }
private:
    std::string message_str_;
};

class LogMessageUnknown : public LogMessage
{
public:
    explicit LogMessageUnknown(const  std::string& message_str) noexcept : message_str_(message_str) { };
    MsgType msg_type() const override
    {
        return MsgType::msg_type_unknown;
    };
    const std::string& message() const override
    {
        return  message_str_; 
    }
private:
    std::string message_str_;
};
