#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create network manager
    networkManager = new QNetworkAccessManager(this);

    // Connect input bar and button to handler
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::handleInput);
    connect(ui->inputBar, &QLineEdit::returnPressed, this, &MainWindow::handleInput);
}

void MainWindow::handleInput() {
    QString userInput = ui->inputBar->text();
    qDebug() << "User input:" << userInput;

    ui->responseWidget->append("✅ Server: " + userInput);

    QNetworkRequest request(QUrl("http://127.0.0.1:8000/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["input"] = userInput;
    QJsonDocument doc(json);

    QNetworkReply* reply = networkManager->post(request, doc.toJson());

    // Handle when the request is done
    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray responseData = reply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << parseError.errorString();
            reply->deleteLater();
            return;
        }

        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON object received";
            reply->deleteLater();
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj.contains("status") && jsonObj["status"] == "complete") {
            ui->responseWidget->append("🤖 Bot: " + jsonObj["response"].toString() + "\n");
        } else {
            qDebug() << "Unexpected JSON:" << jsonObj;
        }

        reply->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
