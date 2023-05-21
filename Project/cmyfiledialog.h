#ifndef CMYFILEDIALOG_H
#define CMYFILEDIALOG_H

#include <QFileDialog>
#include <QWidget>
#include <QFileDialog>
#include <QListView>
#include <QTreeView>
#include <QDialogButtonBox>

class CMyFileDialog : public QFileDialog {

    Q_OBJECT

    public:
        explicit CMyFileDialog(QWidget * parent = nullptr);
        QString homedir = "";

    public slots:
        void slot_myAccetp();
        void ontDirectoryChanged(QString dirName);

    signals:

};

#endif // CMYFILEDIALOG_H
