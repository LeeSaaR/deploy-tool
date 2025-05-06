#ifndef DTDATA_H
#define DTDATA_H

#include <QString>
#include <QList>

class DTData
{
private:
    DTData(){}
private:
    static QString stat_start;
    static QString stat_finish;
    static QString stat_complet;
    static QString stat_mkdir;
    static QString stat_write;
    static QString stat_copy;
    static QString stat_from;
    static QString stat_to;

    static QString m_qrc_license;
    static QString m_qrc_config;
    static QString m_qrc_control;
    static QString m_qrc_package;
    static QString m_qrc_install;
    static QString m_qrc_style;
private:
    static QString m_vendor_name;
    static QString m_vendor_url;
    static QString m_product_name;
    static QString m_product_version;
    static QString m_product_description;
    static QString m_product_size;
    static QString m_package_domain;
    static QString m_installer_name;
    static QString m_file_config_json;
    static QString m_file_config;
    static QString m_file_controller;
    static QString m_file_package;
    static QString m_file_installscript;
    static QString m_file_exe_src;
    static QString m_file_exe;
    static QString m_file_installer;
    static QString m_file_logo;
    static QString m_file_icon;
    static QString m_file_license;
    static QString m_file_style;
    static QString m_dir_source;
    static QString m_dir_output;
    static QString m_dir_installer;
    static QString m_dir_config;
    static QString m_dir_packages;
    static QString m_dir_pack;
    static QString m_dir_data;
    static QString m_dir_meta;
public:
    static const QString s_start(){ return stat_start; }
    static const QString s_finish(){ return stat_finish; }
    static const QString s_complet(){ return stat_complet; }

    static const QString file_exe(){ return m_file_exe; }
    static const QString file_installer(){ return m_file_installer; }

    static const QString dir_source(){ return m_dir_source; }
    static const QString dir_output(){ return m_dir_output; }
    static const QString dir_installer(){ return m_dir_installer; }
    static const QString dir_data(){ return m_dir_data; }
public:
    static const void file_exe(const QString& val){ m_file_exe = val; }
    static const void file_installer(const QString& val){ m_file_installer = val; }
    static const void dir_source(const QString& val){ m_dir_source = val; }
    static const void dir_output(const QString& val){ m_dir_output = val; }
    static const void dir_installer(const QString& val){ m_dir_installer = val; }
    static const void dir_data(const QString& val){ m_dir_data = val; }

private:
    static QStringList m_list_dirs;
public:
    static void load();
    static void makeDirs();
    static void copyFiles();
    static void copyDlls();
    static void makeFiles();
    static void makeConfigFile();
    static void makePackageFile();
    static void makeScriptFile();
    static void generateInstaller();
    static void extractJsonData();
    static const QString findEXE();
    static const QString findICON();
    static const QString contentConfig();
    static const QString contentControl();
    static const QString contentPackage();
    static const QString contentInstall();
    static const QString contentLicense();
};

#endif // DTDATA_H
