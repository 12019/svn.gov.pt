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
 * Authors: Luis Medinas <luis.medinas@caixamagica.pt>
 * 	    André Guerreiro <andre.guerreiro@caixamagica.pt>	
 *
 **************************************************************************** */

#include <QListView>
#include <QFileInfo>
#include <QDir>

#include <fstream>
#include <iostream>
#include <string.h>

#include "dlgsignature.h"

#include "eidlib.h"
#include "mainwnd.h"

#include "eidErrors.h"

using namespace eIDMW;


dlgSignature::dlgSignature( QWidget* parent, CardInformation& CI_Data)
    : QDialog(parent)
    , m_CI_Data(CI_Data)
    , m_CurrReaderName("")
{
	if (CI_Data.isDataLoaded())
	{
		ui.setupUi(this);

		//Set icon
		const QIcon Ico = QIcon( ":/images/Images/Icons/ICO_CARD_EID_PLAIN_16x16.png" );
		this->setWindowIcon( Ico );

		QDesktopWidget* desktop = QApplication::desktop();
		int screenNr = desktop->screenNumber();
		QRect rect = desktop->availableGeometry(screenNr);
		int height = rect.height();
		list_model = new QStringListModel();
		ui.listView->setModel(list_model);

		int thiswidth = this->width();
		int thisheight = this->height();

		if (thisheight > height)
		{
			this->resize(thiswidth,height-20); //make sure the window fits
		}
		

	}

}

dlgSignature::~dlgSignature()
{

}

void dlgSignature::ShowErrorMsgBox()
{

	QString caption  = tr("Error");
        QString msg = tr("Error Generating Signature!");
  	QMessageBox msgBoxp(QMessageBox::Warning, caption, msg, 0, this);
  	msgBoxp.exec();
}

void dlgSignature::ShowSuccessMsgBox()
{

		QString caption  = tr("File Signature (XAdES)");
        QString msg = tr("Signature(s) succesfully generated");
		QMessageBox msgBoxp(QMessageBox::Information, caption, msg, 0, this);
  		msgBoxp.exec();


}

void dlgSignature::on_pbCancel_clicked( void )
{
	done(0);
}

void dlgSignature::on_pbAddFiles_clicked( void )
{
	QStringList fileselect;
	QString defaultopenfilepath;

	defaultopenfilepath = QDir::homePath();
	fileselect = QFileDialog::getOpenFileNames(this, tr("Select File(s)"), defaultopenfilepath, NULL);
	QCoreApplication::processEvents();

	SignListView(fileselect);
}



void dlgSignature::SignListView (QStringList list)
{
	view = ui.listView;

	for(int i=0; i != list.size(); i++)
	{

		list_model->insertRows(list_model->rowCount(), 1);
		list_model->setData(list_model->index(list_model->rowCount()-1, 0), list.at(i));

	}

	//Enable sign button now that we have data
	if (!list.isEmpty())
		ui.pbSign->setEnabled(true);

	//signal right click
	//view->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect (ui.listView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
}


void dlgSignature::on_pbSign_clicked ( void )
{
	QAbstractItemModel* model = view->model() ;
	QStringList strlist;
	QFuture<void> future;
	int n_files;

	for ( int i = 0 ; i < model->rowCount() ; ++i )
	{
		// Get item at row i, col 0.
		strlist << model->index( i, 0 ).data( Qt::DisplayRole ).toString() ;
	}

	int listsize = strlist.count();
	char *cpychar;
	const char **files_to_sign = new const char*[listsize];
	char *output_file;

	QCheckBox *signatures_checkbox = ui.checkbox_singlefiles;
	bool individual_sigs = signatures_checkbox->checkState() == Qt::Checked;

	for (n_files = 0; n_files < listsize; n_files++)
	{
		int listtotalLength = strlist.at(n_files).size();
		QString s = QDir::toNativeSeparators(strlist.at(n_files));

		cpychar = new char[listtotalLength+1];
#ifdef WIN32		
		strcpy(cpychar, s.toStdString().c_str());
#else		
		strcpy(cpychar, s.toUtf8().constData());
#endif		
		files_to_sign[n_files] = cpychar;
		PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "File to Sign: %s", files_to_sign[n_files]);
	}
	
	//Default save filepath should be helpful and try to save in the same directory as the file(s)
	QString defaultsavefilepath = QFileInfo(strlist.last()).dir().absolutePath();
	QString savefilepath;
	QString nativedafaultpath;
	if (!individual_sigs)
		defaultsavefilepath.append("/xadessign.zip");
	nativedafaultpath = QDir::toNativeSeparators(defaultsavefilepath);
	if (individual_sigs)
	{
		savefilepath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
				nativedafaultpath,
				QFileDialog::ShowDirsOnly);

	}
	else
		savefilepath = QFileDialog::getSaveFileName(this, tr("Save File"), 
				nativedafaultpath, tr("Zip files 'XAdES' (*.zip)"));

	if (savefilepath.isNull() || savefilepath.isEmpty())
		return;

	QString native_path = QDir::toNativeSeparators(savefilepath);

	pdialog = new QProgressDialog();
	pdialog->setWindowModality(Qt::WindowModal);
	pdialog->setWindowTitle(tr("Sign"));
	pdialog->setLabelText(tr("Signing data..."));
	pdialog->setMinimum(0);
	pdialog->setMaximum(0);
	connect(&this->FutureWatcher, SIGNAL(finished()), pdialog, SLOT(cancel()));

	//Get the Xades-T checkbox value
	QCheckBox *xades_t = ui.checkbox_timestamp;
	bool is_xades_t = xades_t->checkState() == Qt::Checked;


