#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "useradddialog.h"
#include "usereditdialog.h"
#include "userdatacontroller.h"

#include <QMainWindow>
#include <QLabel>
#include "filebrowser.h"
#include "filecontroller.h"
#include <QFileDialog>
#include "cmyfiledialog.h"
#include <QTextEdit>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget * parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow * ui;

        QTextEdit * logView;
        FileBrowser * fileBrowser;
        FileController * fileController = new FileController();
        UserAddDialog * userAddDialog = new UserAddDialog;
        CMyFileDialog * fileDialog = new CMyFileDialog();
        UserEditDialog * userEditDialog = new UserEditDialog;

        UserDataController * userDC = new UserDataController();
        bool isFailured = false;

        void prepare();

    private slots:
        void stateShouldChange(ResultType resultType, QString message);
        void shouldAddUser(User * user);
        void shouldShowDetails(User * user);
        void shouldUpdateUser(User * user);
        void shouldRefreshTreeFiles();

        void on_userAddButton_clicked();
        void on_saveFileButton_clicked();
        void on_refreshUserButton_clicked();
        void on_refreshFileButton_clicked();
};
#endif // MAINWINDOW_H
