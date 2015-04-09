#include "flexview_properties.h"
#include "new_property.h"
#include "remove_property.h"

#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QFile>
#include <abstractformwindow.h>
#include <QStackedWidget>
#include <QScrollArea>
#include <QMessageBox>

QHash<QString, QString> flexview_properties::formPro;
QWidget* flexview_properties::formProperties;
QWidget* flexview_properties::buttonProperties;
QWidget* flexview_properties::checkboxProperties;
QWidget* flexview_properties::textboxProperties;
QWidget* flexview_properties::mtexteditProperties;
QWidget* flexview_properties::comboboxProperties;
QWidget* flexview_properties::labelProperties;
QWidget* flexview_properties::calanderProperties;
QWidget* flexview_properties::tableProperties;
QWidget* flexview_properties::layoutProperties;
QWidget* flexview_properties::tempwidget;
QString flexview_properties::className;

#define PSTRING     "string"
#define PBOOL       "bool"
#define PCOMBO      "combobox"
#define BUTTON      "QPushButton"
#define CHECKBOX    "QCheckBox"
#define TEXTBOX     "QLineEdit"
#define MTEXTEDIT   "QTextEdit"
#define COMBOBOX    "QComboBox"
#define LABEL       "QLabel"
#define CALANDER    "QCalendarWidget"
#define TABLE       "QTableWidget"
#define LAYOUT      "QLayoutWidget"
#define DIALOG      "QDesignerDialog"

