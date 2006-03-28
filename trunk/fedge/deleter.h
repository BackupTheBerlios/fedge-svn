#ifndef DELETER_H
#define DELETER_H

#include <qobject.h>
#include <qvaluestack.h>
#include <qvaluelist.h>

class Message;

class Deleter : public QObject {
	Q_OBJECT
public:
	Deleter(QValueList<Q_UINT16> *crctable) { m_crctable = crctable; };
	virtual void deleteMessages() = 0; 
	void pushMessage(Message* m) { m_messagestack.push(m); };
	void clearMessages() { while (!m_messagestack.isEmpty()) delete m_messagestack.pop(); };

protected:
	QValueList<Q_UINT16> *m_crctable;
	QValueStack<Message*> m_messagestack;

signals:
	void deleteFinished();
	void log(QString l);
};

#endif // DELETER_H
