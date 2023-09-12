#include <QApplication>
#include <QHighDpiScaling>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QHighDpiScaling::setApplicationDpiAwareness(QHighDpiScaling::SystemAware);

    // Enable visual styles
    QApplication::setStyle("Fusion");

    // Set compatible text rendering
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Game");
    mainWindow.show();

    return app.exec();
}
