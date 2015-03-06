#ifndef FLEXVIEW_PROPERTIES_H
#define FLEXVIEW_PROPERTIES_H

#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QStringList;
class QComboBox;

class flexview_properties : public QDialog
{
    Q_OBJECT

public:
    flexview_properties(QWidget *parent = 0);
    QStringList flexProList ();

private slots:
    void submit ();

private:
    QLabel      *msgLabel;
    QLabel      *commentLabel;
    QLabel      *outputLabel;
    QLineEdit   *msgLineEdit;
    QTextEdit   *commentLineEdit;
    QCheckBox   *validationCheckBox;
    QComboBox   *outputComboBox;
    QPushButton *okButton;

    QStringList flexviewproperties;

};

#endif // FLEXVIEW_PROPERTIES_H
