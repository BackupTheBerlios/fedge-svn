//
// C++ Interface: pop3common
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef POP3COMMON_H
#define POP3COMMON_H

#include <qstring.h>
#include <qmap.h>
#include <kio/job.h>

/**
	@author mkulke <magnus.kulke@radicalapproach.de>
*/
class Pop3Common{
public:
    Pop3Common();

    ~Pop3Common();

	static void setMetaData(QMap<QString, QString> *configmap, KIO::Job *job);
	static QString kurlBase(QMap<QString, QString> *configmap);
};

#endif
