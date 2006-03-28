//
// C++ Implementation: account
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <kapplication.h>
#include <ksystemtray.h>

#include "fedge.h"
#include "fetcher.h"
#include "deleter.h"
#include "fedgeballoon.h"
#include "message.h"

#include "account.h"

Account::Account(QString name) : QObject()
{
	m_name = name;
	m_ready = true;
	m_enabled = true;
}

Account::~Account()
{
}

void Account::clearMessages() {

	m_crctable.clear();
	m_deleter->clearMessages();
	m_fetcher->clearMessages();
}

/*!
    \fn Fedge::slotOpen(Message *message)
 */
void Account::slotOpen(Message *message)
{
    /* Delete the crc table, the messages on the delete and the fetchstack. */
 
	if (m_opener->open()) clearMessages();
	else setReady(true);
}

void Account::slotDelete(Message *message) {
 
 	m_deleter->pushMessage(message);
	showMessage(m_fetcher->popMessage());
}

void Account::slotIgnore(Message *message) {

	/* The message gets deleted, as its of no use anymore, 
	then the next message on the fetchers stack is popped. */

	delete message;
	showMessage(m_fetcher->popMessage());
}

void Account::slotFetchFinished() {

	showMessage(m_fetcher->popMessage());
}

void Account::slotDeleteFinished() {

	setReady(true);
}

void Account::slotOpenFinished() {

	setReady(true);
}

void Account::showMessage(Message *message) {

	/* When there are no more messages to be shown, the messages which
	have been selected to be deleted get deleted.*/

	if(!message) m_deleter->deleteMessages();
	else {
	
		Fedge *fedge = static_cast<Fedge*>(KApplication::kApplication()->mainWidget());

		qWarning("no: %d, crc: %d, sender:%s, subject:%s", 
			message->number(), 
			message->crc(), 
			message->sender().latin1(), 
			message->subject().latin1());
	
		FedgeBalloon *balloon = new FedgeBalloon(message);
		balloon->setAnchor(fedge->systemTray()->mapToGlobal(QPoint(0, 0)));
		connect(balloon, SIGNAL(del(Message*)), SLOT(slotDelete(Message*)));
		connect(balloon, SIGNAL(ignore(Message*)), SLOT(slotIgnore(Message*)));
		connect(balloon, SIGNAL(open(Message*)), SLOT(slotOpen(Message*)));
	
		balloon->show();
	}
}
