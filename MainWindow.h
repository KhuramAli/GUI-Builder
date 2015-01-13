#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class QAction;
class QMenu;
class QDockWidget;
class QPushButton;

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
    void mousePressEvent(QMouseEvent *event);

    QMenu *fileMenu;
    QMenu *viewMenu;
    QAction *exitAct;

    QPushButton *button1;

private slots:


};

#endif // MAINWINDOW_H
