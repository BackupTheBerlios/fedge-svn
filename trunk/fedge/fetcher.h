#ifndef FETCHER_H
#define FETCHER_H

#include <qobject.h>
#include <qvaluelist.h>
#include <qvaluestack.h>

class Message;

class Fetcher : public QObject {
	Q_OBJECT
	public:
		Fetcher(QValueList<Q_UINT16> *crctable) { m_crctable = crctable; };
		virtual void fetchMessages() = 0; 
		Message* popMessage() {	return m_messagestack.pop(); };	
		void clearMessages() { while (!m_messagestack.isEmpty()) delete m_messagestack.pop(); };

	protected:
		QValueList<Q_UINT16> *m_crctable;		
		QValueStack<Message*> m_messagestack;

	signals:
		void fetchFinished();
};

#endif // FETCHER_H
