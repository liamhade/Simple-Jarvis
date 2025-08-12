#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleInput();
    // void handleBackendReply(QNetworkReply*);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* networkManager;      // <- to make HTTP requests
};

#endif // MAINWINDOW_H
