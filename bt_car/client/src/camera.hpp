#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImageReader>
#include <QLabel>

class EspCamera : public QObject {
    Q_OBJECT
public:
    EspCamera(QLabel* displayLabel);
    void startStream(const QUrl& url);
private slots:
    void readData();
    void onDataReceived(QNetworkReply* reply);
    void processFrames();
private:
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QByteArray buffer;
    QLabel* label;
};
