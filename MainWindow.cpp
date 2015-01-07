#include <QtGui>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QListWidget>
#include <QDockWidget>
#include <QPushButton>


#include "MainWindow.h"


MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();
    createDockToolBox();

    setWindowTitle(tr("FlexView GUI Builder"));
    QString statusMessage = tr("FlexView GUI Builder");
    statusBar()->showMessage(statusMessage);

    setMinimumSize(160,160);

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createActions()
{
    exitAct = new QAction (tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Close Application"));
    connect (exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu (this);
    menu.addAction(exitAct);
    menu.exec(event->globalPos());
}

void MainWindow::createDockToolBox()
{
    QDockWidget *toolBox = new QDockWidget(tr("Tool Box"), this);
    toolBox->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    addDockWidget(Qt::LeftDockWidgetArea, toolBox);

    //adding controls
    QWidget *controlWidget = new QWidget (this);
    QPushButton *button1 = new QPushButton ("Push Button", controlWidget);
    QHBoxLayout *toolBoxLayout = new QHBoxLayout;
    toolBoxLayout->addWidget(button1);
    controlWidget->setLayout(toolBoxLayout);
    toolBox->setWidget(controlWidget);

}
