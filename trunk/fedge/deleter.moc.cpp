/****************************************************************************
** Deleter meta object code from reading C++ file 'deleter.h'
**
** Created: Thu Mar 16 04:34:02 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "deleter.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Deleter::className() const
{
    return "Deleter";
}

QMetaObject *Deleter::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Deleter( "Deleter", &Deleter::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Deleter::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Deleter", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Deleter::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Deleter", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Deleter::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Deleter", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Deleter.setMetaObject( metaObj );
    return metaObj;
}

void* Deleter::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Deleter" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool Deleter::qt_invoke( int _id, QUObject* _o )
{
    return QObject::qt_invoke(_id,_o);
}

bool Deleter::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Deleter::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool Deleter::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
