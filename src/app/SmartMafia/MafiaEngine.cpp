#include "MafiaEngine.h"

#include <QDebug>
#include <shs_lib_Color_RGB888.h>
#include <shs_lib_Color_RgbManagerVirtual.h>

MafiaEngine::MafiaEngine(QObject* parent)
    : QObject{ parent },
    m_player(this), m_manager(this),
    m_dtp(std::make_shared<shs::DTP>(m_ID))
{
    using ID_t = shs::t::shs_ID_t;
    m_spots.push_back(shs::SmartSpotVirtual(m_dtp, ID_t(m_ID), ID_t(14, 1, 0)));
    m_spots.push_back(shs::SmartSpotVirtual(m_dtp, ID_t(m_ID), ID_t(11, 1, 0)));

    m_loads.push_back(std::make_shared<shs::LoadVirtual>(ID_t(m_ID), ID_t(22, 1), *m_dtp));  // braR
    m_loads.push_back(std::make_shared<shs::LoadVirtual>(ID_t(m_ID), ID_t(22, 2), *m_dtp));  // braL


    std::vector<std::shared_ptr<shs::lib::Color::RgbManager>> rgbs;
    for (auto& spot : m_spots)
    {
        rgbs.push_back(spot.getManager());
        m_dtp->attachAPI(&spot);
    }
    std::vector<ID_t> ids = {ID_t(23, 1), ID_t(22, 4), ID_t(22, 5)};
    for (auto id : ids) {
    rgbs.push_back(std::make_shared<shs::lib::Color::RgbManagerVirtual>(m_dtp, ID_t(m_ID), id));
    }
    m_manager.setManagers(rgbs);
    m_manager.setBra(m_loads);

    m_dtp->start();

    startTimer(20);


    connect(&m_player, &MafiaPlayer::playingStarted, &m_manager, &MafiaManager::onPlayingStarted);
    connect(&m_player, &MafiaPlayer::playingFinished, &m_manager, &MafiaManager::onPlayingFinished);
    connect(&m_manager, &MafiaManager::mafiaAction, &m_player, &MafiaPlayer::onMafiaAction, Qt::QueuedConnection);
}

MafiaPlayer* MafiaEngine::player()
{
    return &m_player;
}

MafiaManager* MafiaEngine::manager()
{
    return &m_manager;
}

void MafiaEngine::tick()
{
    m_dtp->tick();
    // for (auto& spot : m_spots)
    // {
    //     spot.tick();
    // }
}

void MafiaEngine::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    using shs::lib::Color::RGB888;

    qDebug() << "Set color: " << static_cast<int>(r) << static_cast<int>(g) << static_cast<int>(b);

    auto rgb_manager = m_spots[0].getManager();
    rgb_manager->setBrightness(255);
    rgb_manager->setColor(RGB888(r, g, b));
}

Q_INVOKABLE void MafiaEngine::onMafiaAction(int action)
{
    m_player.onMafiaAction(action);

    m_manager.onMafiaAction(action);
}
