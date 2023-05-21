#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H

#include <QDialog>
#include "user.h"
#include <QLineEdit>
#include <QSpinBox>

namespace Ui { class UserEditDialog; }

class UserEditDialog : public QDialog {
    Q_OBJECT

    public:
        explicit UserEditDialog(QWidget *parent = nullptr);
        ~UserEditDialog();

        void startEdit(User * user);

    private:
        Ui::UserEditDialog *ui;
        User * user;

        QLineEdit * nameField;
        QSpinBox * ageField;
        QLineEdit * departmentField;
        QLineEdit * courseField;
        QLineEdit * sectionField;

    signals:
        void shouldUpdateUser(User * newUser);

    private slots:
        void on_nameField_textEdited(const QString &arg1);
        void on_ageField_valueChanged(int arg1);
        void on_departmentField_textEdited(const QString &arg1);
        void on_courseField_textEdited(const QString &arg1);
        void on_sectionField_textEdited(const QString &arg1);
        void on_changeButton_clicked();
        void on_cancelButton_clicked();
};

#endif // USEREDITDIALOG_H
