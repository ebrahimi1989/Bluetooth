#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    QObject::connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
        [](const QBluetoothDeviceInfo &device) {
            qDebug() << "Found device:" << device.name() << "(" << device.address().toString() << ")";
        });

    QObject::connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
        [discoveryAgent]() {
            if (discoveryAgent->error() != QBluetoothDeviceDiscoveryAgent::NoError) {
                qDebug() << "Error:" << discoveryAgent->error();
            }
            discoveryAgent->deleteLater();
        });

    discoveryAgent->start();

    return app.exec();
}
