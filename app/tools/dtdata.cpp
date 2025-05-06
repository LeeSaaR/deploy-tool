#include "dtdata.h"

#include "appwindow.h"
#include "io.h"
#include "json.h"
#include <QFileInfo>
#include <QDate>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QProcess>

QString DTData::stat_start   = "STATUS: START      : ";
QString DTData::stat_finish  = "STATUS: FINISHED   : ";
QString DTData::stat_complet = "STATUS: COMPLETED  : ";
QString DTData::stat_mkdir   = "STATUS: MKDIR      : ";
QString DTData::stat_write   = "STATUS: WRITE      : ";
QString DTData::stat_copy    = "STATUS: COPY       : ";
QString DTData::stat_from    = "FROM             <-: ";
QString DTData::stat_to      = "TO               <-: ";

QString DTData::m_qrc_license = ":/preset/packages/com.vendor.template/meta/license.txt";
QString DTData::m_qrc_config  = ":/preset/config/config.xml";
QString DTData::m_qrc_control = ":/preset/config/controlscript.js";
QString DTData::m_qrc_style   = ":/preset/config/style.qss";
QString DTData::m_qrc_package = ":/preset/packages/com.vendor.template/meta/package.xml";
QString DTData::m_qrc_install = ":/preset/packages/com.vendor.template/meta/installscript.js";

QString DTData::m_vendor_name;
QString DTData::m_vendor_url;
QString DTData::m_product_name;
QString DTData::m_product_version;
QString DTData::m_product_description;
QString DTData::m_product_size;
QString DTData::m_package_domain;
QString DTData::m_installer_name;
QString DTData::m_file_config_json;
QString DTData::m_file_config;
QString DTData::m_file_controller;
QString DTData::m_file_package;
QString DTData::m_file_installscript;
QString DTData::m_file_exe_src;
QString DTData::m_file_exe;
QString DTData::m_file_installer;
QString DTData::m_file_logo;
QString DTData::m_file_icon;
QString DTData::m_file_license;
QString DTData::m_file_style;
QString DTData::m_dir_source;
QString DTData::m_dir_output;
QString DTData::m_dir_installer;
QString DTData::m_dir_config;
QString DTData::m_dir_packages;
QString DTData::m_dir_pack;
QString DTData::m_dir_data;
QString DTData::m_dir_meta;

QStringList DTData::m_list_dirs;

void DTData::load()
{
    AppWindow::get()->log("");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("================== LOAD CONFIG ==================");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("");
    extractJsonData();
    AppWindow::get()->log(stat_finish+"load config.json");
}

void DTData::generateInstaller()
{
    qDebug() << __FUNCTION__;
    AppWindow::get()->log("");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("=================== GENERATE ====================");
    AppWindow::get()->log("=================================================");
    AppWindow::get()->log("");

    makeDirs();
    copyFiles();
    makeFiles();
    AppWindow::get()->runPrograms();
}

