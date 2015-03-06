#include "flexview_properties.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>


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

    okButton = new QPushButton (tr("Create Wddx Packets"));


    connect(okButton, SIGNAL(clicked()),this, SLOT (submit()));

    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(msgLabel);
    hbox1->addWidget(msgLineEdit);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(commentLabel);
    hbox2->addWidget(commentLineEdit);

    QHBoxLayout *hbox3 = new QHBoxLayout;
    hbox3->addWidget(outputLabel);
    hbox3->addWidget(outputComboBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(hbox1);
    layout->addLayout(hbox2);
    layout->addLayout(hbox3);
    layout->addWidget(validationCheckBox);
    layout->addSpacing(2);
    layout->addWidget(okButton);
    setLayout(layout);

    setWindowTitle(tr("FlexView Properties"));
    setFixedHeight(250);
    setFixedWidth(300);
}

void flexview_properties::submit()
{
    flexviewproperties << msgLineEdit->text() << commentLineEdit->toPlainText() << outputComboBox->currentText();

    if (validationCheckBox->isChecked())
    {
        flexviewproperties << "true";
    }else{
        flexviewproperties << "false";
    }

    close();
}

QStringList flexview_properties::flexProList()
{
    return flexviewproperties;
}
