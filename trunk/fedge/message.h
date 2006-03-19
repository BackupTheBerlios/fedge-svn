#ifndef MESSAGE_H
#define MESSAGE_H

#include <qstring.h>

#include "opener.h"
#include "deleter.h"

class Message {

	public:
		Message(QString sender, QString subject, int number = -1, Q_UINT16 crc = 0);
		
		QString getSender() { return m_sender; };
		QString getSubject() { return m_subject; };
		Q_UINT16 getCrc() { return m_crc; };
		int getNumber() { return m_number; };
		
	private:
		Deleter* m_deleter;	
		Opener* m_opener;
		QString m_sender;
		QString m_subject;
		int m_number;
		Q_UINT16 m_crc;
};

#endif // MESSAGE_H
