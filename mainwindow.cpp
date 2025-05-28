#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::onLoadDataButtonClicked);
    connect(ui->chooseFileButton, &QPushButton::clicked, this, &MainWindow::onChooseFileButtonClicked);
    connect(ui->calculateMetricsButton, &QPushButton::clicked, this, &MainWindow::onCalculateMetricsButtonClicked);
    connect(ui->columnComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onColumnComboBoxClicked);
    connect(ui->regionLineEdit, &QLineEdit::textChanged, this, &MainWindow::onRegionLineEditClicked);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setupGraphArea();
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLabels() {
    ui->fileNameLineEdit->setText(QString::fromStdString(context.fileName));
    ui->maxLineEdit->setText(QString::number(context.metrics.max));
    ui->minLineEdit->setText(QString::number(context.metrics.min));
    ui->medianLineEdit->setText(QString::number(context.metrics.median));
    ui->columnComboBox->setCurrentIndex(context.chosenColumn);
    ui->regionLineEdit->setText(QString::fromStdString(context.chosenRegion));

}

void MainWindow::onColumnComboBoxClicked(int index) {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->newIndex = index;
    doOperation(UpdateColumn, &context, param);
    free(param);
}

void MainWindow::onRegionLineEditClicked() {
    if (strlen(ui->regionLineEdit->text().toStdString().c_str()) < MAX_LENGTH) {
        AppParams* param = (AppParams*) malloc(sizeof(AppParams));
        strcpy(param->newValue, ui->regionLineEdit->text().toStdString().c_str());
        doOperation(UpdateRegion, &context, param);
        free(param);
    }
    else
        warningMessage(TooLong);
}

void MainWindow::onCalculateMetricsButtonClicked() {
    Errors error = Ok;
    if (!context.fileStatus) {
        error = FileNotChosen;
        warningMessage(error);
        updateLabels();
        return;
    }

    if (context.tableData.dataList.head == nullptr) {
        error = CannotOpenFile;
        warningMessage(error);
        updateLabels();
        return;
    }

    if (context.chosenColumn == -1) {
        error = ColumnNotChosen;
        warningMessage(error);
        updateLabels();
        return;
    }

    error = doOperation(Calculation, &context, NULL);

    if (error != Ok) warningMessage(error);
    drawGraph();
    updateLabels();
}


void MainWindow::onChooseFileButtonClicked() {
    Errors status = Ok;
    ui->fileNameLineEdit->clear();
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    strcpy(param->newValue, QFileDialog::getOpenFileName(this, tr("Открыть CSV файл"), "", tr("CSV Files (*.csv)")).toStdString().c_str());
    status = doOperation(ChooseFile, &context, param);
    if (status != Ok) {
        warningMessage(status);
    }
    updateLabels();
    free(param);
}

void MainWindow::onLoadDataButtonClicked() {
    initLines(&context);
    Errors status = Ok;
    if (context.fileStatus) {
        status = doOperation(LoadData, &context, NULL);
        bool filterByRegion = (context.chosenRegion[0] != '\0');
        if (status == Ok) {
            QStringList headers;
            Node* headerNode = context.tableData.headers.head;
            while(headerNode) {
                headers << QString(headerNode->data.region);
                headerNode = headerNode->next;
            }
            ui->tableWidget->setColumnCount(headers.size());
            ui->tableWidget->setHorizontalHeaderLabels(headers);
            ui->tableWidget->setRowCount(0);

            if (context.tableData.dataList.head == nullptr) {
                status = EmptyFile;
            }
            else {
                Node* dataNode = context.tableData.dataList.head;
                int rowIndex = 0;

                while(dataNode) {
                    if(!filterByRegion || strcmp(dataNode->data.region, context.chosenRegion) == 0) {
                        ui->tableWidget->insertRow(rowIndex);
                        ui->tableWidget->setItem(rowIndex, YEAR_COLUMN, new QTableWidgetItem(dataNode->data.year));
                        ui->tableWidget->setItem(rowIndex, REGION_COLUMN, new QTableWidgetItem(dataNode->data.region));
                        ui->tableWidget->setItem(rowIndex, NPG_COLUMN, new QTableWidgetItem(dataNode->data.npg));
                        ui->tableWidget->setItem(rowIndex, BIRTH_RATE_COLUMN, new QTableWidgetItem(dataNode->data.birth_rate));
                        ui->tableWidget->setItem(rowIndex, DEATH_RATE_COLUMN, new QTableWidgetItem(dataNode->data.death_rate));
                        ui->tableWidget->setItem(rowIndex, GDW_COLUMN, new QTableWidgetItem(dataNode->data.gdw));
                        ui->tableWidget->setItem(rowIndex, URBANIZATION_COLUMN, new QTableWidgetItem(dataNode->data.urbanization));

                        rowIndex++;
                    }
                    dataNode = dataNode->next;
                }
                for(int i = 0; i < ui->tableWidget->columnCount(); i++){
                    ui->tableWidget->setColumnWidth(i, 80);
                    if(i == REGION_COLUMN) {
                        ui->tableWidget->setColumnWidth(i, 207);
                    }
                }
            }
        }
        if (!filterByRegion) infoMessage();
    }
    else {
        status = FileNotChosen;
    }

    if (status != Ok) {
        warningMessage(status);
    }
}

