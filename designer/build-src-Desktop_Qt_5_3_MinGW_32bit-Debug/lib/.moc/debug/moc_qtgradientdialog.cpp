/****************************************************************************
** Meta object code from reading C++ file 'qtgradientdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../shared/qtgradienteditor/qtgradientdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtgradientdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtGradientDialog_t {
    QByteArrayData data[10];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtGradientDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtGradientDialog_t qt_meta_stringdata_QtGradientDialog = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 22),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 7),
QT_MOC_LITERAL(4, 49, 18),
QT_MOC_LITERAL(5, 68, 8),
QT_MOC_LITERAL(6, 77, 9),
QT_MOC_LITERAL(7, 87, 19),
QT_MOC_LITERAL(8, 107, 14),
QT_MOC_LITERAL(9, 122, 20)
    },
    "QtGradientDialog\0slotAboutToShowDetails\0"
    "\0details\0extensionWidthHint\0gradient\0"
    "QGradient\0backgroundCheckered\0"
    "detailsVisible\0detailsButtonVisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtGradientDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       4,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    3,    4,

 // properties: name, type, flags
       5, 0x80000000 | 6, 0x0009510b,
       7, QMetaType::Bool, 0x00095103,
       8, QMetaType::Bool, 0x00095103,
       9, QMetaType::Bool, 0x00095103,

       0        // eod
};

void QtGradientDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtGradientDialog *_t = static_cast<QtGradientDialog *>(_o);
        switch (_id) {
        case 0: _t->d_func()->slotAboutToShowDetails((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject QtGradientDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtGradientDialog.data,
      qt_meta_data_QtGradientDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *QtGradientDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtGradientDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtGradientDialog.stringdata))
        return static_cast<void*>(const_cast< QtGradientDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtGradientDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QGradient*>(_v) = gradient(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isBackgroundCheckered(); break;
        case 2: *reinterpret_cast< bool*>(_v) = detailsVisible(); break;
        case 3: *reinterpret_cast< bool*>(_v) = isDetailsButtonVisible(); break;
        default: break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setGradient(*reinterpret_cast< QGradient*>(_v)); break;
        case 1: setBackgroundCheckered(*reinterpret_cast< bool*>(_v)); break;
        case 2: setDetailsVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: setDetailsButtonVisible(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
