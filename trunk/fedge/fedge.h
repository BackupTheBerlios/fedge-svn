#ifndef FEDGE_H
#define FEDGE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qvaluelist.h>

#include <kapplication.h>
#include <kmainwindow.h>

#include <kio/global.h>

class KURL;
class Fetcher;
class Deleter;
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
		void slotDelete(Message *message);
		void slotIgnore(Message *message);		

private:
	void setupAccel();
	void setupActions();
	void showMessage(Message *message);

private:
		
	Deleter *m_deleter;
	Fetcher *m_fetcher;
	QTimer		*m_timer;
	KSystemTray *m_systemtray;
	bool m_busy;
	QValueList<Q_UINT16> m_crctable;
public slots:
    void slotShowConfigure();
};

#endif // FEDGE_H
