#include "dtstyle.h"

int DTStyle::m_button_height = 32;

void DTStyle::setButton(QPushButton *btn, const QString &icon)
{
    btn->setIcon(QIcon(icon));
    btn->setIconSize(QSize(m_button_height*0.7,m_button_height*0.7));
    btn->setMinimumHeight(m_button_height);
    btn->setMaximumHeight(m_button_height);
}
