#include "downloader.h"

/**
 * @brief downloader::downloader
 * @param parent
 */
downloader::downloader(QObject *parent) : QObject(parent)
{
   http = new QNetworkAccessManager();
   connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(onResult(QNetworkReply*)));
}

/**
 * @brief downloader::onRequest
 * @param request
 */
void downloader::onRequest(QNetworkRequest *request)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    textPart.setBody("my text");
    multiPart->append(textPart);

    QUrl url("http://localhost:55555");
    request->setUrl(url);
    QNetworkReply *reply = http->post(*request,multiPart);
    multiPart->setParent(reply);
}

/**
 * @brief downloader::getData
 */
void downloader::getData()
{
    QUrl url(""); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    http->get(request);      // Выполняем запрос
}

/**
 * @brief downloader::onResult
 * @param reply
 */
void downloader::onResult(QNetworkReply *reply)
{
    // Если в процесе получения данных произошла ошибка
    if(reply->error()){
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        // В противном случае создаём объект для работы с файлом
        QFile *file = new QFile("C:/example/file.xml");
        // Создаём файл или открываем его на перезапись ...
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
            file->close();                  // закрываем файл
        qDebug() << "Downloading is completed";
        emit onReady(); // Посылаем сигнал о завершении получения файла
        }
    }
}
