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
#include <QFile>
#include <abstractformwindow.h>
#include <QStackedWidget>
#include <QScrollArea>

QHash<QString, QString> flexview_properties::formPro;
QWidget* flexview_properties::formProperties;
QWidget* flexview_properties::buttonProperties;
QWidget* flexview_properties::checkboxProperties;
QWidget* flexview_properties::textboxProperties;
QWidget* flexview_properties::comboboxProperties;
QWidget* flexview_properties::labelProperties;
QWidget* flexview_properties::tempwidget;

flexview_properties::flexview_properties(QWidget * parent):QDialog(parent)
{
    stackArea   = new QStackedWidget;
    scrollArea  = new QScrollArea;
    mainLayout  = new QVBoxLayout;

    widgetname  = new QLabel;
    newProperty = new QPushButton (tr("add property"));

    connect(newProperty, SIGNAL(clicked()),this,SLOT(showDialog()));

    QHBoxLayout *hbox0 = new QHBoxLayout;
    hbox0->addWidget(widgetname);
    hbox0->addWidget(newProperty);
    tempwidget = new QWidget;
    stackArea->addWidget(tempwidget);

    scrollArea->setWidget(stackArea);
    scrollArea->setWidgetResizable(true);
    mainLayout->addLayout(hbox0);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    formProperties      = new QWidget;
    buttonProperties    = new QWidget;

    setWindowTitle(tr("FlexView Properties"));
    
if (!settingFile->exists("settings.ini"))
{
    settingFile = new QFile("settings.ini");
}else{
    settingFile = new QFile;
    loadSettings();
}

loadFormSettings();
loadButtonSettings();
stackArea->setCurrentWidget(tempwidget);

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
    stackArea->setCurrentWidget(tempwidget);
}

void flexview_properties::setWidgetName(QString widget_name, QString class_name)
{
    widgetname->setText(widget_name.append(" : ").append(class_name));
    className = class_name;
}


void flexview_properties::addProperty(QString propertyName, QString propertyType,QStringList comboList)
{
widget_key key;
QHBoxLayout *newhbox = new QHBoxLayout;
    if(propertyType == "string")
    {
        QLabel      *newlabel = new QLabel(propertyName);
        newlabel->setObjectName(propertyName);
        QLineEdit   *newline  = new QLineEdit;
        newline->setObjectName(propertyName);
        newlabel->setBuddy(newline);

        newhbox->addWidget(newlabel);
        newhbox->addWidget(newline);

        textList.append(newline);
        key.first = className;
        key.second = "textBox";

    }
    if(propertyType == "bool")
    {
        QLabel      *newlabel = new QLabel(propertyName);
        QCheckBox   *newcheckbox  = new QCheckBox;
        newcheckbox->setText("");
        newcheckbox->setObjectName(propertyName);
        newlabel->setBuddy(newcheckbox);

        newhbox->addWidget(newlabel);
        newhbox->addWidget(newcheckbox);

        checkboxList.append(newcheckbox);
        key.first = className;
        key.second = "checkBox";
    }

    if (propertyType == "combobox")
    {
        QLabel      *newlabel = new QLabel(propertyName);
        QComboBox   *newcombobox  = new QComboBox;
        newcombobox->addItems(comboList);
        newcombobox->setObjectName(propertyName);
        newlabel->setBuddy(newcombobox);

        newhbox->addWidget(newlabel);
        newhbox->addWidget(newcombobox);

        comboboxList.append(newcombobox);
        key.first = className;
        key.second = "comboBox";
    }
    if (className == "QPushButton")
    {
        newbuttonbox->addLayout(newhbox);
    }else{
        layout->addLayout(newhbox);
    }

    newProperties.insertMulti(key,propertyName);
    saveSettings(newProperties);
    showProperty();

}

void flexview_properties::saveSettings(QHash<widget_key, QString> newProperties)
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

}

void flexview_properties::showDialog()
{
    new_property * PropertyDialog = new new_property;
    PropertyDialog->exec();
}

void flexview_properties::showProperty()
{


    if (className == "QPushButton")
    {
       stackArea->setCurrentWidget(buttonProperties);
    }else{
        stackArea->setCurrentWidget(formProperties);
    }

}

QWidget * flexview_properties::loadFormSettings()
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

    layout->addLayout(hbox1);
    layout->addLayout(hbox2);
    layout->addLayout(hbox3);
    layout->addWidget(validationCheckBox);

    widget_key key("QDesignerDialog","textBox");


    QHash<widget_key, QString>::iterator i = newProperties.find(key);

    while (i != newProperties.end() && i.key() == key) {
        QLabel      *newlabel   = new QLabel(i.value()) ;
        QLineEdit   *newline    = new QLineEdit;
        QHBoxLayout * newhbox = new QHBoxLayout;

        newlabel->setBuddy(newline);
        newhbox->addWidget(newlabel);
        newhbox->addWidget(newline);
        layout->addLayout(newhbox);

        ++i;
    }

    formProperties = new QWidget;
    formProperties->setLayout(layout );
    stackArea->addWidget(formProperties);
    return formProperties;
}

QWidget * flexview_properties::loadButtonSettings()
{
        widget_key key("QPushButton","textBox");
        newbuttonbox = new QVBoxLayout;

        QHash<widget_key, QString>::iterator i = newProperties.find(key);

        while (i != newProperties.end() && i.key() == key) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            newlabel->setBuddy(newline);

            QHBoxLayout * newhbox = new QHBoxLayout;
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newbuttonbox->addLayout(newhbox);

            ++i;
        }

        buttonProperties->setLayout(newbuttonbox);
               stackArea->addWidget(buttonProperties);
    return buttonProperties;
}
