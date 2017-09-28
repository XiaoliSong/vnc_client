/********************************************************************************
** Form generated from reading UI file 'vnc_client.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VNC_CLIENT_H
#define UI_VNC_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_vnc_clientClass
{
public:

    void setupUi(QDialog *vnc_clientClass)
    {
        if (vnc_clientClass->objectName().isEmpty())
            vnc_clientClass->setObjectName(QStringLiteral("vnc_clientClass"));
        vnc_clientClass->resize(600, 400);

        retranslateUi(vnc_clientClass);

        QMetaObject::connectSlotsByName(vnc_clientClass);
    } // setupUi

    void retranslateUi(QDialog *vnc_clientClass)
    {
        vnc_clientClass->setWindowTitle(QApplication::translate("vnc_clientClass", "vnc_client", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class vnc_clientClass: public Ui_vnc_clientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VNC_CLIENT_H
