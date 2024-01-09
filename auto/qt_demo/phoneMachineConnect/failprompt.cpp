#include "failprompt.h"
#include "ui_failprompt.h"

FailPrompt::FailPrompt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailPrompt)
{
    ui->setupUi(this);
}

FailPrompt::~FailPrompt()
{
    delete ui;
}
