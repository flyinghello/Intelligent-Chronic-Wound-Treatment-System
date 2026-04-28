#ifndef VIDEOPLAYERWIDGET_H
#define VIDEOPLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QEvent>
class VideoPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayerWidget(QWidget* parent = nullptr);
    ~VideoPlayerWidget();
private slots:
    void playPause();

private:
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
    QPushButton* playPauseButton;
};

#endif // VIDEOPLAYERWIDGET_H