void MainWindow::warningMessage(Errors status) {
    QMessageBox::information(this, "Ошибка", getErrorDescription(status));
}

const char* MainWindow::getErrorDescription(Errors status) {
    const char* description;
    switch (status) {
    case FileNotChosen:
        description = "Сначала нужно выбрать файл :(";
        break;
    case ColumnNotChosen:
        description = "Сначала нужно выбрать столбец :(";
        break;
    case RegionNotChosen:
        description = "Сначала нужно выбрать регион :(";
        break;
    case CannotOpenFile:
        description = "Не удалось открыть файл :((";
        break;
    case EmptyFile:
        description = "Пустой файл :(";
        break;
    case WrongFile:
        description = "Неправильный файл";
        break;
    case WrongRegion:
        description = "Нeправильный регион";
        break;
    case TooLong:
        description = "Слишком много";
        break;
    case Ok:
        description = "\0";
        break;
    }
    return description;
}

void MainWindow::infoMessage() {
    char description[MAX_LENGTH];
    infoDescription(description, MAX_LENGTH);
    QMessageBox::information(this, "Уведомление", description);
}

void MainWindow::infoDescription(char* buffer, size_t bufferSize) {
    snprintf(buffer, bufferSize,
             "Всего строк: %d\nКорректных: %d\nНекорректных: %d\n",
             context.tableData.validRows + context.tableData.invalidRows,
             context.tableData.validRows,
             context.tableData.invalidRows);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    if (context.metrics.points != nullptr && context.metrics.count > 0) {
        drawGraph();
    }
}

void MainWindow::drawGraph() {
    if (context.metrics.points == nullptr || context.metrics.count == 0) return;

    scene->clear();
    QFont yearFont("Arial", 8);
    QFont valueFont("Arial", 7);

    QRectF viewRect = ui->graphicsView->viewport()->rect();
    qreal availableWidth = viewRect.width() - 140;
    qreal availableHeight = viewRect.height() - 120;

    availableWidth = qMax(availableWidth, 200.0);
    availableHeight = qMax(availableHeight, 150.0);

    qreal leftMargin = 70;
    qreal topMargin = 30;
    qreal bottomMargin = 30;
    qreal graphHeight = availableHeight - topMargin - bottomMargin;
    qreal graphBottomY = topMargin + graphHeight;

    scene->addLine(leftMargin, graphBottomY, leftMargin + availableWidth, graphBottomY, QPen(Qt::black, 2)); // X
    scene->addLine(leftMargin, graphBottomY, leftMargin, topMargin, QPen(Qt::black, 2)); // Y

    double minY = context.metrics.min;
    double maxY = context.metrics.max;
    double minX = context.metrics.points[0].year;
    double maxX = context.metrics.points[context.metrics.count - 1].year;

    double yPadding = (maxY - minY) * 0.15;
    minY -= yPadding;
    maxY += yPadding;

    double xScale = availableWidth / (maxX - minX);
    double yScale = graphHeight / (maxY - minY);

    QPainterPath path;
    for (int i = 0; i < context.metrics.count; i++) {
        qreal x = leftMargin + (context.metrics.points[i].year - minX) * xScale;
        qreal y = graphBottomY - (context.metrics.points[i].value - minY) * yScale;

        scene->addEllipse(x-3, y-3, 6, 6, QPen(Qt::blue), QBrush(Qt::blue));

        QGraphicsTextItem* valueLabel = scene->addText(QString::number(context.metrics.points[i].value, 'f', 1), valueFont);
        valueLabel->setDefaultTextColor(Qt::darkBlue);
        valueLabel->setPos(x - valueLabel->boundingRect().width()/2, y - 18);

        if (i == 0) path.moveTo(x, y);
        else path.lineTo(x, y);

        QGraphicsTextItem* yearLabel = scene->addText(QString::number(context.metrics.points[i].year), yearFont);
        yearLabel->setDefaultTextColor(Qt::black);
        yearLabel->setPos(x - yearLabel->boundingRect().width()/2, graphBottomY + 5);
    }
    scene->addPath(path, QPen(Qt::blue, 2));

    auto addHorizontalLine = [&](double value, const QString& label, const QColor& color) {
        qreal yPos = graphBottomY - (value - minY) * yScale;
        scene->addLine(leftMargin, yPos, leftMargin + availableWidth, yPos, QPen(color, 1, Qt::DashLine));

        QGraphicsTextItem* labelItem = scene->addText(QString("%1: %2").arg(label).arg(value, 0, 'f', 1), valueFont);
        labelItem->setDefaultTextColor(color);
        labelItem->setPos(leftMargin + availableWidth + 5, yPos - 8);
    };

    addHorizontalLine(context.metrics.min, "Min", Qt::red);
    if (context.metrics.median != context.metrics.min && context.metrics.median != context.metrics.max) {
        addHorizontalLine(context.metrics.median, "Med", Qt::green);
    }
    addHorizontalLine(context.metrics.max, "Max", Qt::red);
}
void MainWindow::setupGraphArea() {
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(Qt::white);
}

