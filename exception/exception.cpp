#include "exception.h"

#include <iostream>

namespace my_exception {

std::string BaseException::What() const {
    return exception_message_;
}

void React(const BaseException& e) {
    try {
        throw std::logic_error(e.What());
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }
}

} // my_exception namespace
