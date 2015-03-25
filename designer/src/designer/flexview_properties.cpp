#include "flexview_properties.h"
#include "new_property.h"

#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QGridLayout>
#include <QStringList>
#include<QFile>
#include <abstractformwindow.h>

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

    widgetname = new QLabel;
   newProperty = new QPushButton (tr("add property"));

    connect(newProperty, SIGNAL(clicked()),this,SLOT(showDialog()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(msgLabel);
    gridLayout->addWidget(msgLineEdit);
    gridLayout->addWidget(commentLabel);
    gridLayout->addWidget(commentLineEdit);
    gridLayout->addWidget(outputLabel);
    gridLayout->addWidget(outputComboBox);
    gridLayout->addWidget(validationCheckBox);

/*
    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(msgLabel);
    hbox1->addWidget(msgLineEdit);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(commentLabel);
    hbox2->addWidget(commentLineEdit);

    QHBoxLayout *hbox3 = new QHBoxLayout;
    hbox3->addWidget(outputLabel);
    hbox3->addWidget(outputComboBox);
*/
    layout = new QVBoxLayout;

    layout->addLayout(gridLayout);
    layout->addWidget(newProperty);
  //  layout->addLayout(hbox);
    //layout->addSpacing(2);
   // layout->addWidget(okButton);

    setLayout(layout);


    setWindowTitle(tr("FlexView Properties"));
    //set(sizeHint().height());
    
if (!settingFile->exists("settings.ini"))
{
    settingFile = new QFile("settings.ini");
}else{
    settingFile = new QFile;
    loadSettings();
}

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

void flexview_properties::setWidgetName(QString name)
{
    widgetname->setText(name);
}

void flexview_properties::addProperty(QString propertyName, QString propertyType)
{
    int i =0;
    QString name = "New Property";
    name +i;
    QLabel * newlabel = new QLabel(tr("New Property"));
    i++;
    QHBoxLayout * newhbox = new QHBoxLayout;
    newhbox->addWidget(newlabel);
    layout->addLayout(newhbox);

    newProperties.insert("QLabel", name);
    qDebug() << name;
    qDebug() << newProperties.size();
    saveSettings(newProperties);

}

void flexview_properties::saveSettings(QHash<QString, QString> newProperties)
{qDebug() << "in saveSettings";

    settingFile->setFileName("settings.ini");
    if(settingFile->open(QFile::WriteOnly|QFile::Append))
    {qDebug() << "in file open";
            settingFile->atEnd();
            QDataStream out(settingFile);
                   out << newProperties;
                   //settingFile->flush();
                   settingFile->close();
    }
}

void flexview_properties::loadSettings()
{
    settingFile->setFileName("settings.ini");
    if(settingFile->open(QFile::ReadOnly))
    {
        QDataStream in(settingFile);
        while(!settingFile->atEnd())
        {
            in >> newProperties;

        }
    settingFile->close();
    }
qDebug() << newProperties.size();
        for(int i = 0; i < newProperties.size(); ++i)
        {
            if (newProperties.contains("QLabel"))
            {
                QLabel * newlabel = new QLabel (newProperties.value("QLabel"));
                QHBoxLayout * newhbox = new QHBoxLayout;
                newhbox->addWidget(newlabel);
                layout->addLayout(newhbox);
            }
         }

}

void flexview_properties::showDialog()
{
    new_property * PropertyDialog = new new_property;
    PropertyDialog->show();
}
