#include <QtGui>
#include <QFrame>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>
#include <QPushButton>


#include "MainWindow.h"
#include "toolbox.h"


MainWindow::MainWindow()
{
    QFrame *centerFrame = new QFrame;
    centerFrame->setFrameStyle(QFrame::StyledPanel);
    centerFrame->acceptDrops();

    setCentralWidget(centerFrame);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    centerFrame->setLayout(layout);

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
    ToolBox *dock = new ToolBox ;

  //  QDockWidget *toolBox = new QDockWidget(tr("Tool Box"));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    addDockWidget(Qt::LeftDockWidgetArea, dock);

    /*
    QWidget *controlWidget = new QWidget (this);
    QPushButton *button1 = new QPushButton ("Push Button", controlWidget);
    QHBoxLayout *toolBoxLayout = new QHBoxLayout;

    toolBoxLayout->addWidget(button1);
    controlWidget->setLayout(toolBoxLayout);
    toolBox->setWidget(controlWidget);
*/
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton && button1->geometry().contains(event->pos()))
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        drag->setMimeData(mimeData);
        drag->setHotSpot(button1->pos());

        Qt::DropAction dropAction = drag->exec();
    }
}

