#include <QtCore/QCoreApplication>
#include "chatserver.h"
/*!
 * \file
 * @brief Чат С++/Qt/network
 * \author Федоров Никита Сергеевич
 * \version 1.0
 * \date 20.05.2016
 * \warning Всегда останавливаете сервер после работы с ним.
 * \example http://doc.crossplatform.ru/qt/4.5.0/simplechat
 * \todo размещение страницы
 */
/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChatServer server(55555);
    return a.exec();
}