void DTData::extractJsonData()
{
    qDebug() << __FUNCTION__;
    m_file_config_json = m_dir_source+"/config.json";
    m_file_logo        = m_dir_source+"/logo.png";
    m_file_icon        = m_dir_source+"/"+findICON();
    m_file_exe_src     = m_dir_source+"/"+findEXE();

    const QString content = IO::readFile( m_file_config_json );
    QJsonDocument json_doc = QJsonDocument::fromJson( content.toUtf8() );

    QJsonObject obj = json_doc.object();
    m_vendor_name         = Json::extractString("VendorName", obj);
    m_vendor_url          = Json::extractString("VendorUrl", obj);
    m_product_name        = Json::extractString("ProductName", obj);
    m_product_version     = Json::extractString("ProductVersion", obj);
    m_product_description = Json::extractString("ProductDescription", obj);
    m_product_size        = Json::extractString("ProductSize", obj);
    m_package_domain      = Json::extractString("PackageDomain", obj)+m_product_name.toLower();
    m_installer_name      = m_product_name + " Setup";
    m_dir_installer       = m_dir_output+"/Setup-"+m_product_name+"-"+m_product_version;
    m_file_installer      = m_product_name.toLower()+"-"+m_product_version+"-setup.exe";
    m_dir_config          = m_dir_installer+"/config";
    m_file_config         = m_dir_config+"/config.xml";
    m_file_controller     = m_dir_config+"/controlscript.js";
    m_file_style          = m_dir_config+"/style.qss";
    m_dir_packages        = m_dir_installer+"/packages";
    m_dir_pack            = m_dir_packages+"/"+m_package_domain;
    m_dir_data            = m_dir_pack+"/data";
    m_file_exe            = m_dir_data+"/"+QFileInfo(m_file_exe_src).fileName();
    m_dir_meta            = m_dir_pack+"/meta";
    m_file_package        = m_dir_meta+"/package.xml";
    m_file_installscript  = m_dir_meta+"/installscript.js";
    m_file_license        = m_dir_meta+"/license.txt";

    m_list_dirs
        << m_dir_installer
        << m_dir_config
        << m_dir_packages
        << m_dir_pack
        << m_dir_data
        << m_dir_meta
    ;

    AppWindow::get()->log("DATA:");
    AppWindow::get()->log("vendor name        : "+m_vendor_name);
    AppWindow::get()->log("vendor url         : "+m_vendor_url);
    AppWindow::get()->log("product name       : "+m_product_name);
    AppWindow::get()->log("product version    : "+m_product_version);
    AppWindow::get()->log("package domain     : "+m_package_domain);
    AppWindow::get()->log("installer name     : "+m_installer_name);
    AppWindow::get()->log("");
    AppWindow::get()->log("SOURCE FILES:");
    AppWindow::get()->log("config.json        : "+m_file_config_json);
    AppWindow::get()->log("logo.png           : "+m_file_logo);
    AppWindow::get()->log("win_icon.png       : "+m_file_icon);
    AppWindow::get()->log("source.exe         : "+m_file_exe_src);
    AppWindow::get()->log("");
    AppWindow::get()->log("NEW DIRS:");
    AppWindow::get()->log("dir installer      : "+m_dir_installer);
    AppWindow::get()->log("dir config         : "+m_dir_config);
    AppWindow::get()->log("dir packages       : "+m_dir_packages);
    AppWindow::get()->log("dir domain         : "+m_dir_pack);
    AppWindow::get()->log("dir data           : "+m_dir_data);
    AppWindow::get()->log("dir meta           : "+m_dir_meta);
    AppWindow::get()->log("");
    AppWindow::get()->log("COPY FILES:");
    AppWindow::get()->log("config.xml         : "+m_file_config);
    AppWindow::get()->log("controlscript.js   : "+m_file_controller);
    AppWindow::get()->log("style.qss          : "+m_file_style);
    AppWindow::get()->log("package.xml        : "+m_file_package);
    AppWindow::get()->log("installscript.js   : "+m_file_installscript);
    AppWindow::get()->log("license.txt        : "+m_file_license);
    AppWindow::get()->log("file exe           : "+m_file_exe);
    AppWindow::get()->log("");
    AppWindow::get()->log("OUTPUT:");
    AppWindow::get()->log("dir output         : "+m_dir_output);
    AppWindow::get()->log("file installer     : "+m_file_installer);

    // DISPLAY
    /*qDebug().noquote() << "SOURCE FILES ========================================================";
    qDebug().noquote() << "config.json        :" << m_file_config_json;
    qDebug().noquote() << "logo.png           :" << m_file_logo;
    qDebug().noquote() << "win_icon.png       :" << m_file_icon;
    qDebug().noquote() << ".exe               :" << m_file_exe_src;
    qDebug().noquote() << "";
    qDebug().noquote() << "NEW DIRS ============================================================";
    qDebug().noquote() << "dir installer      :" << m_dir_installer;
    qDebug().noquote() << "dir config         :" << m_dir_config;
    qDebug().noquote() << "dir packages       :" << m_dir_packages;
    qDebug().noquote() << "dir pack           :" << m_dir_pack;
    qDebug().noquote() << "dir data           :" << m_dir_data;
    qDebug().noquote() << "dir meta           :" << m_dir_meta;

    qDebug().noquote() << "";
    qDebug().noquote() << "COPY FILES FROM QRC =================================================";
    qDebug().noquote() << "config.xml         :" << m_file_config;
    qDebug().noquote() << "controlscript.js   :" << m_file_controller;
    qDebug().noquote() << "style.qss          :" << m_file_style;
    qDebug().noquote() << "package.xml        :" << m_file_package;
    qDebug().noquote() << "installscript.js   :" << m_file_installscript;
    qDebug().noquote() << "license.txt            :" << m_file_license;

    qDebug().noquote() << "";
    qDebug().noquote() << "DATA ========================================================";
    qDebug().noquote() << "vendor name        :" << m_vendor_name;
    qDebug().noquote() << "vendor url         :" << m_vendor_url;
    qDebug().noquote() << "package domain     :" << m_package_domain;
    qDebug().noquote() << "product name       :" << m_product_name;
    qDebug().noquote() << "installer          :" << m_installer_name;
    qDebug().noquote() << "product version    :" << m_product_version;

    qDebug().noquote() << "OUTPUT ==============================================================";
    qDebug().noquote() << "dir output         :" << m_dir_output;
    qDebug().noquote() << "file installer     :" << m_file_installer;
    qDebug().noquote() << "file exe           :" << m_file_exe;
    qDebug().noquote() << "";*/
}

