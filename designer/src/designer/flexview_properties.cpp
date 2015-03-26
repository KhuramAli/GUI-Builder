#include "flexview_properties.h"
#include "new_property.h"

#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStringList>
#include<QFile>
#include <abstractformwindow.h>
#include<QScrollArea>

QHash<QString, QString> flexview_properties::formPro;

flexview_properties::flexview_properties(QWidget * parent):QDialog(parent)
{

    msgLabel    = new QLabel(tr("Message:"));
    msgLineEdit = new QLineEdit;
    msgLabel->setBuddy(msgLineEdit);

    commentLabel    = new QLabel (tr("Comment:"));
    commentLineEdit = new QTextEdit;
    commentLineEdit->setAcceptRichText(false);
    commentLineEdit->setFixedHeight(50);
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

    QHBoxLayout *hbox0 = new QHBoxLayout;
    hbox0->addWidget(widgetname);
    hbox0->addWidget(newProperty);

    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(msgLabel);
    hbox1->addWidget(msgLineEdit);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(commentLabel);
    hbox2->addWidget(commentLineEdit);

    QHBoxLayout *hbox3 = new QHBoxLayout;
    hbox3->addWidget(outputLabel);
    hbox3->addWidget(outputComboBox);     


    layout = new QVBoxLayout;

    layout->addLayout(hbox0);
    layout->addLayout(hbox1);
    layout->addLayout(hbox2);
    layout->addLayout(hbox3);
    layout->addWidget(validationCheckBox);


    //Create a widget and set its layout as your new layout created above
    viewport = new QWidget;
    viewport->setLayout(layout );

    //Add the viewport to the scroll area
    scrollArea = new QScrollArea;

    scrollArea->setWidget(viewport);
    scrollArea->setWidgetResizable(true);
    mainLayout = new QVBoxLayout;

    //Add the scroll area to your main window's layout
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);


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

void flexview_properties::setWidgetName(QString widget_name, QString class_name)
{
    widgetname->setText(widget_name.append(" : ").append(class_name));
    className = class_name;
}


void flexview_properties::addProperty(QString propertyName, QString propertyType)
{
    if(propertyType == "string")
    {
        QLabel      *newlabel = new QLabel(propertyName);
        newlabel->setObjectName(propertyName);
        QLineEdit   *newline  = new QLineEdit;
        newline->setObjectName(propertyName);
        newlabel->setBuddy(newline);

        QHBoxLayout *newhbox = new QHBoxLayout;
        newhbox->addWidget(newlabel);
        newhbox->addWidget(newline);
        layout->addLayout(newhbox);

        textList.append(newline);
    }
    if(propertyType == "bool")
    {
        QLabel      *newlabel = new QLabel(propertyName);
        QCheckBox   *newcheckbox  = new QCheckBox;
        newcheckbox->setText("");
        newcheckbox->setObjectName(propertyName);
        newlabel->setBuddy(newcheckbox);

        QHBoxLayout *newhbox = new QHBoxLayout;
        newhbox->addWidget(newlabel);
        newhbox->addWidget(newcheckbox);
        layout->addLayout(newhbox);

        checkboxList.append(newcheckbox);
    }



    newProperties.insert("QLabel", propertyName);

    qDebug() << newProperties.size();
    saveSettings(newProperties);
    showProperty();

}

void flexview_properties::saveSettings(QHash<QString, QString> newProperties)
{

    settingFile->setFileName("settings.ini");
    if(settingFile->open(QFile::WriteOnly|QFile::Append))
    {
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

void flexview_properties::showProperty()
{
   for(int i = 0; i<textList.size(); i++)
   {
       qDebug() << textList.at(i)->text();
   }
}
