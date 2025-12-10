


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