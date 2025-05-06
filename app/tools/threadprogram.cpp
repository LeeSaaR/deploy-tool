#include "threadprogram.h"

#include "dtdata.h"
#include "appwindow.h"

ThreadProgram::ThreadProgram(QObject* parent)
    : QThread(parent)
{
}

ThreadProgram::~ThreadProgram()
{
}

void ThreadProgram::run()
{
    qDebug() << __FUNCTION__;
    QProcess* process = new QProcess(this);
    connect(
        process, &QProcess::readyReadStandardOutput,
        AppWindow::get(), &AppWindow::readOut,
        Qt::DirectConnection
        );
    connect(
        process, &QProcess::readyReadStandardError,
        AppWindow::get(), &AppWindow::readErr,
        Qt::DirectConnection
        );
    connect(
        process, &QProcess::finished/*static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished)*/,
        this, &ThreadProgram::onFinished
        );
    process->setProcessChannelMode(QProcess::MergedChannels);

    switch (m_type) {
    case WinDeployQt: initWinDeployQt( process ); break;
    case BinaryCreator: initBinaryCreator( process ); break;
    default: break;
    }
    process->start();
}

void ThreadProgram::setType(const Type &type)
{
    m_type = type;
}

void ThreadProgram::initWinDeployQt(QProcess* process)
{
    qDebug() << __FUNCTION__;
    QString file_backspaced = DTData::file_exe();
    file_backspaced.replace("/", "\\");
    QStringList args = {"--compiler-runtime", file_backspaced};

    process->setWorkingDirectory( DTData::dir_data() );
    process->setProgram("windeployqt6.exe");
    process->setArguments(args);
}

void ThreadProgram::initBinaryCreator(QProcess* process)
{
    qDebug() << __FUNCTION__;
    QStringList args = {
    "-v",
    "-c",
    "config\\config.xml",
    "-p",
    "packages",
    DTData::file_installer()
    };

    process->setWorkingDirectory( DTData::dir_installer() );
    process->setProgram("binarycreator.exe");
    process->setArguments(args);
}

void ThreadProgram::onFinished()
{
    qDebug() << __FUNCTION__;
    emit programFinished(m_type);
}
