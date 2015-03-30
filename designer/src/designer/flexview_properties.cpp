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

    tempwidget          = new QWidget;
    buttonProperties    = new QWidget;
    formProperties      = new QWidget;
    checkboxProperties  = new QWidget;
    textboxProperties   = new QWidget;
    comboboxProperties  = new QWidget;
    labelProperties     = new QWidget;

    connect(newProperty, SIGNAL(clicked()),this,SLOT(showDialog()));

    QHBoxLayout *hbox0 = new QHBoxLayout;
    hbox0->addWidget(widgetname);
    hbox0->addWidget(newProperty);

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
loadCheckboxSettings();
loadComboboxSettings();
loadLabelSettings();
loadTextboxSettings();
stackArea->setCurrentWidget(tempwidget);

}

void flexview_properties::submit()
{

    formPro.insert("comment",commentLineEdit->toPlainText());
    formPro.insert("msg", msgLineEdit->text());
    formPro.insert("output", outputComboBox->currentText());

    if (validationCheckBox->isChecked())
    {
        formPro.insert("formValidation","true");
    }else{
        formPro.insert("formValidation", "false");
    }

}


void flexview_properties::updatePro()
{
    msgLineEdit->setText(formPro.value("msg"));
    commentLineEdit->setText(formPro.value("comment"));
    outputComboBox->setCurrentText(formPro.value("output"));
qDebug () << formPro.value("output");
    if (formPro.value("formValidation") == "false")
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

        key.first = className;
        key.second = "comboBox";
        propertyName.append(",");
        propertyName.append(comboList.join("\n"));
    }
    if (className == "QPushButton")
    {
        newbuttonboxlayout->addLayout(newhbox);
    }else if(className == "QCheckBox")
    {
        newcheckboxlayout->addLayout(newhbox);
    }else if (className == "QLineEdit")
    {
        newtextboxlayout->addLayout(newhbox);
    }else if(className == "QComboBox")
    {
        newcomboboxlayout->addLayout(newhbox);
    }else if (className == "QLabel")
    {
        newlabellayout->addLayout(newhbox);
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
    }else if (className == "QCheckBox")
    {
        stackArea->setCurrentWidget(checkboxProperties);
    }else if (className == "QLineEdit")
    {
        stackArea->setCurrentWidget(textboxProperties);
    }else if (className == "QComboBox")
    {
        stackArea->setCurrentWidget(comboboxProperties);
    }else if (className == "QLabel")
    {
        stackArea->setCurrentWidget(labelProperties);
    }else{
        stackArea->setCurrentWidget(formProperties);
    }

}

void flexview_properties::loadFormSettings()
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


    widget_key textkey("QDesignerDialog","textBox");
    widget_key boolkey("QDesignerDialog","checkBox");
    widget_key combokey("QDesignerDialog","comboBox");

        QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            layout->addLayout(newhbox);

            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            layout->addLayout(newhbox);

            ++i;
        }

        i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

        while (i != newProperties.end() && i.key() == combokey) {
            templist = i.value().split(",",QString::SkipEmptyParts);
            value = templist.at(0);
            templist.removeAt(0);
            temp = templist.join("\n");
            combolist = temp.split("\n");

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            layout->addLayout(newhbox);

            ++i;
        }

    formProperties = new QWidget;
    formProperties->setLayout(layout );
    stackArea->addWidget(formProperties);
}

