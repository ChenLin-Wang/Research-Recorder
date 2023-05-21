#include "userdatacontroller.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QDateTime>
#include <QImage>

UserDataController::UserDataController() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("index.db");
}

void UserDataController::connect() {
    if (db.open()) emit result(Normal, "database open successfully");
    else { emit result(Error, "database open failure"); return; }

    bool result = isDbInitialized();
    if (result) return;

    executeSqlFile(":/other/sql.sql");
}

QList<User *> UserDataController::fetchAllUsers() {

    QSqlQuery sqlQuery;
    QList<User *> queryRes;

    if (!sqlQuery.exec("select * from users order by \"name\"")) { emit result(Error, "Failed to execute SQL query: " + sqlQuery.lastError().text()); return queryRes; }

    while (sqlQuery.next()) {
        QString id = sqlQuery.value(0).toString();
        QString name = sqlQuery.value(1).toString();
        QImage avator = User::defaultAvator;                // <- all users are used default avator yet.
        int age = sqlQuery.value(3).toInt();
        QString department = sqlQuery.value(4).toString();
        QString course = sqlQuery.value(5).toString();
        QString section = sqlQuery.value(6).toString();
        QString homeDirURL = sqlQuery.value(7).toString();

        User * newUser = new User(id, MakeUserInfo(name, avator, age, department, course, section, homeDirURL));
        queryRes.append(newUser);
    }

    emit result(Normal, "Fetch users successed from database");
    return queryRes;

}

QString UserDataController::insertUser(User * user) {
    QSqlQuery sqlQuery;
    QString curId = QString::number(QDateTime::currentMSecsSinceEpoch());
    QString insertStr = QString("insert into users values ('%1', '%2', 'default', %3, '%4', '%5', '%6', '%7');")
        .arg(curId)
        .arg(user->name())
        .arg(user->age())
        .arg(user->department())
        .arg(user->course())
        .arg(user->section())
        .arg(user->homeDirURL());

    if (!sqlQuery.exec(insertStr)) { emit result(Error, "Failed when insert user data to database: " + sqlQuery.lastError().text()); return ""; }
    return curId;
}

void UserDataController::updateUser(User * user) {
    QSqlQuery sqlQuery;
    QString updateStr = QString("UPDATE users SET \"name\" = '%1', \"avator\" = 'default', \"age\" = %2, \"department\" = '%3', \"course\" = '%4', \"section\" = '%5', \"home_dir_url\" = '%6' WHERE \"id\" = '%7';")
        .arg(user->name())
        .arg(user->age())
        .arg(user->department())
        .arg(user->course())
        .arg(user->old_section())
        .arg(user->homeDirURL())
        .arg(user->userId());

    if (!sqlQuery.exec(updateStr)) emit result(Error, "Failed when update user data in database: " + sqlQuery.lastError().text());
}



// execute .sql file to initialize database file
void UserDataController::executeSqlFile(const QString& filePath) {
    // create database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) { emit result(Error, "Database is not open"); return; }

    // Open .sql file
    QFile sqlFile(filePath);
    if (!sqlFile.open(QIODevice::ReadOnly | QIODevice::Text)) { emit result(Error, "Failed to open .sql file"); return; }

    // read SQL statements and execute
    QTextStream in(&sqlFile);
    while (!in.atEnd()) {
        QString queryText = in.readLine().trimmed();

        // ignore empty line and comments
        if (queryText.isEmpty() || queryText.startsWith("--")) continue;

        QSqlQuery query(db);
        if (!query.exec(queryText)) { emit result(Error, "Failed to execute SQL query: " + query.lastError().text()); return; }
    }

    sqlFile.close();
    emit result(Normal, "database initial successfully");
}

bool UserDataController::isDbInitialized() {
    QSqlQuery sqlQuery;

    sqlQuery.exec("select name from sqlite_master where type='table' order by name");
    if(!sqlQuery.exec()) emit result(Error, "Fail to query table. " + sqlQuery.lastError().text());
    else return sqlQuery.next();

    return false;
}
