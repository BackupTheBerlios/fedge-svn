#include <qstring.h>
#include <qwidget.h>
#include <qptrlist.h>
#include <qtextstream.h>
#include <qfile.h>

#include <kio/job.h>
#include <kio/global.h>
#include <klocale.h>

#include "pop3fetcher.h"
#include "message.h"
#include "fedgeconfig.h"

Pop3Fetcher::Pop3Fetcher(QValueList<Q_UINT16> *crctable) : Fetcher(crctable) {	
}

Pop3Fetcher::~Pop3Fetcher() {
}

void Pop3Fetcher::fetchMessages() {

	/* A list job of the url declared in derived classes is issued. The job
	is connected to a slot which handles the arrived list and to a slot for
	the result of the operation. */

	KIO::ListJob *listjob = KIO::listDir(kurlBase(), false);
	if (FedgeConfig::showErrorDialogs()) listjob->setAutoErrorHandlingEnabled(true);  	
	connect(listjob, SIGNAL(entries(KIO::Job*, const KIO::UDSEntryList&)), SLOT(slotEntries(KIO::Job*, const KIO::UDSEntryList&)));	
	connect(listjob, SIGNAL(result(KIO::Job*)), SLOT(slotListDirResult(KIO::Job*)));
}

void Pop3Fetcher::getMessage(int n) {
	
	/* The messagebuffer is filled with an empty array (aka cleared). */

	m_messagebuffer.setBuffer(QByteArray());
	
	/* The url for the slave to get a mail is constructed by the kurl-base, a
	string defined in derived classes a "headers" string and the number
	of the message to be fetched. We only need */
		
	 KURL kurl = kurlBase() + "/headers/" + QString::number(n);	

	/* The TransferJob is started by the get Method (true says it should not 
	be retrieved from cache and false supresses progress widgets). */

	KIO::TransferJob *transferjob = KIO::get(kurl, true, false);

	/* The job is added the number of the message as metadata */
	transferjob->addMetaData("pop3number", QString::number(n));

	/* Depending on the config, error Dialogs are to be shown. */

	if (FedgeConfig::showErrorDialogs()) transferjob->setAutoErrorHandlingEnabled(true);

	/* The job gets connected to a slot which handles data arriving from the job (the mail) and
	a slot for the result of the job. */ 
  	
	connect(transferjob, SIGNAL(data(KIO::Job*, const QByteArray&)), SLOT(slotData(KIO::Job*, const QByteArray&)));
	connect(transferjob, SIGNAL(result(KIO::Job*)), SLOT(slotGetResult(KIO::Job*)));
}

void Pop3Fetcher::slotData(KIO::Job*, const QByteArray &data) {
	
	/* The messagebuffer is opened, the newly arrived data is appended
	at the messagebuffers end, then the buffer is closed. */ 

	QIODevice::Offset size = m_messagebuffer.size();
	
	m_messagebuffer.open(IO_WriteOnly);
	m_messagebuffer.at(size);
	m_messagebuffer.writeBlock(data);
	m_messagebuffer.close();
}

void Pop3Fetcher::slotCommitResult(KIO::Job *job) { 

	/* When the commit job failed, it retries. */

	if (job->error()) commit(); 
	else {

		/* When commit returns emit the finish signal */

		emit fetchFinished();
	}
}

void Pop3Fetcher::slotListDirResult(KIO::Job *job) {

	/* When the list job fails it retries, otherwise it begins fetching the 
	Messages. */

	if (job->error()) fetchMessages();
	else getMessage();
}

void Pop3Fetcher::getMessage() {
	
	if (m_tofetch) getMessage(m_tofetch--);
	else commit();
}

void Pop3Fetcher::slotGetResult(KIO::Job *job) {

	/* If the get job fails, it has to be retried. */

	if (job->error()) getMessage(job->outgoingMetaData()["pop3number"].toInt());		
	else {

		/* The crc of the arrived message is calculated. */

		QByteArray a = m_messagebuffer.buffer();
		Q_UINT16 crc = qChecksum(a, a.size());
		
		/* Check wether the crc of the message is yet in the list, which means
		we have shown this message yet. */

		if (!m_crctable->contains(crc)) {
			
			/* The messagebuffer is opened and a textstream is created with it. 
			the standard values are set.*/

			m_messagebuffer.open(IO_ReadOnly);
			QTextStream stream(&m_messagebuffer);
			QString line = "";
			QString sender = "";
			QString subject = i18n("no subject");;
					
			/* The stream is parsed per line and the subject and sender are
			extracted from the header. */
	
			while(!stream.atEnd()) {
							
				line = stream.readLine();
				if ((line.startsWith("Subject:")) || (line.startsWith("subject:"))) subject = line.remove(0,8);
				else if ((line.startsWith("From:")) || (line.startsWith("from:"))) sender = line.remove(0,5);		
			}	
			m_messagebuffer.close();

			if (sender == "") {

				qWarning("get: fetched illegal message.");
				getMessage();
				return;
			}
			
			/* The number of the header is extracted from the jobs metadata,
			the crc is added to the table and a new message is created on the
			messagestack. */

			int number = job->outgoingMetaData()["pop3number"].toInt();
			m_crctable->append(crc);
			
			m_messagestack.push(new Message(sender, subject, number, crc));
		}
	
		getMessage();
	}
}

void Pop3Fetcher::slotEntries(KIO::Job *, const KIO::UDSEntryList &list) {
		
	unsigned int count = list.count();
	
	qWarning("get: %d entries arrived", count);
	
	/* If there are less messages read in, than there are hashes in the hashtable,
	we assume an email-client has been invoked and the messages have been read. */

	if (count < m_crctable->size()) m_crctable->clear();
 	
	/* The number of mails to fetch is set according to te size of the list.*/

	m_tofetch = count;
}

/*!
    \fn Pop3Fetcher::commit()
 */
void Pop3Fetcher::commit()
{
	/* To close the connection to the pop3 server the "commit" file is to be
	retrieved. */
	
	KIO::TransferJob *commitjob = KIO::get(kurlBase() + "/commit", true, false);
	if (FedgeConfig::showErrorDialogs()) commitjob->setAutoErrorHandlingEnabled(true); 
	connect(commitjob, SIGNAL(result(KIO::Job*)), SLOT(slotCommitResult(KIO::Job*))); 
}
