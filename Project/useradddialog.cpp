#include "useradddialog.h"
#include "ui_useradddialog.h"

UserAddDialog::UserAddDialog(QWidget *parent) : QDialog(parent), ui(new Ui::UserAddDialog) {
    ui->setupUi(this);

    nameField = findChild<QLineEdit *>("nameField");
    ageField = findChild<QSpinBox *>("ageField");
    departmentField = findChild<QLineEdit *>("departmentField");
    courseField = findChild<QLineEdit *>("courseField");
    sectionField = findChild<QLineEdit *>("sectionField");

    initialize();
}

UserAddDialog::~UserAddDialog() { delete ui; }

void UserAddDialog::initialize() {
    nameField->setText("");
    ageField->setValue(0);
    departmentField->setText("");
    courseField->setText("");
    sectionField->setText("");
    
    user = new User("-1", MakeUserInfo("", User::defaultAvator, 0, "", "", "", ""));
}

void UserAddDialog::on_nameField_textEdited(const QString &arg1)        { user->infoChanged(Name, QVariant(arg1));          }
void UserAddDialog::on_ageField_valueChanged(int arg1)                  { user->infoChanged(Age, QVariant(arg1));           }
void UserAddDialog::on_departmentField_textEdited(const QString &arg1)  { user->infoChanged(Department, QVariant(arg1));    }
void UserAddDialog::on_courseField_textEdited(const QString &arg1)      { user->infoChanged(Course, QVariant(arg1));        }
void UserAddDialog::on_sectionField_textEdited(const QString &arg1)     { user->infoChanged(Section, QVariant(arg1));       }

void UserAddDialog::on_addButton_clicked() { user->submit(); emit shouldAddNewUser(user); initialize(); close(); }

void UserAddDialog::on_cancelButton_clicked() { initialize(); close(); }

