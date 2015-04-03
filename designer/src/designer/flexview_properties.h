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
    static QString getClassName();
    void updatePro ();
    void submit ();
    void clear();
    void setWidgetName(QWidget *current);
    void addProperty(QString propertyName, QString propertyType, QStringList comboList);
    void showProperty();
    void removeProperties(QString propertyName);
    void saveSettings (QHash<QPair <QString, QString>,QString> newProperties);
    QStringList* getPropertyList();
    QHash<QPair <QString, QString>, QString> saveProperties();
    QWidgetList* getWidgetList();
    void updatePropertyList();

private slots:
    void showDialog();
    void showRemove();
    void updateButtonList();
   /* void updateCheckBoxList();
    void updateComboBoxList();
    void updateTextBoxList();
    void updateLabelList();
    void updateFormList();*/

private:
    void loadSettings ();
    void loadFormSettings();
    void loadButtonSettings();
    void loadCheckboxSettings();
    void loadTextboxSettings();
    void loadComboboxSettings();
    void loadLabelSettings();

    static QWidget *formProperties;
    static QWidget *buttonProperties;
    static QWidget *checkboxProperties;
    static QWidget *textboxProperties;
    static QWidget *comboboxProperties;
    static QWidget *labelProperties;
    static QWidget *tempwidget;

    static QHash<QString,QString> formPro;
    static QString className;

    QLabel          *msgLabel;
    QLabel          *commentLabel;
    QLabel          *outputLabel;
    QLabel          *widgetname;
    QLineEdit       *msgLineEdit;
    QTextEdit       *commentLineEdit;
    QCheckBox       *validationCheckBox;
    QComboBox       *outputComboBox;
    QPushButton     *newProperty;
    QPushButton     *removeProperty;

    QVBoxLayout     *layout;
    QVBoxLayout     *mainLayout;
    QVBoxLayout     *newbuttonboxlayout;
    QVBoxLayout     *newcheckboxlayout;
    QVBoxLayout     *newtextboxlayout;
    QVBoxLayout     *newcomboboxlayout;
    QVBoxLayout     *newlabellayout;
    QScrollArea     *scrollArea;
    QStackedWidget  *stackArea;
    QWidget         *currentWidget;

    typedef QPair <QString, QString> widget_key;
    QHash<widget_key, QString> newProperties;
    QHash<QString, QHash<QString,QString>> widgetList;
    QStringList stringList;
    QFile * settingFile;

    struct propertyList
    {
        QString classname;
        QString title;
        QHash<QString, QString> list;
    };

    QHash<QString, propertyList*> hashList;
};

#endif // FLEXVIEW_PROPERTIES_H
