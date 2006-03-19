#ifndef FETCHER_H
#define FETCHER_H

#include <qobject.h>
#include <qvaluelist.h>
#include <qptrstack.h>

#include <kmdcodec.h>

class Message;

class Fetcher : public QObject {
	Q_OBJECT
	public:
		Fetcher(QValueList<Q_UINT16> *crctable) { m_crctable = crctable; };
		virtual void fetchMessages() = 0; 
		Message* popMessage() {	return m_messagestack.pop(); };	

	protected:
		QValueList<Q_UINT16> *m_crctable;		
		QPtrStack<Message> m_messagestack;

	signals:
		void fetchFinished();
};

#endif // FETCHER_H
