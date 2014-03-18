/****************************************************************************
** Meta object code from reading C++ file 'scissor_diag.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scissor_diag.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scissor_diag.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_scissor_diag_t {
    QByteArrayData data[13];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_scissor_diag_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_scissor_diag_t qt_meta_stringdata_scissor_diag = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 16),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 13),
QT_MOC_LITERAL(4, 45, 13),
QT_MOC_LITERAL(5, 59, 13),
QT_MOC_LITERAL(6, 73, 12),
QT_MOC_LITERAL(7, 86, 11),
QT_MOC_LITERAL(8, 98, 5),
QT_MOC_LITERAL(9, 104, 7),
QT_MOC_LITERAL(10, 112, 8),
QT_MOC_LITERAL(11, 121, 5),
QT_MOC_LITERAL(12, 127, 14)
    },
    "scissor_diag\0sc_image_contour\0\0"
    "sc_image_only\0sc_pixel_node\0sc_cost_graph\0"
    "sc_path_tree\0sc_min_path\0sc_OK\0sc_snap\0"
    "sc_brush\0cs_cf\0sc_change_blur\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_scissor_diag[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08,
       3,    0,   70,    2, 0x08,
       4,    0,   71,    2, 0x08,
       5,    0,   72,    2, 0x08,
       6,    0,   73,    2, 0x08,
       7,    0,   74,    2, 0x08,
       8,    0,   75,    2, 0x08,
       9,    0,   76,    2, 0x08,
      10,    0,   77,    2, 0x08,
      11,    0,   78,    2, 0x08,
      12,    0,   79,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void scissor_diag::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        scissor_diag *_t = static_cast<scissor_diag *>(_o);
        switch (_id) {
        case 0: _t->sc_image_contour(); break;
        case 1: _t->sc_image_only(); break;
        case 2: _t->sc_pixel_node(); break;
        case 3: _t->sc_cost_graph(); break;
        case 4: _t->sc_path_tree(); break;
        case 5: _t->sc_min_path(); break;
        case 6: _t->sc_OK(); break;
        case 7: _t->sc_snap(); break;
        case 8: _t->sc_brush(); break;
        case 9: _t->cs_cf(); break;
        case 10: _t->sc_change_blur(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject scissor_diag::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_scissor_diag.data,
      qt_meta_data_scissor_diag,  qt_static_metacall, 0, 0}
};


const QMetaObject *scissor_diag::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *scissor_diag::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_scissor_diag.stringdata))
        return static_cast<void*>(const_cast< scissor_diag*>(this));
    return QDialog::qt_metacast(_clname);
}

int scissor_diag::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
