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

    int distype;

private slots:

    void on_video_btn_clicked();

    void on_music_btn_clicked();

    void on_return_btn_clicked();

signals:

protected:

private:
	Ui::MediaHome *ui;

};

extern MediaHome* pGlobalMediaHome;


#endif // MEDIAHOME_H
