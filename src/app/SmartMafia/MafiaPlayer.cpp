#include "MafiaPlayer.h"

#include <QDebug>
#include <QPropertyAnimation>


MafiaPlayer::MafiaPlayer(QObject* parent)
    : QObject{ parent },
    m_background_sound{ new QSoundEffect{ this } },
    m_sound{ new QSoundEffect{ this } }

{
    m_background_sound->setSource(QUrl{ "qrc:/sounds/background_music.wav" });
    m_background_sound->setLoopCount(QSoundEffect::Infinite);
    m_background_sound->setVolume(0);
    m_background_sound->play();

    increaseBackground();

}

void MafiaPlayer::setBackgroundMinVolume(const double volume)
{
    m_background_min_volume = volume;
}

void MafiaPlayer::setBackgroundMaxVolume(const double volume)
{
    m_background_max_volume = volume;
}

void MafiaPlayer::playBackground()
{
    m_background_sound->play();
}

QPropertyAnimation* MafiaPlayer::increaseBackground()
{
    return fadeBackground(m_background_max_volume);
}

QPropertyAnimation* MafiaPlayer::decreaseBackground()
{
    return fadeBackground(m_background_min_volume);
}

QPropertyAnimation* MafiaPlayer::fadeBackground(const double volume)
{
    auto* animation = new QPropertyAnimation{ m_background_sound, "volume" };
    animation->setDuration(2000);
    animation->setStartValue(m_background_sound->volume());
    animation->setEndValue(volume);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    return animation;
}

void MafiaPlayer::stopBackground()
{
    m_background_sound->stop();
}

void MafiaPlayer::onMafiaAction(int action)
{
    using ma = shs::mafia::MafiaActions;

    if (action >= static_cast<int>(shs::mafia::MafiaActions::COUNT)) return;

    qDebug() << shs::mafia::mafiaActionNames[action];

    switch (static_cast<ma>(action))
    {
        case ma::INCREASE_BACKGROUND: increaseBackground(); break;
        case ma::DECREASE_BACKGROUND: decreaseBackground(); break;
        case ma::NO_ACTION: break;
        default: playSound(static_cast<ma>(action)); break;
    }
}

bool MafiaPlayer::playSound(shs::mafia::MafiaActions action)
{
    using ma = shs::mafia::MafiaActions;

    if (action == ma::NO_ACTION || action > ma::MURDER) return false;

    const auto sound_path = QString::fromStdString(std::string(sounds_path) + shs::mafia::mafiaActionNames[static_cast<size_t>(action)] + std::string(file_extension));

    if (m_background_sound->volume() != m_background_min_volume)
    {
        auto* animation = decreaseBackground();
        connect(animation, &QPropertyAnimation::finished, this,
            [this, sound_path]
                {
                    m_sound->setSource(QUrl{ sound_path });
                    m_sound->play();
                });
        return true;
    }

    m_sound->setSource(QUrl{ sound_path });
    m_sound->play();

    return true;
}
