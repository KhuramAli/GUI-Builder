#ifndef FLEXVIEW_PROPERTIES_H
#define FLEXVIEW_PROPERTIES_H

#include <QDialog>
#include <QHash>
#include <QLineEdit>
#include <QTextEdit>


class QCheckBox;
class QLabel;
class QPushButton;
class QStringList;
class QComboBox;
class domParser;

class flexview_properties : public QDialog
{
    Q_OBJECT

   friend class domParser;
   friend class QDesignerActions;

public:
    flexview_properties(QWidget *parent = 0);

private slots:
    void submit ();
    void updatePro ();

private:
    QLabel      *msgLabel;
    QLabel      *commentLabel;
    QLabel      *outputLabel;
    QLineEdit   *msgLineEdit;
    QTextEdit   *commentLineEdit;
    QCheckBox   *validationCheckBox;
    QComboBox   *outputComboBox;
    QPushButton *addButton;
    QPushButton *loadButton;

static QHash<QString,QString> formPro;

};

#endif // FLEXVIEW_PROPERTIES_H