#ifdef WIN32		
	size_t len_2 = strlen(native_path.toStdString().c_str());
	output_file = new char[len_2+1];
	strcpy(output_file,(char*)native_path.toStdString().c_str());
#else
	int outp_len = native_path.size(); 
	output_file =  new char[outp_len*2];
	strncpy(output_file, native_path.toUtf8().constData(), outp_len*2);
#endif	    
	PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "Save to file %s", output_file);
	if (individual_sigs)
		future = 
			QtConcurrent::run(this, &dlgSignature::run_multiple_sign, files_to_sign, n_files, output_file, is_xades_t);
		
	else
		future = 
			QtConcurrent::run(this, &dlgSignature::runsign, files_to_sign, n_files, output_file, is_xades_t);
	this->FutureWatcher.setFuture(future);

	pdialog->exec();

	if (this->success)
		ShowSuccessMsgBox();
	else
		ShowErrorMsgBox();

	delete []files_to_sign;
	delete cpychar;
	delete []output_file;

	this->close();
}


void dlgSignature::runsign(const char ** paths, unsigned int n_paths, const char *output_path, bool timestamp)
{

    try
    {
	    PTEID_EIDCard*	Card = dynamic_cast<PTEID_EIDCard*>(m_CI_Data.m_pCard);
	    PTEID_ByteArray SignXades;
	    if (timestamp)
		    SignXades = Card->SignXadesT(paths, n_paths, output_path);
	    else
		    SignXades = Card->SignXades(paths, n_paths, output_path);
		this->success = true;

    }

    catch (PTEID_Exception &e)
    	{
		this->success = false;
    		switch(e.GetError())
		{
    		case EIDMW_ERR_PIN_CANCEL:
    			PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "PIN introduction - CANCELED!");
    			break;
    		case EIDMW_ERR_TIMEOUT:
    			PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "PIN introduction - TIMEOUT!");
    			break;
    		default:
    			PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "GENERAL EXCEPTION CAUGHT!");
    		}
    	}
    return;
}


void dlgSignature::run_multiple_sign(const char ** paths, unsigned int n_paths, const char *output_path, bool timestamp)
{

    try
    {
        
	    PTEID_EIDCard*	Card = dynamic_cast<PTEID_EIDCard*>(m_CI_Data.m_pCard);
	    if (timestamp)
		    Card->SignXadesTIndividual(paths, n_paths, output_path);
	    else
		    Card->SignXadesIndividual(paths, n_paths, output_path);
		this->success = true;
    }
    catch (PTEID_Exception &e)
        	{
				this->success = false;
        		switch(e.GetError()){
        		case EIDMW_ERR_PIN_CANCEL:
        			PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "PIN introduction - CANCELED!");
        			break;
        		case EIDMW_ERR_TIMEOUT:
        			PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "PIN introduction - TIMEOUT!");
        			break;
        		default:
        			PTEID_LOG(PTEID_LOG_LEVEL_DEBUG, "eidgui", "GENERAL EXCEPTION CAUGHT!");
        		}
        	}
    return;
}
