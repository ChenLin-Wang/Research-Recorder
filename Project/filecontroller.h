#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QString>
#include <QObject>
#include <QThread>
#include "shareddefines.h"
#include "filecopyworker.h"

class FileController: public QObject {

    Q_OBJECT

    public:
        FileController();
        static const QString documentsPath;
        void checkHomeDir();
        void createSubDir(QString name);
        void createDataDir(QString userHomeDirName, QString path);
        QList<QVariant> fetchAllFilesAtSubDir(QString name);
        void copyFilesToFolder(QString folder, QList<QString> files);

    private:
        FileCopyWorker * worker = new FileCopyWorker();
        QThread * thread = new QThread();
        void createDirIfNotExists(QString path);
        void fileCopyDidFinish();

    signals:
        void startCopyFile(QString folder, QList<QString> files);
        void newLog(ResultType resultType, QString message);
        void copyFinished();
};

#endif // FILECONTROLLER_H
