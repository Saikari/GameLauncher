#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

bool UpdateGame()
{
    QNetworkAccessManager manager;
    QNetworkReply* replyTime = manager.get(QNetworkRequest(QUrl("https://www.plazmaburst2.com/launcher/time.php")));
    QNetworkReply* replyGame = manager.get(QNetworkRequest(QUrl("https://www.plazmaburst2.com/pb2/pb2_re34.swf")));

    QEventLoop loop;
    QObject::connect(replyTime, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(replyGame, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray dataTime = replyTime->readAll();
    QByteArray dataGame = replyGame->readAll();

    QFile fileGame("data/pb2_re34_alt.swf");
    if (fileGame.open(QIODevice::WriteOnly))
    {
        fileGame.write(dataGame);
        fileGame.close();
    }

    QFile fileTime("data/last_update.v");
    if (fileTime.open(QIODevice::WriteOnly))
    {
        fileTime.write(dataTime);
        fileTime.close();
    }

    return true;
}
