#include "mainwindow.h"


#include <QAction>
#include <QFileDialog>
#include <QMenuBar>

MainWindow::MainWindow()
{
    itemWidget = new item_widget;
    setCentralWidget(itemWidget);
    createMenus();
    setWindowTitle(tr("Rent Split"));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save as..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    toolMenu = menuBar()->addMenu(tr("&Tools"));

    addAct =  new QAction(tr("&Add Bill"), this);
    toolMenu->addAction(addAct);
    connect(addAct, &QAction::triggered, itemWidget, &item_widget::showAddEntryDialog);

    editAct =  new QAction(tr("&Edit Bill"), this);
    editAct->setEnabled(false);
    toolMenu->addAction(editAct);
    connect(editAct, &QAction::triggered, itemWidget, &item_widget::editEntry);

    toolMenu->addSeparator();

    removeAct =  new QAction(tr("&Remove Bill"), this);
    removeAct->setEnabled(false);
    toolMenu->addAction(removeAct);
    connect(removeAct, &QAction::triggered, itemWidget, &item_widget::removeEntry);

    connect(itemWidget, &item_widget::selectionChanged, this, &MainWindow::updateActions);

}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
        itemWidget->readFromFile(fileName);
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if(!fileName.isEmpty())
        itemWidget->writeToFile(fileName);
}
void MainWindow::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if(!indexes.isEmpty()){
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }

}
