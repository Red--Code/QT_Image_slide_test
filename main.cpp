#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QPropertyAnimation>
#include <opencv2/opencv.hpp>
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3); 
    QSurfaceFormat::setDefaultFormat(format);

    QWidget mainWindow;
    mainWindow.setWindowTitle("Image Animation");
    mainWindow.resize(800, 600);


    QPixmap pixmap("image.png");
    if (pixmap.isNull()) {
        qWarning("Failed to load the image.");
        return -1;
    }
    pixmap = pixmap.scaled(400, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel* imageLabel = new QLabel(&mainWindow);
    imageLabel->setPixmap(pixmap);
    imageLabel->setFixedSize(pixmap.size());
    imageLabel->move(800, 200);
    
    QPropertyAnimation* animation = new QPropertyAnimation(imageLabel, "pos");
    animation->setDuration(2000);           
    animation->setStartValue(QPoint(800, 200)); 
    animation->setEndValue(QPoint(-400, 200));  
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setLoopCount(-1);
    mainWindow.setWindowTitle("Loop");
    mainWindow.setStyleSheet("background-color: white;");
    mainWindow.show();

    animation->start();
    
    return app.exec();
}