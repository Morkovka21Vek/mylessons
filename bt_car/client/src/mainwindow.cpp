#include "mainwindow.hpp"
#include "car_joy.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QCameraInfo>
#include <QVideoWidget>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <iostream>

#define BT_DIR "/dev"
#define JOY_DIR "/dev/input"
#define BAUDRATE 9600

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    joyPortsGroup = new QActionGroup(this);
    carPortsGroup = new QActionGroup(this);
    videoPortsGroup = new QActionGroup(this);

    setupMenuConnections();
    setupDataSending();
}

MainWindow::~MainWindow()
{
    if (joyFd >= 0) ::close(joyFd);
    if (carBtFd >= 0) ::close(carBtFd);

    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void MainWindow::setupMenuConnections()
{
    connect(ui->menujoy, &QMenu::aboutToShow, this, &MainWindow::refreshPortsMenu);
    connect(ui->menucar, &QMenu::aboutToShow, this, &MainWindow::refreshPortsMenu);
    connect(ui->menuvideo, &QMenu::aboutToShow, this, &MainWindow::refreshPortsMenu);
}

void MainWindow::setupDataSending()
{
    connect(&workerThread, &QThread::started, this, &MainWindow::sendControlData);
    workerThread.start();

    dataTimer.setInterval(100);
    connect(&dataTimer, &QTimer::timeout, this, &MainWindow::sendControlData);
    dataTimer.start();
}

void MainWindow::refreshPortsMenu()
{
    QMenu* currentMenu = qobject_cast<QMenu*>(sender());

    if (currentMenu == ui->menujoy) {
        refreshJoyPorts(currentMenu);
    }
    else if (currentMenu == ui->menuvideo) {
        refreshVideoPorts(currentMenu);
    }
    else {
        refreshCarPorts(currentMenu);
    }
}

void MainWindow::refreshJoyPorts(QMenu* menu)
{
    QDir dir(JOY_DIR);
    QStringList files = dir.entryList(QStringList("js*"), QDir::System);
    updateMenuActions(menu, joyPortsGroup, files);
}

void MainWindow::refreshVideoPorts(QMenu* menu)
{
    QStringList devices;
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo& cameraInfo : cameras) {
        devices << cameraInfo.deviceName();
    }
    updateMenuActions(menu, videoPortsGroup, devices);
}

void MainWindow::refreshCarPorts(QMenu* menu)
{
    QDir dir(BT_DIR);
    QStringList files = dir.entryList(QStringList("rfcomm*"), QDir::System);
    updateMenuActions(menu, carPortsGroup, files);
}

void MainWindow::updateMenuActions(QMenu* menu, QActionGroup* group, const QStringList& items)
{
    // Remove actions for devices that are no longer available
    foreach (QAction* action, group->actions()) {
        if (!items.contains(action->text())) {
            menu->removeAction(action);
            group->removeAction(action);
            action->deleteLater();
        }
    }

    // Add actions for new devices
    foreach (const QString& item, items) {
        bool exists = false;
        foreach (QAction* action, group->actions()) {
            if (action->text() == item) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            QAction* action = new QAction(item, this);
            action->setCheckable(true);
            group->addAction(action);
            menu->addAction(action);

            if (menu == ui->menujoy) {
                connect(action, &QAction::triggered, this, &MainWindow::handleJoyPortSelection);
            }
            else if (menu == ui->menuvideo) {
                connect(action, &QAction::triggered, this, &MainWindow::handleVideoPortSelection);
            }
            else {
                connect(action, &QAction::triggered, this, &MainWindow::handleCarPortSelection);
            }
        }
    }
}

void MainWindow::handleJoyPortSelection()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action) return;

    QString devicePath = "/dev/input/" + action->text();
    ui->statusbar->showMessage(devicePath);

    if (joyFd >= 0) ::close(joyFd);
    joyFd = open(devicePath.toStdString().c_str(), O_RDONLY);

    if (joyFd < 0) {
        fprintf(stderr, "Failed to open joystick device: %s\n", strerror(errno));
    }
}

void MainWindow::handleVideoPortSelection()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action) return;

    if (camera && camera->state() == QCamera::ActiveState) {
        camera->stop();
        delete camera;
        camera = nullptr;
    }

    QString cameraName = action->text();
    ui->statusbar->showMessage(cameraName);

    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras) {
        if (cameraInfo.deviceName() == cameraName) {
            camera = new QCamera(cameraInfo);
            break;
        }
    }

    QVideoWidget *videoWidget = ui->centralwidget->findChild<QVideoWidget*>();
    if (videoWidget && camera) {
        camera->setViewfinder(videoWidget);
        camera->start();
    }
}

void MainWindow::handleCarPortSelection()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action) return;

    QString devicePath = "/dev/" + action->text();
    ui->statusbar->showMessage(devicePath);

    if (carBtFd >= 0) ::close(carBtFd);
    carBtFd = open(devicePath.toStdString().c_str(), O_WRONLY | O_NOCTTY | O_NONBLOCK);

    if (carBtFd < 0) {
        fprintf(stderr, "Failed to open car Bluetooth device: %s\n", strerror(errno));
        printf("Usage: sudo rfcomm bind /dev/rfcomm0 <BLUETOOTH MAC>\n");
    } else {
        configureBluetoothConnection();
    }
}

void MainWindow::configureBluetoothConnection()
{
    struct termios options;
    tcgetattr(carBtFd, &options);
    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    tcsetattr(carBtFd, TCSANOW, &options);
}

void MainWindow::sendControlData()
{
    if (joyFd >= 0 && carBtFd >= 0) {
        ssize_t written = send_data(stick_joy, joyFd, carBtFd);
        ui->statusbar->showMessage(QString::number(written));
    }
}
