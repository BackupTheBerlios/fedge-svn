#include "message.h"

Message::Message(QString sender, QString subject, int number, Q_UINT16 crc) {

	m_number = number;
	m_crc = crc;
	m_sender = sender;
	m_subject = subject;
}