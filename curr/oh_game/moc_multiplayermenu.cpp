/****************************************************************************
** Meta object code from reading C++ file 'multiplayermenu.h'
**
** Created: Thu Aug 9 18:13:16 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widgets/multiplayermenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multiplayermenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultiplayerMenu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      28,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   16,   16,   16, 0x0a,
      53,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MultiplayerMenu[] = {
    "MultiplayerMenu\0\0mainMenu()\0mpConnected()\0"
    "ipdialog()\0connectBySettings()\0"
};

const QMetaObject MultiplayerMenu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MultiplayerMenu,
      qt_meta_data_MultiplayerMenu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultiplayerMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultiplayerMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultiplayerMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultiplayerMenu))
        return static_cast<void*>(const_cast< MultiplayerMenu*>(this));
    return QWidget::qt_metacast(_clname);
}

int MultiplayerMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mainMenu(); break;
        case 1: mpConnected(); break;
        case 2: ipdialog(); break;
        case 3: connectBySettings(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MultiplayerMenu::mainMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MultiplayerMenu::mpConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
