/****************************************************************************
 **
 ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 ** Contact: Qt Software Information (qt-info@nokia.com)
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain
 ** additional rights. These rights are described in the Nokia Qt LGPL
 ** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
 ** package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you are unsure which license is appropriate for your use, please
 ** contact the sales department at qt-sales@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <QtGui>

#include "graphicsscene.h"
#include "connection.h"
#include <QStringList>
#include <QString>
#include <QPainter>
#include "pin.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QDialog>
#include <QInputDialog>

GraphicsScene::GraphicsScene(QMenu *itemMenu, QObject *parent) :
	QGraphicsScene(parent) {
	myItemMenu = itemMenu;
	myMode = MoveItem;
	line = 0;
}

void GraphicsScene::setMode(Mode mode) {
	myMode = mode;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (mouseEvent->button() != Qt::LeftButton) {
		//		if()
		//		QList<QGraphicsItem *> startItems = items(line->line().p1());
		return;
	}

	switch (myMode) {
	case InsertItem: {
		Component *item;

//		//Búa til dummy upplýsingar til að búa til item:
//		QString name = "Type.Component.InstanceID";
//		QStringList inputs;
//		inputs << "input-1" << "input-2";
//		QStringList outputs;
//		outputs << "output-1" << "output-2" << "output-3";
//		//*************************************************

		bool ok;
		QInputDialog dialog;
		QStringList inputs;
		QStringList outputs;

		QString name = dialog.getText(0, "Name of component","type.component.instanceID", QLineEdit::Normal, "type.component.instanceID", &ok, Qt::Tool);
		int inputsNr = dialog.getInteger(0,"Number of inputs","",1,1,30,1,&ok, Qt::Tool);
		int outputsNr = dialog.getInteger(0,"Number of outputs","",1,1,30,1,&ok, Qt::Tool);

		for (int i = 1;i <= inputsNr;i++)
			inputs << "input";// + QString::toInt(i);
		for (int i = 1;i <= outputsNr;i++)
			outputs << "output";// + QString::toInt(i);

		//if (ok && !text.isEmpty())

		item = new Component(name, inputs, outputs, myItemMenu);
		addItem(item);

		item->setPos(mouseEvent->scenePos());
		emit itemInserted(item);

		////vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
		//		            QList <QGraphicsItem *> items;
		//		            items << item;// << item->childItems();
		//		            QGraphicsItemGroup *group = createItemGroup(items);
		//		            group->setFlag(QGraphicsItem::ItemIsMovable, true);
		//		           	group->setFlag(QGraphicsItem::ItemIsSelectable, true);

		//        	QGraphicsLineItem *testPin = new QGraphicsLineItem(-200,0,200,0);
		//
		//        	 QPen pen;  // creates a default pen
		//        	 pen.setStyle(Qt::DashDotLine);
		//        	 pen.setWidth(5);
		//        	 pen.setBrush(Qt::green);
		//        	 pen.setCapStyle(Qt::RoundCap);
		//        	 pen.setJoinStyle(Qt::RoundJoin);
		//
		//        	testPin->setPen(pen);
		//
		//        	testPin->setFlag(QGraphicsItem::ItemIsMovable, true);
		//        	testPin->setFlag(QGraphicsItem::ItemIsSelectable, true);
		//
		//        	addItem(testPin);
		//        	testPin->setPos(mouseEvent->scenePos());
		//
		//
		////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	}
		break;

	case InsertLine:
		line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
				mouseEvent->scenePos()));
		line->setPen(QPen(Qt::black, 2));
		addItem(line);
		line->setZValue(1000.0);
		break;
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (myMode == InsertLine && line != 0) {
		QLineF newLine(line->line().p1(), mouseEvent->scenePos());
		line->setLine(newLine);
	} else if (myMode == MoveItem) {
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (line != 0 && myMode == InsertLine) {
		QList<QGraphicsItem *> startItems = items(line->line().p1());
		QList<QGraphicsItem *> endItems = items(line->line().p2());

		while (startItems.count() && startItems.first()->type() != Pin::Type) {
			startItems.removeFirst();
		}
		while (endItems.count() && endItems.first()->type() != Pin::Type)
			endItems.removeFirst();
		//Nú innihalda start og end -Items annaðhvort null eða pinna í hólfi .first()
		removeItem(line);
		delete line;

		Pin *startItem = 0;
		Pin *endItem = 0;

		//búa til startItem og endItem
		//skilyrðin eru að þau séu af týpunni Pin
		if (startItems.count() && endItems.count()
				&& startItems.first()->type() == Pin::Type
				&& endItems.first()->type() == Pin::Type) {
			startItem = qgraphicsitem_cast<Pin *> (startItems.first());
			endItem = qgraphicsitem_cast<Pin *> (endItems.first());
		}

		//búa til tengingar
		//skilyrðið er:
		//	upphaf og endir tengingar er ekki sá sami
		//	tengingarnar eru ekki af sömu pinnaTegund (slot/signal)
		//	tengingarnar séu ekki á sama component
		if (startItem != 0 && endItem != 0 && startItem != endItem
				&& startItem->pinType() != endItem->pinType()
				&& startItem->parentItem() != endItem->parentItem()) {

			Connection *connection = new Connection(startItem, endItem);
			connection->setColor(myLineColor);
			connection->setZValue(1000.0);

			addItem(connection);
			connection->updatePosition();

			//láta pinnana vita af tengingunni við hvorn annann
			startItem->setConnectedTo(endItem, connection);
			endItem->setConnectedTo(startItem, connection);

		}
		//********old insertline
		//        QList<QGraphicsItem *> startItems = items(line->line().p1());
		//        QList<QGraphicsItem *> endItems = items(line->line().p2());
		//
		//        while(startItems.count() && startItems.first()->type() != Component::Type)
		//            startItems.removeFirst();
		//        while(endItems.count() && endItems.first()->type() != Component::Type)
		//            endItems.removeFirst();
		//
		//        removeItem(line);
		//        delete line;
		//        if (startItems.count() > 0)
		//        if (startItems.count() > 0 && endItems.count() > 0 &&
		//            startItems.first()->type() == Component::Type &&
		//            endItems.first()->type() == Component::Type &&
		//            startItems.first() != endItems.first()) {
		//            Component *startItem =
		//                qgraphicsitem_cast<Component *>(startItems.first());
		//            Component *endItem =
		//                qgraphicsitem_cast<Component *>(endItems.first());
		//            Arrow *arrow = new Arrow(startItem, endItem);
		//            arrow->setColor(myLineColor);
		//            startItem->addArrow(arrow);
		//            endItem->addArrow(arrow);
		//            arrow->setZValue(-1000.0);
		//            addItem(arrow);
		//            arrow->updatePosition();
		//        }

	}

	line = 0;
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
void GraphicsScene::addItem(QGraphicsItem *item) {
	//þetta fall hefur ekki verið prófað!
	//bæta item við í listann af annaðhvort connections eða componentum
	if (item->type() == Connection::Type)
		qDebug() << "Added a connection to myConnections";
	myConnections << qgraphicsitem_cast<Connection *> (item);
	if (item->type() == Component::Type)
		qDebug() << "Added a component to myComponents";
	myComponents << qgraphicsitem_cast<Component *> (item);
	QGraphicsScene::addItem(item);
}

void GraphicsScene::removeItem(QGraphicsItem *item) {
	//þetta fall hefur ekki verið prófað!
	//Taka item úr lista af annaðhvort connections eða componentum
	if (item->type() == Connection::Type) {
		qDebug() << "Removed a connection from myConnections";
		int indexOf = myConnections.indexOf(qgraphicsitem_cast<Connection *> (
				item));
		if (indexOf != -1)
			myConnections.removeAt(indexOf);
	}

	if (item->type() == Component::Type) {
		qDebug() << "removed a component from myComponents";
		int indexOf = myComponents.indexOf(
				qgraphicsitem_cast<Component*> (item));
		if (indexOf != -1)
			myComponents.removeAt(indexOf);
	}
	QGraphicsScene::removeItem(item);
}
