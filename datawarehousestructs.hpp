#include <cstdint>
#include <cstring>
#include <chrono>

union ValueType{
    float fl;
    double db;
    int32_t i;
    uint64_t ui;
    char ch[32];
};

template <typename T>
struct Record{
public:
    enum Type {float_type, double_type, int_type, uint_type, char_type};
    Record(uint32_t id, char name[64], uint64_t timestamp, Type type, T input_value): id(id), type(type)
    {
        std::memcpy(Name, name, 64);
        defineValueType(input_value);
        timestamp = std::chrono::system_clock::now();
    };
private:
    void defineValueType(T input_value){
        switch (type)
        {
        case float_type:
            value.fl = input_value;
            break;
        case double_type:
            value.db = input_value;
            break;
        case int_type:
            value.i = input_value;
            break;
        case uint_type:
            value.ui = input_value;
            break;
        case char_type:
            std::memcpy(value.ch, input_value, 32);
            break;
        }
    }
    uint32_t id;
    char Name[64];
    uint64_t timestamp;
    Type type;
    ValueType value;
};