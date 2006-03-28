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

#include <qobject.h>
#include <qstring.h>
#include <qvaluelist.h>
#include <qmap.h>

class Deleter;
class Opener;
class Fetcher;
class Message;

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class Account : public QObject {
Q_OBJECT
public:

	Account(QString name);
    ~Account();
	Deleter* deleter() { return m_deleter; };
	Opener* opener() { return m_opener; };
	Fetcher* fetcher() { return m_fetcher; };
	void clearMessages();
	virtual bool ready() { return m_enabled && m_ready; };
	void setReady(bool b) { m_ready = b; };
	void setEnabled(bool b) { m_enabled = b; };
	bool enabled() { return m_enabled; };
	virtual QString string() = 0;
 	virtual QMap<QString, QString> accountMap() = 0;

protected:
	Deleter *m_deleter;
	Opener *m_opener;
	Fetcher *m_fetcher;
	QValueList<Q_UINT16> m_crctable;
	bool m_ready;
	bool m_enabled;
	QString m_name;

private:
	void showMessage(Message *message);

protected slots:
	void slotFetchFinished();
	void slotDeleteFinished();
	void slotOpenFinished();
	void slotDelete(Message *message);
	void slotIgnore(Message *message);		
	void slotOpen(Message *message);
signals:
	void log(QString);
};

#endif
