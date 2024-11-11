#include "mainwindow.h"

#include <iostream>


MainWindow::MainWindow(QWidget* parent) {

    canvas = new Canvas(this);
    setCentralWidget(canvas);
    createActions();
    createMenus();
    setWindowTitle("Leinwand"); //Canvas in German
    resize(1280, 720);
}

void MainWindow::createActions() {
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    foreach(QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(format).toUpper();
        auto* action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActions.append(action);
    }

    penColorAction = new QAction(tr("&Pen color"), this);
    connect(penColorAction, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAction = new QAction(tr("&Pen width"), this);
    connect(penWidthAction, SIGNAL(triggered()), this, SLOT(penWidth()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    clearScreenAction = new QAction(tr("&Clear"), this);
    clearScreenAction->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAction, SIGNAL(triggered()), canvas, SLOT(slotClearImage()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


}
void MainWindow::createMenus() {
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach(QAction* action, saveAsActions)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAction);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    optionMenu = new QMenu(tr("&Option"), this);
    optionMenu->addAction(penColorAction);
    optionMenu->addAction(penWidthAction);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAction);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addMenu(optionMenu);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::canSave() {
    if(canvas->isModified()) {
        QMessageBox::StandardButton button;
        button = QMessageBox::warning(this, tr("Leinwand"), tr("Do you want to save modified image?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if(button == QMessageBox::Save)
            return saveFile("png");
        else if(button == QMessageBox::Cancel)
            return false;
    }
    return true;
}


bool MainWindow::saveFile(const QByteArray& fileFormat) {
    QString path = QDir::currentPath() + "/untitled." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), path, fileFormat);

    if(fileName.isEmpty())
        return false;
    else
        return canvas->saveImage(fileName, fileFormat.constData());
}



void MainWindow::closeEvent(QCloseEvent* event) {
    if(canSave())
        event->accept();
    else
        event->ignore();
}


void MainWindow::open() {
    if(canSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
        if(!fileName.isEmpty())
            canvas->openImage(fileName);
    }
}

void MainWindow::save() {
    QAction* action = qobject_cast<QAction*>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor() {
    QColor color = QColorDialog::getColor(canvas->penColor());
    if(color.isValid())
        canvas->setPenColor(color);
}

void MainWindow::penWidth() {
    bool ok;
    int width = QInputDialog::getInt(this, "Leinwand", "Select pen width:", canvas->penWidth(), 1, 200 ,1, &ok);

    if(ok)
        canvas->setPenWidth(width);
}

void MainWindow::about() {
    QMessageBox::about(this, "About program", "Leinwand is a program for drawing");
}
















