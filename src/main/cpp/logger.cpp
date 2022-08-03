
#include "logger.hpp"

#include <string>

namespace logging
{

    LogValue::LogValue(bool value) : type{LogValueType::Boolean}, value{&value} {}
    LogValue::LogValue(double value) : type{LogValueType::Double}, value{&value} {}
    LogValue::LogValue(int value) : type{LogValueType::Int}, value{&value} {}
    LogValue::LogValue(long value) : type{LogValueType::Long}, value{&value} {}
    LogValue::LogValue(std::string &value) : type{LogValueType::String}, value{&value} {}
    LogValue::LogValue(bool *value) : type{LogValueType::BooleanArray}, value{value} {}
    LogValue::LogValue(double *value) : type{LogValueType::DoubleArray}, value{value} {}
    LogValue::LogValue(int *value) : type{LogValueType::IntArray}, value{value} {}
    LogValue::LogValue(long *value) : type{LogValueType::LongArray}, value{value} {}
    LogValue::LogValue(std::string *value) : type{LogValueType::StringArray}, value{value} {}

    LogValueType LogValue::getType()
    {
        return this->type;
    }

    void *LogValue::getValue()
    {
        return this->value;
    }

    Logger *Logger::logger = nullptr;
}