flexview_properties::flexview_properties(QWidget * parent):QDialog(parent)
{
    stackArea   = new QStackedWidget;
    scrollArea  = new QScrollArea;
    mainLayout  = new QVBoxLayout;

    widgetname      = new QLabel;
    newProperty     = new QPushButton (tr("add property"));
    removeProperty  = new QPushButton (tr("remove property"));

    tempwidget          = new QWidget;
    buttonProperties    = new QWidget;
    formProperties      = new QWidget;
    checkboxProperties  = new QWidget;
    textboxProperties   = new QWidget;
    comboboxProperties  = new QWidget;
    labelProperties     = new QWidget;
    calanderProperties  = new QWidget;
    mtexteditProperties = new QWidget;
    tableProperties     = new QWidget;
    layoutProperties    = new QWidget;

    connect(newProperty, SIGNAL(clicked()),this,SLOT(showDialog()));
    connect(removeProperty, SIGNAL(clicked()),this,SLOT(showRemove()));

    QHBoxLayout *hbox0 = new QHBoxLayout;
    hbox0->addWidget(widgetname);
    hbox0->addWidget(newProperty);
    hbox0->addWidget(removeProperty);

    tempwidget->setObjectName("tempwidget");
    stackArea->addWidget(tempwidget);

    scrollArea->setWidget(stackArea);
    scrollArea->setWidgetResizable(true);
    mainLayout->addLayout(hbox0);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    setWindowTitle(tr("FlexView Properties"));
    
if (!settingFile->exists("settings.ini")){
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
loadMtextEditSettings();
loadCalanderSettings();
loadTableSettings();
loadLayoutSettings();
stackArea->setCurrentWidget(tempwidget);
}

void flexview_properties::submit()
{
    formPro.insert("comment",commentLineEdit->toPlainText());
    formPro.insert("msg", msgLineEdit->text());
    formPro.insert("output", outputComboBox->currentText());

    if (validationCheckBox->isChecked()){
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
    if (formPro.value("formValidation") == "false"){
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

void flexview_properties::setWidgetName(QWidget* current)
{
    QString name;
    name.append(current->objectName());
    name.append(" : ");
    name.append(current->property("text").toString());
    widgetname->setText(name);
    className = current->metaObject()->className();
    currentWidget = current;
}


void flexview_properties::addProperty(QString propertyName, QString propertyType,QStringList comboList)
{
widget_key key;
QHBoxLayout *newhbox = new QHBoxLayout;
key.first = className;
key.second = propertyType;
QStringList temp;

if (propertyType == PCOMBO){
    temp = newProperties.value(key).split(",");
}else{
    temp.append(newProperties.value(key));
}

if (propertyName != temp.at(0)){
    if(propertyType == PSTRING){
        QLabel      *newlabel = new QLabel(propertyName);
        newlabel->setObjectName(propertyName);
        newlabel->setAccessibleName(className);
        QLineEdit   *newline  = new QLineEdit;
        newline->setObjectName(propertyName);
        newline->setAccessibleName(className);
        newlabel->setBuddy(newline);
        connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
        newhbox->addWidget(newlabel);
        newhbox->addWidget(newline);
    }
    if(propertyType == PBOOL){
        QLabel      *newlabel = new QLabel(propertyName);
        QCheckBox   *newcheckbox  = new QCheckBox;
        newcheckbox->setText("");
        newcheckbox->setObjectName(propertyName);
        newlabel->setObjectName(propertyName);
        newcheckbox->setAccessibleName(className);
        newlabel->setAccessibleName(className);
        newlabel->setBuddy(newcheckbox);
        connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
        newhbox->addWidget(newlabel);
        newhbox->addWidget(newcheckbox);
    }
    if (propertyType == PCOMBO){
        QLabel      *newlabel = new QLabel(propertyName);
        QComboBox   *newcombobox  = new QComboBox;
        newcombobox->addItems(comboList);
        newcombobox->setObjectName(propertyName);
        newlabel->setObjectName(propertyName);
        newcombobox->setAccessibleName(className);
        newlabel->setAccessibleName(className);
        newlabel->setBuddy(newcombobox);
        connect(newcombobox,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
        newhbox->addWidget(newlabel);
        newhbox->addWidget(newcombobox);
    }
    if (className == BUTTON){
        newbuttonboxlayout->addLayout(newhbox);
    }else if(className == CHECKBOX){
        newcheckboxlayout->addLayout(newhbox);
    }else if (className == TEXTBOX){
        newtextboxlayout->addLayout(newhbox);
    }else if (className == MTEXTEDIT){
        newmtexteditlayout->addLayout(newhbox);
    }else if(className == COMBOBOX){
        newcomboboxlayout->addLayout(newhbox);
    }else if (className == LABEL){
        newlabellayout->addLayout(newhbox);
    }else if (className == CALANDER){
        newcalanderlayout->addLayout(newhbox);
    }else if (className == TABLE){
        newtablelayout->addLayout(newhbox);
    }else if (className == LAYOUT){
        newlayoutlayout->addLayout(newhbox);
    }else{
        layout->addLayout(newhbox);
    }
    saveSettings(saveProperties());
    showProperty();
}else{
    QMessageBox::warning(this, tr("Flexview GUI Builder"),
                         tr("You cannot add duplicate properties"),QMessageBox::Ok);
}
}

void flexview_properties::saveSettings(QHash<QPair <QString, QString>, QString> newProperties)
{
    settingFile->setFileName("settings.ini");
    if(settingFile->open(QFile::WriteOnly)){
            settingFile->atEnd();
            QDataStream out(settingFile);
                   out << newProperties;
                   settingFile->close();
    }
}

void flexview_properties::loadSettings()
{
    settingFile->setFileName("settings.ini");
    if(settingFile->open(QFile::ReadOnly)){
        QDataStream in(settingFile);
        while(!settingFile->atEnd()){
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
    for(int i = 0; i < stackArea->count(); i++){
        if (className == stackArea->widget(i)->objectName()){
            stackArea->setCurrentWidget(stackArea->widget(i));
            updatePropertyList(stackArea->widget(i));
            break;
        }
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

    connect(msgLineEdit,SIGNAL(editingFinished()),this,SLOT(updateList()));
    connect(commentLineEdit,SIGNAL(textChanged()),this,SLOT(updateList()));
    connect(validationCheckBox,SIGNAL(released()),this,SLOT(updateList()));
    connect(outputComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
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

    widget_key textkey(DIALOG,PSTRING);
    widget_key boolkey(DIALOG,PBOOL);
    widget_key combokey(DIALOG,PCOMBO);

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey){
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            layout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey){
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            layout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

        while (i != newProperties.end() && i.key() == combokey){
            templist = i.value().split(",",QString::SkipEmptyParts);
            value = templist.at(0);
            templist.removeAt(0);
            temp = templist.join("\n");
            combolist = temp.split("\n");
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newcombo->addItems(combolist);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            layout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    formProperties = new QWidget;
    formProperties->setObjectName(DIALOG);
    formProperties->setLayout(layout );
    stackArea->addWidget(formProperties);
}

void flexview_properties::loadButtonSettings()
{
        widget_key textkey(BUTTON,PSTRING);
        widget_key boolkey(BUTTON,PBOOL);
        widget_key combokey(BUTTON,PCOMBO);
        newbuttonboxlayout = new QVBoxLayout;

        QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

            while (i != newProperties.end() && i.key() == textkey){
                QLabel      *newlabel   = new QLabel(i.value()) ;
                QLineEdit   *newline    = new QLineEdit;
                QHBoxLayout * newhbox = new QHBoxLayout;

                newlabel->setBuddy(newline);
                newlabel->setObjectName(i.value());
                newline->setObjectName(i.value());
                newhbox->addWidget(newlabel);
                newhbox->addWidget(newline);
                newbuttonboxlayout->addLayout(newhbox);
                connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
                ++i;
            }

            i = newProperties.find(boolkey);

            while (i != newProperties.end() && i.key() == boolkey){
                QLabel      *newlabel       = new QLabel(i.value()) ;
                QCheckBox   *newcheckbox    = new QCheckBox;
                QHBoxLayout * newhbox = new QHBoxLayout;

                newlabel->setBuddy(newcheckbox);
                newlabel->setObjectName(i.value());
                newcheckbox->setObjectName(i.value());
                newhbox->addWidget(newlabel);
                newhbox->addWidget(newcheckbox);
                newbuttonboxlayout->addLayout(newhbox);
                connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
                ++i;
            }

            i = newProperties.find(combokey);
//logic should be improved. not an Elegant solution.
QStringList combolist;
QStringList templist;
QString value;
QString temp;

            while (i != newProperties.end() && i.key() == combokey){
                templist = i.value().split(",",QString::SkipEmptyParts);
                value = templist.at(0);
                templist.removeAt(0);
                temp = templist.join("\n");
                combolist = temp.split("\n");
                combolist.removeAt(0);

                QLabel      *newlabel   = new QLabel(value) ;
                QComboBox   *newcombo   = new QComboBox;
                QHBoxLayout * newhbox = new QHBoxLayout;

                newlabel->setBuddy(newcombo);
                newcombo->addItems(combolist);
                newlabel->setObjectName(value);
                newcombo->setObjectName(value);
                newhbox->addWidget(newlabel);
                newhbox->addWidget(newcombo);
                connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
                newbuttonboxlayout->addLayout(newhbox);
                ++i;
            }

        buttonProperties->setLayout(newbuttonboxlayout);
        buttonProperties->setObjectName(BUTTON);
        stackArea->addWidget(buttonProperties);
}

void flexview_properties::loadCheckboxSettings()
{
    widget_key textkey(CHECKBOX,PSTRING);
    widget_key boolkey(CHECKBOX,PBOOL);
    widget_key combokey(CHECKBOX,PCOMBO);
    newcheckboxlayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newcheckboxlayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newcheckboxlayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newcheckboxlayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    checkboxProperties->setLayout(newcheckboxlayout);
    checkboxProperties->setObjectName(CHECKBOX);
    stackArea->addWidget(checkboxProperties);
}

void flexview_properties::loadTextboxSettings()
{
    widget_key textkey(TEXTBOX,PSTRING);
    widget_key boolkey(TEXTBOX,PBOOL);
    widget_key combokey(TEXTBOX,PCOMBO);
    newtextboxlayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newtextboxlayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newtextboxlayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newtextboxlayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    textboxProperties->setLayout(newtextboxlayout);
    textboxProperties->setObjectName(TEXTBOX);
    stackArea->addWidget(textboxProperties);
}

void flexview_properties::loadMtextEditSettings()
{
    widget_key textkey(MTEXTEDIT,PSTRING);
    widget_key boolkey(MTEXTEDIT,PBOOL);
    widget_key combokey(MTEXTEDIT,PCOMBO);
    newmtexteditlayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newmtexteditlayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newmtexteditlayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newmtexteditlayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    mtexteditProperties->setLayout(newmtexteditlayout);
    mtexteditProperties->setObjectName(MTEXTEDIT);
    stackArea->addWidget(mtexteditProperties);
}

void flexview_properties::loadComboboxSettings()
{
    widget_key textkey(COMBOBOX,PSTRING);
    widget_key boolkey(COMBOBOX,PBOOL);
    widget_key combokey(COMBOBOX,PCOMBO);
    newcomboboxlayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newcomboboxlayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newcomboboxlayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newcomboboxlayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    comboboxProperties->setLayout(newcomboboxlayout);
    comboboxProperties->setObjectName(COMBOBOX);
    stackArea->addWidget(comboboxProperties);
}

void flexview_properties::loadLabelSettings()
{
    widget_key textkey(LABEL,PSTRING);
    widget_key boolkey(LABEL,PBOOL);
    widget_key combokey(LABEL,PCOMBO);
    newlabellayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newlabellayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newlabellayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newlabellayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    labelProperties->setLayout(newlabellayout);
    labelProperties->setObjectName(LABEL);
    stackArea->addWidget(labelProperties);
}

void flexview_properties::loadCalanderSettings()
{
    widget_key textkey(CALANDER,PSTRING);
    widget_key boolkey(CALANDER,PBOOL);
    widget_key combokey(CALANDER,PCOMBO);
    newcalanderlayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newcalanderlayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newcalanderlayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newcalanderlayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    calanderProperties->setLayout(newcalanderlayout);
    calanderProperties->setObjectName(CALANDER);
    stackArea->addWidget(calanderProperties);
}

void flexview_properties::loadTableSettings()
{
    widget_key textkey(TABLE,PSTRING);
    widget_key boolkey(TABLE,PBOOL);
    widget_key combokey(TABLE,PCOMBO);
    newtablelayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newtablelayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newtablelayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newtablelayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    tableProperties->setLayout(newtablelayout);
    tableProperties->setObjectName(TABLE);
    stackArea->addWidget(tableProperties);
}

void flexview_properties::loadLayoutSettings()
{
    widget_key textkey(LAYOUT,PSTRING);
    widget_key boolkey(LAYOUT,PBOOL);
    widget_key combokey(LAYOUT,PCOMBO);
    newlayoutlayout = new QVBoxLayout;

    QHash<widget_key, QString>::iterator i = newProperties.find(textkey);

        while (i != newProperties.end() && i.key() == textkey) {
            QLabel      *newlabel   = new QLabel(i.value()) ;
            QLineEdit   *newline    = new QLineEdit;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newline);
            newlabel->setObjectName(i.value());
            newline->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newline);
            newlayoutlayout->addLayout(newhbox);
            connect(newline,SIGNAL(editingFinished()),this,SLOT(updateList()));
            ++i;
        }

        i = newProperties.find(boolkey);

        while (i != newProperties.end() && i.key() == boolkey) {
            QLabel      *newlabel       = new QLabel(i.value()) ;
            QCheckBox   *newcheckbox    = new QCheckBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcheckbox);
            newlabel->setObjectName(i.value());
            newcheckbox->setObjectName(i.value());
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcheckbox);
            newlayoutlayout->addLayout(newhbox);
            connect(newcheckbox,SIGNAL(released()),this,SLOT(updateList()));
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
            combolist.removeAt(0);

            QLabel      *newlabel   = new QLabel(value) ;
            QComboBox   *newcombo   = new QComboBox;
            QHBoxLayout * newhbox = new QHBoxLayout;

            newlabel->setBuddy(newcombo);
            newlabel->setObjectName(value);
            newcombo->setObjectName(value);
            newcombo->addItems(combolist);
            newhbox->addWidget(newlabel);
            newhbox->addWidget(newcombo);
            newlayoutlayout->addLayout(newhbox);
            connect(newcombo,SIGNAL(currentTextChanged(QString)),this,SLOT(updateList()));
            ++i;
        }

    layoutProperties->setLayout(newlayoutlayout);
    layoutProperties->setObjectName(LAYOUT);
    stackArea->addWidget(layoutProperties);
}

QString flexview_properties::getClassName()
{
    return className;
}

QStringList* flexview_properties::getPropertyList()
{
    QObjectList list;

    if(className == BUTTON){
        list = buttonProperties->children();
        stringList.clear();
        for(int i = 0; i < list.size(); i++){
            stringList.append(list.at(i)->objectName());
        }
        return &stringList;
    }else if(className == TEXTBOX){
        list = textboxProperties->children();
        stringList.clear();
        for(int i = 0; i < list.size(); i++){
            stringList.append(list.at(i)->objectName());
        }
        return &stringList;
    }else if(className == MTEXTEDIT){
        list = mtexteditProperties->children();
        stringList.clear();
        for(int i = 0; i < list.size(); i++){
            stringList.append(list.at(i)->objectName());
        }
        return &stringList;
    }else if(className == CHECKBOX){
        list = checkboxProperties->children();
        stringList.clear();
        for(int i = 0; i < list.size(); i++){
            stringList.append(list.at(i)->objectName());
        }
        return &stringList;
    }if(className == COMBOBOX){
        list = comboboxProperties->children();
        stringList.clear();
        for(int i = 0; i < list.size(); i++){
            stringList.append(list.at(i)->objectName());
        }
        return &stringList;
    }if(className == LABEL){
        list = labelProperties->children();
        stringList.clear();
        for(int i = 0; i < list.size(); i++){
            stringList.append(list.at(i)->objectName());
        }
        return &stringList;
    }else{
        list = formProperties->children();
        stringList.clear();
        for(int i = 0; i < list.size(); i++){
            stringList.append(list.at(i)->objectName());
        }
        return &stringList;
    }
}

void flexview_properties::showRemove()
{
    remove_property * rp = new remove_property;
    rp->exec();
}

void flexview_properties::removeProperties(QString propertyName)
{
    QWidget *stackWidget = stackArea->currentWidget();
        for(int i = 0; i <stackWidget->children().size(); i++){
            if(stackWidget->children().at(i)->objectName() == propertyName){
                delete stackWidget->children().at(i);
            }
        }
   saveSettings(saveProperties());
}

QHash<QPair <QString, QString>, QString> flexview_properties::saveProperties()
{
    widget_key  key;        //stores settings. first = classname, second = property type.
    QString     temp;
    QString     propertyName;
    newProperties.clear();
    QWidget *stackWidget;

    for (int j = 0; j < stackArea->count();j++){
        stackWidget = stackArea->widget(j);
        for(int i = 0; i < stackWidget->children().size(); i++){
            temp = stackWidget->children().at(i)->metaObject()->className();
            if(temp == TEXTBOX){
                key.first       = stackWidget->objectName();
                key.second      = PSTRING;
                propertyName    = stackWidget->children().at(i)->objectName();
                if(propertyName != newProperties.value(key)){
                    newProperties.insertMulti(key,propertyName);
                }
            }else if(temp == CHECKBOX){
                key.first       = stackWidget->objectName();
                key.second      = PBOOL;
                propertyName    = stackWidget->children().at(i)->objectName();
                if(propertyName != newProperties.value(key)){
                    newProperties.insertMulti(key,propertyName);
                }
            }else if(temp == COMBOBOX){
                key.first       = stackWidget->objectName();
                key.second      = PCOMBO;
                propertyName    = stackWidget->children().at(i)->objectName();
                if(propertyName != newProperties.value(key)){
                    QComboBox * newcombo = (QComboBox*)stackWidget->children().at(i);
                    propertyName.append(",");
                    for(int j =0; j < newcombo->count();j++){
                        propertyName.append("\n");
                        propertyName.append(newcombo->itemText(j));
                    }
                    newProperties.insertMulti(key,propertyName);
                }
        }
      }
   }
    return newProperties;
}

void flexview_properties::updatePropertyList(QWidget *stackedWidget)
{
QString temp;
QLineEdit *newline;
QCheckBox *newcheckbox;
QComboBox *newcombo;

for(int i = 0; i < stackedWidget->children().size(); i++){
    temp = stackedWidget->children().at(i)->metaObject()->className();
    if(temp == TEXTBOX){
        newline = (QLineEdit*)stackedWidget->children().at(i);
            foreach(currentWidget->objectName(),widgetList.keys()){
                foreach(newline->objectName(),widgetList.value(currentWidget->objectName()).keys()){
                    newline->setText(widgetList.value(currentWidget->objectName()).value(newline->objectName()));
                }
            }
    }else if(temp == CHECKBOX){
        newcheckbox = (QCheckBox*)stackedWidget->children().at(i);
            foreach(currentWidget->objectName(),widgetList.keys()){
                foreach(newcheckbox->objectName(),widgetList.value(currentWidget->objectName()).keys()){
                    if(widgetList.value(currentWidget->objectName()).value(newcheckbox->objectName()) == "true"){
                        newcheckbox->setChecked(true);
                    }else{
                        newcheckbox->setChecked(false);
                    }
                }
            }
    }else if(temp == COMBOBOX){
        newcombo = (QComboBox*)stackedWidget->children().at(i);
            foreach(currentWidget->objectName(),widgetList.keys()){
                foreach(newcombo->objectName(),widgetList.value(currentWidget->objectName()).keys()){
                    newcombo->setCurrentText(widgetList.value(currentWidget->objectName()).value(newcombo->objectName()));
                }
            }
    }
  }

}

void flexview_properties::updateList()
{
    QWidget *stackWidget = stackArea->currentWidget();
    QString temp;
    QString ischecked = "false";
    QLineEdit *newline;
    QCheckBox *newcheckbox;
    QComboBox *newcombo;
    QHash<QString,QString> hash;

    for(int i = 0; i < stackWidget->children().size(); i++){
        temp = stackWidget->children().at(i)->metaObject()->className();
        if( temp == TEXTBOX){
            newline = (QLineEdit*)stackWidget->children().at(i);
            hash.insert(newline->objectName(),newline->text());
            widgetList.insert(currentWidget->objectName(),hash);

        }else if( temp == CHECKBOX){
            newcheckbox = (QCheckBox*)stackWidget->children().at(i);
            if (newcheckbox->isChecked()){
                ischecked = "true";
            }else{
                ischecked = "false";
            }
            hash.insert(newcheckbox->objectName(),ischecked);
            widgetList.insert(currentWidget->objectName(),hash);

        }else if( temp == COMBOBOX){
            newcombo = (QComboBox*)stackWidget->children().at(i);
            hash.insert(newcombo->objectName(),newcombo->currentText());
            widgetList.insert(currentWidget->objectName(),hash);
            }
       }
}
