#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>

void appendLogMessage(QTextEdit * logView, const QString& message, const QColor& color);

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
    logView = findChild<QTextEdit *>("logView");
    fileBrowser = findChild<FileBrowser *>("fileBrowser");
    fileBrowser->fileController = fileController;
    prepare();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::prepare() {
    QObject::connect(userDC, &UserDataController::result, this, &MainWindow::stateShouldChange);
    QObject::connect(userAddDialog, &UserAddDialog::shouldAddNewUser, this, &MainWindow::shouldAddUser);
    QObject::connect(fileBrowser, &FileBrowser::shouldShowDetails, this, &MainWindow::shouldShowDetails);
    QObject::connect(userEditDialog, &UserEditDialog::shouldUpdateUser, this, &MainWindow::shouldUpdateUser);
    QObject::connect(fileController, &FileController::newLog, this, &MainWindow::stateShouldChange);
    QObject::connect(fileController, &FileController::copyFinished, this, &MainWindow::shouldRefreshTreeFiles);
    fileController->checkHomeDir();
    userDC->connect();
    QList<User *> users = userDC->fetchAllUsers();
    fileBrowser->refresh(users);


    fileDialog->setOption(QFileDialog::DontUseNativeDialog,true);
    QListView *listView = fileDialog->findChild<QListView*>("listView");
    if (listView) listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QTreeView *treeView = fileDialog->findChild<QTreeView*>();
    if (treeView) treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QDialogButtonBox *button = fileDialog->findChild<QDialogButtonBox *>("buttonBox");
    disconnect(button,SIGNAL(accepted()),fileDialog,SLOT(accept()));//使链接失效
    connect(button,SIGNAL(accepted()),fileDialog,SLOT(slot_myAccetp()));//改成自己的槽
}


void MainWindow::shouldRefreshTreeFiles() {
    fileBrowser->refreshItemsTree();
}

void MainWindow::stateShouldChange(ResultType resultType, QString message) {
    appendLogMessage(logView, message, resultType == Normal ? Qt::blue : Qt::red);
}

void MainWindow::shouldAddUser(User * user) {
    QString id = userDC->insertUser(user);
    fileController->createSubDir(id);
    QList<User *> users = userDC->fetchAllUsers();
    fileBrowser->refresh(users);
}

void MainWindow::shouldUpdateUser(User * user) {
    userDC->updateUser(user);
    QList<User *> users = userDC->fetchAllUsers();
    fileBrowser->refresh(users);
}

void MainWindow::shouldShowDetails(User * user) {
    userEditDialog->startEdit(user);
    userEditDialog->show();
}

void MainWindow::on_userAddButton_clicked() { userAddDialog->show(); }

void MainWindow::on_saveFileButton_clicked() {
    if (!fileBrowser->curSelectedUser()) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Warning");
        messageBox.setText("You can't save file, because you are not selected a user yet.");
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.exec();
        return;
    }
    if (!fileDialog->exec()) return;
    QList<QString> selectedFiles = fileDialog->selectedFiles();
    fileBrowser->addDataFilesUsingPath(selectedFiles);
}

void MainWindow::on_refreshUserButton_clicked() {
    QList<User *> users = userDC->fetchAllUsers();
    fileBrowser->refresh(users);
}

void MainWindow::on_refreshFileButton_clicked() { fileBrowser->refreshItemsTree(); }



void appendLogMessage(QTextEdit * logView, const QString& message, const QColor& color) {
    QTextCursor cursor(logView->document());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat format;
    format.setForeground(color); // 设置前景色
    cursor.insertBlock();
    cursor.insertText(message, format);
    QScrollBar * verticalScrollBar = logView->verticalScrollBar();
    verticalScrollBar->setValue(verticalScrollBar->maximum());
}
