#include <QFile>
#include <QProcess>
#include <QDir>
#include <QCoreApplication>
#include <QWindow>
#include <QScreen>

void RunGame(QString s)
{
    QString myParams = "?from_standalone=1";

    QFile authFile("data/Plazma Burst 2.auth");
    if (authFile.exists())
    {
        if (authFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString authData = authFile.readAll();
            QStringList authLines = authData.split('\n');
            if (authLines.size() >= 2)
            {
                QString username = authLines[0];
                QString password = authLines[1];
                myParams = "?l=" + username + "&p=" + password + "&from_standalone=1";
            }
            authFile.close();
        }
    }

    QString executablePath = QDir::currentPath() + "/data/flashplayer11_7r700_224_win_sa.exe";
    QString arguments;
    if (s.isEmpty())
    {
        arguments = "\"data/pb2_re34_alt.swf" + myParams + "\"";
    }
    else
    {
        arguments = "\"data/" + s + "\"";
    }

    QProcess process;
    process.setProgram(executablePath);
    process.setArguments({ arguments });
    process.setWindowFlags(Qt::Window);
    process.startDetached();

    // Set window position and size
    QWindow* window = process.windowHandle();
    if (window)
    {
        const int windowWidth = 800;
        const int windowHeight = 400;
        const int windowX = (QGuiApplication::primaryScreen()->size().width() - windowWidth) / 2;
        const int windowY = 0;
        window->setGeometry(windowX, windowY, windowWidth, windowHeight);
        window->setWindowTitle(s.isEmpty() ? "Plazma Burst 2" : "Plazma Burst: Forward to the Past");
        window->setIcon(QIcon("data/favicon.ico"));
        window->showNormal();
        window->requestActivate();
    }

    QCoreApplication::quit();
}
