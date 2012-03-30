/* ****************************************************************************

 * PTeID Middleware Project.
 * Copyright (C) 2011-2012 Caixa Mágica Software.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version
 * 3.0 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, see
 * http://www.gnu.org/licenses/.
 *
 * Author: Luis Medinas <luis.medinas@caixamagica.pt>
 **************************************************************************** */

#include <iostream>

#include <QtGui>
#include <QtNetwork>

#include "httpwindow.h"
#include "eidlib.h"
#include "mainwnd.h"

#ifdef WIN32
#include <windows.h>
#endif

std::string urli;
//std::string dtitle ("Cartão de Cidadão");
std::string getdistro;
QString fileName;

HttpWindow::HttpWindow(std::string uri, std::string distro, QWidget *parent)
: QDialog(parent)
{
    urli = uri;
    getdistro = distro;

    statusLabel = new QLabel(tr("There are updates available press Install do perform the updates."));

    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(true);
    downloadButton = new QPushButton(tr("Install"));
    downloadButton->setAutoDefault(false);


    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(cancelButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(downloadButton, QDialogButtonBox::RejectRole);

    QTextEdit *textEditor = new QTextEdit();
    textEditor->setText(GetReleaseNotes());
    textEditor->setReadOnly(true);

    progressDialog = new QProgressDialog(this);

    connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(downloadButton, SIGNAL(clicked()), this, SLOT(downloadFile()));

    QHBoxLayout *topLayout = new QHBoxLayout;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(textEditor);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Auto-Update"));

    //statusLabel = new QLabel(tr("There are updates available press Install do perform the updates."));

}

HttpWindow::~HttpWindow()
{
}

QString HttpWindow::GetReleaseNotes()
{
    QString line;
    QString str;
    QRegExp sep("\\#");

    QString rnpath = QDir::tempPath();
    rnpath.append("/version.txt");



    QString s = QDir::toNativeSeparators(rnpath);

    QFile file(s);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Get Release Notes failed";

    QTextStream in(&file);

    while (!in.atEnd())
    {
        line = in.readAll();
    }

    str = line.section(sep, 1, -1);

    return str;
}

void HttpWindow::startRequest(QUrl url)
{
	reply = qnam.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()),
			this, SLOT(httpFinished()));
	connect(reply, SIGNAL(readyRead()),
			this, SLOT(httpReadyRead()));
	connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
			this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void HttpWindow::downloadFile()
{
	url = urli.c_str();

	QFileInfo fileInfo(url.path());
	fileName = fileInfo.fileName();
	if (fileName.isEmpty())
	{
		QMessageBox::information(this, tr("Auto-Update"),
				tr("Unable to download the update please check your Network Connection.")
		.arg(fileName).arg(file->errorString()));
	}

	QFile::remove(fileName);
	/*if (QFile::exists(fileName)) {
		if (QMessageBox::question(this, QString::fromUtf8(dtitle.c_str()),
				tr("There already exists a file called %1 in "
						"the current directory. Overwrite?").arg(fileName),
						QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
		== QMessageBox::No)
			return;
		QFile::remove(fileName);
	}*/

	std::string tmpfile;
	tmpfile.append(QDir::tempPath().toStdString());
	tmpfile.append("/");
	tmpfile.append(fileName.toStdString());

	file = new QFile(QString::fromUtf8((tmpfile.c_str())));
	if (!file->open(QIODevice::WriteOnly)) {
		QMessageBox::information(this, tr("Auto-Update"),
				tr("Unable to save the file %1: %2.")
		.arg(fileName).arg(file->errorString()));
		delete file;
		file = 0;
		return;
	}

	progressDialog->setWindowTitle(tr("Auto-Update"));
	progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));
	downloadButton->setEnabled(false);

	// schedule the request
	httpRequestAborted = false;
	startRequest(url);
}

void HttpWindow::cancelDownload()
{
	statusLabel->setText(tr("Download canceled. Try again."));
	httpRequestAborted = true;
	reply->abort();
	downloadButton->setEnabled(true);
}

void HttpWindow::httpFinished()
{
    if (httpRequestAborted)
    {
        if (file)
        {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        progressDialog->hide();
        return;
    }

    progressDialog->hide();
    file->flush();
    file->close();

    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error())
    {
        file->remove();
        QMessageBox::information(this, tr("Auto-Update"),
                                 tr("Download failed: %1.")
                                 .arg(reply->errorString()));
        downloadButton->setEnabled(true);
        this->close();
    }
    else if (!redirectionTarget.isNull())
    {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());

        if (QMessageBox::question(this, tr("Auto-Update"),
                                  tr("Redirect to %1 ?").arg(newUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            url = newUrl;
            reply->deleteLater();
            file->open(QIODevice::WriteOnly);
            file->resize(0);
            startRequest(url);
            return;
        }
    }
    else
    {
        downloadButton->setEnabled(true);
        this->close();
    }

    if (!reply->error())
        RunPackage(fileName.toStdString() , getdistro);

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void HttpWindow::httpReadyRead()
{
	// this slot gets called everytime the QNetworkReply has new data.
	// We read all of its new data and write it into the file.
	// That way we use less RAM than when reading it at the finished()
	// signal of the QNetworkReply
	if (file)
		file->write(reply->readAll());
}

void HttpWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
	if (httpRequestAborted)
		return;

	progressDialog->setMaximum(totalBytes);
	progressDialog->setValue(bytesRead);
}

void HttpWindow::RunPackage(std::string pkg, std::string distro)
{
	std::string pkgpath;
	pkgpath.append(QDir::tempPath().toStdString());
	pkgpath.append("/");
	pkgpath.append(pkg);
#ifdef WIN32
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(si)); 
	si.cb = sizeof(si); 

	std::string winpath;
    winpath.append("C:\\Windows\\system32\\msiexec.exe /i");
	//TODO: Verificar a path do msi em Windows
	//C:\\Users\\Luis\\AppData\\Local\\Temp\\PteidMW35-Basic-en.msi
    QString s = QDir::toNativeSeparators(QString::fromStdString(pkgpath));
    winpath.append(s.toStdString());
    winpath.append(" /L*v ");
    winpath.append(QDir::tempPath().toStdString());
    winpath.append("\PTeID-MSI.log");
	CreateProcess(NULL, LPTSTR(winpath.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	exit(0);

#elif __APPLE__

	execl("/usr/bin/hdiutil", "hdiutil", "attach", pkgpath.c_str(), NULL);

#else

	std::cout << "pkgpath " << pkgpath << " distro " << distro << std::endl;
	if (distro == "debian")
	{
	  	execl ("/usr/bin/software-center", "software-center", pkgpath.c_str(), NULL);
	}

	if (distro == "fedora")
	{
	  	execl ("/usr/bin/gpk-install-local-file", "gpk-install-local-file", pkgpath.c_str(), NULL);
	}

	if (distro == "suse")
	{
	    	execl ("/usr/bin/gpk-install-local-file", "gpk-install-local-file", pkgpath.c_str(), NULL);
	}
#endif
}

