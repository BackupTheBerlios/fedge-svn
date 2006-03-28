//
// C++ Interface: fedgeselectdialog
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FEDGESELECTDIALOG_H
#define FEDGESELECTDIALOG_H

#include <qstringlist.h>

#include <kdialogbase.h>

class QListBox;
class QLabel;

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class FedgeSelectDialog : public KDialogBase
{
Q_OBJECT
public:
    FedgeSelectDialog(QWidget *parent = 0, const QString& caption = "", const QStringList &list = QStringList());

    ~FedgeSelectDialog();
	int exec();
private:
	QListBox *m_list;
	QLabel *m_label;
	
};

#endif
