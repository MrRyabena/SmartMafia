cmake_minimum_required(VERSION 3.16)

project(appSmartMafia VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SHS_CMF_QT ON CACHE BOOL "Enable Qt" FORCE)
set(SHS_CMF_UNUSE_SHS_SETTINGS ON CACHE BOOL "Disable shs_settings.h" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appSmartMafia
    main.cpp
)

qt_add_big_resources(appSmartMafia_big_resources qml.qrc)
target_sources(appSmartMafia PRIVATE ${appSmartMafia_big_resources})

set(EXTERNAL_MAFIA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../SmartMafia")


qt_add_qml_module(appSmartMafia
    URI appSmartMafia
    VERSION 1.0
    QML_FILES
        Main.qml
        SmartMafiaGui.qml
        MafiaActions.qml
    SOURCES
        MafiaPlayer.h
        MafiaPlayer.cpp
    RESOURCES
        qml.qrc
        SOURCES MafiaEngine.h MafiaEngine.cpp
        SOURCES MafiaManager.h MafiaManager.cpp
)


# include(FetchContent)

# FetchContent_Declare(
#     SHScore
#     URL https://github.com/MrRyabena/SmartHomeSystem/releases/latest/download/SHScore.zip
#     URL https://github.com/MrRyabena/SmartHomeSystem/releases/latest/download/SHS-library_SHS_ARGB.zip
# )

# FetchContent_MakeAvailable(SHScore)

add_subdirectory(ShsBuild/SHScore/)
add_subdirectory(ShsBuild/SHS_SmartSpot/)
add_subdirectory(ShsBuild/SHS_APIids/)
add_subdirectory(ShsBuild/SHS_Color/src)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSmartMafia PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSmartMafia
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(SHScore PRIVATE SHS_SF_UNUSE_SHS_SETTINGS)
target_compile_definitions(SHS_SmartSpot PRIVATE SHS_SF_UNUSE_SHS_SETTINGS)
target_compile_definitions(appSmartMafia PUBLIC SHS_SF_UNUSE_SHS_SETTINGS)

target_include_directories(appSmartMafia
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../SmartMafia")

target_link_libraries(appSmartMafia
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Multimedia
    PRIVATE SHScore
    PRIVATE SHS_SmartSpot
)

install(TARGETS appSmartMafia
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
