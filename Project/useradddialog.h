#ifndef USERADDDIALOG_H
#define USERADDDIALOG_H

#include <QDialog>
#include "user.h"
#include <QLineEdit>
#include <QSpinBox>

namespace Ui { class UserAddDialog; }

class UserAddDialog : public QDialog {
    Q_OBJECT

    public:
        explicit UserAddDialog(QWidget * parent = nullptr);
        ~UserAddDialog();

    private:
        Ui::UserAddDialog * ui;
        User * user;

        QLineEdit * nameField;
        QSpinBox * ageField;
        QLineEdit * departmentField;
        QLineEdit * courseField;
        QLineEdit * sectionField;

        void initialize();

    signals:
        void shouldAddNewUser(User * newUser);

    private slots:
        void on_nameField_textEdited(const QString &arg1);
        void on_ageField_valueChanged(int arg1);
        void on_departmentField_textEdited(const QString &arg1);
        void on_courseField_textEdited(const QString &arg1);
        void on_sectionField_textEdited(const QString &arg1);
        void on_addButton_clicked();
        void on_cancelButton_clicked();
};

#endif // USERADDDIALOG_H
