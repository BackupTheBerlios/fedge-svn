//
// C++ Implementation: appopener
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <kprocess.h>

#include "appopener.h"

AppOpener::AppOpener(QStringList args)
 : Opener()
{
	m_args = args;
}


AppOpener::~AppOpener()
{
}

bool AppOpener::open() {

   KProcess *proc = new KProcess();

	for (QStringList::Iterator it = m_args.begin(); it != m_args.end(); ++it ) *proc << *it;

	connect(proc, SIGNAL(processExited(KProcess *)), SLOT(slotKmailExited(KProcess *)));
   if (proc->start()) return true;
	else {

		qWarning("open: app start failed");

		delete proc;
		return false;
	}
}

void AppOpener::slotKmailExited(KProcess *proc) {

	qWarning("open: app exited");

	delete proc;
	emit openFinished();
}