void flexview_properties::loadButtonSettings()
{
        widget_key textkey("QPushButton","textBox");
        widget_key boolkey("QPushButton","checkBox");
        widget_key combokey("QPushButton","comboBox");
        newbuttonboxlayout = new QVBoxLayout;

            QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

            while (i != newProperties.end() && i.key() == textkey) {
                QLabel      *newlabel   = new QLabel(i.value()) ;
                QLineEdit   *newline    = new QLineEdit;
                QHBoxLayout * newhbox = new QHBoxLayout;

                newlabel->setBuddy(newline);
                newhbox->addWidget(newlabel);
                newhbox->addWidget(newline);
                newbuttonboxlayout->addLayout(newhbox);

                ++i;
            }

            i = newProperties.find(boolkey);

            while (i != newProperties.end() && i.key() == boolkey) {
                QLabel      *newlabel       = new QLabel(i.value()) ;
                QCheckBox   *newcheckbox    = new QCheckBox;
                QHBoxLayout * newhbox = new QHBoxLayout;

                newlabel->setBuddy(newcheckbox);
                newhbox->addWidget(newlabel);
                newhbox->addWidget(newcheckbox);
                newbuttonboxlayout->addLayout(newhbox);

                ++i;
            }

            i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

            while (i != newProperties.end() && i.key() == combokey) {
                templist = i.value().split(",",QString::SkipEmptyParts);
                value = templist.at(0);
                templist.removeAt(0);
                temp = templist.join("\n");
                combolist = temp.split("\n");

                QLabel      *newlabel   = new QLabel(value) ;
                QComboBox   *newcombo   = new QComboBox;
                QHBoxLayout * newhbox = new QHBoxLayout;

                newlabel->setBuddy(newcombo);
                newcombo->addItems(combolist);
                newhbox->addWidget(newlabel);
                newhbox->addWidget(newcombo);
                newbuttonboxlayout->addLayout(newhbox);

                ++i;
            }

        buttonProperties->setLayout(newbuttonboxlayout);
        stackArea->addWidget(buttonProperties);
}

void flexview_properties::loadCheckboxSettings()
{
    widget_key textkey("QCheckBox","textBox");
    widget_key boolkey("QCheckBox","checkBox");
    widget_key combokey("QCheckBox","comboBox");
    newcheckboxlayout = new QVBoxLayout;

        QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newcheckboxlayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newcheckboxlayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

        while (i != newProperties.end() && i.key() == combokey) {
            templist = i.value().split(",",QString::SkipEmptyParts);
            value = templist.at(0);
            templist.removeAt(0);
            temp = templist.join("\n");
            combolist = temp.split("\n");

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newcheckboxlayout->addLayout(newhbox);
            ++i;
        }

    checkboxProperties->setLayout(newcheckboxlayout);
    stackArea->addWidget(checkboxProperties);
}

void flexview_properties::loadTextboxSettings()
{
    widget_key textkey("QLineEdit","textBox");
    widget_key boolkey("QLineEdit","checkBox");
    widget_key combokey("QLineEdit","comboBox");
    newtextboxlayout = new QVBoxLayout;

        QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newtextboxlayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newtextboxlayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

        while (i != newProperties.end() && i.key() == combokey) {
            templist = i.value().split(",",QString::SkipEmptyParts);
            value = templist.at(0);
            templist.removeAt(0);
            temp = templist.join("\n");
            combolist = temp.split("\n");

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newtextboxlayout->addLayout(newhbox);
            ++i;
        }

    textboxProperties->setLayout(newtextboxlayout);
    stackArea->addWidget(textboxProperties);
}

void flexview_properties::loadComboboxSettings()
{

    widget_key textkey("QComboBox","textBox");
    widget_key boolkey("QComboBox","checkBox");
    widget_key combokey("QComboBox","comboBox");
    newcomboboxlayout = new QVBoxLayout;

        QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newcomboboxlayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newcomboboxlayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

        while (i != newProperties.end() && i.key() == combokey) {
            templist = i.value().split(",",QString::SkipEmptyParts);
            value = templist.at(0);
            templist.removeAt(0);
            temp = templist.join("\n");
            combolist = temp.split("\n");

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newcomboboxlayout->addLayout(newhbox);
            ++i;
        }

    comboboxProperties->setLayout(newcomboboxlayout);
    stackArea->addWidget(comboboxProperties);
}

void flexview_properties::loadLabelSettings()
{
    widget_key textkey("QLabel","textBox");
    widget_key boolkey("QLabel","checkBox");
    widget_key combokey("QLabel","comboBox");
    newlabellayout = new QVBoxLayout;

        QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newlabellayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newlabellayout->addLayout(newhbox);
            ++i;
        }

        i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

        while (i != newProperties.end() && i.key() == combokey) {
            templist = i.value().split(",",QString::SkipEmptyParts);
            value = templist.at(0);
            templist.removeAt(0);
            temp = templist.join("\n");
            combolist = temp.split("\n");

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newlabellayout->addLayout(newhbox);
            ++i;
        }

    labelProperties->setLayout(newlabellayout);
    stackArea->addWidget(labelProperties);
}

QWidget* flexview_properties::getProperty()
{
    QObjectList list = stackArea->children();
    QWidget *widget;
    for (int i =0;i<list.size();i++)
    {
        qDebug() <<list.at(i);
    }

}
