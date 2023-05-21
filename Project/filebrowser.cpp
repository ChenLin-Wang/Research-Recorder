#include "filebrowser.h"
#include "ui_filebrowser.h"
#include <QFileInfo>
#include <QRegularExpression>
#include <QFileIconProvider>
#include <QDesktopServices>

QList<User *> FileBrowser::users() { return curUsers; }

FileBrowser::FileBrowser(QWidget * parent) : QWidget(parent), ui(new Ui::FileBrowser) {
    ui->setupUi(this);
    userTableView = findChild<QTableWidget *>("userTableView");
    itemsTreeView = findChild<QTreeWidget *>("itemsTreeView");

    fileDialog->setOption(QFileDialog::DontUseNativeDialog,true);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setWindowTitle("choose where you want save:");

    prepareUserTable();
    prepareItemsTree();
}

FileBrowser::~FileBrowser() { delete ui; }

void FileBrowser::prepareUserTable() {
    userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    userTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    userTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    userTableView->setColumnWidth(0, 20);
    userTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    userTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    for (int i = 2; i < 6; i++) {
        userTableView->setColumnWidth(i, 70);
    }
    userTableView->setShowGrid(true);
}

void FileBrowser::prepareItemsTree() {
    itemsTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    itemsTreeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    itemsTreeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    for (int i = 1; i < 5; i++) {
        itemsTreeView->header()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    itemsTreeView->header()->setStretchLastSection(false);
}

void FileBrowser::addDataFilesUsingPath(QList<QString> paths) { fileController->copyFilesToFolder(curFolder, paths); }

User * FileBrowser::curSelectedUser() { return curClickedUser; }



QString formatFileSize(qint64 bytes);

void FileBrowser::refresh(QList<User *> users) {
    curUsers = users;
    refreshUserTable();
    itemsTreeView->clear();
}

void FileBrowser::refreshUserTable() {

    userTableView->clearContents();

    userTableView->setRowCount(curUsers.count());
    int i = 0;
    for (User * curUser : curUsers) {
        QTableWidgetItem * iconItem = new QTableWidgetItem();
        iconItem->setIcon(QIcon(QPixmap::fromImage(curUser->avator())));
        userTableView->setItem(i, 0, iconItem);
        userTableView->setItem(i, 1, new QTableWidgetItem(curUser->name()));
        userTableView->setItem(i, 2, new QTableWidgetItem(QString::number(curUser->age())));
        userTableView->setItem(i, 3, new QTableWidgetItem(curUser->department()));
        userTableView->setItem(i, 4, new QTableWidgetItem(curUser->course()));
        userTableView->setItem(i, 5, new QTableWidgetItem(curUser->section()));
        i ++;
    }

}

void FileBrowser::refreshItemsTree() {
    itemsTreeView->clear();
    if (!curClickedUser) return;
    QList<QVariant> subFiles = fileController->fetchAllFilesAtSubDir(curClickedUser->userId());
    QTreeWidgetItem * rootItem = createTree(subFiles);
    for (QTreeWidgetItem * curChild : rootItem->takeChildren()) itemsTreeView->addTopLevelItem(curChild);
}

QTreeWidgetItem * FileBrowser::createTree(const QList<QVariant>& nodeList) {
    QTreeWidgetItem * rootItem = new QTreeWidgetItem();

    QFileIconProvider iconProvider;

    foreach (const QVariant& nodeVariant, nodeList) {
        if (nodeVariant.canConvert<QList<QVariant>>()) {
            QList<QVariant> subDirInfos = nodeVariant.value<QList<QVariant>>();
            QFileInfo subDirInfo = subDirInfos[0].value<QFileInfo>();
            QList<QVariant> subNodeList = subDirInfos[1].value<QList<QVariant>>();
            QTreeWidgetItem * item = createTree(subNodeList);
            item->setText(0, subDirInfo.fileName());
            item->setIcon(0, iconProvider.icon(subDirInfo));
            item->setText(2, "FOLDER");
            item->setText(3, subDirInfo.lastModified().toString());
            item->setText(4, subDirInfo.birthTime().toString());
            item->setData(0, Qt::UserRole, QVariant::fromValue(subDirInfo));
            rootItem->addChild(item);
        } else if (nodeVariant.canConvert<QFileInfo>()) {
            QFileInfo fileInfo = nodeVariant.value<QFileInfo>();
            QTreeWidgetItem * item = new QTreeWidgetItem(rootItem);
            item->setText(0, fileInfo.fileName());
            item->setIcon(0, iconProvider.icon(fileInfo));
            item->setText(1, formatFileSize(fileInfo.size()));
            item->setText(2, fileInfo.suffix().toUpper());
            item->setText(3, fileInfo.lastModified().toString());
            item->setText(4, fileInfo.birthTime().toString());
            item->setData(0, Qt::UserRole, QVariant::fromValue(fileInfo));
            rootItem->addChild(item);
        }
    }
    return rootItem;
}


QString formatFileSize(qint64 bytes) {
    QString sizeString;

    if (bytes < 1024) {
        // Less than 1 KB
        sizeString = QString("%1 bytes").arg(bytes);
    } else if (bytes < 1024 * 1024) {
        // Between 1 KB and 1 MB
        double kilobytes = bytes / 1024.0;
        QString kilobytesString = QString::number(kilobytes, 'f', kilobytes < 10.0 ? 2 : 1);
        sizeString = QString("%1 KB").arg(kilobytesString.remove(QRegularExpression("\\.0+$")));
    } else if (bytes < 1024 * 1024 * 1024) {
        // Between 1 MB and 1 GB
        double megabytes = bytes / (1024.0 * 1024.0);
        QString megabytesString = QString::number(megabytes, 'f', megabytes < 10.0 ? 2 : 1);
        sizeString = QString("%1 MB").arg(megabytesString.remove(QRegularExpression("\\.0+$")));
    } else {
        // Greater than or equal to 1 GB
        double gigabytes = bytes / (1024.0 * 1024.0 * 1024.0);
        QString gigabytesString = QString::number(gigabytes, 'f', gigabytes < 10.0 ? 2 : 1);
        sizeString = QString("%1 GB").arg(gigabytesString.remove(QRegularExpression("\\.0+$")));
    }

    return sizeString;
}



void FileBrowser::on_userTableView_cellClicked(int row, int column) {
    curClickedUser = curUsers[row];
    curFolder = FileController::documentsPath + "/" + curClickedUser->userId();
    refreshItemsTree();
}

void FileBrowser::on_userTableView_cellDoubleClicked(int row, int column) {
    emit shouldShowDetails(curUsers[row]);
}

void FileBrowser::on_itemsTreeView_itemClicked(QTreeWidgetItem * item, int column) {
    QFileInfo curFileInfo = item->data(0, Qt::UserRole).value<QFileInfo>();
    if (curFileInfo.isDir()) curFolder = curFileInfo.filePath();
    else curFolder = curFileInfo.dir().path();
}

void FileBrowser::on_itemsTreeView_itemDoubleClicked(QTreeWidgetItem * item, int column) {
    QFileInfo curFileInfo = item->data(0, Qt::UserRole).value<QFileInfo>();
    QUrl fileUrl = QUrl::fromLocalFile(curFileInfo.path());
    QDesktopServices::openUrl(fileUrl);
}


