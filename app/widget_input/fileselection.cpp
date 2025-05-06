#include "fileselection.h"
#include "ui_fileselection.h"

#include "dtstyle.h"
#include <QFileDialog>

FileSelection::FileSelection(QWidget *parent, SelectType type)
    : QWidget(parent)
    , ui(new Ui::FileSelection)
    , m_type(type)
{
    ui->setupUi(this);
    init();
    // set default directory here
    m_default_dir = "";
}

FileSelection::~FileSelection()
{
    delete ui;
}

void FileSelection::init()
{
    DTStyle::setButton(ui->btn_clear, ":/icons/bin.svg");
    connect(ui->btn_dialog, &QPushButton::clicked, this, &FileSelection::onDialog);
    connect(ui->btn_clear, &QPushButton::clicked, this, &FileSelection::onClear);
}

void FileSelection::reset()
{
    ui->btn_dialog->setText(m_placeholder);
    m_value.clear();
    ui->btn_dialog->setToolTip(m_caption);
}

void FileSelection::setCaption(const QString &val)
{
    m_caption = val;
}

void FileSelection::setText(const QString &val)
{
    ui->btn_dialog->setText(val);
}

void FileSelection::setPlaceholder(const QString &val)
{
    m_placeholder = val;
    ui->btn_dialog->setText(m_placeholder);
}

void FileSelection::setDefaultDir(const QString &val)
{
    m_default_dir = val;
}

const QString  FileSelection::selectFile()
{
    return QFileDialog::getOpenFileName(this, m_caption, m_default_dir);
}

const QString  FileSelection::selectDir()
{
    return QFileDialog::getExistingDirectory(this, m_caption, m_default_dir);
}

const QString FileSelection::value() &
{
    return m_value;
}

bool FileSelection::isEmpty()
{
    return m_value.isEmpty();
}

void FileSelection::onDialog()
{
    qDebug() << __FUNCTION__;
    QString dialog_result;
    switch (m_type) {
    case SelectFile:
        dialog_result = selectFile(); break;
    case SelectDir:
        dialog_result = selectDir(); break;
    default:
        return; break;
    }
    if (dialog_result.isEmpty()) return;

    m_value = dialog_result;
    setText(m_value);
    emit edited();
}

void FileSelection::onClear()
{
    reset();
    emit edited();
}
