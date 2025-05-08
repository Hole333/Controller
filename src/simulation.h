#ifndef SIMULATION_H
#define SIMULATION_H
/**
 * brief: 搭配手柄控制grSim仿真环境机器
 * date: 2025.5.9
 * author: DEBUG DQY
*/
#include <QObject>
#include <QString>
#include <QtDebug>
#include <QUdpSocket>
#include "ssl-client/net/robocup_ssl_client/robocup_ssl_client.h"
#include "ssl-client/net/grSim_client_example/grSim_client_example.h"
#include "ssl-client/protobuf-files/pb/grSim_Packet.pb.h"
#include "ssl-client/protobuf-files/pb/grSim_Commands.pb.h"
#include "ssl-client/protobuf-files/pb/grSim_Replacement.pb.h"
class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);
    Q_INVOKABLE void socketConnect(void);
    Q_INVOKABLE void socketDisconnect(void);
    Q_INVOKABLE void setClientAddr(QString addr);
    Q_INVOKABLE void setGrSimAddr(QString addr);
    Q_INVOKABLE void setClientPort(QString port);
    Q_INVOKABLE void setGrSimPort(QString port);
    Q_INVOKABLE void test(bool flag);
    Q_INVOKABLE void sendCommand(void);
    Q_INVOKABLE QStringList getSidesSetting(void);
    Q_INVOKABLE void getControlSide(int index);
    Q_INVOKABLE void updateCommandParams(int robotID,int velX,int velY,int velR,bool ctrl,int ctrlLevel,bool mode,bool shoot,int power)
    {
        this->robotID = robotID;
        this->velX = velX; this->velY = velY; this->velR = velR;
        this->ctrl = ctrl;
        this->shootMode = mode;this->shoot = shoot; this->shootPowerLevel = power;
        this->ctrlPowerLevel = ctrlLevel;
        // qDebug() << "ID" << robotID;
    }
private:
    RoboCupSSLClient client;
    SSL_WrapperPacket packet;
    GrSim_Client_Example grSimClient;
    QStringList Sides;
    bool side;
    quint16 _port;
    QString clientAddr;
    QString grSimAddr;
    QString clientPort;
    QString grSimPort;
    bool shoot;
    bool ctrl;
    bool shootMode;//false is "flat shoot" and true is "lift shoot".
    quint8 robotID;
    //packageTypes: 0x00, 0x40, 0x80, 0xc0
    quint8 packageType = 0x00;
    //gameStatus: 0x00, 0x10, 0x20, 0x30
    quint8 gameStatus = 0x00;
    qint16 velX;
    qint16 velY;
    qint16 velR;
    quint16 ctrlPowerLevel;
    quint16 shootPowerLevel;
};

#endif // SIMULATION_H
