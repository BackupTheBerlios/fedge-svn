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
#include "pop3common.h"

Pop3Deleter::Pop3Deleter(QValueList<Q_UINT16> *crctable, QMap<QString, QString> *configmap) : Deleter(crctable) {

	m_configmap = configmap;
}

Pop3Deleter::~Pop3Deleter() {}

void Pop3Deleter::deleteMessages() {

	getMessage(m_messagestack.pop());
}
	
void Pop3Deleter::getMessage(Message *m) {
		
	if (!m) commit(); 
	else {
	
		KURL kurl = Pop3Common::kurlBase(m_configmap) + "/headers/" + QString::number(m->number());
		KIO::StoredTransferJob *transferjob = KIO::storedGet(kurl, true, false);
		Pop3Common::setMetaData(m_configmap, transferjob);
		transferjob->addMetaData("pop3number", QString::number(m->number()));
		transferjob->addMetaData("crc", QString::number(m->crc()));
		if (FedgeConfig::showErrorDialogs()) transferjob->setAutoErrorHandlingEnabled(true);  	
		connect(transferjob, SIGNAL(result(KIO::Job*)), SLOT(slotGetResult(KIO::Job*)));
	}
	delete m;	
}

void Pop3Deleter::slotCommitResult(KIO::Job *job) { 

	if (job->error()) commit();
	else {
	
		/* When commit returns emit the finish signal */

		emit deleteFinished();
	}
}

void Pop3Deleter::slotGetResult(KIO::Job *job) {

	QByteArray bytearray = static_cast<KIO::StoredTransferJob*>(job)->data();
	Q_UINT16 crc = qChecksum(bytearray, bytearray.size());
	KIO::MetaData meta = job->outgoingMetaData();

	/* if there was an error the next message should be checked. */

	if (job->error()){

		emit log("pop3deleter: error trying to get message " + meta["pop3number"] + ".");
		getMessage(m_messagestack.pop());
	} else if (meta["crc"].toUInt() != crc) {

		 emit log("pop3deleter: message " + meta["pop3number"] + " crc mismatch");
		 getMessage(m_messagestack.pop());		
	} else {

		emit log("pop3deleter: message " + meta["pop3number"] + " deleted.");
		KIO::TransferJob *deletejob = KIO::get(Pop3Common::kurlBase(m_configmap) + "/remove/" + meta["pop3number"], true, false);
		Pop3Common::setMetaData(m_configmap, deletejob);
		deletejob->addMetaData(meta);
		if (FedgeConfig::showErrorDialogs()) deletejob->setAutoErrorHandlingEnabled(true);
		connect(deletejob, SIGNAL(result(KIO::Job*)), SLOT(slotDelResult(KIO::Job*))); 
	}
}

void Pop3Deleter::slotDelResult(KIO::Job *job) {

	KIO::MetaData meta = job->outgoingMetaData();

	if (job->error()){

		emit log("pop3deleter: error trying to remove message " + meta["pop3number"] + ".");		
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
	KIO::TransferJob *commitjob = KIO::get(Pop3Common::kurlBase(m_configmap) + "/commit", true, false);
	Pop3Common::setMetaData(m_configmap, commitjob);
	if (FedgeConfig::showErrorDialogs()) commitjob->setAutoErrorHandlingEnabled(true); 
	connect(commitjob, SIGNAL(result(KIO::Job*)), SLOT(slotCommitResult(KIO::Job*)));
}