const QString DTData::findEXE()
{
    QString file;
    foreach (file, IO::listFiles(m_dir_source)) {
        if (file.contains(".exe"))
            return file;
    }
    return "";
}

const QString DTData::findICON()
{
    if (IO::listFiles(m_dir_source).contains("win_icon.png"))
        return "win_icon.png";
    else
        return "logo.png";
}



void DTData::makeDirs()
{
    qDebug() << __FUNCTION__;
    IO::deleteDir(m_dir_installer);
    QString dir;
    foreach (dir, m_list_dirs)
    {
        AppWindow::get()->log(stat_mkdir+dir);
        IO::makeDir(dir);
    }
}

void DTData::copyFiles()
{
    qDebug() << __FUNCTION__;
    AppWindow::get()->log(stat_copy);
    AppWindow::get()->log(stat_from+m_file_logo);
    AppWindow::get()->log(stat_to+m_dir_config+"/"+"logo.png");
    IO::copyFile(m_file_logo, m_dir_config, "logo.png");

    AppWindow::get()->log(stat_copy);
    AppWindow::get()->log(stat_from+m_file_icon);
    AppWindow::get()->log(stat_to+m_dir_config+"/"+"win_icon.png");
    IO::copyFile(m_file_icon, m_dir_config, "win_icon.png");

    AppWindow::get()->log(stat_copy);
    AppWindow::get()->log(stat_from+m_file_exe_src);
    AppWindow::get()->log(stat_to+m_dir_data+"/"+QFileInfo(m_file_exe_src).fileName());
    IO::copyFile(m_file_exe_src, m_dir_data);
}

void DTData::copyDlls()
{
    qDebug() << __FUNCTION__;
    QString file;
    foreach (file, IO::listFiles(m_dir_source)) {
        if (file.endsWith(".dll"))
        {
            AppWindow::get()->log(stat_copy);
            AppWindow::get()->log(stat_from+m_dir_source+"/"+file);
            AppWindow::get()->log(stat_to+m_dir_data+"/"+file);
        }
    }
}

void DTData::makeFiles()
{
    qDebug() << __FUNCTION__;
    AppWindow::get()->log(stat_write+m_file_config);
    IO::writeFile( contentConfig(),     m_file_config );

    AppWindow::get()->log(stat_write+m_file_controller);
    IO::writeFile( contentControl(), m_file_controller );

    AppWindow::get()->log(stat_write+m_file_style);
    IO::writeFile( IO::readFile(m_qrc_style), m_file_style );

    AppWindow::get()->log(stat_write+m_file_package);
    IO::writeFile( contentPackage(),    m_file_package );

    AppWindow::get()->log(stat_write+m_file_installscript);
    IO::writeFile( contentInstall(), m_file_installscript );

    AppWindow::get()->log(stat_write+m_file_license);
    IO::writeFile( contentLicense(),    m_file_license );
}

const QString DTData::contentConfig()
{
    qDebug() << __FUNCTION__;
    QString content = IO::readFile(m_qrc_config);
    content.replace("#NAMEANDVERSION#", m_product_name+" "+m_product_version);
    content.replace("#VERSION#", m_product_version);
    content.replace("#PRODUCTNAME#", m_product_name);
    content.replace("#VENDORNAME#", m_vendor_name);
    content.replace("#VENDORURL#", m_vendor_url);
    return content;
}

const QString DTData::contentControl()
{
    qDebug() << __FUNCTION__;
    QString content = IO::readFile(m_qrc_control);
    content.replace("#NAMEANDVERSION#", m_product_name+" "+m_product_version);
    content.replace("#SIZE#", m_product_size);
    content.replace("#PRODUCTNAME#", m_product_name);
    return content;
}

const QString DTData::contentPackage()
{
    qDebug() << __FUNCTION__;
    QString content = IO::readFile(m_qrc_package);
    content.replace("#PRODUCTNAME#", m_product_name);
    content.replace("#VERSION#", m_product_version);
    content.replace("#CURRENTDATE#", QDate::currentDate().toString("yyyy-MM-dd"));
    return content;
}

const QString DTData::contentInstall()
{
    qDebug() << __FUNCTION__;
    QString content = IO::readFile(m_qrc_install);
    content.replace("#PRODUCTNAME#", m_product_name);
    content.replace("#FILEEXE#", QFileInfo(m_file_exe).fileName());
    return content;
}

const QString DTData::contentLicense()
{
    return IO::readFile(m_qrc_license);
}

