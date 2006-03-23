//
// C++ Interface: appopener
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef APPOPENER_H
#define APPOPENER_H

#include <qstringlist.h>

#include <opener.h>

class KProcess;

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class AppOpener : public Opener
{
	Q_OBJECT
public:
    AppOpener(QStringList args);
    ~AppOpener();
	bool open();

public slots:	
	void slotKmailExited(KProcess *proc);

private:
	QStringList m_args;

};

#endif
