#ifndef FLEXVIEW_PROPERTIES_H
#define FLEXVIEW_PROPERTIES_H

#include <QDialog>
#include <QHash>
#include <QPair>

class QCheckBox;
class QLabel;
class QPushButton;
class QLineEdit;
class QTextEdit;
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

private slots:
    void showDialog();
    void showRemove();
    void updateList();

private:
    void loadSettings ();
    void loadFormSettings();
    void loadButtonSettings();
    void loadCheckboxSettings();
    void loadTextboxSettings();
    void loadMtextEditSettings();
    void loadComboboxSettings();
    void loadLabelSettings();
    void loadCalanderSettings();
    void loadTableSettings();
    void updatePropertyList(QWidget* stackedWidget);

    static QWidget *formProperties;
    static QWidget *buttonProperties;
    static QWidget *checkboxProperties;
    static QWidget *textboxProperties;
    static QWidget *mtexteditProperties;
    static QWidget *comboboxProperties;
    static QWidget *labelProperties;
    static QWidget *calanderProperties;
    static QWidget *tableProperties;
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
    QVBoxLayout     *newmtexteditlayout;
    QVBoxLayout     *newcomboboxlayout;
    QVBoxLayout     *newlabellayout;
    QVBoxLayout     *newcalanderlayout;
    QVBoxLayout     *newtablelayout;
    QScrollArea     *scrollArea;
    QStackedWidget  *stackArea;
    QWidget         *currentWidget;

    typedef QPair <QString, QString> widget_key;
    QHash<widget_key, QString> newProperties;
    QHash<QString, QHash<QString,QString>> widgetList;
    QStringList stringList;
    QFile * settingFile;
};

#endif // FLEXVIEW_PROPERTIES_H
