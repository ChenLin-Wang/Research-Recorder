#include "user.h"

UserInfo MakeUserInfo(QString name, QImage avator, int age, QString department, QString course, QString section, QString homeDirURL) {
    UserInfo info;
    info.name = name;
    info.avator = avator;
    info.age = age;
    info.department = department;
    info.course = course;
    info.section = section;
    info.homeDirURL = homeDirURL;
    return info;
}

User::User(QString userId, UserInfo info): info(info), tempInfo(info) { this->info.userId = userId; }

const QImage User::defaultAvator = QImage(":/images/user.jpeg");

QString     User::name()            {  if (isModified) return tempInfo.name;        else return info.name;          }
QImage      User::avator()          {  if (isModified) return tempInfo.avator;      else return info.avator;        }
int         User::age()             {  if (isModified) return tempInfo.age;         else return info.age;           }
QString     User::department()      {  if (isModified) return tempInfo.department;  else return info.department;    }
QString     User::course()          {  if (isModified) return tempInfo.course;      else return info.course;        }
QString     User::section()         {  if (isModified) return tempInfo.section;     else return info.section;       }
QString     User::homeDirURL()      {  if (isModified) return tempInfo.homeDirURL;  else return info.homeDirURL;    }

QString     User::old_name()        {  return info.name;        }
QImage      User::old_avator()      {  return info.avator;      }
int         User::old_age()         {  return info.age;         }
QString     User::old_department()  {  return info.department;  }
QString     User::old_course()      {  return info.course;      }
QString     User::old_section()     {  return info.section;     }
QString     User::old_homeDirURL()  {  return info.homeDirURL;  }

QString     User::userId()          {  return info.userId;      }

bool            User::isInfoModified()  {  return isModified;  }

void User::infoChanged(UserInfoKey key, QVariant newValue) {
    switch (key) {
        case Name:          if (tempInfo.name == newValue.value<QString>()) return;         else tempInfo.name = newValue.value<QString>();         break;
        case Avator:        if (tempInfo.avator == newValue.value<QImage>()) return;        else tempInfo.avator = newValue.value<QImage>();        break;
        case Age:           if (tempInfo.age == newValue.value<int>()) return;              else tempInfo.age = newValue.value<int>();              break;
        case Department:    if (tempInfo.department == newValue.value<QString>()) return;   else tempInfo.department = newValue.value<QString>();   break;
        case Course:        if (tempInfo.course == newValue.value<QString>()) return;       else tempInfo.course = newValue.value<QString>();       break;
        case Section:       if (tempInfo.section == newValue.value<QString>()) return;      else tempInfo.section = newValue.value<QString>();      break;
        case HomeDirURL:    if (tempInfo.homeDirURL == newValue.value<QString>()) return;   else tempInfo.homeDirURL = newValue.value<QString>();   break;
    }
    if (!isModified) isModified = true;
}

void User::submit() {
    if (!isModified) return;
    info = tempInfo;
}
