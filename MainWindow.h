#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class QAction;
class QMenu;
class QListWidget;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void createActions();
    void createMenus();
    void createDockToolBox();

    QMenu *fileMenu;
    QAction *exitAct;
    QListWidget *ToolBox;
private slots:


};

#endif // MAINWINDOW_H
