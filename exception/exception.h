#pragma once

#include <string>
#include <utility>

namespace my_exception {

class BaseException : public std::exception {
public:
    explicit BaseException(std::string message) : exception_message_(std::move(message)) {};
    [[nodiscard]] std::string What() const;

private:
    std::string exception_message_;
};

class ParserException : public BaseException { ;
public:
    explicit ParserException(const std::string& message) : BaseException("Invalid input command: " + message) {}
};

class ImageException : public BaseException {
public:
    explicit ImageException(const std::string& message) : BaseException("Invalid image: " +
        message) {};
};

class FiltersException : public BaseException {
public:
    explicit FiltersException(const std::string& message) : BaseException("Invalid filter: " +
        message) {};
};

void React(const BaseException& e);

} // my_exception namespace
