#include "VideoPlayerWidget.h"
#include <QFileDialog>
#include <QMediaPlayer>

VideoPlayerWidget::VideoPlayerWidget(QWidget* parent)
    : QWidget(parent),
    mediaPlayer(new QMediaPlayer(this)),
    videoWidget(new QVideoWidget(this)),
    playPauseButton(new QPushButton("Play", this))
{
    // ���ò���
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    layout->addWidget(playPauseButton);

    // ���ò���������Ƶ�����QVideoWidget
    mediaPlayer->setVideoOutput(videoWidget);

    // ��ť����
    connect(playPauseButton, &QPushButton::clicked, this, &VideoPlayerWidget::playPause);

     //������Ƶ�ļ�
    QString fileName = "E:/socketcpp/PC_software/PC_software/image/11.mp4";
    if (!fileName.isEmpty()) {
        mediaPlayer->setSource(QUrl::fromLocalFile(fileName));  // ʹ�� setSource ���� setMedia
    }

    // ���ù̶���СΪ320x240
    this->setFixedSize(320, 240);

    // ������Ƶ�Ŀ�߱�
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
}

VideoPlayerWidget::~VideoPlayerWidget()
{
}

void VideoPlayerWidget::playPause()
{
    // �л����ź���ͣ״̬
    if (mediaPlayer->playbackState() == QMediaPlayer::PlaybackState::PlayingState) {
        mediaPlayer->pause();
        playPauseButton->setText("Play");
    }
    else {
        mediaPlayer->play();
        playPauseButton->setText("Pause");
    }
}
