#include "widgetinput.h"
#include "ui_widgetinput.h"

#include "dtdata.h"
#include <QDebug>

WidgetInput::WidgetInput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetInput)
{
    ui->setupUi(this);
    init();
}

WidgetInput::~WidgetInput()
{
    delete ui;
}

void WidgetInput::init()
{
    lo = ui->frame->layout();

    dir_source = new FileSelection(this, FileSelection::SelectDir);
    dir_source->setText("Source Dir");
    dir_source->setCaption("Select Source Dir");
    dir_source->setPlaceholder("Source Dir");
    lo->addWidget(dir_source);
    connect(dir_source, &FileSelection::edited, this, &WidgetInput::onSelectedDirSource);
    m_list_selections.append(dir_source);

    dir_output = new FileSelection(this, FileSelection::SelectDir);
    dir_output->setText("Output Dir");
    dir_output->setCaption("Select Output Dir");
    dir_output->setPlaceholder("Output Dir");
    lo->addWidget(dir_output);
    connect(dir_output, &FileSelection::edited, this, &WidgetInput::onSelectedDirOutput);
    m_list_selections.append(dir_output);
}

bool WidgetInput::isSelected()
{
    return !dir_source->isEmpty() && !dir_output->isEmpty();
}

void WidgetInput::onSelectedDirSource()
{
    qDebug() << __FUNCTION__;
    if (dir_source->isEmpty()) return;
    DTData::dir_source( dir_source->value() );
    dir_output->setDefaultDir( dir_source->value() );
    if (isSelected())
        emit selected();
}

void WidgetInput::onSelectedDirOutput()
{
    qDebug() << __FUNCTION__;
    if (dir_output->isEmpty()) return;
    DTData::dir_output( dir_output->value() );
    dir_source->setDefaultDir( dir_output->value() );
    if (isSelected())
        emit selected();
}

