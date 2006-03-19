/*
    fedgeballoon.h  -  Nice Balloon

    Copyright (c) 2002      by Duncan Mac-Vicar Prett <duncan@kde.org>

    Kopete    (c) 2002-2005      by the Kopete developers  <kopete-devel@kde.org>

    Portions of this code based on Kim Applet code
    Copyright (c) 2000-2002 by Malte Starostik        <malte@kde.org>

    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#ifndef FEDGEBALLOON_H
#define FEDGEBALLOON_H

#include <qwidget.h>
#include <kactivelabel.h>

class QPaintEvent;

/**
 * A little balloon for notifications
 *
 * @author Malte Starostik <malte@kde.org>
 * @author Duncan Mac-Vicar Prett <duncan@kde.org>
 */

class Message;

class FedgeBalloon : public QWidget
{
	Q_OBJECT

public:
	FedgeBalloon(Message *message);
//	FedgeBalloon();

	void setAnchor(const QPoint &anchor);
	void paintEvent(QPaintEvent * e);
	
public slots:
	void slotDel();
	void slotOpen();
	void slotIgnore();

signals:
	void del(Message*);
	void open(Message*);
	void ignore(Message*);
	void signalTimeout();

protected:
	virtual void updateMask();

private:
	QPoint mAnchor;
	Message *m_message;
};

#endif // FEDGEBALLOON_H
