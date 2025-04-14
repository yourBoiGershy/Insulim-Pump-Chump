// datastorage.h
#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QVariantList>

class DataStorage {
public:
    DataStorage();
    ~DataStorage();

    void initializeDB();
    void saveProfile(QString name, double basal, double correctionFactor, double carbRatio, double targetBG);
    void logEvent(QString type, QString details);

private:
    QSqlDatabase db;
    void createTables();
};

#endif
