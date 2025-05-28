#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "logic.h"

typedef enum {
    Initialization,
    ChooseFile,
    LoadData,
    Calculation,
    UpdateColumn,
    UpdateRegion
} Operation;

typedef struct {
    char newValue[MAX_LENGTH];
    int newIndex;
} AppParams;

Errors doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
