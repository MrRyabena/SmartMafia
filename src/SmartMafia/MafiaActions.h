#pragma once

#include <stdint.h>
#include <array>
#include <QObject>

namespace shs::mafia
{
    enum class MafiaActions : uint8_t
    {
        NO_ACTION,
        CITY_SLEEP = 1,
        MAFIA = 2,
        MAFIA_SLEEP = 3,
        MAFIA_SLEEP_MANIAC_WU = 4,
        MANIAC_WU = 5,
        MANIAC = 6,
        MANIAC_SLEEP = 7,
        MANIAC_SLEEP_DOCTOR_WU = 8,
        DOCTOR_WU = 9,
        DOCTOR = 10,
        DOCTOR_SLEEP = 11,
        DOCTOR_SLEEP_SHERIF_WU = 12,
        SHERIF_WU = 13,
        SHERIF = 14,
        SHERIF_SLEEP = 15,
        SHERIF_SLEEP_BITCH_WU = 16,
        BITCH_WU = 17,
        BITCH_SLEEP = 18,
        TOWNSMAN_1 = 19,
        TOWNSMAN_2 = 20,
        CITY_WU = 21,
        MURDER = 22,
        INCREASE_BACKGROUND = 23,
        DECREASE_BACKGROUND = 24,


        COUNT
    };

    constexpr std::array<const char*, static_cast<size_t>(MafiaActions::COUNT)> mafiaActionNames = {
        "no_action",                   // 0
        "city_sleep",                  // 1
        "mafia",                       // 2
        "mafia_sleep",                 // 3
        "mafia_sleep_maniac_wu",       // 4
        "maniac_wu",                   // 5
        "maniac",                      // 6
        "maniac_sleep",                // 7
        "maniac_sleep_doctor_wu",      // 8
        "doctor_wu",                   // 9
        "doctor",                      // 10
        "doctor_sleep",                // 11
        "doctor_sleep_sherif_wu",      // 12
        "sherif_wu",                   // 13
        "sherif",                      // 14
        "sherif_sleep",                // 15
        "sherif_sleep_bitch_wu",       // 16
        "bitch_wu",                    // 17
        "bitch_sleep",                 // 18
        "townsman_1",                  // 19
        "townsman_2",                  // 20
        "city_wu",                     // 21
        "murder",                      // 22
        "increase_background",         // 23
        "decrease_background"          // 24
    };
}
