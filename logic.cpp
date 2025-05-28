#include "logic.h"

Errors chooseFile(AppContext* context, char* newValue) {
    Errors status = Ok;
    QString filePath = QString::fromUtf8(newValue);
    QFileInfo file_info(filePath);
    if (strlen(newValue) >= MAX_LENGTH) {
        status = CannotOpenFile;
    }
    else if ((file_info.suffix().toLower() == "csv") ) {
        strncpy(context->fileName, newValue, MAX_LENGTH - 1);
        context->fileName[MAX_LENGTH - 1] = '\0';
        context->fileStatus = 1;
    }
    else
        status = WrongFile;
    return status;
}

void updateColumn(AppContext* context, int newValue) {
    context->chosenColumn = newValue;
}

void updateRegion(AppContext* context, char* newValue) {
    strncpy(context->chosenRegion, newValue, MAX_LENGTH - 1);
    context->chosenRegion[MAX_LENGTH - 1] = '\0';
}

Errors loadData(AppContext* context) {
    Errors status = Ok;
    FILE *file = fopen(context->fileName, "r");
    if (!file) {
        status = CannotOpenFile;
    }
    else {
        char line[MAX_LENGTH];
        context->tableData.dataList = List{NULL, NULL};
        context->tableData.headers = List{NULL, NULL};
        if (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            char *token = strtok(line, ",");
            while (token && context->tableData.cols < MAX_COLUMNS) {
                Demography header;
                strncpy(header.region, token, MAX_LENGTH-1);
                addCsvRow(&context->tableData.headers, &header);
                token = strtok(NULL, ",");
                context->tableData.cols++;
            }
        }

        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            if (strlen(line) == 0) {
                context->tableData.invalidRows++;
                continue;
            }
            Demography rowData;
            int col = 0;
            char *token = strtok(line, ",");

            while (token && col < context->tableData.cols  && col < MAX_ROWS) {
                if (strlen(token) == 0) {
                    context->tableData.invalidRows++;
                    break;
                }
                switch(col) {
                case YEAR_COLUMN: strncpy(rowData.year, token, MAX_LENGTH-1); break;
                case REGION_COLUMN: strncpy(rowData.region, token, MAX_LENGTH-1); break;
                case NPG_COLUMN: strncpy(rowData.npg, token, MAX_LENGTH-1); break;
                case BIRTH_RATE_COLUMN: strncpy(rowData.birth_rate, token, MAX_LENGTH-1); break;
                case DEATH_RATE_COLUMN: strncpy(rowData.death_rate, token, MAX_LENGTH-1); break;
                case GDW_COLUMN: strncpy(rowData.gdw, token, MAX_LENGTH-1); break;
                case URBANIZATION_COLUMN: strncpy(rowData.urbanization, token, MAX_LENGTH-1); break;
                }
                token = strtok(NULL, ",");
                col++;
            }
            if (col != MAX_COLUMNS) {
                context->tableData.invalidRows++;
            }
            else {
            addCsvRow(&context->tableData.dataList, &rowData);
            context->tableData.validRows++;
            }
        }
    }

    if (context->tableData.validRows == 0 && status == Ok) {
        status = EmptyFile;
    }
    fclose(file);
    return status;
}

int compareByYear(const void *a, const void *b) {
    const DataPoint *pointA = (const DataPoint *)a;
    const DataPoint *pointB = (const DataPoint *)b;

    return (pointA->year - pointB->year);
}

void addCsvRow(List* list, Demography* row) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = *row;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

int compareYears(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

List init(Demography* data) {
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = *data;
    root->next = NULL;
    return List{root, root};
}

void initLines(AppContext* context) {
    context->tableData.invalidRows = 0;
    context->tableData.validRows = 0;
    context->tableData.dataList.head = NULL;
    context->tableData.headers.head = NULL;
    context->tableData.cols = 0;
    context->tableData.sizeDataColum = 0;
}

void clearList(List* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void clear(AppContext* context) {
    memset(context->chosenRegion, 0, MAX_LENGTH);
    clearList(&context->tableData.dataList);
    clearList(&context->tableData.headers);
    memset(&context->metrics, 0, sizeof(Metrics));
    context->tableData.invalidRows = 0;
    context->tableData.sizeDataColum = 0;
}

void initialize(AppContext* context) {
    context->metrics = Metrics();
    context->metrics.max = 0;
    context->metrics.min = 0;
    context->metrics.median = 0;
    context->tableData.invalidRows = 0;
    context->tableData.validRows = 0;
    context->tableData.sizeDataColum = 0;
    context->tableData.cols = 0;
    context->chosenRegion[0] = '\0';
    context->chosenColumn = -1;
    strncpy(context->fileName, "File not selected", MAX_LENGTH);
}

Errors calculateMetrics(AppContext* context) {
    Errors status = Ok;
    int count = 0;
    Node* current = context->tableData.dataList.head;
    while (current != nullptr) {
        if (strcmp(current->data.region, context->chosenRegion) == 0) {
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        status = WrongRegion;
        return status;
    }

    if (context->metrics.points != nullptr) {
        free(context->metrics.points);
        context->metrics.points = nullptr;
    }

    context->metrics.points = (DataPoint*)malloc(count * sizeof(DataPoint));
    context->metrics.count = count;

    current = context->tableData.dataList.head;
    int index = 0;
    while (current != nullptr) {
        if (strcmp(current->data.region, context->chosenRegion) == 0) {
            context->metrics.points[index].year = atoi(current->data.year);
            strncpy(context->metrics.points[index].region, current->data.region, MAX_LENGTH - 1);

            const char* valueStr = NULL;
            switch (context->chosenColumn + 2) {
            case NPG_COLUMN: valueStr = current->data.npg; break;
            case BIRTH_RATE_COLUMN: valueStr = current->data.birth_rate; break;
            case DEATH_RATE_COLUMN: valueStr = current->data.death_rate; break;
            case GDW_COLUMN: valueStr = current->data.gdw; break;
            case URBANIZATION_COLUMN: valueStr = current->data.urbanization; break;
            default: valueStr = "0"; break;
            }

            char* endptr;
            context->metrics.points[index].value = strtod(valueStr, &endptr);
            if (valueStr == endptr) {
                context->metrics.points[index].value = 0.0;
            }

            index++;
        }
        current = current->next;
    }
    qsort(context->metrics.points, context->metrics.count, sizeof(DataPoint), compareByValue);
    context->metrics.min = context->metrics.points[0].value;
    context->metrics.max = context->metrics.points[context->metrics.count - 1].value;
    if (context->metrics.count % 2 == 0) {
        context->metrics.median = (context->metrics.points[context->metrics.count/2 - 1].value +
        context->metrics.points[context->metrics.count/2].value) / 2;
        } else {
            context->metrics.median = context->metrics.points[context->metrics.count/2].value;
        }
    qsort(context->metrics.points, context->metrics.count, sizeof(DataPoint), compareByYear);
    return status;
}

int compareByValue(const void *a, const void *b) {
    const DataPoint *pointA = (const DataPoint *)a;
    const DataPoint *pointB = (const DataPoint *)b;

    if (pointA->value < pointB->value) return -1;
    if (pointA->value > pointB->value) return 1;
    return 0;
}
