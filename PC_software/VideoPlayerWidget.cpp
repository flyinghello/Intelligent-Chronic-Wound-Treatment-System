#include "VideoPlayerWidget.h"
#include <QFileDialog>
#include <QMediaPlayer>

VideoPlayerWidget::VideoPlayerWidget(QWidget* parent)
    : QWidget(parent),
    mediaPlayer(new QMediaPlayer(this)),
    videoWidget(new QVideoWidget(this)),
    playPauseButton(new QPushButton("Play", this))
{
    // 设置布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    layout->addWidget(playPauseButton);

    // 设置播放器的视频输出到QVideoWidget
    mediaPlayer->setVideoOutput(videoWidget);

    // 按钮连接
    connect(playPauseButton, &QPushButton::clicked, this, &VideoPlayerWidget::playPause);

     //加载视频文件
    QString fileName = "E:/socketcpp/PC_software/PC_software/image/11.mp4";
    if (!fileName.isEmpty()) {
        mediaPlayer->setSource(QUrl::fromLocalFile(fileName));  // 使用 setSource 代替 setMedia
    }

    // 设置固定大小为320x240
    this->setFixedSize(320, 240);

    // 保持视频的宽高比
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
}

VideoPlayerWidget::~VideoPlayerWidget()
{
}

void VideoPlayerWidget::playPause()
{
    // 切换播放和暂停状态
    if (mediaPlayer->playbackState() == QMediaPlayer::PlaybackState::PlayingState) {
        mediaPlayer->pause();
        playPauseButton->setText("Play");
    }
    else {
        mediaPlayer->play();
        playPauseButton->setText("Pause");
    }
}
