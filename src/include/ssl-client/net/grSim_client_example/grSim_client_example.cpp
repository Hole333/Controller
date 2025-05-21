#include "grSim_client_example.h"
#include <ssl-client/protobuf-files/pb/zss_cmd.pb.h>
#include "ssl-client/protobuf-files/protobuf-files.h"

GrSim_Client_Example::GrSim_Client_Example(QObject* parent) : QObject(parent) {
  // create a QUDP socket
  socket = new QUdpSocket(this);

  this->_addr.setAddress("224.5.23.2");
  this->_port = quint16(20011);

  socket->bind(this->_addr, this->_port);
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void GrSim_Client_Example::setPortAndAddress(int port, const QString& address) {
  this->_port = quint16(port);
  this->_addr.setAddress(address);
}

//void GrSim_Client_Example::DEBUGsendCommandV2(bool side, int robotID, int velX, int velY, int velR, bool
//  ctrl, int ctrlLevel, bool mode, bool shoot, int power) {
//  double zero = 0.0;
//  grSim_Packet packet;
//  bool yellow = true;
//  if (side) // blue
//  {
//    yellow = false;
//  }
//  packet.mutable_commands()->set_isteamyellow(yellow);
//  packet.mutable_commands()->set_timestamp(0.0);
//  grSim_Robot_Command* command =
//    packet.mutable_commands()->add_robot_commands();
//  command->set_id(robotID);

//  command->set_wheelsspeed(!true);
//  command->set_wheel1(zero);
//  command->set_wheel2(zero);
//  command->set_wheel3(zero);
//  command->set_wheel4(zero);
//  command->set_veltangent(velX);
//  command->set_velnormal(velY);
//  command->set_velangular(velR);

//  // true chip false flat
//  if (shoot && !mode)
//  {
//    command->set_kickspeedx(zero);
//    command->set_kickspeedz(ctrlLevel);
//  }
//  else if (shoot && mode)
//  {
//    command->set_kickspeedx(power);
//    command->set_kickspeedz(zero);
//  }
//  else if (!shoot)
//  {
//    command->set_kickspeedx(zero);
//    command->set_kickspeedz(zero);
//  }
//  else
//  {
//    command->set_kickspeedx(zero);
//    command->set_kickspeedz(zero);
//  }

//  command->set_spinner(false);

//  QByteArray dgram;
//  dgram.resize(packet.ByteSize());
//  packet.SerializeToArray(dgram.data(), dgram.size());
//  if (socket->writeDatagram(dgram, this->_addr, this->_port) > -1) {
//    qDebug("send data");
//  }
//}

void GrSim_Client_Example::DEBUGsendCommandV3(bool side, int robotID, int velX, int velY
  , int velR, bool ctrl, int ctrlLevel, bool mode, bool shoot, int power)

{
  grSim_Packet packet;
  bool yellow = !side;
  packet.mutable_commands()->set_isteamyellow(yellow);
  packet.mutable_commands()->set_timestamp(0.0);

  // 新版 grSim 需要 ZSS::New::Robots_Command
  grSim_Commands * commands = packet.mutable_commands();
  //robot cmd ZSS::New::Robot_Command cmd 学Mark、用auto
  auto *command = commands->mutable_robot_commands()->add_command();
  command->set_robot_id(robotID);

  // 速度控制
  command->set_cmd_type(ZSS::New::Robot_Command_CmdType_CMD_VEL);
  auto* vel = command->mutable_cmd_vel();
  vel->set_velocity_x(velX);
  vel->set_velocity_y(velY);
  vel->set_velocity_r(velR);

  // 踢球和带球
  if (shoot) {
    if (mode) {
      command->set_kick_mode(ZSS::New::Robot_Command_KickMode_KICK);
      command->set_desire_power(power);
    }
    else {
      command->set_kick_mode(ZSS::New::Robot_Command_KickMode_CHIP);
      command->set_desire_power(ctrlLevel);
    }
  }
  else {
    command->set_kick_mode(ZSS::New::Robot_Command_KickMode_NONE);//bushemen
    command->set_desire_power(0.0);
  }
  command->set_dribble_spin(0.0);

  // 序列化并发送
  QByteArray dgram;
  dgram.resize(packet.ByteSize());
  packet.SerializeToArray(dgram.data(), dgram.size());
  if (socket->writeDatagram(dgram, this->_addr, this->_port) > -1) {
    qDebug("send data");
  }
}


//void GrSim_Client_Example::sendCommand(double velX, int id) {
//  double zero = 0.0;
//  grSim_Packet packet;
//  bool yellow = false;
//  packet.mutable_commands()->set_isteamyellow(yellow);
//  packet.mutable_commands()->set_timestamp(0.0);
//  grSim_Robot_Command* command =
//    packet.mutable_commands()->add_robot_commands();
//  command->set_id(id);

//  command->set_wheelsspeed(!true);
//  command->set_wheel1(zero);
//  command->set_wheel2(zero);
//  command->set_wheel3(zero);
//  command->set_wheel4(zero);
//  command->set_veltangent(velX);
//  command->set_velnormal(zero);
//  command->set_velangular(zero);

//  command->set_kickspeedx(zero);
//  command->set_kickspeedz(zero);
//  command->set_spinner(false);

//  QByteArray dgram;
//  dgram.resize(packet.ByteSize());
//  packet.SerializeToArray(dgram.data(), dgram.size());
//  if (socket->writeDatagram(dgram, this->_addr, this->_port) > -1) {
//    qDebug("send data");
//  }
//}

void GrSim_Client_Example::readyRead() {
  // when data comes in
  QByteArray buffer;
  buffer.resize(socket->pendingDatagramSize());

  QHostAddress sender;
  quint16 senderPort;

  socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

  qDebug() << "Message from: " << sender.toString();
  qDebug() << "Message port: " << senderPort;
  qDebug() << "Message: " << buffer;
}

void GrSim_Client_Example::reconnectUDP(void)
{
  socket->bind(this->_addr, this->_port);
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void GrSim_Client_Example::disconnectUDP(void)
{
  this->socket->close();
}
