//
// C++ Implementation: kmailaccount
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <kconfig.h>

#include <pop3deleter.h>
#include <pop3fetcher.h>
#include <appopener.h>

#include "kmailaccount.h"

KmailAccount::KmailAccount(QString accountname) : Account("KMail")
{
	m_accountname = accountname; // "Account 1";

	m_config = new KConfig("kmailrc", true);
	readConfig();
	
	QStringList args;
	args << "kmail" << "--check";
	m_opener = new AppOpener(args);

	m_deleter = new Pop3Deleter(&m_crctable, &m_configmap);
	m_fetcher = new Pop3Fetcher(&m_crctable, &m_configmap);

	connect(m_fetcher, SIGNAL(fetchFinished()), SLOT(slotFetchFinished()));	
	connect(m_deleter, SIGNAL(deleteFinished()), SLOT(slotDeleteFinished()));	
	connect(m_opener, SIGNAL(openFinished()), SLOT(slotOpenFinished()));
}

KmailAccount::~KmailAccount()
{
	delete m_config;
}

QMap<QString, QString> KmailAccount::accountMap() {
	
	QMap<QString, QString> map;
	map["name"] = m_name;
	map["accountname"] = m_accountname; 
	map["enabled"] = m_enabled ? "true" : "false";
	map["string"] = string();

	return map;
}

void KmailAccount::readConfig() {

	m_config->reparseConfiguration();
	m_configmap = m_config->entryMap(m_accountname);	

	if (m_configmap.empty()) {
	
		qWarning("kmail: %s configuration entry is not valid in kmailrc, disabling the account.", m_accountname.latin1());
		m_enabled = false;
	}

	if (m_configmap["Type"] != "pop") {
	
		qWarning("kmail: %s accounts currently not-supported, disabling the account.", m_configmap["Type"].latin1());
		m_enabled = false;
	}
}


