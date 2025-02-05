#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <iostream>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMenuAboutToShow();
    void onMenuActionTriggered();

private:
    Ui::MainWindow *ui;
};

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключить сигнал aboutToShow() меню
    connect(ui->menujoy, &QMenu::aboutToShow, this, &MainWindow::onMenuAboutToShow);
}

void MainWindow::onMenuAboutToShow()
{
    static QActionGroup* group = new QActionGroup(this);

    QDir dir("/dev");
    QStringList files = dir.entryList(QStringList("tty*"), QDir::System);
    //QStringList files = dir.entryList(QDir::System);
    //QStringList files = dir.entryList(QDir::AllEntries);
    //foreach (const QString& file, files) {
    //    QAction* action = new QAction(file, this);
    //    action->setCheckable(true);
    //    group->addAction(action);
    //    ui->menujoy->addAction(action);

    //    connect(action, &QAction::triggered, this, &MainWindow::onMenuActionTriggered);
    //    //ui->menujoy->addAction(action);
    //}

    foreach (QAction* action, group->actions()) {
        if (!files.contains(action->text())) {
            ui->menujoy->removeAction(action);
            group->removeAction(action);
            action->deleteLater();
        }
    }

    foreach (const QString& text, files) {
        bool found = false;
        foreach (QAction* action, group->actions()) {
            if (action->text() == text) {
                found = true;
                break;
            }
        }
        if (!found) {
            QAction* action = new QAction(text, this);
            action->setCheckable(true);
            group->addAction(action);

            ui->menujoy->addAction(action);


            connect(action, &QAction::triggered, this, &MainWindow::onMenuActionTriggered);
        }
    }
}

void MainWindow::onMenuActionTriggered()
{
     QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        QString file = action->text();
        std::cout << file.toStdString() << std::endl;
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
