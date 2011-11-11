/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2009-2010 FedICT.
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

**************************************************************************** */

#include <QtGui/qdialog.h>
#include <QtGui/qlabel.h>
#include <QtGui/qpushbutton.h>
#include <QtGui/qgridlayout.h>
#include <QtGui/QApplication>

QT_BEGIN_NAMESPACE

class accessibleDialogbox{

public:
	accessibleDialogbox( QString title,QString body, QString acceptButton, QString cancelButton, QWidget *parent = 0 );
	~accessibleDialogbox();
	int exec(void);
	static int showDialogBox( QString title,QString body, QString acceptButton, QString cancelButton, QWidget *parent = 0 );

protected:
	QDialog* dialog;
	QGridLayout* grid;
	QLabel* label;
	QPushButton* ok;
	QPushButton* cancel;
};

QT_END_NAMESPACE
