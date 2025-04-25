#include "functionsforclient.h"

FunctionsForClient::FunctionsForClient()
{
    client = Singltoneforclient::getInstance();

    ui_auth = new AuthRegForm;
    ui_auth->show();
    connect(ui_auth, &AuthRegForm::auth, this, &FunctionsForClient::sendAuth);
    connect(ui_auth, &AuthRegForm::reg, this, &FunctionsForClient::sendReg);
    connect(client, &Singltoneforclient::msgFromServer, this, &FunctionsForClient::msgHandler);

}

void FunctionsForClient::sendAuth(QString log, QString pass)
{
    this->login = log;
    client->sendMsgToServer("auth&" + log + "&" + pass);
}

void FunctionsForClient::sendReg(QString log, QString pass, QString email)
{
    this->login = log;
    client->sendMsgToServer("reg&" + log + "&" + pass + "&" + email);
}

void FunctionsForClient::msgHandler(QString msg)
{
    if (msg == "auth\n" || msg == "reg\n")
    {
        delete ui_auth;
        ui_main = new MainWindow;
        ui_main->show();
        connect(ui_main, &MainWindow::Task1, this, &FunctionsForClient::sendTask1);
        connect(ui_main, &MainWindow::Task2, this, &FunctionsForClient::sendTask2);
        connect(ui_main, &MainWindow::Task3, this, &FunctionsForClient::sendTask3);
        connect(ui_main, &MainWindow::Task4, this, &FunctionsForClient::sendTask4);
        connect(ui_main, &MainWindow::Stat, this, &FunctionsForClient::sendStat);


        connect(this, &FunctionsForClient::solution, ui_main, &MainWindow::solution);
    }
    else
    {
        emit solution(msg);
    }

}

void FunctionsForClient::sendTask1(QString text)
{
    client->sendMsgToServer("task1&" + this->login + "&" + text);
}

void FunctionsForClient::sendTask2(QString text)
{
    client->sendMsgToServer("task2&" + this->login + "&"  + text);
}

void FunctionsForClient::sendTask3(QString func, QString left, QString right, QString epsilon, QString maxIter)
{
    client->sendMsgToServer("task3&" + this->login + "&"  + func + "&" + left + "&" + right + "&" + epsilon + "&" + maxIter);
}

void FunctionsForClient::sendTask4(QString text)
{
    client->sendMsgToServer("task4&" + this->login + "&" + text);
}

void FunctionsForClient::sendStat()
{
    client->sendMsgToServer("stat&" + this->login);
}

