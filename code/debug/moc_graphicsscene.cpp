/****************************************************************************
** Meta object code from reading C++ file 'graphicsscene.h'
**
** Created: Thu Oct 1 11:06:31 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../graphicsscene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicsscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphicsScene[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      45,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   74,   14,   14, 0x0a,
      93,   15,   14,   14, 0x0a,
     117,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphicsScene[] = {
    "GraphicsScene\0\0item\0itemInserted(Component*)\0"
    "itemSelected(QGraphicsItem*)\0mode\0"
    "setMode(Mode)\0addItem(QGraphicsItem*)\0"
    "removeItem(QGraphicsItem*)\0"
};

const QMetaObject GraphicsScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_GraphicsScene,
      qt_meta_data_GraphicsScene, 0 }
};

const QMetaObject *GraphicsScene::metaObject() const
{
    return &staticMetaObject;
}

void *GraphicsScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsScene))
        return static_cast<void*>(const_cast< GraphicsScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int GraphicsScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemInserted((*reinterpret_cast< Component*(*)>(_a[1]))); break;
        case 1: itemSelected((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 2: setMode((*reinterpret_cast< Mode(*)>(_a[1]))); break;
        case 3: addItem((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 4: removeItem((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GraphicsScene::itemInserted(Component * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphicsScene::itemSelected(QGraphicsItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
