/****************************************************************************
** Meta object code from reading C++ file 'paintable.h'
**
** Created: Fri Jun 12 01:26:59 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "paintable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_paintable[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      20,   10,   10,   10, 0x0a,
      30,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_paintable[] = {
    "paintable\0\0zoomIn()\0zoomOut()\0run()\0"
};

const QMetaObject paintable::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_paintable,
      qt_meta_data_paintable, 0 }
};

const QMetaObject *paintable::metaObject() const
{
    return &staticMetaObject;
}

void *paintable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_paintable))
        return static_cast<void*>(const_cast< paintable*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int paintable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: zoomIn(); break;
        case 1: zoomOut(); break;
        case 2: run(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
