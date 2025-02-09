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
#include <unistd.h>
#include "ui_mainwindow.h"
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <iostream>

#include "assets.h"

#ifndef BAUDRATE
  #define BAUDRATE 9600
#endif

int joy_fd = -1, car_bt_fd = -1;

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

    void send_data_class();

private:
    Ui::MainWindow *ui;
    QThread thread;
    QTimer timer;
    QActionGroup* group_joy;
    QActionGroup* group_car;
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
  //if (joy_fd < 0 || car_bt_fd < 0)
  if (joy_fd >= 0 && car_bt_fd >= 0)
  {
    int written = send_data(stick_joy, joy_fd, car_bt_fd);
    ui->statusbar->showMessage(QString::number(written));
  }
  std::cout << "joy_fd: " << joy_fd << "; car_bt_fd: " << car_bt_fd << std::endl;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    group_joy = new QActionGroup(this);
    group_car = new QActionGroup(this);

    connect(&thread, &QThread::started, this, &MainWindow::send_data_class);
    thread.start();

    timer.setInterval(100);
    connect(&timer, &QTimer::timeout, this, &MainWindow::send_data_class);
    timer.start();


    connect(ui->menujoy, &QMenu::aboutToShow, this, &MainWindow::onMenuAboutToShow_port);
    connect(ui->menucar, &QMenu::aboutToShow, this, &MainWindow::onMenuAboutToShow_port);
}

void MainWindow::onMenuAboutToShow_port()
{
    QMenu* curr_menu = qobject_cast<QMenu*>(sender());
    QStringList files;

    //QActionGroup* curr_group = (curr_menu == ui->menujoy) ? group_joy : group_car;
    QActionGroup* curr_group;

    if (curr_menu == ui->menujoy)
    {
      //QDir dir("/dev/input");
      //files = dir.entryList(QStringList("js*"), QDir::System);
      QDir dir("/home/morkovka21vek/lessons/bc_car/dev/input");
      files = dir.entryList(QStringList("js*"));
      curr_group = group_joy;
    }
    else
    {
      //QDir dir("/dev");
      //files = dir.entryList(QStringList("rfcomm*"), QDir::System);
      QDir dir("/home/morkovka21vek/lessons/bc_car/dev");
      files = dir.entryList(QStringList("rfcomm*"));
      curr_group = group_car;
    }

    foreach (QAction* action, curr_group->actions()) {
        if (!files.contains(action->text())) {
            curr_menu->removeAction(action);
            curr_group->removeAction(action);
            action->deleteLater();
        }
    }

    foreach (const QString& text, files) {
        bool found = false;
        foreach (QAction* action, curr_group->actions()) {
            if (action->text() == text) {
                found = true;
                break;
            }
        }
        if (!found) {
            QAction* action = new QAction(text, this);
            action->setCheckable(true);
            curr_group->addAction(action);

            curr_menu->addAction(action);


            if (curr_menu == ui->menujoy)
              connect(action, &QAction::triggered, this, &MainWindow::onMenuActionTriggered_menujoy);
            else
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
        //joy_fd = open(("/dev/input/" + file.toStdString()).c_str(), O_RDONLY);
        joy_fd = open(("/home/morkovka21vek/lessons/bc_car/dev/input/" + file.toStdString()).c_str(), O_RDONLY);

        if (joy_fd < 0) {
            fprintf(stderr, "%s: Не удалось открыть устройство(джойстик) (ERROR: %d; Line: %d): %s\n", __FILE__, errno, __LINE__, strerror(errno));
        }
    }
}

void MainWindow::onMenuActionTriggered_menucar()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        QString file = action->text();
        ui->statusbar->showMessage(file);

        //action->setChecked(false);
        if (car_bt_fd >= 0) ::close(car_bt_fd);

        //car_bt_fd = open(("/dev/" + file.toStdString()).c_str(), O_RDWR| O_NOCTTY);
        //car_bt_fd = open(("/dev/" + file.toStdString()).c_str(), O_WRONLY | O_NOCTTY | O_NONBLOCK);
        car_bt_fd = open(("/home/morkovka21vek/lessons/bc_car/dev/" + file.toStdString()).c_str(), O_WRONLY | O_NOCTTY | O_NONBLOCK);

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
