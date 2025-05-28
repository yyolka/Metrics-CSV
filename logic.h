#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>
#include <stdio.h>
#include "appcontext.h"
#include <QFileDialog>
#include <string.h>
#include <float.h>


typedef enum {
    Ok,
    FileNotChosen,
    CannotOpenFile,
    EmptyFile,
    WrongFile,
    WrongRegion,
    RegionNotChosen,
    ColumnNotChosen,
    TooLong
} Errors;

void disposeLinkedList(List* list);
void initList(List* list, size_t dataSize);
void addCsvRow(List* list, Demography* row);
void clear(AppContext* context);
void clearList(List* list);
void initialize(AppContext* context);
Errors loadData(AppContext* context);
void initLines(AppContext* context);
Errors calculateMetrics(AppContext* context);
void updateColumn(AppContext* context, int newIndex);
void updateRegion(AppContext* context, char* newValue);
int compareByYear(const void *a, const void *b);
int compareByValue(const void *a, const void *b);
Errors chooseFile(AppContext* context, char* newValue);
int compareYears(const void* a, const void* b);
void findMax();
void findMin();
void findMedian();

#endif // LOGIC_H
