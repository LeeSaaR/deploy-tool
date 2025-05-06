#ifndef FILESELECTION_H
#define FILESELECTION_H

#include <QWidget>

namespace Ui {
class FileSelection;
}

class FileSelection : public QWidget
{
    Q_OBJECT
public:
    enum SelectType {
        SelectFile = 0,
        SelectDir
    };
private:
    Ui::FileSelection *ui;
    QString m_placeholder = "select something";
    QString m_caption = "select file";
    QString m_default_dir = "D:/Qt/Dev/BeKo/BeKo";
    QString m_value = "";
    SelectType m_type = SelectFile;
public:
    explicit FileSelection(QWidget *parent = nullptr, SelectType type = SelectFile);
    ~FileSelection();
private:
    void init();
public:
    void reset();
    void setCaption(const QString& val);
    void setText(const QString& val);
    void setPlaceholder(const QString& val);
    void setDefaultDir(const QString& val);
    const QString value() &;
    const QString selectFile();
    const QString selectDir();
public:
    bool isEmpty();
private slots:
    void onDialog();
    void onClear();
signals:
    void edited();
};

#endif // FILESELECTION_H
