#ifndef REMOVE_PROPERTY_H
#define REMOVE_PROPERTY_H

#include<QDialog>

class QPushButton;
class QLabel;
class QComboBox;

class remove_property: public QDialog
{
      Q_OBJECT
public:
    remove_property(QWidget *parent = 0);

private slots:
void remove();

private:
QLabel      *label;
QComboBox   *combobox;
QPushButton *button;

QStringList  list;

};

#endif // REMOVE_PROPERTY_H
