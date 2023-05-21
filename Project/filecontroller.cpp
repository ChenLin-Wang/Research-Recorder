#include "filecontroller.h"
#include <QStandardPaths>
#include <QDir>
#include <QThread>

const QString FileController::documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/RRC_Root";

QList<QVariant> traverseDirectory(const QString& rootDir);

FileController::FileController() {
    worker->moveToThread(thread);
    connect(this, &FileController::startCopyFile, worker, &FileCopyWorker::copyFiles);
    connect(worker, &FileCopyWorker::filepCopyFinished, this, &FileController::fileCopyDidFinish);
    connect(worker, &FileCopyWorker::newLog, this, &FileController::newLog);
}

void FileController::checkHomeDir() { createDirIfNotExists(FileController::documentsPath); }

void FileController::createSubDir(QString name) { createDirIfNotExists(FileController::documentsPath + "/" + name); }
void FileController::createDataDir(QString userHomeDirName, QString path) { createDirIfNotExists(FileController::documentsPath + "/" + userHomeDirName + path); }
QList<QVariant> FileController::fetchAllFilesAtSubDir(QString name) { return traverseDirectory(FileController::documentsPath + "/" + name); }

void FileController::copyFilesToFolder(QString folder, QList<QString> files) {
    thread->start();
    emit newLog(Normal, "Copy files to " + folder);
    emit startCopyFile(folder, files);
}

void FileController::fileCopyDidFinish() {
    emit copyFinished();
    emit newLog(Normal, "File copy finished.");
}




void FileController::createDirIfNotExists(QString path) {
    QDir customFolder(path);

    // check custom folder if exists
    if (!customFolder.exists()) {
        // if not exist, create one.
        if (customFolder.mkpath(".")) emit newLog(Normal, "folder created successfully.");
        else emit newLog(Normal, "folder created successfully." "failed to create folder.");
    }
    else emit newLog(Normal, "folder founded.");
}


QList<QVariant> traverseDirectory(const QString& rootDir) {
    QList<QVariant> fileInfoList;
    QDir dir(rootDir);
    // 遍历子目录
    QStringList subDirectories = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (const QString& subDir, subDirectories) {
        QString subdirPath = dir.filePath(subDir);

        // 递归调用遍历子目录，并将结果添加到列表中
        QList<QVariant> subDirFileInfoList = traverseDirectory(subdirPath);

        QList<QVariant> dirFileInfoList;
        dirFileInfoList.append(QVariant::fromValue(QFileInfo(subdirPath)));
        dirFileInfoList.append(QVariant::fromValue(subDirFileInfoList));
        fileInfoList.append(QVariant::fromValue(dirFileInfoList));
    }

    // 遍历文件
    QStringList files = dir.entryList(QDir::Files);
    foreach (const QString& file, files) {
        QString filePath = dir.filePath(file);

        // 获取文件信息并添加到列表中
        QFileInfo fileInfo(filePath);
        fileInfoList.append(QVariant::fromValue(fileInfo));
    }
    return fileInfoList;
}

