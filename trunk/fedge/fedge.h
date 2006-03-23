#ifndef FEDGE_H
#define FEDGE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapplication.h>
#include <kmainwindow.h>

class Account;
class QTimer;
class KSystemTray;
class Message;

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

private:

	void saveSettings();

private slots:
	
	void slotTimeout();
	void slotFetchFinished();
	void slotDeleteFinished();
	void slotOpenFinished();
	void slotDelete(Message *message);
	void slotIgnore(Message *message);		
	void slotOpen(Message *message);

private:
	void setupAccel();
	void setupActions();
	void showMessage(Message *message);

private:
		
	Account *m_account;
	QTimer		*m_timer;
	KSystemTray *m_systemtray;
// 	bool m_busy;

public slots:
    void slotShowConfigure();
};

#endif // FEDGE_H
