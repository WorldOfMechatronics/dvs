#ifndef DVS_FUNCTION_HEADER_OBJECT_H_
#define DVS_FUNCTION_HEADER_OBJECT_H_

#include <limits.h>
#include <stdint.h>

#include "enumerations.h"

const size_t kMaxNumFunctionHeaderBytes = SCHAR_MAX;

typedef struct S_FunctionHeaderObject
{
    FunctionHeaderObjectType type;
    uint8_t num_bytes;
    uint8_t data[kMaxNumFunctionHeaderBytes];
} FunctionHeaderObject;

FunctionHeaderObject getLastFHO()
{
    FunctionHeaderObject obj;
    obj.type = FHOT_UNKNOWN;

    return obj;
}

#endif

