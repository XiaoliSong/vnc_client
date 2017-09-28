/********************************************************************************
** Form generated from reading UI file 'QtVnc.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTVNC_H
#define UI_QTVNC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QtVncClass
{
public:

    void setupUi(QDialog *QtVncClass)
    {
        if (QtVncClass->objectName().isEmpty())
            QtVncClass->setObjectName(QStringLiteral("QtVncClass"));
        QtVncClass->resize(600, 400);

        retranslateUi(QtVncClass);

        QMetaObject::connectSlotsByName(QtVncClass);
    } // setupUi

    void retranslateUi(QDialog *QtVncClass)
    {
        QtVncClass->setWindowTitle(QApplication::translate("QtVncClass", "QtVnc", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtVncClass: public Ui_QtVncClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTVNC_H
