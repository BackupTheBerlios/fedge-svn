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

#include <fetcher.h>
#include <deleter.h>

#include "account.h"

Account::Account(QString name)
{
	m_name = name;
}


Account::~Account()
{
}

void Account::clearMessages() {

	m_crctable.clear();
	m_deleter->clearMessages();
	m_fetcher->clearMessages();
}