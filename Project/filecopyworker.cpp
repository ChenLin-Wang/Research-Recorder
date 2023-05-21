#include "filecopyworker.h"

void FileCopyWorker::copyFiles(QString destinationFolder, QList<QString> filesNeedCopy) {
    copy(destinationFolder, filesNeedCopy);
    emit fileCopyFinished();
}

void FileCopyWorker::copy(QString destinationFolder, QList<QString> filesNeedCopy) {
    // traversal files
    foreach (const QString& filePath, filesNeedCopy) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QString destinationPath = QDir(destinationFolder).filePath(fileName);

        if (fileInfo.isDir()) {
            // if it is folder, copy the contents of folder
            QDir().mkpath(destinationPath);             // create destination folder
            QDir sourceDir(filePath);
            QStringList subItems = sourceDir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
            QList<QString> subItemsList;
            foreach (const QString& subItem, subItems) {
                subItemsList.append(sourceDir.filePath(subItem));
            }
            // 递归调用拷贝文件方法
            copy(destinationPath, subItemsList);
        } else {
            // if it is files, just copy it to destination folder
            if (QFile::copy(filePath, destinationPath)) {
                emit newLog(Normal, "Copy file success: " + filePath + "->" + destinationPath);
            } else {
                emit newLog(Error, "Copy file failed: " + filePath);
            }
        }
    }
}
