#pragma once

#include <QThread>
#include <QTimer>
#include <QMainWindow>
#include <QActionGroup>
#include <QCamera>
#include <unistd.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refreshPortsMenu();
    void handleJoyPortSelection();
    void handleCarPortSelection();
    void handleVideoPortSelection();
    void sendControlData();
    void updateMenuActions(QMenu* menu, QActionGroup* group, const QStringList& items);

private:
    void setupMenuConnections();
    void setupDataSending();
    void refreshJoyPorts(QMenu* menu);
    void refreshVideoPorts(QMenu* menu);
    void refreshCarPorts(QMenu* menu);
    void configureBluetoothConnection();

    Ui::MainWindow *ui;
    QThread workerThread;
    QTimer dataTimer;
    QActionGroup* joyPortsGroup;
    QActionGroup* carPortsGroup;
    QActionGroup* videoPortsGroup;
    QCamera* camera = nullptr;
    ssize_t joyFd = -1;
    ssize_t carBtFd = -1;
};
