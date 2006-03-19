//
// C++ Interface: kmaildeleter
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef KMAILDELETER_H
#define KMAILDELETER_H

#include <qstring.h>

#include <pop3deleter.h>

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class KmailDeleter : public Pop3Deleter
{
	Q_OBJECT
public:
    KmailDeleter(QValueList<Q_UINT16> *crctable);

    ~KmailDeleter();
private:
	QString kurlBase();

};

#endif
