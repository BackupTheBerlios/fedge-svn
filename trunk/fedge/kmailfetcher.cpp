#include "kmailfetcher.h"

#include "kmailfetcher.moc"
#include "fedgeconfig.h"

KmailFetcher::KmailFetcher(QValueList<Q_UINT16> *crctable) : Pop3Fetcher(crctable) {
}

QString KmailFetcher::kurlBase() {
	
	return FedgeConfig::kurl();
}

