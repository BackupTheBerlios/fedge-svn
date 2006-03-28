//
// C++ Implementation: fedgeconfigdialog
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <klocale.h>

#include "fedgeconfig.h"
#include "configgeneraloptions.h"
#include "fedgeconfigaccounts.h"
#include "fedgeconfigdialog.h"

FedgeConfigDialog::FedgeConfigDialog(QPtrList<Account> *accounts) : KConfigDialog(0, "settings", FedgeConfig::self(), KDialogBase::IconList,  KDialogBase::Ok | KDialogBase::Apply | KDialogBase::Cancel)
{

	m_accounts = accounts;
	m_accountsdialog = new FedgeConfigAccounts(0, i18n("Accounts"), m_accounts);

	addPage(new ConfigGeneralOptions(0, i18n("General")), i18n("General"), "fedge");
	addPage(m_accountsdialog, i18n("Accounts"), "identity");
	connect(m_accountsdialog, SIGNAL(accountsChanged()), this, SLOT(updateButtons()));
}


FedgeConfigDialog::~FedgeConfigDialog()
{
}

bool FedgeConfigDialog::hasChanged() {

	qWarning("hasChanged() called");

 	return m_accountsdialog->changed() || KConfigDialog::hasChanged();
}

void FedgeConfigDialog::updateSettings() {

	qWarning("updateSettings() called");

	m_accountsdialog->save();
	emit settingsChanged();

	KConfigDialog::updateSettings();
}

#include "fedgeconfigdialog.moc"
