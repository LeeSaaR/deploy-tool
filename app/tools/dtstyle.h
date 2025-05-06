#ifndef DTSTYLE_H
#define DTSTYLE_H

#include <QPushButton>
#include <QIcon>

class DTStyle
{
private:
    static int m_button_height;
private:
    DTStyle(){}
public:
    static void setButton(QPushButton* btn, const QString& icon);
};

#endif // DTSTYLE_H
