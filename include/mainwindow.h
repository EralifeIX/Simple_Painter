#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QList>
#include "canvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    void createActions();
    void createMenus();
    bool canSave();
    bool saveFile(const QByteArray &fileFormat);

    Canvas *canvas;
    QMenu *saveAsMenu;
    QMenu* fileMenu;
    QMenu* optionMenu;
    QMenu *helpMenu;
    QAction *openAction;
    QList<QAction*> saveAsActions;
    QAction *penColorAction;
    QAction *penWidthAction;
    QAction *clearScreenAction;
    QAction *aboutAction;
    QAction *exitAction;
};




#endif //MAINWINDOW_H
