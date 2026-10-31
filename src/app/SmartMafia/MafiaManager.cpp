#include "MafiaManager.h"

#include <functional>
#include <memory>

#include <QTimer>
#include <shs_lib_Color_FireRgbEffect.h>
#include <shs_lib_Color_RGB888.h>

using shs::lib::Color::RGB888;

MafiaManager::MafiaManager(QObject* parent)
    : QObject(parent)
{
}

MafiaManager::MafiaManager(
    std::vector<std::shared_ptr<shs::lib::Color::RgbManager>> rgbs,
    QObject* parent)
    : QObject(parent), m_rgbs(std::move(rgbs))
{

}

void MafiaManager::onPlayingStarted(shs::mafia::MafiaActions action)
{
    using ma = shs::mafia::MafiaActions;

    switch (action)
    {
    case ma::CITY_SLEEP: citySleep(); break;
    case ma::CITY_WU: [[fallthrough]];
    case ma::ON_DAY:
    {
        onDay();
    }
    break;
    case ma::INTRO: intro(); break;
    case ma::BITCH_SLEEP: [[fallthrough]];
    case ma::DOCTOR_SLEEP: [[fallthrough]];
    case ma::MANIAC_SLEEP: [[fallthrough]];
    case ma::SHERIFF_SLEEP: [[fallthrough]];
    case ma::MAFIA_SLEEP:
    {
        somthSleep(1000, 2000);
    }
    break;
    case ma::MANIAC_WU: maniacWu(); break;
    case ma::DOCTOR_WU: doctorWu(); break;
    case ma::SHERIFF_WU: sherifWu(); break;
    case ma::BITCH_WU: bitchWu(); break;

    case ma::MAFIA_SLEEP_MANIAC_WU:
    {
        somthSleep(2000, 1000);
        QTimer::singleShot(3000, this, [this]() {maniacWu(); });
    }
    break;
    case ma::MANIAC_SLEEP_SHERIFF_WU:
    {
        somthSleep(2000, 1000);
        QTimer::singleShot(6000, this, [this]() {sherifWu();});
    }break;
    case ma::SHERIFF_SLEEP_DOCTOR_WU:
    {
        somthSleep(2000, 1400);
        QTimer::singleShot(2200, this, [this]() {doctorWu();});

    }break;
    case ma::DOCTOR_SLEEP_BITCH_WU:
    {
        somthSleep(2000, 1000);
        QTimer::singleShot(1000, this, [this]() {bitchWu();});
    }
    break;
    // case ma::FIRST_NIGHT: firstNight(); break;
    case ma::MURDER:
    {
        somthWu(RGB888(255, 0, 0), 500, 2800);
        QTimer::singleShot(10000, this, [this]() {onDay();});
    }
    }
}

void MafiaManager::onMafiaAction(int action)
{
    using ma = shs::mafia::MafiaActions;
    switch (static_cast<ma>(action))
    {
    case ma::ON_DAY: onDay(); break;
    case ma::FIRST_NIGHT: m_first_night_flag = true; emit mafiaAction(static_cast<int>(ma::CITY_SLEEP)); break;
    }
}


