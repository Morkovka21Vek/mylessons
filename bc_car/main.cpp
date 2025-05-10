#include "ui_mainwindow.h"
#include <QAction>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStringList>
#include <iostream>

#include <errno.h>
#include <fcntl.h>
#include <termios.h>

#ifndef BAUDRATE
#define baud_rate 9600
#else
#define baud_rate BAUDRATE
#endif

int joy_fd, car_bt_fd;

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void onMenuAboutToShow_menujoy();
    void onMenuActionTriggered_menujoy();

    void onMenuAboutToShow_menucar();
    void onMenuActionTriggered_menucar();

  private:
    Ui::MainWindow *ui;
};

MainWindow::~MainWindow() { delete ui; }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Подключить сигнал aboutToShow() меню
    connect(ui->menujoy, &QMenu::aboutToShow, this,
            &MainWindow::onMenuAboutToShow_menujoy);
    connect(ui->menucar, &QMenu::aboutToShow, this,
            &MainWindow::onMenuAboutToShow_menucar);
}

void MainWindow::onMenuAboutToShow_menujoy() {
    static QActionGroup *group = new QActionGroup(this);

    QDir dir("/dev/input");
    QStringList files = dir.entryList(QStringList("js*"), QDir::System);

    foreach (QAction *action, group->actions()) {
        if (!files.contains(action->text())) {
            ui->menujoy->removeAction(action);
            group->removeAction(action);
            action->deleteLater();
        }
    }

    foreach (const QString &text, files) {
        bool found = false;
        foreach (QAction *action, group->actions()) {
            if (action->text() == text) {
                found = true;
                break;
            }
        }
        if (!found) {
            QAction *action = new QAction(text, this);
            action->setCheckable(true);
            group->addAction(action);

            ui->menujoy->addAction(action);

            connect(action, &QAction::triggered, this,
                    &MainWindow::onMenuActionTriggered_menujoy);
        }
    }
}

void MainWindow::onMenuActionTriggered_menujoy() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString file = action->text();
        std::cout << file.toStdString() << std::endl;

        joy_fd = open(("/dev/input/" + file.toStdString()).c_str(), O_RDONLY);
        if (joy_fd < 0) {
            fprintf(stderr,
                    "%s: Не удалось открыть устройство(джойстик) (ERROR: %d; "
                    "Line: %d): %s\n",
                    __FILE__, errno, __LINE__, strerror(errno));
        }
    }
}

void MainWindow::onMenuAboutToShow_menucar() {
    static QActionGroup *group = new QActionGroup(this);

    QDir dir("/dev/input");
    QStringList files = dir.entryList(QStringList("js*"), QDir::System);

    foreach (QAction *action, group->actions()) {
        if (!files.contains(action->text())) {
            ui->menucar->removeAction(action);
            group->removeAction(action);
            action->deleteLater();
        }
    }

    foreach (const QString &text, files) {
        bool found = false;
        foreach (QAction *action, group->actions()) {
            if (action->text() == text) {
                found = true;
                break;
            }
        }
        if (!found) {
            QAction *action = new QAction(text, this);
            action->setCheckable(true);
            group->addAction(action);

            ui->menucar->addAction(action);

            connect(action, &QAction::triggered, this,
                    &MainWindow::onMenuActionTriggered_menucar);
        }
    }
}

void MainWindow::onMenuActionTriggered_menucar() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString file = action->text();
        std::cout << file.toStdString() << std::endl;

        joy_fd = open(("/dev/" + file.toStdString()).c_str(), O_RDONLY);
        if (car_bt_fd < 0) {
            fprintf(stderr,
                    "%s: Не удалось открыть устройство(машина)   (ERROR: %d; "
                    "Line: %d): %s\n",
                    __FILE__, errno, __LINE__, strerror(errno));
            printf("\x1B[32musing:\033[0m\nsudo rfcomm bind /dev/rfcomm0 "
                   "<BLUETOOTH MAC>\n");
        }

        //==========CONFIG_CAR==========//
        struct termios options;
        tcgetattr(car_bt_fd, &options);
        cfsetispeed(&options, baud_rate);
        cfsetospeed(&options, baud_rate);
        options.c_cflag |=
            (CLOCAL | CREAD); // Ignore modem control lines and enable receiver
        options.c_cflag &= ~PARENB; // No parity
        options.c_cflag &= ~CSTOPB; // 1 stop bit
        options.c_cflag &= ~CSIZE;  // Clear the current data size setting
        options.c_cflag |= CS8;     // 8 data bits
        options.c_iflag &=
            ~(IXON | IXOFF | IXANY); // Disable software flow control
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
        options.c_oflag &= ~OPOST;                          // Raw output
        tcsetattr(car_bt_fd, TCSANOW, &options);
        //==========CONFIG_CAR==========//
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#include "main.moc"
