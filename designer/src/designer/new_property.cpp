#include "new_property.h"
#include "mainwindow.h"

#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
#include<QPushButton>
#include<QListView>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QStringListModel>
#include<QInputDialog>

new_property::new_property(QWidget * parent):QDialog(parent)
{
    nameLabel = new QLabel(tr("Property Name"));
    nameText  = new QLineEdit;
    nameLabel->setBuddy(nameText);

    typeLabel = new QLabel(tr("Type"));
    type      = new QComboBox;
    typeLabel->setBuddy(type);

    type->addItem("string");
    type->addItem("bool");
    type->addItem("combobox");

    okButton = new QPushButton(tr("Add New Property"));

    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(nameLabel);
    hbox1->addWidget(nameText);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(typeLabel);
    hbox2->addWidget(type);

    QHBoxLayout *hbox3 = new QHBoxLayout;
    hbox3->addWidget(okButton);

    connect(okButton,SIGNAL(clicked()),this,SLOT(createProperty()));
    connect(type,SIGNAL(currentTextChanged(QString)),this,SLOT(comboItems()));

    layout = new QVBoxLayout;
    layout->addLayout(hbox1);
    layout->addLayout(hbox2);
    layout->addLayout(hbox3);

    setLayout(layout);

    input = new QInputDialog;
    setWindowTitle(tr("Add New Property"));

}

void new_property::createProperty()
{

    DockedMainWindow::flex->addProperty(nameText->text(),type->currentText(), stringlist);
}

void new_property::comboItems()
{
QString text;
    if (type->currentText() == "combobox")
    {

    text = input->getMultiLineText(this,tr("add combobox items"),tr("add items"));
    }
stringlist = text.split("\n",QString::SkipEmptyParts);

}