void MafiaManager::onPlayingFinished(shs::mafia::MafiaActions action)
{
    using ma = shs::mafia::MafiaActions;
    if (action == ma::INTRO)
    {
        onDay();

        emit mafiaAction(static_cast<int>(ma::INCREASE_BACKGROUND));
    }

    if (!m_first_night_flag) return;

    switch (action)
    {
    case ma::CITY_SLEEP: emit mafiaAction(static_cast<int>(ma::MAFIA)); break;
    case ma::MAFIA: emit mafiaAction(static_cast<int>(ma::MAFIA_SLEEP_MANIAC_WU)); break;
    case ma::MAFIA_SLEEP_MANIAC_WU: emit mafiaAction(static_cast<int>(ma::MANIAC)); break;
    case ma::MANIAC: emit mafiaAction(static_cast<int>(ma::MANIAC_SLEEP_SHERIFF_WU)); break;
    case ma::MANIAC_SLEEP_SHERIFF_WU: emit mafiaAction(static_cast<int>(ma::SHERIFF)); break;
    case ma::SHERIFF: emit mafiaAction(static_cast<int>(ma::SHERIFF_SLEEP_DOCTOR_WU)); break;
    case ma::SHERIFF_SLEEP_DOCTOR_WU: emit mafiaAction(static_cast<int>(ma::DOCTOR)); break;
    case ma::DOCTOR: emit mafiaAction(static_cast<int>(ma::DOCTOR_SLEEP_BITCH_WU)); break;
    case ma::DOCTOR_SLEEP_BITCH_WU: emit mafiaAction(static_cast<int>(ma::BITCH_SLEEP)); break;
    case ma::BITCH_SLEEP: emit mafiaAction(static_cast<int>(ma::TOWNSMAN_1)); break;
    case ma::TOWNSMAN_1: emit mafiaAction(static_cast<int>(ma::TOWNSMAN_2)); break;
    case ma::TOWNSMAN_2: emit mafiaAction(static_cast<int>(ma::CITY_WU)); break;
    case ma::CITY_WU: m_first_night_flag = false; break;
    }
}

void MafiaManager::citySleep()
{
    for (auto& rgb : m_rgbs)
    {
        auto layer = rgb->getTopLayer();
        layer->clearEffects();
        layer->enableFade();
        layer->setFadePeriod(10000);
        rgb->setColor(RGB888{});
    }

    QTimer::singleShot(14000, this, [this]
    {
        for (auto rgb : m_rgbs)
        {
            auto layer = rgb->getTopLayer();
            layer->enableFade();
            layer->setFadePeriod(500);
            rgb->setColor(RGB888(255, 0, 0));
        }
    });

}

void MafiaManager::somthSleep(uint32_t fade, uint32_t pause)
{
    QTimer::singleShot(pause, this, [this, fade]()
    {for (auto rgb : m_rgbs)
    {
        auto layer = rgb->getTopLayer();
        layer->setFadePeriod(fade);
        rgb->setColor(RGB888(0, 0, 0));
    }});
}

void MafiaManager::somthWu(RGB888 color, uint32_t fade, uint32_t pause){

    QTimer::singleShot(pause, this, [this, color, fade]()
    {for (auto rgb : m_rgbs)
    {
        auto layer = rgb->getTopLayer();
        layer->setFadePeriod(fade);
        rgb->setColor(color);
    }
    });
}

void MafiaManager::sherifWu()
{
    auto counter = 0;
    for (auto rgb : m_rgbs)
    {
        auto layer = rgb->getTopLayer();
        layer->setFadePeriod(500);
        rgb->setColor(counter++ % 2 ? RGB888(255, 0, 0) : RGB888(0, 0, 255));
    }
}

void MafiaManager::firstNight()
{
    citySleep();

}

void MafiaManager::onDay()
{
    qDebug() << "On day";
    for (auto rgb : m_rgbs)
    {
        auto layer = rgb->getTopLayer();
        layer->enableFade();
        layer->setFadePeriod(5000);
        rgb->setBrightness(255);
        rgb->setColor(RGB888(255, 60, 0));
    }

    //     QTimer::singleShot(5000, this, [this]{
    // for (auto rgb : m_rgbs)
    // {
    //         auto layer = rgb->getTopLayer();
    //         layer->clearEffects();
    //         // layer->setFadePeriod(20);
    //         layer->disableFade();
    //         using Fire = shs::lib::Color::FireRgbEffect;
    //         layer->pushEffect(std::make_unique<Fire>(Fire::DEFAULT_START_HUE, Fire::DEFAULT_HUE_GAP,
    //         0.12, 50));
    // }
    //     });
}

