#ifndef USER_H
#define USER_H

#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtGui/QImage>

struct UserInfo {
    QString userId;
    QString name;
    QImage avator;
    int age;
    QString department;
    QString course;
    QString section;
    QString homeDirURL;
};

UserInfo MakeUserInfo(QString name, QImage avator, int age, QString department, QString course, QString section, QString homeDirURL);


enum UserInfoKey { Name, Avator, Age, Department, Course, Section, HomeDirURL };


class User {
    public:
        User(QString userId, UserInfo info);
        
        const static QImage defaultAvator;

        QString userId();

        QString name();
        QImage avator();
        int age();
        QString department();
        QString course();
        QString section();
        QString homeDirURL();
    
        QString old_name();
        QImage old_avator();
        int old_age();
        QString old_department();
        QString old_course();
        QString old_section();
        QString old_homeDirURL();
    
        bool isInfoModified();
    
        void infoChanged(UserInfoKey key, QVariant newValue);
        void submit();
    
    private:
        UserInfo info;
        UserInfo tempInfo;
        bool isModified = false;
};

#endif // USER_H
