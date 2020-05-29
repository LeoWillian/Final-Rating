#pragma once
#include <stdexcept>
#include <string>

inline void error(const std::string& message) {
    throw std::runtime_error(message);
}