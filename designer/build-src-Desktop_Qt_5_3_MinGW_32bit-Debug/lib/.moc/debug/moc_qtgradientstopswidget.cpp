/****************************************************************************
** Meta object code from reading C++ file 'qtgradientstopswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../shared/qtgradienteditor/qtgradientstopswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtgradientstopswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtGradientStopsWidget_t {
    QByteArrayData data[26];
    char stringdata[321];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtGradientStopsWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtGradientStopsWidget_t qt_meta_stringdata_QtGradientStopsWidget = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 11),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 4),
QT_MOC_LITERAL(4, 40, 13),
QT_MOC_LITERAL(5, 54, 15),
QT_MOC_LITERAL(6, 70, 4),
QT_MOC_LITERAL(7, 75, 15),
QT_MOC_LITERAL(8, 91, 13),
QT_MOC_LITERAL(9, 105, 6),
QT_MOC_LITERAL(10, 112, 16),
QT_MOC_LITERAL(11, 129, 5),
QT_MOC_LITERAL(12, 135, 5),
QT_MOC_LITERAL(13, 141, 15),
QT_MOC_LITERAL(14, 157, 8),
QT_MOC_LITERAL(15, 166, 16),
QT_MOC_LITERAL(16, 183, 8),
QT_MOC_LITERAL(17, 192, 22),
QT_MOC_LITERAL(18, 215, 11),
QT_MOC_LITERAL(19, 227, 10),
QT_MOC_LITERAL(20, 238, 11),
QT_MOC_LITERAL(21, 250, 13),
QT_MOC_LITERAL(22, 264, 10),
QT_MOC_LITERAL(23, 275, 11),
QT_MOC_LITERAL(24, 287, 13),
QT_MOC_LITERAL(25, 301, 19)
    },
    "QtGradientStopsWidget\0zoomChanged\0\0"
    "zoom\0slotStopAdded\0QtGradientStop*\0"
    "stop\0slotStopRemoved\0slotStopMoved\0"
    "newPos\0slotStopsSwapped\0stop1\0stop2\0"
    "slotStopChanged\0newColor\0slotStopSelected\0"
    "selected\0slotCurrentStopChanged\0"
    "slotNewStop\0slotDelete\0slotFlipAll\0"
    "slotSelectAll\0slotZoomIn\0slotZoomOut\0"
    "slotResetZoom\0backgroundCheckered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtGradientStopsWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       1,  128, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   92,    2, 0x08 /* Private */,
       7,    1,   95,    2, 0x08 /* Private */,
       8,    2,   98,    2, 0x08 /* Private */,
      10,    2,  103,    2, 0x08 /* Private */,
      13,    2,  108,    2, 0x08 /* Private */,
      15,    2,  113,    2, 0x08 /* Private */,
      17,    1,  118,    2, 0x08 /* Private */,
      18,    0,  121,    2, 0x08 /* Private */,
      19,    0,  122,    2, 0x08 /* Private */,
      20,    0,  123,    2, 0x08 /* Private */,
      21,    0,  124,    2, 0x08 /* Private */,
      22,    0,  125,    2, 0x08 /* Private */,
      23,    0,  126,    2, 0x08 /* Private */,
      24,    0,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QReal,    6,    9,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,   11,   12,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QColor,    6,   14,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Bool,    6,   16,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      25, QMetaType::Bool, 0x00095103,

       0        // eod
};

void QtGradientStopsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtGradientStopsWidget *_t = static_cast<QtGradientStopsWidget *>(_o);
        switch (_id) {
        case 0: _t->zoomChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->d_func()->slotStopAdded((*reinterpret_cast< QtGradientStop*(*)>(_a[1]))); break;
        case 2: _t->d_func()->slotStopRemoved((*reinterpret_cast< QtGradientStop*(*)>(_a[1]))); break;
        case 3: _t->d_func()->slotStopMoved((*reinterpret_cast< QtGradientStop*(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 4: _t->d_func()->slotStopsSwapped((*reinterpret_cast< QtGradientStop*(*)>(_a[1])),(*reinterpret_cast< QtGradientStop*(*)>(_a[2]))); break;
        case 5: _t->d_func()->slotStopChanged((*reinterpret_cast< QtGradientStop*(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 6: _t->d_func()->slotStopSelected((*reinterpret_cast< QtGradientStop*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->d_func()->slotCurrentStopChanged((*reinterpret_cast< QtGradientStop*(*)>(_a[1]))); break;
        case 8: _t->d_func()->slotNewStop(); break;
        case 9: _t->d_func()->slotDelete(); break;
        case 10: _t->d_func()->slotFlipAll(); break;
        case 11: _t->d_func()->slotSelectAll(); break;
        case 12: _t->d_func()->slotZoomIn(); break;
        case 13: _t->d_func()->slotZoomOut(); break;
        case 14: _t->d_func()->slotResetZoom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtGradientStopsWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtGradientStopsWidget::zoomChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QtGradientStopsWidget::staticMetaObject = {
    { &QAbstractScrollArea::staticMetaObject, qt_meta_stringdata_QtGradientStopsWidget.data,
      qt_meta_data_QtGradientStopsWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *QtGradientStopsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtGradientStopsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtGradientStopsWidget.stringdata))
        return static_cast<void*>(const_cast< QtGradientStopsWidget*>(this));
    return QAbstractScrollArea::qt_metacast(_clname);
}

int QtGradientStopsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = isBackgroundCheckered(); break;
        default: break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBackgroundCheckered(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QtGradientStopsWidget::zoomChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
