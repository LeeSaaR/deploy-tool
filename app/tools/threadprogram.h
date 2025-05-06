#ifndef THREADPROGRAM_H
#define THREADPROGRAM_H

#include <QThread>
#include <QProcess>

class ThreadProgram : public QThread
{
    Q_OBJECT
public:
    enum Type
    {
        WinDeployQt = 0,
        BinaryCreator
    };
private:
    Type m_type;
public:
    explicit ThreadProgram(QObject* parent = nullptr);
    ~ThreadProgram();
public:
    void run() override;
    void setType(const Type& type);
    void initWinDeployQt(QProcess* process);
    void initBinaryCreator(QProcess* process);
private:
    void onFinished();
signals:
    void programFinished(const Type& type);
};

#endif // THREADPROGRAM_H
