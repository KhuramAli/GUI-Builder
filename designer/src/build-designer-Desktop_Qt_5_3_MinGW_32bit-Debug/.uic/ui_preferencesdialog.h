/********************************************************************************
** Form generated from reading UI file 'preferencesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *m_optionTabWidget;
    QWidget *tab_2;
    QDialogButtonBox *m_dialogButtonBox;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QStringLiteral("PreferencesDialog"));
        PreferencesDialog->resize(474, 304);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDialog->sizePolicy().hasHeightForWidth());
        PreferencesDialog->setSizePolicy(sizePolicy);
        PreferencesDialog->setModal(true);
        verticalLayout = new QVBoxLayout(PreferencesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_optionTabWidget = new QTabWidget(PreferencesDialog);
        m_optionTabWidget->setObjectName(QStringLiteral("m_optionTabWidget"));
        sizePolicy.setHeightForWidth(m_optionTabWidget->sizePolicy().hasHeightForWidth());
        m_optionTabWidget->setSizePolicy(sizePolicy);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        m_optionTabWidget->addTab(tab_2, QString());
        m_optionTabWidget->setTabText(m_optionTabWidget->indexOf(tab_2), QStringLiteral("Tab 1"));

        verticalLayout->addWidget(m_optionTabWidget);

        m_dialogButtonBox = new QDialogButtonBox(PreferencesDialog);
        m_dialogButtonBox->setObjectName(QStringLiteral("m_dialogButtonBox"));
        m_dialogButtonBox->setOrientation(Qt::Horizontal);
        m_dialogButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Apply|QDialogButtonBox::Ok);

        verticalLayout->addWidget(m_dialogButtonBox);


        retranslateUi(PreferencesDialog);
        QObject::connect(m_dialogButtonBox, SIGNAL(accepted()), PreferencesDialog, SLOT(accept()));
        QObject::connect(m_dialogButtonBox, SIGNAL(rejected()), PreferencesDialog, SLOT(reject()));

        m_optionTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
