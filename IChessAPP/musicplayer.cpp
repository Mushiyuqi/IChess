#include "musicplayer.h"
#include <QUrl>

MusicPlayer::MusicPlayer(QObject *parent)
    : QObject(parent)
    , m_player(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
{
    m_player->setAudioOutput(m_audioOutput);
    m_player->setSource(QUrl("qrc:/music/start_bgm.ogg"));
    m_player->setLoops(QMediaPlayer::Infinite); // 设置为循环播放
    m_player->play();
}

qreal MusicPlayer::volume() const
{
    return m_audioOutput->volume();
}

void MusicPlayer::setVolume(qreal volume)
{
    if (m_audioOutput->volume() != volume) {
        m_audioOutput->setVolume(volume);
        emit volumeChanged(volume);
    }
}
