//
// C++ Interface: account
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <qstring.h>
#include <qvaluelist.h>

class Deleter;
class Opener;
class Fetcher;
class Message;

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class Account{
public:

	Account(QString name);
    ~Account();
	Deleter* deleter() { return m_deleter; };
	Opener* opener() { return m_opener; };
	Fetcher* fetcher() { return m_fetcher; };
	void clearMessages();
	virtual bool ready() { return m_ready; };
	void setReady(bool b) { m_ready = b; };

protected:
	Deleter *m_deleter;
	Opener *m_opener;
	Fetcher *m_fetcher;
	QValueList<Q_UINT16> m_crctable;
	bool m_ready;

private:
	QString m_name;
};

#endif
