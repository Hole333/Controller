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

/**
 * @brief Simulation::socketConnect 连接Socket
 */
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

/**
 * @brief Simulation::socketDisconnect 断开Socket连接
 */
void Simulation::socketDisconnect(void)
{
    this->grSimClient.disconnectUDP();
}


/**
 * @brief Simulation::setClientAddr 设置Client IP地址
 * @param addr
 */
void Simulation::setClientAddr(QString addr)
{
    this->clientAddr = addr;
    qDebug()<< "client addr"<< addr;
}

/**
 * @brief Simulation::setGrSimAddr 设置grSim IP地址
 * @param addr
 */
void Simulation::setGrSimAddr(QString addr)
{
    this->grSimAddr = addr;
    qDebug()<< "grSim addr"<< addr;
}

/**
 * @brief Simulation::setClientPort 设置Client 端口
 * @param port
 */
void Simulation::setClientPort(QString port)
{
    this->clientPort = port;
    qDebug()<< "client addr"<< port;
}

/**
 * @brief Simulation::setGrSimPort 设置grSim 端口
 * @param port
 */
void Simulation::setGrSimPort(QString port)
{
    this->grSimPort = port;
    qDebug()<< "grSim port"<< port;
}

/**
 * @brief Simulation::getControlSide 选择控制方
 * @param index
 */
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

/**
 * @brief Simulation::getSidesSetting 获取控制方
 * @return
 */
QStringList Simulation::getSidesSetting(void)
{
    return this->Sides;
}

/**
 * @brief Simulation::sendCommand 发送指令
 */
void Simulation::sendCommand(void)
{
    this->grSimClient.DEBUGsendCommandV2(this->side, this->robotID, this->velX,
                                         this->velY, this->velR, this->ctrl, this->ctrlPowerLevel,
                                         this->shootMode, this->shoot, this->shootPowerLevel);
}

/**
 * @brief Simulation::test 正常没用 调试用
 * @param flag
 */
void Simulation::test(bool flag)
{
    qDebug()<< "flag: "<< flag;
}
