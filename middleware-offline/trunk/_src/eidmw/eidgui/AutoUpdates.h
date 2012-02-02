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

#ifndef AUTOUPDATES_H_
#define AUTOUPDATES_H_

#include <QDialog>
#include <QtGui>
#include <QNetworkAccessManager>
#include <QUrl>
#include <iostream>
#include <QString>

class QDialogButtonBox;
class QFile;
class QLabel;
class QLineEdit;
class QProgressDialog;
class QPushButton;
class QAuthenticator;
class QNetworkReply;

class AutoUpdates : public QDialog
{
	Q_OBJECT

public:
	AutoUpdates(QWidget *parent = 0);
	~AutoUpdates();

	std::string CheckUpdates();
	bool VerifyUpdates(std::string filedata);
	bool FileExists(const char *filename);
	//The Perl script can be run only one time to generate the file
	std::string VerifyOS(std::string param, bool runscript);
	void ChooseVersion(std::string distro, std::string arch);
	void DownloadDialog();

	void startRequest(QUrl url);

private slots:
	void cancelDownload();
	void downloadFile();
	void httpFinished();
	void httpReadyRead();
	void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);

private:
    	QPushButton *cancelButton;
    	QDialogButtonBox *buttonBox;
    	QPushButton *downloadButton;
    	QLabel *statusLabel;
    	QProgressDialog *progressDialog;

	QUrl url;
	QNetworkAccessManager qnam;
	QNetworkReply *reply;
	QFile *file;
	int httpGetId;
	bool httpRequestAborted;
	std::string filedata;
};

#endif /* AUTOUPDATES_H_ */
