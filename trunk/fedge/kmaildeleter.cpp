//
// C++ Implementation: kmaildeleter
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "fedgeconfig.h"

#include "kmaildeleter.h"

KmailDeleter::KmailDeleter(QValueList<Q_UINT16> *crctable)
 : Pop3Deleter(crctable)
{
}

KmailDeleter::~KmailDeleter()
{
}

QString KmailDeleter::kurlBase() {

	return FedgeConfig::kurl();
}