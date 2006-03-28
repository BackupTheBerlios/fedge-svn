//
// C++ Interface: fedgeconfigdialog
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FEDGECONFIGDIALOG_H
#define FEDGECONFIGDIALOG_H

#include <qvaluelist.h>

#include <kconfigdialog.h>

class FedgeConfigAccounts;
class Account;

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class FedgeConfigDialog : public KConfigDialog
{
Q_OBJECT
public:
    FedgeConfigDialog(QPtrList<Account> *accounts);

    ~FedgeConfigDialog();
private:
	FedgeConfigAccounts *m_accountsdialog;
	QPtrList<Account> *m_accounts;

protected slots:
	void updateSettings();

protected:
	bool hasChanged();	
};

#endif
