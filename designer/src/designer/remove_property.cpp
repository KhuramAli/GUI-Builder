#include "remove_property.h"
#include "flexview_properties.h"
#include "mainwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>


remove_property::remove_property(QWidget * parent):QDialog(parent)
{
    label       = new QLabel(tr("Select Property to Remove"));
    combobox    = new QComboBox;
    button      = new QPushButton(tr("Remove"));

    list = *DockedMainWindow::flex->getPropertyList();
    list.removeDuplicates();
    combobox->addItems(list);

    connect(button,SIGNAL(clicked()),this,SLOT(remove()));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(label);
    hbox->addWidget(combobox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox);
    vbox->addWidget(button);

    setLayout(vbox);
    setWindowTitle("Remove Property");
}

void remove_property::remove()
{
    if (combobox->currentText() != ""){
    DockedMainWindow::flex->removeProperties(combobox->currentText());
    DockedMainWindow::flex->removeProperties(combobox->currentText());
    combobox->removeItem(combobox->currentIndex());
    }
}
