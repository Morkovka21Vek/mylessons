#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <unistd.h>
#include <QCameraInfo>
#include "ui_mainwindow.h"
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include <iostream>
#include "car_joy.h"

#ifndef BAUDRATE
  #define BAUDRATE 9600
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMenuAboutToShow_port();

    void onMenuActionTriggered_menujoy();
    void onMenuActionTriggered_menucar();
    void onMenuActionTriggered_menuvideo();

    void send_data_class();

private:
    Ui::MainWindow *ui;
    QThread thread;
    QTimer timer;
    QActionGroup* group_ports_joy;
    QActionGroup* group_ports_car;
    QActionGroup* group_ports_video;
    QCamera* camera = nullptr;
    ssize_t joy_fd = -1, car_bt_fd = -1;
};

MainWindow::~MainWindow()
{
    if (joy_fd >= 0)    ::close(joy_fd);
    if (car_bt_fd >= 0) ::close(car_bt_fd);
    thread.quit();
    thread.wait();

    delete ui;
}

void MainWindow::send_data_class() {
  if (joy_fd >= 0 && car_bt_fd >= 0)
  {
    ssize_t written = send_data(stick_joy, joy_fd, car_bt_fd);
    ui->statusbar->showMessage(QString::number(written));
  }
  //std::cout << "joy_fd: " << joy_fd << "; car_bt_fd: " << car_bt_fd << std::endl;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    group_ports_joy   = new QActionGroup(this);
    group_ports_car   = new QActionGroup(this);
    group_ports_video = new QActionGroup(this);

    connect(&thread, &QThread::started, this, &MainWindow::send_data_class);
    thread.start();

    timer.setInterval(100);
    connect(&timer, &QTimer::timeout, this, &MainWindow::send_data_class);
    timer.start();


    connect(ui->menujoy, &QMenu::aboutToShow, this, &MainWindow::onMenuAboutToShow_port);
    connect(ui->menucar, &QMenu::aboutToShow, this, &MainWindow::onMenuAboutToShow_port);
    connect(ui->menuvideo, &QMenu::aboutToShow, this, &MainWindow::onMenuAboutToShow_port);
}

void MainWindow::onMenuAboutToShow_port()
{
    QMenu* curr_menu = qobject_cast<QMenu*>(sender());
    QStringList files;

    QActionGroup *curr_group;

    if (curr_menu == ui->menujoy)
    {
      QDir dir("/dev/input");
      files = dir.entryList(QStringList("js*"), QDir::System);
      curr_group = group_ports_joy;
    }
    else if (curr_menu == ui->menuvideo)
    {
      const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
      for (const QCameraInfo& cameraInfo : cameras) {
        files << cameraInfo.deviceName();
      }
      curr_group = group_ports_video;
    }
    //else if (curr_menu == ui->menucar)
    else
    {
      QDir dir("/dev");
      files = dir.entryList(QStringList("rfcomm*"), QDir::System);
      curr_group = group_ports_car;
    }

    foreach (QAction* action, curr_group->actions()) {
        if (!files.contains(action->text())) {
            curr_menu->removeAction(action);
            curr_group->removeAction(action);
            action->deleteLater();
        }
    }

    foreach (const QString& text, files) {
        bool found_flag = false;
        foreach (QAction* action, curr_group->actions()) {
          if (action->text() == text){
            found_flag = true;
            break;
          }
        }

        if (!found_flag) {
          QAction* action = new QAction(text, this);
          action->setCheckable(true);

          curr_group->addAction(action);
          curr_menu->addAction(action);


          if (curr_menu == ui->menujoy)
            connect(action, &QAction::triggered, this, &MainWindow::onMenuActionTriggered_menujoy);
          else if (curr_menu == ui->menuvideo)
            connect(action, &QAction::triggered, this, &MainWindow::onMenuActionTriggered_menuvideo);
          else if (curr_menu == ui->menucar)
            connect(action, &QAction::triggered, this, &MainWindow::onMenuActionTriggered_menucar);
        }
    }
}


void MainWindow::onMenuActionTriggered_menujoy()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        QString file = action->text();
        ui->statusbar->showMessage(file);

        if (joy_fd >= 0) ::close(joy_fd);
        joy_fd = open(("/dev/input/" + file.toStdString()).c_str(), O_RDONLY);

        if (joy_fd < 0) {
            fprintf(stderr, "%s: Не удалось открыть устройство(джойстик) (ERROR: %d; Line: %d): %s\n", __FILE__, errno, __LINE__, strerror(errno));
        }
    }
}

void MainWindow::onMenuActionTriggered_menuvideo()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
      if (camera && camera->state() == QCamera::ActiveState) {
        std::cout << "Delete camera" << std::endl;
        camera->stop();
        delete camera;
        camera = nullptr;
      }
      QString textCamera = action->text();
      ui->statusbar->showMessage(textCamera);

      const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
      for (const QCameraInfo &cameraInfo : cameras) {
        if (cameraInfo.deviceName() == textCamera)
          camera = new QCamera(cameraInfo);
      }

      QVideoWidget *videoWidget = ui->centralwidget->findChild<QVideoWidget*>();

      if (videoWidget && camera) {
        camera->setViewfinder(videoWidget);
        camera->start();
      }
    }
}

void MainWindow::onMenuActionTriggered_menucar()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        QString file = action->text();
        ui->statusbar->showMessage(file);

        if (car_bt_fd >= 0) ::close(car_bt_fd);
        //car_bt_fd = open(("/dev/" + file.toStdString()).c_str(), O_RDWR| O_NOCTTY);
        car_bt_fd = open(("/dev/" + file.toStdString()).c_str(), O_WRONLY | O_NOCTTY | O_NONBLOCK);

        if (car_bt_fd < 0) {
          fprintf(stderr, "%s: Не удалось открыть устройство(машина)   (ERROR: %d; Line: %d): %s\n", __FILE__, errno, __LINE__, strerror(errno));
          printf("\x1B[32musing:\033[0m\nsudo rfcomm bind /dev/rfcomm0 <BLUETOOTH MAC>\n");
        }
        else
        {
          struct termios options;
          tcgetattr(car_bt_fd, &options);
          cfsetispeed(&options, BAUDRATE);
          cfsetospeed(&options, BAUDRATE);
          options.c_cflag |= (CLOCAL | CREAD); // Ignore modem control lines and enable receiver
          options.c_cflag &= ~PARENB; // No parity
          options.c_cflag &= ~CSTOPB; // 1 stop bit
          options.c_cflag &= ~CSIZE; // Clear the current data size setting
          options.c_cflag |= CS8; // 8 data bits
          options.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
          options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
          options.c_oflag &= ~OPOST; // Raw output
          tcsetattr(car_bt_fd, TCSANOW, &options);
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#include "main.moc"
