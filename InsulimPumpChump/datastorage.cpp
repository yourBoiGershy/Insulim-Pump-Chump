// datastorage.cpp
#include "datastorage.h"

DataStorage::DataStorage() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("insulinPump.db");
}

DataStorage::~DataStorage() {
    db.close();
}

void DataStorage::initializeDB() {
    if(db.open()) {
        createTables();
    }
}

void DataStorage::createTables() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Profiles(id INTEGER PRIMARY KEY, name TEXT, basal REAL, correctionFactor REAL, carbRatio REAL, targetBG REAL)");
    query.exec("CREATE TABLE IF NOT EXISTS Logs(id INTEGER PRIMARY KEY, type TEXT, details TEXT, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");
}

void DataStorage::saveProfile(QString name, double basal, double correctionFactor, double carbRatio, double targetBG) {
    QSqlQuery query;
    query.prepare("INSERT INTO Profiles(name, basal, correctionFactor, carbRatio, targetBG) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(basal);
    query.addBindValue(correctionFactor);
    query.addBindValue(carbRatio);
    query.addBindValue(targetBG);
    query.exec();
}

void DataStorage::logEvent(QString type, QString details) {
    QSqlQuery query;
    query.prepare("INSERT INTO Logs(type, details) VALUES (?, ?)");
    query.addBindValue(type);
    query.addBindValue(details);
    query.exec();
}