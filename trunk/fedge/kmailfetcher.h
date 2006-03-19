#ifndef KMAILFETCHER_H
#define KMAILFETCHER_H

#include <pop3fetcher.h>

class KmailFetcher : public Pop3Fetcher {
	Q_OBJECT
	public:
		KmailFetcher(QValueList<Q_UINT16> *crctable);
		
	protected:
		QString kurlBase();
};

#endif // KMAILFETCHER_H
