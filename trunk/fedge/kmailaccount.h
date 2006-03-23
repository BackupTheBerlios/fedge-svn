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
    KmailAccount();
    ~KmailAccount();
	bool ready();
private:
	
	bool readConfig();
	QMap<QString, QString> m_configmap;
	KConfig *m_config;
};

#endif
