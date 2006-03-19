/*
    fedgeballoon.cpp  -  Nice Balloon

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

#include <qpointarray.h>
#include <qpushbutton.h>
#include <qtooltip.h>
#include <qlayout.h>
#include <qtimer.h>
#include <qlabel.h>
#include <qpainter.h>

#include <kdeversion.h>
#include <kglobalsettings.h>

#include <kapplication.h>
#include <kdialog.h>
#include <klocale.h>

#include "message.h"
#include "fedgeballoon.h"

FedgeBalloon::FedgeBalloon(Message *message)
: QWidget(0L, "FedgeBalloon", WStyle_StaysOnTop | WStyle_Customize |
	WStyle_NoBorder | WStyle_Tool | WX11BypassWM)
{
	setCaption("");

	m_message = message;

	QString text = i18n("From:") + message->getSender() + "\n" + i18n("Subject:") + message->getSubject();

	QVBoxLayout *BalloonLayout = new QVBoxLayout(this, 22, KDialog::spacingHint(), "BalloonLayout");

	QLabel *header = new QLabel(i18n("New Mail arrived:"), this);
	QFont headerfont = header->font();
	headerfont.setBold(true);
	header->setFont(headerfont);

	// BEGIN Layout0
	QHBoxLayout *Layout0 = new QHBoxLayout(BalloonLayout,
		KDialog::spacingHint(), "Layout0");
	Layout0->addItem(new QSpacerItem(10,0));
	Layout0->addWidget(header);
	Layout0->addStretch();
	Layout0->addItem(new QSpacerItem(10,0));
	// END  Layout0

	// BEGIN Layout1
	QHBoxLayout *Layout1 = new QHBoxLayout(BalloonLayout,
		KDialog::spacingHint(), "Layout1");
	QLabel *mCaption = new QLabel(text, this, "mCaption");
	mCaption->setPalette(QToolTip::palette());
	mCaption->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

	Layout1->addItem(new QSpacerItem(10,0));
	Layout1->addWidget(mCaption);
	Layout1->addItem(new QSpacerItem(10,0));
	// END Layout1

	// BEGIN Layout2
	QHBoxLayout *Layout2 = new QHBoxLayout(BalloonLayout,
		KDialog::spacingHint(), "Layout2");
	QPushButton *mOpenButton = new QPushButton(i18n("Open"), this,
		"mViewButton");
	QPushButton *mIgnoreButton = new QPushButton(i18n("Ignore"), this,
		"mIgnoreButton");
	QPushButton *mDeleteButton = new QPushButton(i18n("Delete"), this,
		"mDeleteButton");

	Layout2->addItem(new QSpacerItem(10,0));
	Layout2->addStretch();
	Layout2->addWidget(mOpenButton);
	Layout2->addWidget(mIgnoreButton);
	Layout2->addWidget(mDeleteButton);
	Layout2->addStretch();
	Layout2->addItem(new QSpacerItem(10,0));
	// END Layout2
	
	setPalette(QToolTip::palette());
	setAutoMask(TRUE);

	connect(mOpenButton, SIGNAL(clicked()), SLOT(slotOpen()));
	connect(mOpenButton, SIGNAL(clicked()), SLOT(deleteLater()));
	connect(mDeleteButton, SIGNAL(clicked()), SLOT(slotDel()));
	connect(mDeleteButton, SIGNAL(clicked()), SLOT(deleteLater()));
	connect(mIgnoreButton, SIGNAL(clicked()), SLOT(slotIgnore()));
	connect(mIgnoreButton, SIGNAL(clicked()), SLOT(deleteLater()));
}

void FedgeBalloon::slotOpen() {

	emit open(m_message);
}

void FedgeBalloon::slotDel() {

	emit del(m_message);
}

void FedgeBalloon::slotIgnore() {

	emit ignore(m_message);
}

void FedgeBalloon::setAnchor(const QPoint &anchor)
{
	mAnchor = anchor;
	updateMask();
}

void FedgeBalloon::updateMask()
{	
	QPointArray box(4);
	box.setPoint(0, 0, 0);
	box.setPoint(1, width()+10, 0);
	box.setPoint(2, width()+10, height());
	box.setPoint(3, 0, height());
	
	QRegion mask(20, 10, width() - 40, height() - 20);
	
	QRect deskRect = KGlobalSettings::desktopGeometry(mAnchor);

	bool bottom = (mAnchor.y() + height()) > ((deskRect.y() + deskRect.height()-48));
	bool right = (mAnchor.x() + width()) > ((deskRect.x() + deskRect.width()-48));
	
	QPointArray arrow(4);

	arrow.setPoint(0, QPoint(right ? width() - 20 : 20, bottom ? height() - 30 : 30));
	arrow.setPoint(1, QPoint(right ? width() - 4 : 4, bottom ? height() - 22 : 22));
	arrow.setPoint(2, QPoint(right ? width() - 4 : 4, bottom ? height() - 20 : 21));	
	arrow.setPoint(3, QPoint(right ? width() - 20 : 20, bottom ? height() - 20 : 21));
	mask += arrow;

	move( right ? mAnchor.x() - width() : ( mAnchor.x() < 0 ? 0 : mAnchor.x() ),
 	bottom ? mAnchor.y() - height() + 30 : ( mAnchor.y() < 0 ? 0 : mAnchor.y() ));
	
	setMask(mask);
}

void FedgeBalloon::paintEvent(QPaintEvent * e) {
		
	QRect deskRect = KGlobalSettings::desktopGeometry(mAnchor);

	bool bottom = (mAnchor.y() + height()) > ((deskRect.y() + deskRect.height()-48));
	bool right = (mAnchor.x() + width()) > ((deskRect.x() + deskRect.width()-48));
	
	QPainter paint(this);
	paint.drawLine(20, 10, width() - 21, 10);
	paint.drawLine(right ? width() - 21 : 20, bottom ? height() - 30 : 30, 
		right ? width() - 21 : 20, bottom ? 10 : height() - 10);  
	paint.drawLine(right ? width() - 4 : 3, bottom ? height() - 21 : 21, 
		right ? width() - 21 : 20, bottom ? height() - 30 : 30);
	paint.drawLine(right ? width() - 4 : 3, bottom ? height() - 21 : 21, 
		right ? width() - 21 : 20, bottom ? height() - 21 : 21);
	paint.drawLine(right ? width() - 21 : 20, bottom ? height() - 21 : 20, 
		right ? width() - 21 : 20, bottom ? height() - 11 : 11);
	paint.drawLine(width() - 21, height() - 11, 21, height() - 11);	
	paint.drawLine(right ? 20 : width() - 21, height() - 11, 
		right ? 20 : width() - 21, 10);
}

#include "fedgeballoon.moc"
// vim: set noet ts=4 sts=4 sw=4:
