#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QDockWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

class ToolBox : public QDockWidget
{
public:
    ToolBox();


private:
    QWidget *controlWidget = new QWidget (this);
    QPushButton *button1 = new QPushButton ("Push Button", controlWidget);
    QHBoxLayout *toolBoxLayout = new QHBoxLayout;


};

#endif // TOOLBOX_H
