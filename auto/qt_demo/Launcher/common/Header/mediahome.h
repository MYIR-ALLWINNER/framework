#ifndef MEDIAHOME_H
#define MEDIAHOME_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QPixmap>

namespace Ui {
class MediaHome;
}


class MediaHome : public QWidget
{
   Q_OBJECT

public:
    explicit MediaHome(QWidget *parent = 0);
    static MediaHome *Instance(QWidget *parent = 0);
	~MediaHome();

private slots:

    void on_media_btn_clicked();

    void on_camera_home_btn_clicked();

signals:

protected:

private:
	Ui::MediaHome *ui;


};


#endif // MEDIAHOME_H
