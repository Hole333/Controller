#ifndef GRSIMCLIENTEXAMPLE_H
#define GRSIMCLIENTEXAMPLE_H

#include <QObject>
#include <QUdpSocket>

class GrSim_Client_Example : public QObject {
  Q_OBJECT
 public:
  explicit GrSim_Client_Example(QObject* parent = 0);
  void setPortAndAddress(int port, const QString& address);
  void sendCommand(double velX, int id);
  void DEBUGsendCommandV2(bool side, int robotID,int velX,int velY,int velR,bool ctrl,int ctrlLevel,bool mode,bool shoot,int power);
  void DEBUGsendCommandV3(bool side, int robotID,int velX,int velY,int velR,bool ctrl,int ctrlLevel,bool mode,bool shoot,int power);
  void disconnectUDP(void);
  void reconnectUDP(void);
  QHostAddress _addr;
  quint16 _port;
  // friend class Robot_Command;

 signals:

 public slots:
  void readyRead();

 private:
  QUdpSocket* socket;
};

#endif // GRSIMCLIENTEXAMPLE_H
