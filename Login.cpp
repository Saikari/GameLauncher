#include <QFile>
#include <QStringList>

QString GetLogin()
{
    QString login = "Guest";
    QFile authFile("data/Plazma Burst 2.auth");
    if (authFile.exists())
    {
        if (authFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString authData = authFile.readAll();
            QStringList authLines = authData.split('\n');
            if (!authLines.isEmpty())
            {
                login = authLines[0];
            }
            authFile.close();
        }
    }
    return login;
}

void SaveLoginPassword(QString l, QString p)
{
    QFile authFile("data/Plazma Burst 2.auth");
    if (authFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        authFile.write((l + '\n' + p).toUtf8());
        authFile.close();
    }
}

void DontAskForLogin()
{
    QFile::remove("data/skip_auth.v");
}

bool GetAskForLogin()
{
    return !QFile::exists("data/skip_auth.v");
}
