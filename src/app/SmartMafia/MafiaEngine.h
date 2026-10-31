#pragma once

#include <memory>
#include <vector>
#include <shs_types.h>

#include <QObject>

#include <shs_DTP.h>
#include <shs_LoadVirtual.h>
#include <shs_SmartSpotVirtual.h>

#include "MafiaPlayer.h"
#include "MafiaManager.h"


class MafiaEngine : public QObject
{
    Q_OBJECT
        Q_PROPERTY(MafiaPlayer* player READ player CONSTANT)
        Q_PROPERTY(MafiaManager* manager READ manager CONSTANT)
public:
    explicit MafiaEngine(QObject* parent = nullptr);

    MafiaPlayer* player();
    MafiaManager* manager();

    void tick();

signals:

public slots:
    void timerEvent([[maybe_unused]] QTimerEvent* event) override { tick(); }
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    Q_INVOKABLE void onMafiaAction(int action);

private:
    MafiaPlayer m_player;
    MafiaManager m_manager;
    std::shared_ptr<shs::DTP> m_dtp;
    std::vector<shs::SmartSpotVirtual> m_spots;
    std::vector<std::shared_ptr<shs::LoadVirtual>> m_loads;


    static constexpr shs::t::shs_moduleID_t m_ID{ 100 };
};
