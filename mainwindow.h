#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"
#include "entrypoint.h"
#include <QComboBox>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AppContext context;
    QGraphicsScene *scene;
    void updateMetrics();
    void updateLabels();
    void onChooseFileButtonClicked();
    void onLoadDataButtonClicked();
    void onCalculateMetricsButtonClicked();
    void onColumnComboBoxClicked(int index);
    void onRegionLineEditClicked();
    void warningMessage(Errors status);
    void infoMessage();
    void displayMetrics(const Metrics& metrics);
    const char* getErrorDescription(Errors status);
    void infoDescription(char* buffer, size_t bufferSize);
    void setupGraphArea();
    void drawGraph();
    void resizeEvent(QResizeEvent* event);
};
#endif // MAINWINDOW_H
