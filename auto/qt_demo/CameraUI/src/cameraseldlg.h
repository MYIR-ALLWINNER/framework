#ifndef CAMERASELDLG_H
#define CAMERASELDLG_H

#include <QDialog>
#include <QAbstractButton>


namespace Ui {
class CameraSelDlg;
}

class CameraSelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CameraSelDlg(QWidget *parent = 0);
    ~CameraSelDlg();
public slots:
    void onButtonClicked(QAbstractButton*);
    void on_pushButtonEnter_clicked();
    int GetCameraId(QString QStr);
    void SelCheckBox(int iCheBoxId);
private:
    void InitCheckBoxStyle();
    Ui::CameraSelDlg *ui;
    int m_iNewCameraId;
};

#endif // CAMERASELDLG_H
