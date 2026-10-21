#ifndef MAFIAPLAYER_H
#define MAFIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>

class MafiaPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MafiaPlayer(QObject *parent = nullptr);


signals:
};

#endif // MAFIAPLAYER_H
