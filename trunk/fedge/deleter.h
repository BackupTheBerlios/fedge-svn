#ifndef DELETER_H
#define DELETER_H

#include <qobject.h>
#include <qptrstack.h>
#include <qvaluelist.h>

class Message;

class Deleter : public QObject {
	Q_OBJECT
public:
	Deleter(QValueList<Q_UINT16> *crctable) { m_crctable = crctable; };
	virtual void deleteMessages() = 0; 
	void pushMessage(Message* m) { m_messagestack.push(m); };

protected:
	QValueList<Q_UINT16> *m_crctable;
	QPtrStack<Message> m_messagestack;

signals:
	void deleteFinished();
};

#endif // DELETER_H