void MafiaManager::intro()
{
    auto schedule = [this](const int delay, std::function<void()> action)
    {
        QTimer::singleShot(delay, this, std::move(action));
    };

    auto setColor = [this](const size_t index, const RGB888 color,
                           const uint32_t fadePeriod, const bool fadeEnabled)
    {
        if (index >= m_rgbs.size()) return;

        auto layer = m_rgbs[index]->getTopLayer();
        if (fadeEnabled) layer->enableFade();
        else layer->disableFade();
        layer->setFadePeriod(fadePeriod);
        m_rgbs[index]->setColor(color);
    };

    auto setAll = [this, setColor](const RGB888 color,
                                   const uint32_t fadePeriod,
                                   const bool fadeEnabled)
    {
    for (size_t index = 0; index < m_rgbs.size(); ++index)
    {
        m_rgbs[index]->getTopLayer()->clearEffects();
        setColor(index, color, fadePeriod, fadeEnabled);
    }
    };

    auto setBra = [this](const bool enabled)
    {
        for (auto bra : m_bra)
        {
            if (enabled) bra->on();
            else bra->off();
        }
    };

    schedule(1000, [this, setAll]
    {
        setAll(RGB888(255, 90, 0), 4000, true);
        for (auto bra : m_bra) bra->on();
    });

    schedule(1000, [this, setAll]
             {
                 setAll(RGB888(255, 90, 0), 4000, true);
                 for (auto bra : m_bra) bra->on();
             });

    schedule(33000, [this, setAll]
    {
        setAll(RGB888(103, 76, 48), 1000, true);
        if (!m_bra.empty() && m_bra[0]) m_bra[0]->on(100);
    });

    schedule(49500, [this]
    {
        if (!m_bra.empty() && m_bra[0]) m_bra[0]->on(100);
    });

    constexpr int strobeStart = 40000;
    constexpr int strobePerSpot = 3000;
    constexpr int strobePerFlash = 1500;

    for (size_t spot = 0; spot < std::size(m_rgbs); ++spot)
    {
        for (int flash = 0; flash < 3; ++flash)
        {
            const int start = strobeStart
                + static_cast<int>(spot) * strobePerSpot
                + flash * strobePerFlash;

            schedule(start, [this, setColor, setBra, spot] {
                setColor(spot, RGB888{}, 0, false);
                m_bra[spot % 2]->off();
            });
            schedule(start + 500, [this, setColor, setBra, spot] {
                setColor(spot, RGB888(187, 187, 255), 0, false);
                m_bra[spot % 2]->on();
            });
            schedule(start + 1000, [this, setColor, setBra, spot] {
                setColor(spot, RGB888{}, 0, false);
                m_bra[spot % 2]->off();
            });
            schedule(start + 1500, [this, setColor, setBra, spot] {
                setColor(spot, RGB888(221, 221, 255), 0, false);
                m_bra[spot % 2]->on();
            });
        }
    }

    schedule(55000, [this, setAll] {
        setAll(RGB888{}, 0, false);
        for (auto bra : m_bra) bra->off();
    });
    schedule(57000, [this, setAll] {
        setAll(RGB888{}, 0, false);
        for (auto bra : m_bra) bra->off();
    });

    schedule(58000, [this, setAll] {
        setAll(RGB888{}, 0, false);
        for (auto bra : m_bra) bra->off();
    });
    constexpr int redFlashStart = 80000;
    for (int flash = 0; flash < 26; ++flash)
    {
        const int start = redFlashStart + flash * 400;
        schedule(start, [setColor] {
            setColor(0, RGB888(255, 0, 0), 0, false);
        });
        schedule(start + 400, [setColor] {
            setColor(0, RGB888{}, 0, false);
        });
    }

    schedule(145000, [setAll]
    {
        setAll(RGB888(0, 255, 0), 10000, true);
    });
    schedule(170000, [setAll]
    {
        setAll(RGB888(0, 0, 0), 3000, true);
    });
    schedule(191000, [setAll]
    {
        setAll(RGB888{255, 0, 0}, 500, true);
    });

    for (auto rgb = 0; rgb < std::size(m_rgbs); rgb++)
    {
        schedule(218000 + 500*rgb, [setColor, rgb] { setColor(rgb, RGB888{}, 0, false); });
    }
    schedule(218000, [setColor]
    {
        setColor(0, RGB888(0, 0, 0), 100, true);
    });
    schedule(218600, [setColor]
             {
                 setColor(1, RGB888(0, 0, 0), 100, true);
             });
}
