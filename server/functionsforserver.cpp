#include "functionsforserver.h"
#include "database.h"
#include "aes.h"
#include "sha512.h"
#include "dijkstra.h"
#include "dichotomymethod.h"

// Контекст текущего запроса (уникален для каждого потока)
static thread_local QString contextLogin;

QByteArray parsing(QString data_from_client)
{
    data_from_client = data_from_client.trimmed();
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));

    if (data_from_client_list.isEmpty()) {
        return "Error: Empty request\n";
    }

    QString nameOfFunc = data_from_client_list.front();
    data_from_client_list.pop_front();

    if (nameOfFunc == "auth") {
        if (data_from_client_list.size() < 1)
            return "Error: Not enough parameters for auth\n";
        return auth(data_from_client_list.at(0), data_from_client_list.at(1));
    } else if (nameOfFunc == "reg") {
        if (data_from_client_list.size() < 2)
            return "Error: Not enough parameters for reg\n";
        return reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2));
    } else if (nameOfFunc == "task1") {
        if (data_from_client_list.size() < 2)
            return "Error: Not enough parameters for task1\n";
        contextLogin = data_from_client_list.at(0);
        return task1(data_from_client_list.at(1));
    } else if (nameOfFunc == "task2") {
        if (data_from_client_list.size() < 2)
            return "Error: Not enough parameters for task2\n";
        contextLogin = data_from_client_list.at(0);
        return task2(data_from_client_list.at(1));
    } else if (nameOfFunc == "task3") {
        if (data_from_client_list.size() < 6)
            return "Error: Not enough parameters for task3\n";
        contextLogin = data_from_client_list.at(0);
        return task3(data_from_client_list.at(1), data_from_client_list.at(2),
                     data_from_client_list.at(3), data_from_client_list.at(4), data_from_client_list.at(5));
    } else if (nameOfFunc == "task4") {
        if (data_from_client_list.size() < 2)
            return "Error: Not enough parameters for task4\n";
        contextLogin = data_from_client_list.at(0);
        //qDebug() << data_from_client_list.at(1);
        return task4(data_from_client_list.at(1));
    } else if (nameOfFunc == "stat") {
        if (data_from_client_list.size() < 1)
            return "Error: Not enough parameters for stat\n";
        contextLogin = data_from_client_list.at(0);
        return stat();
    } else if (nameOfFunc == "check") {
        if (data_from_client_list.size() < 3)
            return "Error: Not enough parameters for check\n";
        return check(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2));
    } else {
        return "Error during parsing: Unknown command\n";
    }
}
QByteArray auth(QString log, QString pass)
{
    if (log.trimmed().isEmpty() || pass.trimmed().isEmpty()) {
        return "Error: Login and password must not be empty\n";
    }

    DataBase& dbInstance = DataBase::getInstance();
    QStringList selectQuery;
    selectQuery << "SELECT * FROM users WHERE login = :login AND password = :password"
                << ":login" << log
                << ":password" << pass;

    QSqlQuery query(dbInstance.getDatabase());
    query.prepare(selectQuery[0]);
    query.bindValue(selectQuery[1], selectQuery[2]);
    query.bindValue(selectQuery[3], selectQuery[4]);

    if (query.exec() && query.first()) {
        return "auth\n";
    } else {
        return "Error: Authentication failed\n";
    }
}

QByteArray reg(QString log, QString pass, QString mail)
{
    if (log.trimmed().isEmpty() || pass.trimmed().isEmpty() || mail.trimmed().isEmpty()) {
        return "Error: Login, mail and password must not be empty\n";
    }
    DataBase& dbInstance = DataBase::getInstance();
    QStringList insertQuery;
    insertQuery << "INSERT INTO users (login, password, email) VALUES (:login, :password, :email)"
                << ":login" << log
                << ":password" << pass
                << ":email" << mail;

    QSqlQuery query(dbInstance.getDatabase());
    query.prepare(insertQuery[0]);
    query.bindValue(insertQuery[1], insertQuery[2]);
    query.bindValue(insertQuery[3], insertQuery[4]);
    query.bindValue(insertQuery[5], insertQuery[6]);

    if (query.exec()) {
        return "reg\n";
    } else {
        return "Error: Registration failed\n";
    }
}

void incrementStat()
{
    if (contextLogin.isEmpty()) return;
    DataBase& dbInstance = DataBase::getInstance();
    QSqlQuery query(dbInstance.getDatabase());
    query.prepare("UPDATE users SET stat = stat + 1 WHERE login = :login");
    query.bindValue(":login", contextLogin);
    query.exec();
}

