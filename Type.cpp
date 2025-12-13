//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8


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