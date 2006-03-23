#ifndef MESSAGE_H
#define MESSAGE_H

#include <qstring.h>

#include "opener.h"
#include "deleter.h"

class Message {

	public:
		Message(QString sender, QString subject, int number = -1, Q_UINT16 crc = 0);
		
		QString sender() { return m_sender; };
		QString subject() { return m_subject; };
		Q_UINT16 crc() { return m_crc; };
		int number() { return m_number; };
		
	private:
		Deleter* m_deleter;	
		Opener* m_opener;
		QString m_sender;
		QString m_subject;
		int m_number;
		Q_UINT16 m_crc;
};

#endif // MESSAGE_H
