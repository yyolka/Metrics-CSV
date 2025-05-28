#include "entrypoint.h"

Errors doOperation(Operation operation, AppContext* context, AppParams* params) {
    Errors error = Ok;
    switch(operation) {
    case ChooseFile:
        error = chooseFile(context, params->newValue);
        break;
    case Initialization:
        initialize(context);
        break;
    case LoadData:
        error = loadData(context);
        break;
    case UpdateColumn:
        updateColumn(context, params->newIndex);
        break;
    case Calculation:
        error = calculateMetrics(context);
        break;
    case UpdateRegion:
        updateRegion(context, params->newValue);
        break;
    }
    return error;
}
