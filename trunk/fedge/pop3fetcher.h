#ifndef POP3FETCHER_H
#define POP3FETCHER_H

#include <qvaluestack.h>
#include <qbuffer.h>
#include <qmap.h>

#include <kfileitem.h>
#include <kio/global.h>
#include <kio/job.h>

#include <fetcher.h>

class Pop3Fetcher : public Fetcher {
	Q_OBJECT
	public:
		Pop3Fetcher(QValueList<Q_UINT16> *crctable, QMap<QString, QString> *configmap);
		~Pop3Fetcher();
		void fetchMessages();

	private:
		void getMessage();
		void getMessage(int n);		
    	void commit();

	public slots:	
		void slotEntries(KIO::Job *job, const KIO::UDSEntryList &list);
		void slotGetResult(KIO::Job *job);
		void slotCommitResult(KIO::Job *job);
		void slotListDirResult(KIO::Job *job);
	
	private:
		unsigned int m_tofetch;
		QMap<QString, QString> *m_configmap;
};

#endif // POP3FETCHER_H
