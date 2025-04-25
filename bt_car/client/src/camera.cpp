#include <QBuffer>
#include "camera.hpp"

void EspCamera::startStream(const QUrl& url) {
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "multipart/x-mixed-replace");
    reply = manager->get(request);
    connect(reply, &QIODevice::readyRead, this, &EspCamera::readData);
}

void EspCamera::readData() {
    buffer.append(reply->readAll());
    processFrames();
}

void EspCamera::processFrames() {
    const QByteArray boundary = "--boundary";
    while (buffer.contains(boundary)) {
        int start = buffer.indexOf(boundary);
        int end = buffer.indexOf(boundary, start + boundary.length());
        if (end == -1) break;

        QByteArray frameData = buffer.mid(start, end - start);
        buffer.remove(0, end);

        // Извлечение JPEG-данных
        int jpgStart = frameData.indexOf("\r\n\r\n") + 4;
        QByteArray jpgData = frameData.mid(jpgStart);

        // Декодирование JPEG
        QImage image;
        QBuffer jpgBuffer(&jpgData);
        jpgBuffer.open(QIODevice::ReadOnly);
        QImageReader reader(&jpgBuffer, "JPEG");

        if (reader.read(&image)) {
            // Обновление GUI в главном потоке
            QMetaObject::invokeMethod(label, [this, image]() {
                label->setPixmap(QPixmap::fromImage(image).scaled(
                    label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }, Qt::QueuedConnection);
        }
    }
}

EspCamera::EspCamera(QLabel* displayLabel) : label(displayLabel) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &EspCamera::onDataReceived);
}

void EspCamera::onDataReceived(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        return;
    }
    // Обработка завершения запроса (если нужно)
    reply->deleteLater();
}
