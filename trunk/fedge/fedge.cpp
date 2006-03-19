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

#include "kmailfetcher.h"
#include "fedgeballoon.h"
#include "kmaildeleter.h"
#include "message.h"
#include "fedgeconfig.h"
#include "configgeneraloptions.h"

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
		
	m_fetcher = new KmailFetcher(&m_crctable);
	connect(m_fetcher, SIGNAL(fetchFinished()), SLOT(slotFetchFinished()));	

	m_deleter = new KmailDeleter(&m_crctable);
	connect(m_deleter, SIGNAL(deleteFinished()), SLOT(slotDeleteFinished()));	

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), SLOT(slotTimeout()));
	m_timer->start(30000);
	
	m_busy = false;
	slotTimeout();
		
// 	slotMessage(new Message("langer namexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", "langes subject"));
// 	slotMessage(new Message("name", "subject"));
}

Fedge::~Fedge() { }

void Fedge::slotFetchFinished() {

	showMessage(m_fetcher->popMessage());
}

void Fedge::slotDeleteFinished() {

	m_busy = false;
}

void Fedge::slotTimeout() {
	
	/* if the busy flag is unset, the messages are fetched and the 
	busy flag is set. */

	if (!m_busy) {

		m_fetcher->fetchMessages();
		m_busy = true;
	}
}

void Fedge::showMessage(Message *message) {

	/* When there are no more messages to be shown, the busy flag is unset and
	the method returns. */
	
	if(!message) {

		m_deleter->deleteMessages();
		return;
	}
	
	qWarning("no: %d, crc: %d, sender:%s, subject:%s", 
		message->getNumber(), 
		message->getCrc(), 
		message->getSender().latin1(), 
		message->getSubject().latin1());

	FedgeBalloon *balloon = new FedgeBalloon(message);
	balloon->setAnchor(m_systemtray->mapToGlobal(QPoint(0, 0)));//m_systemtray->pos());
	connect(balloon, SIGNAL(del(Message*)), SLOT(slotDelete(Message*)));
	connect(balloon, SIGNAL(ignore(Message*)), SLOT(slotIgnore(Message*)));

	balloon->show();
}

void Fedge::slotIgnore(Message *message) {

	/* The message gets deleted, as its of no use anymore, 
	then the next message on the fetchers stack is popped. */

	delete message;
	showMessage(m_fetcher->popMessage());
}

void Fedge::slotDelete(Message *message) {
 
 	m_deleter->pushMessage(message);
	showMessage(m_fetcher->popMessage());
}

/*!
    \fn Fedge::slotShowConfigure()
 */
void Fedge::slotShowConfigure()
{
	KConfigDialog* dialog = new KConfigDialog(0, "settings", FedgeConfig::self(), KDialogBase::IconList,
                KDialogBase::Ok | KDialogBase::Apply | KDialogBase::Cancel );
	dialog->addPage(new ConfigGeneralOptions(0, i18n("General")), i18n("General"), "fedge");
	dialog->show();
// 	 connect(dialog, SIGNAL(settingsChanged()), this, SLOT(slotApplyConfig()));
}

void Fedge::saveSettings()
{
	FedgeConfig::writeConfig();
}

#include "fedge.moc"