#ifndef FEDGE_H
#define FEDGE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qptrlist.h>

#include <kapplication.h>
#include <kmainwindow.h>

class Account;
class QTimer;
class KSystemTray;
class KListBox;
class Message;
class FedgeLogBox;

/**
 * This class serves as the main window for fedge.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author mkulke <magnus.kulke@radicalapproach.de>
 * @version 0.1
 */
class Fedge : public KMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    Fedge();

    /**
     * Default Destructor
     */
    virtual ~Fedge();

    /**
     * Use this method to load whatever file/URL you have
     */
//     void load(const KURL& url);
	KSystemTray* systemTray() { return m_systemtray; };

private slots:
	
	void slotTimeout();
	void slotApplyConfig();
	void slotShowConfigure();	
	void slotLog(QString l);

private:
	void setupAccel();
	void setupActions();
	
private:
		
	KListBox *m_logbox;
	QPtrList<Account> m_accounts;
	QTimer		*m_timer;
	KSystemTray *m_systemtray;
};

#endif // FEDGE_H
