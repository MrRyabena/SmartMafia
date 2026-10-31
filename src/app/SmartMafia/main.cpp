#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "MafiaEngine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MafiaEngine mafiaEngine(&app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mafiaEngine", &mafiaEngine);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("appSmartMafia", "Main");

    return QCoreApplication::exec();
}
