//
// C++ Interface: fedgeconfigaccounts
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FEDGECONFIGACCOUNTS_H
#define FEDGECONFIGACCOUNTS_H

#include <qptrlist.h>

#include <account.h>
#include <configaccounts.h>

class KConfig;

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class FedgeConfigAccounts : public ConfigAccounts
{
Q_OBJECT
public:
	FedgeConfigAccounts(QWidget *parent = 0, const char *name = 0, QPtrList<Account> *accounts = 0);
	~FedgeConfigAccounts();
	void save();
	bool changed() { return m_changed; };
private:
	bool m_changed;
	KConfig *m_config;
private slots:
	void slotKmail();
	void slotRemove();
	void slotEnable();
	void slotSelectionChanged();
signals:
	void accountsChanged();
private:
	QString newGroup();
	void addAccount(Account *account);
	void removeAccount(int i);
	void moveAccount(int source, int dest);
};

#endif
