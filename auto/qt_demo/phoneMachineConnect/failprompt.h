#ifndef FAILPROMPT_H
#define FAILPROMPT_H

#include <QWidget>

namespace Ui {
class FailPrompt;
}

class FailPrompt : public QWidget
{
    Q_OBJECT

public:
    explicit FailPrompt(QWidget *parent = 0);
    ~FailPrompt();

private:
    Ui::FailPrompt *ui;
};

#endif // FAILPROMPT_H
