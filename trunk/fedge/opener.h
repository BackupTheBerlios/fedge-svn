#ifndef OPENER_H
#define OPENER_H

#include <qobject.h>

class Opener : public QObject {
	Q_OBJECT
public:
	Opener() {};
	virtual bool open() = 0;
 
signals:
	void openFinished();
};

#endif // OPENER_H
