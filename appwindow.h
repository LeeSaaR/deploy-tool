#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "widgetinput.h"
#include "threadprogram.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class AppWindow;
}
QT_END_NAMESPACE

class AppWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::AppWindow *ui;
    static AppWindow* m_instance;
    WidgetInput* wgt_input;
    QLayout *lo;
    ThreadProgram* program_thread;
public:
    AppWindow(QWidget *parent = nullptr);
    ~AppWindow();
    static AppWindow* get(){return m_instance;}
public:
    void runPrograms();
    void log(const QString& line);
private:
    void init();
    void initUi();
    void initStyleSheet();
    void initInput();
    void initConnections();
    void initThreadProgram();
    void runWinDeployQt();
    void runBinaryCreator();
    void load();
    void completed();
public slots:
    void read(const QString& line);
    void readOut();
    void readErr();
private slots:
    void onGenerate();
    void onSelected();
    void onFinishedProgram(ThreadProgram::Type type);
signals:
    void writeLog(const QString& line);
};
#endif // APPWINDOW_H
