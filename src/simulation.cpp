#include "simulation.h"

Simulation::Simulation(QObject *parent):QObject(parent)
{
    // 初始化仿真参数
    this->clientAddr = "224.5.23.2";
    this->clientPort = "10020";
    this->grSimAddr  = "127.0.0.1";
    this->grSimPort  = "20011";
    this->Sides.append("blue");
    this->Sides.append("yellow");
};

void Simulation::socketConnect(void)
{
    this->client.setIpAddress(this->clientAddr.toStdString());
    this->client.setPort(this->clientPort.toUInt());
    this->client.open(true);
    this->grSimClient.setPortAndAddress(this->grSimPort.toUInt(), this->grSimAddr);
    qDebug()<< "/////////////////////////////////////////////////////";
    qDebug()<< "client: " << this->clientAddr << this->clientPort;
    qDebug()<< "grSimClient: " << this->grSimAddr << this->grSimPort;
    qDebug()<< "socket Connect";
    qDebug()<< "/////////////////////////////////////////////////////";
}

void Simulation::socketDisconnect(void)
{
    this->grSimClient.disconnectUDP();
}

void Simulation::setClientAddr(QString addr)
{
    this->clientAddr = addr;
    qDebug()<< "client addr"<< addr;
}

void Simulation::setGrSimAddr(QString addr)
{
    this->grSimAddr = addr;
    qDebug()<< "grSim addr"<< addr;
}

void Simulation::setClientPort(QString port)
{
    this->clientPort = port;
    qDebug()<< "client addr"<< port;
}

void Simulation::setGrSimPort(QString port)
{
    this->grSimPort = port;
    qDebug()<< "grSim port"<< port;
}

void Simulation::getControlSide(int index)
{
    qDebug()<< this->Sides[index];
    if (this->Sides[index] == "blue")
    {
        this->side = true;
    }
    else
    {
        this->side = false;
    }
}

QStringList Simulation::getSidesSetting(void)
{
    return this->Sides;
}

void Simulation::sendCommand(void)
{
    float speed = 0.0f;
    float sigmod = this->velX / 180.0f;
    if (this->velX < 180)
    {
        speed = this->velX * sigmod;
    }
    else if (this->velX > 180)
    {
        speed = this->velX * sigmod;
    }
    else
    {
        speed = this->velX * sigmod;
    }

    
    float speed = this->velX * sigmod; 
    this->grSimClient.DEBUGsendCommandV3(this->side, this->robotID, this->velX,
                                         -(this->velY), -(int)(((float)this->velR)/10.0f), this->ctrl, this->ctrlPowerLevel,
                                         this->shootMode, this->shoot, (int)(((float)this->shootPowerLevel / 127.0f) * 10.0f));
}

void Simulation::test(bool flag)
{
    qDebug()<< "flag: "<< flag;
}
