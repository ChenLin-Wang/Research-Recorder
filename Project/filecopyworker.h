#ifndef FILECOPYWORKER_H
#define FILECOPYWORKER_H

#include <QObject>
#include <QFileInfo>
#include <QDir>
#include "shareddefines.h"

class FileCopyWorker : public QObject {
    Q_OBJECT

    public:
        FileCopyWorker() {}

    private:
        void copy(QString destinationFolder, QList<QString> filesNeedCopy);

    signals:
        void fileCopyFinished();
        void newLog(ResultType resultType, QString message);

    public slots:
        void copyFiles(QString destinationFolder, QList<QString> filesNeedCopy);

};

#endif // FILECOPYWORKER_H
