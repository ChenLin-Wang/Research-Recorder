#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QList>
#include <QTableWidget>
#include <QTreeWidget>
#include <QFileDialog>
#include "user.h"
#include "filecontroller.h"
#include "cmyfiledialog.h"

namespace Ui { class FileBrowser; }

class FileBrowser : public QWidget {
    Q_OBJECT

    public:
        explicit FileBrowser(QWidget * parent = nullptr);
        ~FileBrowser();

        QList<User *> users();
        FileController * fileController;
        User * curSelectedUser();

        void refresh(QList<User *> users);
        void refreshItemsTree();
        void addDataFilesUsingPath(QList<QString> paths);

    private:
        Ui::FileBrowser * ui;

        QTableWidget * userTableView;
        QTreeWidget * itemsTreeView;
        CMyFileDialog * fileDialog = new CMyFileDialog;

        QList<User *> curUsers;
        User * curClickedUser;
        QString curFolder;

        void prepareUserTable();
        void prepareItemsTree();
        void refreshUserTable();

        QTreeWidgetItem * createTree(const QList<QVariant>& nodeList);

    private slots:
        void on_userTableView_cellClicked(int row, int column);
        void on_userTableView_cellDoubleClicked(int row, int column);
        void on_itemsTreeView_itemDoubleClicked(QTreeWidgetItem *item, int column);
        void on_itemsTreeView_itemClicked(QTreeWidgetItem *item, int column);

    signals:
        void shouldShowDetails(User * user);
};

#endif // FILEBROWSER_H