QByteArray zwspProc(QByteArray unformattedText) {
    qDebug() << unformattedText;
    QString str = QString::fromUtf8(unformattedText);
    QString result;
    QString zwsp = QChar(0x200B);
    for (int i = 0; i < str.size(); ++i) {
        result += str[i];
        if (i != str.size() - 1) result += zwsp;
        }
    return result.toUtf8();
}

// QByteArray task1(const QString &text)
// {
//     incrementStat();
//     std::string key = "0123456789abcdef"; // Example key
//     AES aes(key);
//     std::string encryptedText = aes.encrypt(text.toStdString());
//     //return zwspProc(QByteArray::fromStdString(encryptedText));
//     return QByteArray::fromStdString(encryptedText);
// }

QByteArray task1(const QString &text)
{
    incrementStat();

    std::string key = "0123456789abcdef"; // 16 символов = 128 бит
    AES aes(key);

    std::string encryptedBase64 = aes.encrypt(text.toStdString());
    std::string decryptedText = aes.decrypt(encryptedBase64);

    qDebug() << "Encrypted Base64:" << QString::fromStdString(encryptedBase64);
    qDebug() << "Decrypted:" << QString::fromStdString(decryptedText);

    return QByteArray::fromStdString(encryptedBase64);
}

QByteArray task2(QString text)
{
    incrementStat();
    unsigned char digest[SHA512::DIGEST_SIZE];
    memset(digest, 0, SHA512::DIGEST_SIZE);
    SHA512 ctx = SHA512();
    ctx.init();
    ctx.update((unsigned char*)text.toUtf8().constData(), text.length());
    ctx.final(digest);

    char buf[2*SHA512::DIGEST_SIZE+1];
    buf[2*SHA512::DIGEST_SIZE] = 0;
    for (int i = 0; i < SHA512::DIGEST_SIZE; i++)
        sprintf(buf+i*2, "%02x", digest[i]);
    return zwspProc(QByteArray(buf));
}


QByteArray task3(QString func, QString left, QString right, QString epsilon, QString maxIter)
{
    incrementStat();
    if (func.trimmed().isEmpty() || left.trimmed().isEmpty() || right.trimmed().isEmpty() ||
        epsilon.trimmed().isEmpty() || maxIter.trimmed().isEmpty()) {
        return "Error: One or more input fields are empty.\n";
    }
    double left_val = left.toDouble();
    double right_val = right.toDouble();
    double epsilon_val = epsilon.toDouble();
    int maxIter_val = maxIter.toInt();

    try {
        DichotomyMethod bisecMethod(func, left_val, right_val, epsilon_val, maxIter_val);
        double result = bisecMethod.solve();
        return "The value of root is : " + QByteArray::number(result);
    } catch (const std::runtime_error &e) {
        return QByteArray("Error: ") + e.what() + "\n";
    }
}

QByteArray task4(QString text)
{
    incrementStat();
    QStringList parts = text.split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 2)
        return "error";

    int start = parts[0].toInt();
    int end = parts[1].toInt();
    QStringList edges = parts.mid(2);

    Graph g;
    for (const QString& e : edges) {
        // Разделяем сначала по '=' (если есть вес)
        QStringList edgeAndWeight = e.split('=');
        QString edgePart = edgeAndWeight[0];
        int weight = 1; // по умолчанию вес 1

        if (edgeAndWeight.size() == 2) {
            bool ok = false;
            int parsedWeight = edgeAndWeight[1].toInt(&ok);
            if (ok) {
                weight = parsedWeight;
            }
        }

        QStringList nodes = edgePart.split('*');
        if (nodes.size() != 2) continue;

        bool okFrom = false, okTo = false;
        int from = nodes[0].toInt(&okFrom);
        int to = nodes[1].toInt(&okTo);

        if (okFrom && okTo) {
            g.addEdge(from, to, weight);
        }
    }

    QString resultPath = g.dijkstra(start, end);
    return resultPath.toUtf8();
}


QByteArray stat()
{
    DataBase& dbInstance = DataBase::getInstance();
    QSqlQuery query(dbInstance.getDatabase());
    query.prepare("SELECT stat FROM users WHERE login = :login");
    query.bindValue(":login", contextLogin);

    if (query.exec() && query.first()) {
        int statValue = query.value(0).toInt();
        return "Stat for " + contextLogin.toUtf8() + ": " + QByteArray::number(statValue) + " requests\n";
    } else {
        return "Error: Could not retrieve stat\n";
    }
}

QByteArray check(QString task, QString var, QString ans)
{
    return "check\n";
}
