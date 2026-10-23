#ifndef MAFIAPLAYER_H
#define MAFIAPLAYER_H

#include <string_view>

#include <QObject>
#include <QSoundEffect>

#include <MafiaActions.h>

class QPropertyAnimation;

class MafiaPlayer : public QObject
{
    Q_OBJECT
public:
    static constexpr auto DEFAULT_BACKGROUND_MIN_VOLUME = 0.01;
    static constexpr auto DEFAULT_BACKGROUND_MAX_VOLUME = 0.2;

    explicit MafiaPlayer(QObject* parent = nullptr);

    void playBackground();
    QPropertyAnimation* increaseBackground();
    QPropertyAnimation* fadeBackground(const double volume);
    QPropertyAnimation* decreaseBackground();
    void setBackgroundMinVolume(const double volume);
    void setBackgroundMaxVolume(const double volume);
    void stopBackground();

    bool playSound(shs::mafia::MafiaActions action);

public slots:
    Q_INVOKABLE void onMafiaAction(int action);

signals:

private:
    QSoundEffect* m_background_sound;
    QSoundEffect* m_sound;

    double m_background_min_volume = DEFAULT_BACKGROUND_MIN_VOLUME;
    double m_background_max_volume = DEFAULT_BACKGROUND_MAX_VOLUME;

    static constexpr std::string_view sounds_path = "qrc:/sounds/";
    static constexpr std::string_view file_extension = ".wav";
};

#endif // MAFIAPLAYER_H
