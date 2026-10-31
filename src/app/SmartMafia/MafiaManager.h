#pragma once

#include <vector>
#include <memory>

#include <QObject>

#include <shs_LoadVirtual.h>
#include <shs_lib_Color_RgbManager.h>
#include <MafiaActions.h>
#include <shs_lib_Color_RGB888.h>

using shs::lib::Color::RGB888;

class MafiaManager : public QObject
{
    Q_OBJECT
public:
    explicit MafiaManager(QObject* parent = nullptr);
    MafiaManager(std::vector<std::shared_ptr<shs::lib::Color::RgbManager>> rgbs,
                 QObject* parent = nullptr);

    void setManagers(std::vector<std::shared_ptr<shs::lib::Color::RgbManager>> rgbs) { m_rgbs = std::move(rgbs); }
    void setBra(std::vector<std::shared_ptr<shs::LoadVirtual>> bra) { m_bra = std::move(bra); }

signals:
    void mafiaAction(int action);

public slots:
    void onPlayingStarted(shs::mafia::MafiaActions action);
    void onPlayingFinished(shs::mafia::MafiaActions action);
    void onMafiaAction(int action);

private:
    std::vector<std::shared_ptr<shs::lib::Color::RgbManager>> m_rgbs;
    std::vector<std::shared_ptr<shs::LoadVirtual>> m_bra;
    bool m_first_night_flag{};

    void citySleep();
    void somthSleep(uint32_t fade, uint32_t pause);
    void somthWu(RGB888 color, uint32_t fade, uint32_t pause);
    void maniacWu() {somthWu(RGB888(138, 0, 255), 2000, 1200);}
    void sherifWu();
    void doctorWu() { somthWu(RGB888(0, 255, 0), 1000, 2000); }
    void bitchWu() { somthWu(RGB888(255, 80, 200), 1000, 2000); }
    void firstNight();
    void onDay();
    void intro();
};
