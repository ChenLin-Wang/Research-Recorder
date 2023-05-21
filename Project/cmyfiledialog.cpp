#include "cmyfiledialog.h"

CMyFileDialog::CMyFileDialog(QWidget * parent) : QFileDialog(parent) {
    QObject::connect(this, &QFileDialog::directoryEntered, this, &CMyFileDialog::ontDirectoryChanged);
}

void CMyFileDialog::ontDirectoryChanged(QString dirName) {
    if (dirName.startsWith(homedir)) return;
    this->setDirectory(homedir);
}

void CMyFileDialog::slot_myAccetp() { QDialog::accept(); }
