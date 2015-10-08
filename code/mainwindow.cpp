#include <QtGui>

#include "mainwindow.h"
#include "component.h"
#include "graphicsscene.h"

const int InsertTextButton = 10;
const int InsertItemButton = 0;

MainWindow::MainWindow()
{
    createActions();
    createMenus();

    scene = new GraphicsScene(itemMenu);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(Component *)),
            this, SLOT(itemInserted(Component *)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem *)),
        this, SLOT(itemSelected(QGraphicsItem *)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("PinConnect"));
}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        if (item->type() == Component::Type) { //athugar hvaða tala er í type
        	qgraphicsitem_cast<Component *>(item)->removeConnections();
        }
        scene->removeItem(item);
    }
}

void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(GraphicsScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::bringToFront()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue &&
            item->type() == Component::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::sendToBack()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue &&
            item->type() == Component::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::itemInserted(Component *item)
{
    pointerTypeGroup->button(int(GraphicsScene::MoveItem))->setChecked(true);
    scene->setMode(GraphicsScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
	//Hér gæti komið fall sem geri notandanum kleyft að breita upplýsingum um
	//þann hlut sem er valinn. T.d. nafn á component, slots/signals og þess
	//háttar.

}
void MainWindow::about()
{
    QMessageBox::about(this, tr("About QT4PinConnect"),
                       tr("<b>QT4PinConnect</b> is a GUI program"
                          "for managing connections between"
                    	  "signals and slots of components."));
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()),
            this, SLOT(bringToFront()));

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"),
                                 tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+B"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()),
        this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"),
                               tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()),
        this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Alt+F4"));
    exitAction->setStatusTip(tr("Quit QT4PinConnect"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));

    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    QToolButton *itemPointerButton = new QToolButton;
    itemPointerButton->setCheckable(true);
    itemPointerButton->setIcon(QIcon(":/images/rectangle.png"));

    pointerTypeGroup = new QButtonGroup;
    pointerTypeGroup->addButton(pointerButton, int(GraphicsScene::MoveItem));
    // int(GraphicsScene::MoveItem) skilar 3 því MoveItem er hlutur nr (3+1) í enum Mode.
    pointerTypeGroup->addButton(itemPointerButton, int(GraphicsScene::InsertItem));
    pointerTypeGroup->addButton(linePointerButton,
                                int(GraphicsScene::InsertLine));

    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("25%") << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(3);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(sceneScaleChanged(const QString &)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(itemPointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
}

