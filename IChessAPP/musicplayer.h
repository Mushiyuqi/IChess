#pragma once
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>

class MusicPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    explicit MusicPlayer(QObject *parent = nullptr);

    qreal volume() const;
    void setVolume(qreal volume);

signals:
    void volumeChanged(qreal volume);

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
};
