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
class QVBoxLayout;
class QScrollArea;
class QFile;
class domParser;

class flexview_properties : public QDialog
{
    Q_OBJECT

   friend class domParser;
   friend class QDesignerActions;

public:
    flexview_properties(QWidget *parent = 0);
    void updatePro ();
    void submit ();
    void clear();
    void setWidgetName(QString widget_name, QString class_name);
    void addProperty(QString propertyName, QString propertyType);
    void showProperty();

    QVector <QLineEdit*> textList;
    QVector <QCheckBox*> checkboxList;

private slots:
    void showDialog();

private:
    QLabel      *msgLabel;
    QLabel      *commentLabel;
    QLabel      *outputLabel;
    QLabel      *widgetname;
    QLineEdit   *msgLineEdit;
    QTextEdit   *commentLineEdit;
    QCheckBox   *validationCheckBox;
    QComboBox   *outputComboBox;
    QPushButton *newProperty;

     QVBoxLayout *layout;
     QWidget     *viewport;
     QScrollArea *scrollArea;
     QVBoxLayout *mainLayout;

     QHash<QString, QString> newProperties;

static QHash<QString,QString> formPro;

void saveSettings (QHash<QString,QString> newProperties);
void loadSettings ();

QString className;

QFile * settingFile;
};

#endif // FLEXVIEW_PROPERTIES_H
