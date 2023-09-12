#include <QApplication>
#include <QMessageBox>
#include <QDir>
#include <QSize>
#include <QWebEngineView>

class Form1 : public QMainWindow
{
public:
    Form1()
    {
        if (!QDir("data").exists())
        {
            QMessageBox::critical(this, "Unable to continue", "Try to unpack contents of this .zip archive before executing it (application was not able to find 'data' folder near .exe file, usually it only happens when launcher is being executed in .zip archive and not extracted).");
            QApplication::exit(0);
            return;
        }

        QWebEngineView* webBrowser1 = new QWebEngineView(this);
        webBrowser1->setFixedSize(this->size());
        webBrowser1->setAcceptDrops(false);
        this->setCentralWidget(webBrowser1);

        connect(webBrowser1, &QWebEngineView::loadFinished, this, &Form1::onDocumentCompleted);
        webBrowser1->load(QUrl("https://www.plazmaburst2.com/launcher/index.php"));
    }

private slots:
    void onDocumentCompleted(bool isLauncherIndexPhpLoadedProperly)
    {
        QWebEngineView* webBrowser1 = qobject_cast<QWebEngineView*>(sender());
        if (webBrowser1->page()->isContentLoaded())
        {
            QString html = webBrowser1->page()->toHtml();
            if (!html.contains("pb2_logo.png"))
            {
                QNetworkAccessManager* manager = new QNetworkAccessManager(this);
                QNetworkReply* reply = manager->get(QNetworkRequest(QUrl("https://www.plazmaburst2.com/launcher/index.php")));
                connect(reply, &QNetworkReply::finished, [=]() {
                    QByteArray data = reply->readAll();
                    QString new_html = QString::fromUtf8(data);
                    webBrowser1->setHtml(new_html);
                    if (!new_html.contains("pb2_logo.png"))
                    {
                        QFile errorFile("_error1.v");
                        if (errorFile.open(QIODevice::WriteOnly | QIODevice::Text))
                        {
                            QTextStream out(&errorFile);
                            out << "Contents of a page is following (has no 'pb2_logo.png' on page '" << webBrowser1->url() << "'): " << new_html;
                        }
                        errorFile.close();
                        IsOnline = false;
                        RunGame("");
                    }
                });
            }
        }
        else
        {
            QFile errorFile("_error4.v");
            if (errorFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&errorFile);
                out << "Exception during document complete (can be result of offline mode)";
            }
            errorFile.close();
            IsOnline = false;
            RunGame("");
        }
    }
};
