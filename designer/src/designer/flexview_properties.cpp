#include "flexview_properties.h"
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

QHash<QString, QString> flexview_properties::formPro;


flexview_properties::flexview_properties(QWidget * parent):QDialog(parent)
{
    msgLabel    = new QLabel(tr("Message:"));
    msgLineEdit = new QLineEdit;
    msgLabel->setBuddy(msgLineEdit);

    commentLabel    = new QLabel (tr("Comment:"));
    commentLineEdit = new QTextEdit;
    commentLineEdit->setAcceptRichText(false);
    commentLabel->setBuddy(commentLineEdit);

    validationCheckBox = new QCheckBox (tr("Form Validation"));
    validationCheckBox->setChecked(true);

    outputLabel     = new QLabel (tr("Output Property:"));
    outputComboBox = new QComboBox ;
    outputLabel->setBuddy(outputComboBox);

    outputComboBox->addItem("replace");
    outputComboBox->addItem("dialog");
    outputComboBox->addItem("context");
    outputComboBox->addItem("refresh");


   // addButton = new QPushButton (tr("add"));
    //loadButton = new QPushButton(tr("load"));

    //connect(okButton, SIGNAL(clicked()),this, SLOT (submit()));
   /* connect(commentLineEdit,SIGNAL(textChanged()),this,SLOT(submit()));
    connect(msgLineEdit,SIGNAL(textChanged(QString)),this,SLOT(submit()));
    connect (outputComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(submit()));
    connect (validationCheckBox, SIGNAL(clicked()), this,SLOT(submit()));*/

   // connect(addButton, SIGNAL(clicked()),this,SLOT(submit()));
    //connect(loadButton,SIGNAL(clicked()),this,SLOT(updatePro()));

    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(msgLabel);
    hbox1->addWidget(msgLineEdit);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(commentLabel);
    hbox2->addWidget(commentLineEdit);

    QHBoxLayout *hbox3 = new QHBoxLayout;
    hbox3->addWidget(outputLabel);
    hbox3->addWidget(outputComboBox);
/*
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(addButton);
    hbox->addWidget(loadButton);
*/
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addLayout(hbox1);
    layout->addLayout(hbox2);
    layout->addLayout(hbox3);
    layout->addWidget(validationCheckBox);
  //  layout->addLayout(hbox);
    //layout->addSpacing(2);
   // layout->addWidget(okButton);

    setLayout(layout);


    setWindowTitle(tr("FlexView Properties"));
    //set(sizeHint().height());

}

void flexview_properties::submit()
{

    formPro.insert("comment",commentLineEdit->toPlainText());
    formPro.insert("msg", msgLineEdit->text());
    formPro.insert("output", outputComboBox->currentText());

    if (validationCheckBox->isChecked())
    {
        formPro.insert("checkBox","true");
    }else{
        formPro.insert("checkBox", "false");
    }

}


void flexview_properties::updatePro()
{
    msgLineEdit->setText(formPro.value("msg"));
    commentLineEdit->setText(formPro.value("comment"));
    outputComboBox->setCurrentText(formPro.value("output"));
qDebug () << formPro.value("output");
    if (formPro.value("checkBox") == "false")
    {
        validationCheckBox->setChecked(false);
    }else{
        validationCheckBox->setChecked(true);
    }

 }

void flexview_properties::clear()
{
    msgLineEdit->clear();
    commentLineEdit->clear();
    outputComboBox->setCurrentIndex(0);
    validationCheckBox->setChecked(true);

    formPro.clear();
}
