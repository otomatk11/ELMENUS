//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8


// Data types

#ifndef _TYPE_H_
#define _TYPE_H_

#include <string>

enum class DataType {
	INT,
    STR,
    DOUBLE
};

std::string dataTypeName(DataType dt);

#endif // _TYPE_H_