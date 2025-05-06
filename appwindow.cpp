#include "appwindow.h"
#include "./ui_appwindow.h"

#include "io.h"
#include "dtdata.h"
// #include "dtstyle.h"
#include <QProcess>

AppWindow* AppWindow::m_instance = nullptr;

AppWindow::AppWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AppWindow)
{
    ui->setupUi(this);
    init();
    m_instance = this;
}

AppWindow::~AppWindow()
{
    m_instance = nullptr;
    delete ui;
}

void AppWindow::init()
{
    qDebug() << __FUNCTION__;
    initUi();
    initStyleSheet();
    initInput();
    initConnections();
    initThreadProgram();
}

void AppWindow::initUi()
{
    qDebug() << __FUNCTION__;
    setWindowTitle("Deploy Tool");
    lo = ui->frm_content->layout();
    // USE YOUR OWN ICON
    // ui->btn_generate->setText("");
    // DTStyle::setButton(ui->btn_generate, ":/icons/download.svg");
}

void AppWindow::initStyleSheet()
{
    qDebug() << __FUNCTION__;
    setStyleSheet(IO::readFile(":/theme/Default Dark.qss"));
}

void AppWindow::initInput()
{
    qDebug() << __FUNCTION__;
    wgt_input = new WidgetInput(this);
    lo->addWidget(wgt_input);
    connect(wgt_input, &WidgetInput::selected, this, &AppWindow::onSelected);
}

void AppWindow::initConnections()
{
    qDebug() << __FUNCTION__;
    connect(ui->btn_generate, &QPushButton::clicked, this, &AppWindow::onGenerate);
    connect(this, &AppWindow::writeLog, this, &AppWindow::read);
}

void AppWindow::initThreadProgram()
{
    qDebug() << __FUNCTION__;
    program_thread = new ThreadProgram(this);
    connect(program_thread, &ThreadProgram::programFinished, this, &AppWindow::onFinishedProgram);
}

void AppWindow::runWinDeployQt()
{
    qDebug() << __FUNCTION__;
    AppWindow::get()->log("");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("================== WINDEPLOYQT ==================");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("");
    program_thread->setType(ThreadProgram::WinDeployQt);
    program_thread->run();
}

void AppWindow::runBinaryCreator()
{
    qDebug() << __FUNCTION__;
    AppWindow::get()->log("");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("================= BINARYCREATOR =================");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("");
    program_thread->setType(ThreadProgram::BinaryCreator);
    program_thread->run();
}

void AppWindow::load()
{
    DTData::load();
}

void AppWindow::completed()
{
    qDebug() << __FUNCTION__;
    AppWindow::get()->log("");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("=================== COMPLETED ===================");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("");
    emit writeLog("OUTPUT FILE: "+DTData::dir_installer()+"/"+DTData::file_installer());
    ui->btn_generate->setEnabled(true);
}

void AppWindow::runPrograms()
{
    qDebug() << __FUNCTION__;
    runWinDeployQt();
}

void AppWindow::log(const QString &line)
{
    emit writeLog(line);
}

void AppWindow::read(const QString &line)
{
    ui->log->appendPlainText( line );
}

void AppWindow::readOut()
{
    qDebug() << __FUNCTION__;
    QProcess* p = (QProcess*)sender();
    if (p->canReadLine())
        ui->log->appendPlainText( p->readAll() );
}

void AppWindow::readErr()
{
    qDebug() << __FUNCTION__;
    QProcess* p = (QProcess*)sender();
    if (p->canReadLine())
        ui->log->appendPlainText( p->readAll() );
}

void AppWindow::onGenerate()
{
    qDebug() << __FUNCTION__;
    ui->btn_generate->setEnabled(false);
    DTData::generateInstaller();
}

void AppWindow::onSelected()
{
    qDebug() << __FUNCTION__;
    ui->log->clear();
    load();
}

void AppWindow::onFinishedProgram(ThreadProgram::Type type)
{
    switch (type) {
    case ThreadProgram::WinDeployQt:
        emit writeLog(DTData::s_finish()+"windeployqt6.exe");
        DTData::copyDlls();
        runBinaryCreator();
        break;
    case ThreadProgram::BinaryCreator:
        emit writeLog(DTData::s_finish()+"binarycreator.exe");
        completed();
        break;
    default:
        break;
    }
}
