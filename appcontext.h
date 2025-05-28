#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define MAX_LENGTH 100
#define MAX_COLUMNS 7
#define MAX_ROWS 3000

typedef struct {
    char year[MAX_LENGTH];
    char region[MAX_LENGTH];
    char npg[MAX_LENGTH];
    char birth_rate[MAX_LENGTH];
    char death_rate[MAX_LENGTH];
    char gdw[MAX_LENGTH];
    char urbanization[MAX_LENGTH];
} Demography;

typedef struct {
    double value;
    int year;
    char region[MAX_LENGTH];
} DataPoint;

typedef struct {
    DataPoint* points;
    double max;
    double min;
    double median;
    int count;
} Metrics;

typedef struct Node {
    Demography data;
    Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

typedef struct {
    List dataList;
    List headers;
    int sizeDataColum;
    int invalidRows;
    int validRows;
    int cols;
} TableData;

typedef struct {
    TableData tableData;
    Metrics metrics;
    char chosenRegion[MAX_LENGTH];
    int chosenColumn;
    char fileName[MAX_LENGTH];
    int fileStatus;
} AppContext;

typedef enum {
    YEAR_COLUMN,
    REGION_COLUMN,
    NPG_COLUMN,
    BIRTH_RATE_COLUMN,
    DEATH_RATE_COLUMN,
    GDW_COLUMN,
    URBANIZATION_COLUMN
} numberColumns;

#endif // APPCONTEXT_H
