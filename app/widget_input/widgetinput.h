#ifndef WIDGETINPUT_H
#define WIDGETINPUT_H

#include <QWidget>
#include "fileselection.h"
#include "inputtext.h"

namespace Ui {
class WidgetInput;
}

class WidgetInput : public QWidget
{
    Q_OBJECT
private:
    Ui::WidgetInput *ui;
    QLayout *lo;
    // FileSelection* dir_project;
    FileSelection* dir_source;
    FileSelection* dir_output;
    // FileSelection* file_exe;
    QList<FileSelection*> m_list_selections;
public:
    explicit WidgetInput(QWidget *parent = nullptr);
    ~WidgetInput();
private:
    void init();
    bool isSelected();
private slots:
    void onSelectedDirSource();
    void onSelectedDirOutput();
signals:
    void selected();
};

#endif // WIDGETINPUT_H
