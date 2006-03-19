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

    // register ourselves as a dcop client
//     app.dcopClient()->registerAs(app.name(), false);

    // see if we are starting with session management
//     if (app.isRestored())
//         RESTORE(fedge)
//     else
//     {
        // no session.. just start up normally
//         KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
//         if (args->count() == 0)
//         {
//             fedge *widget = new fedge;
            //widget->show();
//         }
//         else
//         {
//             int i = 0;
//             for (; i < args->count(); i++)
//             {
						new Fedge();
//                 fedge *widget = new fedge;
//                 widget->show();
//                 widget->load(args->url(i));
//             }
//         }
//         args->clear();
//     }

    return app.exec();
}
