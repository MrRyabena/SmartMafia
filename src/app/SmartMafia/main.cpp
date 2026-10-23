#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <MafiaActions.h>

#include "MafiaPlayer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    qmlRegisterType<MafiaPlayer>("MafiaPlayer", 1, 0, "MafiaPlayer");
    // qmlRegisterType<shs::mafia::MafiaActions>("MafiaActions", 1, 0, "MafiaActions");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("appSmartMafia", "Main");

    return QCoreApplication::exec();
}
