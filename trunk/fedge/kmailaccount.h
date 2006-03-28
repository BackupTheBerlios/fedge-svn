//
// C++ Interface: kmailaccount
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef KMAILACCOUNT_H
#define KMAILACCOUNT_H

#include <qmap.h>

#include <account.h>

class KConfig;

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class KmailAccount : public Account
{
public:
    KmailAccount(QString accountname);
    ~KmailAccount();
	QMap<QString, QString> accountMap();
	QString string() { return m_name + ": " + m_configmap["Name"]; };
private:
	
	QString m_string;
	QString m_accountname;
	void readConfig();
	QMap<QString, QString> m_configmap;
	KConfig *m_config;
};

#endif
