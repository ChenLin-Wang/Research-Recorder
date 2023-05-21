#ifndef USERDATACONTROLLER_H
#define USERDATACONTROLLER_H
#include <QSqlDatabase>
#include <QObject>
#include "user.h"
#include "shareddefines.h"

class UserDataController: public QObject {

    Q_OBJECT

    public:
        UserDataController();
        void connect();
        QList<User *> fetchAllUsers();
        QString insertUser(User * user);        // <- return new user's id as qstring
        void updateUser(User * user);

    private:
        QSqlDatabase db;

        void executeSqlFile(const QString& filePath);
        bool isDbInitialized();

    signals:
        void result(ResultType resultType, QString message);
};

#endif // USERDATACONTROLLER_H
