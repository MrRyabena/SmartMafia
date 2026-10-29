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
        MANIAC_SLEEP_SHERIFF_WU = 8,
        SHERIFF_WU = 9,
        SHERIFF = 10,
        SHERIFF_SLEEP = 11,
        SHERIFF_SLEEP_DOCTOR_WU = 12,
        DOCTOR_WU = 13,
        DOCTOR = 14,
        DOCTOR_SLEEP = 15,
        DOCTOR_SLEEP_BITCH_WU = 16,
        BITCH_WU = 17,
        BITCH_SLEEP = 18,
        TOWNSMAN_1 = 19,
        TOWNSMAN_2 = 20,
        CITY_WU = 21,
        MURDER = 22,
        INCREASE_BACKGROUND = 23,
        DECREASE_BACKGROUND = 24,
        FIRST_NIGHT = 25,
        INTRO = 26,

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
        "maniac_sleep_sheriff_wu",     // 8
        "sheriff_wu",                  // 9
        "sheriff",                     // 10
        "sheriff_sleep",               // 11
        "sheriff_sleep_doctor_wu",     // 12
        "doctor_wu",                   // 13
        "doctor",                      // 14
        "doctor_sleep",                // 15
        "doctor_sleep_bitch_wu",       // 16
        "bitch_wu",                    // 17
        "bitch_sleep",                 // 18
        "townsman_1",                  // 19
        "townsman_2",                  // 20
        "city_wu",                     // 21
        "murder",                      // 22
        "increase_background",         // 23
        "decrease_background",         // 24
        "first_night",                 // 25
        "intro",                       // 26
    };
}
