//
// C++ Implementation: pop3common
//
// Description: 
//
//
// Author: mkulke <magnus.kulke@radicalapproach.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "pop3common.h"

Pop3Common::Pop3Common()
{
}


Pop3Common::~Pop3Common()
{
}

void Pop3Common::setMetaData(QMap<QString, QString> *configmap, KIO::Job *job) {

	job->addMetaData("auth", (*configmap)["auth"]);
	job->addMetaData("tls", ((*configmap)["use-tls"] == "true") ? "on" : "off");
	job->addMetaData("pipelining", ((*configmap)["pipelining"] == "true") ? "on" : "off");
}

QString Pop3Common::kurlBase(QMap<QString, QString> *configmap) {
	
	/* contruct the kurlbase from the configmap */

	QString prefix = ((*configmap)["use-ssl"] == "true") ? "pop3s://" : "pop3://";

	return prefix 
		+ (*configmap)["login"] 
		+ "@" 
		+ (*configmap)["host"] 
		+ ":" 
		+ (*configmap)["port"];
}


