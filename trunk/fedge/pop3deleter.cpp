//
// C++ Implementation: pop3deleter
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "message.h"
#include "fedgeconfig.h"
#include "pop3deleter.h"


Pop3Deleter::Pop3Deleter(QValueList<Q_UINT16> *crctable) : Deleter(crctable)
{
}


Pop3Deleter::~Pop3Deleter()
{
}


void Pop3Deleter::deleteMessages() {

	getMessage(m_messagestack.pop());
}
	
void Pop3Deleter::getMessage(Message *m) {
		
	if (!m) commit(); 
	else {
	
		m_messagebuffer.setBuffer(QByteArray());
		KURL kurl = kurlBase() + "/headers/" + QString::number(m->getNumber());
		KIO::TransferJob *transferjob = KIO::get(kurl, true, false);
		transferjob->addMetaData("pop3number", QString::number(m->getNumber()));
		transferjob->addMetaData("crc", QString::number(m->getCrc()));
		if (FedgeConfig::showErrorDialogs()) transferjob->setAutoErrorHandlingEnabled(true);  	
		connect(transferjob, SIGNAL(data(KIO::Job*, const QByteArray&)), SLOT(slotData(KIO::Job*, const QByteArray&)));
		connect(transferjob, SIGNAL(result(KIO::Job*)), SLOT(slotGetResult(KIO::Job*)));
	}
	delete m;	
}

void Pop3Deleter::slotData(KIO::Job * job, const QByteArray &data) {
	
	QIODevice::Offset size = m_messagebuffer.size();
	
	m_messagebuffer.open(IO_WriteOnly);
	m_messagebuffer.at(size);
	m_messagebuffer.writeBlock(data);
	m_messagebuffer.close();
}

void Pop3Deleter::slotCommitResult(KIO::Job *job) { 

	if (job->error()) commit();
	else {
	
		/* When commit returns emit the finish signal */

		emit deleteFinished();
	}
}

void Pop3Deleter::slotGetResult(KIO::Job *job) {

	QByteArray a = m_messagebuffer.buffer();
	Q_UINT16 crc = qChecksum(a, a.size());
	KIO::MetaData meta = job->outgoingMetaData();

	/* if there was an error the next message should be checked. */

	if (job->error()){

		qWarning("delete: error trying to get message %s", meta["pop3number"].latin1());
		getMessage(m_messagestack.pop());
	} else if (meta["crc"].toUInt() != crc) {

		 qWarning("delete: message %d: crc mismatch", meta["pop3number"].toInt());
		 getMessage(m_messagestack.pop());		
	} else {

		qWarning("delete: message %d: crc match", meta["pop3number"].toInt());
		KIO::TransferJob *deletejob = KIO::get(kurlBase() + "/remove/" + meta["pop3number"], true, false);
		deletejob->addMetaData(meta);
		if (FedgeConfig::showErrorDialogs()) deletejob->setAutoErrorHandlingEnabled(true);
		connect(deletejob, SIGNAL(result(KIO::Job*)), SLOT(slotDelResult(KIO::Job*))); 
	}
}

void Pop3Deleter::slotDelResult(KIO::Job *job) {

	KIO::MetaData meta = job->outgoingMetaData();

	if (job->error()){

		qWarning("delete: error trying to remove message %s", meta["pop3number"].latin1());		
	} else {

		m_crctable->remove(meta["crc"].toUInt()); 	
	}

	getMessage(m_messagestack.pop()); 
}


/*!
    \fn Pop3Deleter::commit()
 */
void Pop3Deleter::commit()
{
	KIO::TransferJob *commitjob = KIO::get(kurlBase() + "/commit", true, false);
	if (FedgeConfig::showErrorDialogs()) commitjob->setAutoErrorHandlingEnabled(true); 
	connect(commitjob, SIGNAL(result(KIO::Job*)), SLOT(slotCommitResult(KIO::Job*)));
}
