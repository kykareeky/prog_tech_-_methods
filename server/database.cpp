#include "database.h"

DataBase* DataBase::p_instance = nullptr;
DatabaseDestroyer DataBase::destroyer;

DataBase::DataBase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Database.db");
    if (!db.open()) {
        qDebug() << "Error: failed to open database";
    }
}

bool DataBase::createTable(){
    QSqlQuery query(db);
    return query.exec("create table users(id integer primary key not null, "
                      "login text not null unique, password text not null, email text not null unique, "
                      "stat integer default 0, sockid integer not null);");
}

DataBase::~DataBase(){
    db.close();
}

DataBase& DataBase::getInstance(){
    if(!p_instance){
        p_instance = new DataBase();
        p_instance->createTable();
    }
    return *p_instance;
}

QSqlDatabase& DataBase::getDatabase(){
    return db;
}

DatabaseDestroyer::~DatabaseDestroyer() {
    delete p_instance;
}

void DatabaseDestroyer::initialize(DataBase *p) {
    p_instance = p;
}

QStringList DataBase::queryToDatabase(QStringList src){
    QSqlQuery query(db);
    query.prepare(src[0]);
    int i = 1;
    while(i < src.size())
    {
        query.bindValue(src[i], src[i+1]);
        i+=2;
    }

    QStringList res;
    if(src[0].contains("SELECT")){
        // qDebug() << query.exec();
        // qDebug() << query.first();
        if(query.exec() && query.first()){
            res.append("found");
            return res;
        }
    }
    else{
        if(query.exec()){
            res.append("ok");
            return res;
        }
    }
    return res;
}
