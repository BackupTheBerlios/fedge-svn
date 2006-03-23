/*
 * fedge.cpp
 *
 * Copyright (C) 2004 mkulke <magnus.kulke@radicalapproach.de>
 */

#include <kprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qtimer.h>

#include <kdeversion.h>
#include <kglobal.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kmenubar.h>
#include <kstatusbar.h>
#include <kaccel.h>
#include <kio/netaccess.h>
#include <kfiledialog.h>
#include <kconfig.h>
#include <kurl.h>
#include <kurldrag.h>
#include <kurlrequesterdlg.h>
#include <kedittoolbar.h>
#include <kstdaccel.h>
#include <kaction.h>
#include <kstdaction.h>
#include <kio/job.h>
#include <kio/global.h>
#include <kmessagebox.h>
#include <ksystemtray.h>
#include <kconfigdialog.h>
#include <kpopupmenu.h>
#include <kiconloader.h>

#include "fedge.h"

#include "fetcher.h"
#include "opener.h"
#include "deleter.h"
#include "kmailaccount.h"
#include "fedgeballoon.h"
#include "message.h"
#include "fedgeconfig.h"
#include "configgeneraloptions.h"
#include "configaccounts.h"

Fedge::Fedge() : KMainWindow(0, "fedge")
{
// 	FedgeConfig::setShowErrorDialogs(false); 
// 	FedgeConfig::writeConfig(); 



    // accept dnd
    //setAcceptDrops(true);

    // tell the KMainWindow that this is indeed the main widget
    //setCentralWidget(m_view);

    // then, setup our actions
    //setupActions();

    // Add typical actions and save size/toolbars/statusbar
    //setupGUI();

    // allow the view to change the statusbar and caption
//     connect(m_view, SIGNAL(signalChangeStatusbar(const QString&)), SLOT(changeStatusbar(const QString&)));
//     connect(m_view, SIGNAL(signalChangeCaption(const QString&)), SLOT(changeCaption(const QString&)));

	m_systemtray = new KSystemTray(this);
	m_systemtray->setPixmap(KSystemTray::loadIcon("fedge"));
	m_systemtray->contextMenu()->insertItem(
		KIconLoader().loadIcon("configure", KIcon::Small), "Configure fedge", this, SLOT(slotShowConfigure()));
	m_systemtray->show();

	/*The fetcher is created, its message signal is connected
	to a class method. the messages are then fetched. */
		
	m_account = new KmailAccount();
	connect(m_account->fetcher(), SIGNAL(fetchFinished()), SLOT(slotFetchFinished()));	
	connect(m_account->deleter(), SIGNAL(deleteFinished()), SLOT(slotDeleteFinished()));	
	connect(m_account->opener(), SIGNAL(openFinished()), SLOT(slotOpenFinished()));	

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), SLOT(slotTimeout()));
	m_timer->start(30000);
}

Fedge::~Fedge() { }

void Fedge::slotFetchFinished() {

	showMessage(m_account->fetcher()->popMessage());
}

void Fedge::slotDeleteFinished() {

	m_account->setReady(true);
}

void Fedge::slotOpenFinished() {

	m_account->setReady(true);
}

void Fedge::slotTimeout() {
	
	/* if the busy flag is unset, the messages are fetched and the 
	busy flag is set. */

	if (m_account->ready()) {

		m_account->fetcher()->fetchMessages();
		m_account->setReady(false);
	}
}

void Fedge::showMessage(Message *message) {

	/* When there are no more messages to be shown, the messages which
	have been selected to be deleted get deleted.*/

	if(!message) m_account->deleter()->deleteMessages();
	else {
	
		qWarning("no: %d, crc: %d, sender:%s, subject:%s", 
			message->number(), 
			message->crc(), 
			message->sender().latin1(), 
			message->subject().latin1());
	
		FedgeBalloon *balloon = new FedgeBalloon(message);
		balloon->setAnchor(m_systemtray->mapToGlobal(QPoint(0, 0)));//m_systemtray->pos());
		connect(balloon, SIGNAL(del(Message*)), SLOT(slotDelete(Message*)));
		connect(balloon, SIGNAL(ignore(Message*)), SLOT(slotIgnore(Message*)));
		connect(balloon, SIGNAL(open(Message*)), SLOT(slotOpen(Message*)));
	
		balloon->show();
	}
}

void Fedge::slotIgnore(Message *message) {

	/* The message gets deleted, as its of no use anymore, 
	then the next message on the fetchers stack is popped. */

	delete message;
	showMessage(m_account->fetcher()->popMessage());
}

void Fedge::slotDelete(Message *message) {
 
 	m_account->deleter()->pushMessage(message);
	showMessage(m_account->fetcher()->popMessage());
}

/*!
    \fn Fedge::slotShowConfigure()
 */
void Fedge::slotShowConfigure()
{
	KConfigDialog* dialog = new KConfigDialog(0, "settings", FedgeConfig::self(), KDialogBase::IconList,
                KDialogBase::Ok | KDialogBase::Apply | KDialogBase::Cancel );
	dialog->addPage(new ConfigGeneralOptions(0, i18n("General")), i18n("General"), "fedge");
	dialog->addPage(new ConfigAccounts(0, i18n("Accounts")), i18n("Accounts"), "identity");
	dialog->show();
// 	 connect(dialog, SIGNAL(settingsChanged()), this, SLOT(slotApplyConfig()));
}

void Fedge::saveSettings()
{
	FedgeConfig::writeConfig();
}

#include "fedge.moc"

/*!
    \fn Fedge::slotOpen(Message *message)
 */
void Fedge::slotOpen(Message *message)
{
    /* Delete the crc table, the messages on the delete and the fetchstack. */
 
	if (m_account->opener()->open()) m_account->clearMessages();
	else m_account->setReady(true);
}
