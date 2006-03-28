#include "fedge.h"
#include <kapplication.h>
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP("A KDE Application");

static const char version[] = "v0.1";

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("fedge", I18N_NOOP("fedge"), version, description, KAboutData::License_GPL, "(C) 2004 mkulke", 0, 0, "magnus.kulke@radicalapproach.de");
    about.addAuthor( "mkulke", 0, "magnus.kulke@radicalapproach.de" );
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;
	 app.setMainWidget(new Fedge());
    return app.exec();
}
