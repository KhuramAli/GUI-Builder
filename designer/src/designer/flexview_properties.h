#ifndef FLEXVIEW_PROPERTIES_H
#define FLEXVIEW_PROPERTIES_H

#include <QDialog>
#include <QHash>
#include <QLineEdit>
#include <QTextEdit>
#include <QPair>

class QCheckBox;
class QLabel;
class QPushButton;
class QStringList;
class QComboBox;
class QVBoxLayout;
class QScrollArea;
class QFile;
class domParser;
class QStackedWidget;

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
    void addProperty(QString propertyName, QString propertyType, QStringList comboList);
    void showProperty();
    QWidget* getProperty();

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

    QVBoxLayout     *layout;
    QStackedWidget  *stackArea;
    QVBoxLayout     *mainLayout;
    QScrollArea     *scrollArea;
    QVBoxLayout     *newbuttonboxlayout;
    QVBoxLayout     *newcheckboxlayout;
    QVBoxLayout     *newtextboxlayout;
    QVBoxLayout     *newcomboboxlayout;
    QVBoxLayout     *newlabellayout;


    static QWidget *formProperties;
    static QWidget *buttonProperties;
    static QWidget *checkboxProperties;
    static QWidget *textboxProperties;
    static QWidget *comboboxProperties;
    static QWidget *labelProperties;
    static QWidget *tempwidget;

     typedef QPair <QString, QString> widget_key;
     QHash<widget_key, QString> newProperties;

static QHash<QString,QString> formPro;

void saveSettings (QHash<widget_key,QString> newProperties);
void loadSettings ();
void loadFormSettings();
void loadButtonSettings();
void loadCheckboxSettings();
void loadTextboxSettings();
void loadComboboxSettings();
void loadLabelSettings();

QString className;

QFile * settingFile;
};

#endif // FLEXVIEW_PROPERTIES_H
