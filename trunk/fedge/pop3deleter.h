//
// C++ Interface: pop3deleter
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POP3DELETER_H
#define POP3DELETER_H

#include <deleter.h>
#include <qmap.h>
#include <kio/global.h>
#include <kio/job.h>
#include <qbuffer.h>

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/

class Pop3Deleter : public Deleter
{
Q_OBJECT
public:

	Pop3Deleter(QValueList<Q_UINT16> *crctable, QMap<QString, QString> *configmap);
	~Pop3Deleter();
	void deleteMessages();

private:
	void getMessage(Message *m);
   void commit();

public slots:
	void slotCommitResult(KIO::Job *job);
	void slotGetResult(KIO::Job *job);
	void slotDelResult(KIO::Job *job);
	void slotData(KIO::Job * job, const QByteArray &data);

private:	
	QBuffer m_messagebuffer;
	QMap<QString, QString> *m_configmap;	
};

#endif
