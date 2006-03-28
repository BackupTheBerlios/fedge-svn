/*
 * fedge.cpp
 *
 * Copyright (C) 2004 mkulke <magnus.kulke@radicalapproach.de>
 */

#include <kprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qtimer.h>
#include <qstringlist.h>

#include <kdeversion.h>
#include <kglobal.h>
#include <klocale.h>
#include <kmenubar.h>
#include <ksystemtray.h>
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
#include <kpopupmenu.h>
#include <kiconloader.h>

#include "fedge.h"

#include "fetcher.h"
#include "opener.h"
#include "deleter.h"
#include "kmailaccount.h"
#include "fedgeconfig.h"
#include "configgeneraloptions.h"
#include "fedgeconfigaccounts.h"
#include "fedgeconfigdialog.h"

#include <fedgeselectdialog.h>

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
		
// 	m_accounts.append(new KmailAccount("Account 1"));

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), SLOT(slotTimeout()));

	slotApplyConfig();
}

Fedge::~Fedge() { }

void Fedge::slotApplyConfig() {

	qWarning("slotApplyConfig() called");

	m_timer->changeInterval(FedgeConfig::fetchInterval() * 1000);

	KConfig config("fedgerc", true);
	QMap<QString, QString> configmap;
	int i = 0;

	m_accounts.clear();

	while (config.hasGroup("Account " + QString::number(i))) {

		configmap = config.entryMap("Account " + QString::number(i));	
		if (configmap["name"] = "KMail") {

			KmailAccount *account = new KmailAccount(configmap["accountname"]);
			account->setEnabled(configmap["enabled"] == "true");
			m_accounts.append(account);
		}
		i++;
	}	
}

void Fedge::slotTimeout() {
	
	/* if the busy flag is unset, the messages are fetched and the 
	busy flag is set. */

	Account *account;
	for (account = m_accounts.first(); account; account = m_accounts.next()) {

		if (account->ready()) {

			account->fetcher()->fetchMessages();
			account->setReady(false);
		}
	}
}

/*!
    \fn Fedge::slotShowConfigure()
 */
void Fedge::slotShowConfigure()
{
 	FedgeConfigDialog *dialog = new FedgeConfigDialog(&m_accounts);
	connect(dialog, SIGNAL(settingsChanged()), SLOT(slotLoadAccounts()));
 	dialog->show();
}

// void Fedge::saveSettings()
// {
// // 	FedgeConfig::writeConfig();
// }

#include "fedge.moc"
