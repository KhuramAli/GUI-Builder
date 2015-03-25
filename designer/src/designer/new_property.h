#ifndef NEW_PROPERTY_H
#define NEW_PROPERTY_H

#include<QDialog>

class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;

class new_property: public QDialog
{
    Q_OBJECT

public:
    new_property(QWidget *parent = 0);

private slots:
    void createProperty();

private:
    QLabel      *nameLabel;
    QLabel      *typeLabel;
    QLineEdit   *nameText;
    QComboBox   *type;
    QPushButton *okButton;
};

#endif // NEW_PROPERTY_H
