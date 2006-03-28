//
// C++ Implementation: fedgeselectdialog
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <qlistbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qvbox.h>

#include "fedgeselectdialog.h"

FedgeSelectDialog::FedgeSelectDialog(QWidget *parent, const QString& caption, const QStringList &list)
 : KDialogBase(parent, "selectdialog", true, caption, KDialogBase::Ok|KDialogBase::Cancel, KDialogBase::Ok, true )
{
	QVBox *page = makeVBoxMainWidget();
   m_label = new QLabel(caption, page, "caption");
	m_list = new QListBox(page);
	m_list->insertStringList(list);
	m_list->setSelected(0, true);
}


FedgeSelectDialog::~FedgeSelectDialog()
{
}

int FedgeSelectDialog::exec () {

	if (KDialogBase::exec() == QDialog::Rejected) return -1;
	else return m_list->currentItem();
}

#include "fedgeselectdialog.moc"
