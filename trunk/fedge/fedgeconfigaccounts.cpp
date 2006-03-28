//
// C++ Implementation: fedgeconfigaccounts
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <qpushbutton.h>

#include <kiconloader.h>
#include <kconfig.h>
#include <klocale.h>

#include "kmailaccount.h"
#include "fedgeselectdialog.h"
#include "fedgeconfigaccounts.h"

FedgeConfigAccounts::FedgeConfigAccounts(QWidget *parent, const char *name, QPtrList<Account> *accounts)
 : ConfigAccounts(parent, name)
{
	m_changed = false;

	m_config = new KConfig("fedgerc");

	int i = 0;

	Account *account;
	for (account = accounts->first(); account; account = accounts->next()) {
			
		m_config->setGroup("Account " + QString::number(i));
		addAccount(account);
		i++;
	}

	kmailButton->setIconSet(KIconLoader().loadIcon("kmail", KIcon::Desktop));
	
	connect(kmailButton, SIGNAL(clicked()), SLOT(slotKmail()));
	connect(removeButton, SIGNAL(clicked()), SLOT(slotRemove()));
	connect(enableButton, SIGNAL(clicked()), SLOT(slotEnable()));
	connect(accountsBox, SIGNAL(selectionChanged()), SLOT(slotSelectionChanged()));
}


FedgeConfigAccounts::~FedgeConfigAccounts()
{
	delete m_config;
}

void FedgeConfigAccounts::slotSelectionChanged() {

// 	qWarning("slotSelectionChanged() called");

	bool entryselected = (accountsBox->index(accountsBox->selectedItem()) != -1);

	removeButton->setEnabled(entryselected);
	enableButton->setEnabled(entryselected);
}

void FedgeConfigAccounts::addAccount(Account *account)
{
// 	qWarning("add account() called");

	QMap<QString, QString> map = account->accountMap();
	QMap<QString, QString>::Iterator mit;
	for (mit = map.begin(); mit != map.end(); ++mit) m_config->writeEntry(mit.key(), mit.data());
	accountsBox->insertItem(account->enabled() ? account->string() : account->string() + i18n(" (disabled)"));	
}

void FedgeConfigAccounts::removeAccount(int i) {

	if (m_config->hasGroup("Account " +  QString::number(i + 1))) {

		moveAccount(i + 1, i);
		removeAccount(i + 1);
	}
	else m_config->deleteGroup("Account " +  QString::number(i));
}

void FedgeConfigAccounts::moveAccount(int source, int dest)
{

	QMap<QString, QString> map;
	map = m_config->entryMap("Account " + QString::number(source)); 
	m_config->setGroup("Account " +  QString::number(dest));
	QMap<QString, QString>::Iterator mit;
	for (mit = map.begin(); mit != map.end(); ++mit) m_config->writeEntry(mit.key(), mit.data());
}

void FedgeConfigAccounts::slotRemove() {

	int i = accountsBox->index(accountsBox->selectedItem());
	if (i == -1) {

		qWarning("Should not happen: Remove Account with none selected!");
		return;
	}

	accountsBox->removeItem(i);
	removeAccount(i);	
	
	m_changed = true;
   emit accountsChanged();		
}

void FedgeConfigAccounts::slotEnable() {

	int i = accountsBox->index(accountsBox->selectedItem());
	if (i == -1) {

		qWarning("Should not happen: Toggle enable with none selected!");
		return;
	}

	m_config->setGroup("Account " + QString::number(i));
	m_config->writeEntry("enabled", (m_config->readEntry("enabled") == "true" ) ? "false" : "true");
	accountsBox->changeItem((m_config->readEntry("enabled") == "true" ) ? 
		m_config->readEntry("string") : 
		m_config->readEntry("string") + i18n(" (disabled)"), i);
	accountsBox->setSelected(i, true);	

	m_changed = true;
   emit accountsChanged();		
}

void FedgeConfigAccounts::slotKmail() {
		
	KConfig config("kmailrc", true);
	QStringList list;
	QMap<QString, QString> configmap;
	int i = 1;

	while (config.hasGroup("Account " + QString::number(i))) {

		QString account = "Account " + QString::number(i++);
		configmap = config.entryMap(account);	
		if (!configmap.empty()) list << account;
	} 

	int accno = 1;

	if (list.empty()) return;
	if (list.size() > 1) {

		FedgeSelectDialog fsd(0, "Select Kmail Account:", list);
		accno = fsd.exec();	
	}

	KmailAccount account("Account " + QString::number(accno));

	m_config->setGroup(newGroup());
	addAccount(&account);
	
	m_changed = true;
   emit accountsChanged();
}

QString FedgeConfigAccounts::newGroup() {

	int i = 0;
	while (m_config->hasGroup("Account " + QString::number(i))) {

		i++;
	}
	return "Account " + QString::number(i);
}

/*!
    \fn FedgeConfigAccounts::slotSafe()
 */
void FedgeConfigAccounts::save()
{

// 	qWarning("save() called");

	m_changed = false;
	m_config->sync();
}

#include "fedgeconfigaccounts.moc"
