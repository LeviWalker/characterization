
#pragma once

#include <iostream>   // for debugging
#include <functional> // for std::function
#include <map>
#include <stdexcept> // needed for std::runtime_error
#include <string>
#include <type_traits> // needed for std::is_same_v
#include <vector>

namespace logging
{
    enum LogValueType
    {
        Boolean,
        Double,
        Int,
        Long,
        String,
        BooleanArray,
        DoubleArray,
        IntArray,
        LongArray,
        StringArray
    };

    class LogValue
    {
    private:
        LogValueType type;
        void *value;

    public:
        LogValue(bool value);
        LogValue(double value);
        LogValue(int value);
        LogValue(long value);
        LogValue(std::string &value);
        LogValue(bool *value);
        LogValue(double *value);
        LogValue(int *value);
        LogValue(long *value);
        LogValue(std::string *value);
        LogValueType getType();
        void *getValue();
        std::string asJSONValue();
        bool asBoolean();
        double asDouble();
        int asInteger();
        long asLong();
        std::string asString();
        bool* asBooleanArray();
        double* asDoubleArray();
        int* asIntegerArray();
        long* asLongArray();
        std::string* asStringArray();

    };

    typedef std::function<LogValue()> LogValueGetter;

    class Logger
    {
    private:
        static Logger *logger;
        std::map<std::string, LogValueGetter> map;
        Logger(const std::string &fileName);

    public:
        static void Init();
        static void Init(const std::string &fileName);
        static void Periodic();
        static void AddBoolean(const std::string &name, const std::function<bool()> &getter);
        static void AddDouble(const std::string &name, const std::function<double()> &getter);
        static void AddInt(const std::string &name, const std::function<int()> &getter);
        static void AddLong(const std::string &name, const std::function<long()> &getter);
        static void AddString(const std::string &name, const std::function<std::string()> &getter);
        static void AddBooleanArray(const std::string &name, const std::function<bool *()> &getter);
        static void AddDoubleArray(const std::string &name, const std::function<double *()> &getter);
        static void AddIntArray(const std::string &name, const std::function<int *()> &getter);
        static void AddLongArray(const std::string &name, const std::function<long *()> &getter);
        static void AddStringArray(const std::string &name, const std::function<std::string *()> &getter);
        static void GetValue(const std::string &name, double timestamp, void* ptr);
        static void Remove(const std::string &name);
    };
}