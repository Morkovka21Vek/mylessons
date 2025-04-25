#pragma once

#include <QThread>
#include <QTimer>
#include <QMainWindow>
#include <QActionGroup>
#include <QCamera>
#include <unistd.h>
#include <functional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ssize_t getJoyFd();
    ~MainWindow();

private slots:
    void handleJoyPortSelection();
    void updateMenuActions(QMenu* menu, QActionGroup* group, const QStringList& items, const std::function<void()>& handler);

private:
    void setupMenuConnections();
    void refreshJoyPorts();

    ssize_t joyFd;
    Ui::MainWindow *ui;
    QThread workerThread;
    QTimer dataTimer;
    QActionGroup* joyPortsGroup;
};
