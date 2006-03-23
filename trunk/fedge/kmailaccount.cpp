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

KmailAccount::KmailAccount() : Account("KMail")
{
	m_ready = true;

	m_config = new KConfig("kmailrc", true);
	readConfig();
	
// 	qWarning("hallo: %s", map["host"].latin1());

	QStringList args;
	args << "kmail" << "--check";
	m_opener = new AppOpener(args);

	m_deleter = new Pop3Deleter(&m_crctable, &m_configmap);
	m_fetcher = new Pop3Fetcher(&m_crctable, &m_configmap);
}

KmailAccount::~KmailAccount()
{
	delete m_config;
}

bool KmailAccount::ready() {
	
	return (readConfig() && Account::ready());
}

bool KmailAccount::readConfig() {

	m_config->reparseConfiguration();
	m_configmap = m_config->entryMap("Account 1");	

	if (m_configmap["Type"] != "pop") {
	
		qWarning("kmail: %s accounts currently not-supported", m_configmap["Type"].latin1());
		return false;
	}
	return true;
}


