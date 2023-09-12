#include <QFile>
#include <QString>
#include <QTextStream>

qint64 GetLastUpdateServerTime()
{
    QString filePath = "data/last_update.v";
    QFile file(filePath);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString text = in.readAll();
            file.close();
            bool ok;
            qint64 lastUpdateServerTime = text.toLongLong(&ok);
            if (ok)
                return lastUpdateServerTime;
        }
    }
    return 0;
}
