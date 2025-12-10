


#include "Type.h"

using namespace std;

string dataTypeName(DataType dt) {
    switch(dt) {
        case DataType::INT: return "int";
        case DataType::STR: return "string";
        case DataType::DOUBLE: return "double";
    }
    return "Unknown";
}