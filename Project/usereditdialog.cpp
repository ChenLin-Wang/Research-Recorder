#include "usereditdialog.h"
#include "ui_usereditdialog.h"

UserEditDialog::UserEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::UserEditDialog) {
    ui->setupUi(this);

    nameField = findChild<QLineEdit *>("nameField");
    ageField = findChild<QSpinBox *>("ageField");
    departmentField = findChild<QLineEdit *>("departmentField");
    courseField = findChild<QLineEdit *>("courseField");
    sectionField = findChild<QLineEdit *>("sectionField");
}

UserEditDialog::~UserEditDialog() { delete ui; }

void UserEditDialog::startEdit(User * user) {
    this->user = user;
    nameField->setText(user->name());
    ageField->setValue(user->age());
    departmentField->setText(user->department());
    courseField->setText(user->course());
    sectionField->setText(user->section());
}

void UserEditDialog::on_nameField_textEdited(const QString &arg1)        { user->infoChanged(Name, QVariant(arg1));          }
void UserEditDialog::on_ageField_valueChanged(int arg1)                  { user->infoChanged(Age, QVariant(arg1));           }
void UserEditDialog::on_departmentField_textEdited(const QString &arg1)  { user->infoChanged(Department, QVariant(arg1));    }
void UserEditDialog::on_courseField_textEdited(const QString &arg1)      { user->infoChanged(Course, QVariant(arg1));        }
void UserEditDialog::on_sectionField_textEdited(const QString &arg1)     { user->infoChanged(Section, QVariant(arg1));       }

void UserEditDialog::on_changeButton_clicked() { emit shouldUpdateUser(user); close(); }

void UserEditDialog::on_cancelButton_clicked() { close(); }
