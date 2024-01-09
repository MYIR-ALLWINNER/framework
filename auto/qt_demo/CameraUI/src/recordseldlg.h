#ifndef RECORDSELDLG_H
#define RECORDSELDLG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class RecordSelDlg;
}

class RecordSelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RecordSelDlg(QWidget *parent = 0);
    ~RecordSelDlg();
    void SelCheckBox();
    int GetRedCameraId(QString QStr);
    void UpdateCurCamera(int iCameraId);
    bool CheckBoxIsEnabled(int iCameraId);
    void InitCheckBoxStyle();
public slots:
    void onButtonClicked(QAbstractButton *button);
    void on_pushButtonEnter_clicked();

private:
    Ui::RecordSelDlg *ui;
    int *m_pRedCamState;//save the record state for cameras[0:stop 1:start 0xff: invalid value]
    int *m_pNewRedCameraId;
};

#endif // RECORDSELDLG_H
