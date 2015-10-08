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
#include <QPainter>
#include <QColor>

#include "component.h"
#include "connection.h"
#include "pin.h"

Component::Component(QString name, QStringList inputs, QStringList outputs,
		QMenu *contextMenu, QGraphicsItem *parent, QGraphicsScene *scene) :
	QGraphicsPolygonItem(parent, scene), mySlots(inputs), mySignals(outputs),
			myName(name), myContextMenu(contextMenu) {
	minDeviceWidth = 100;
	maxDeviceWidth = 200;
	minDeviceHeight = 100;
	maxDeviceHeight = 600;
	deviceEdgeThickness = 2;
	bewelOfDeviceEdges = 15;
	spaceBetweenPins = 20;
	numberOfSlots = mySlots.size();
	numberOfSignals = mySignals.size();


	QGraphicsTextItem *nameTag = pTailorTextItem(myName, maxDeviceWidth - 20,
			maxDeviceHeight - 40, this);

	widthOfName = nameTag->boundingRect().width();
	heightOfName = nameTag->boundingRect().height();
	nameTag->setPos(-widthOfName / 2, -heightOfName / 2);

	if (widthOfName + 20 < minDeviceWidth)
		myWidth = minDeviceWidth;
	else if (widthOfName + 20 > maxDeviceWidth)
		myWidth = maxDeviceWidth;
	else
		myWidth = widthOfName + 20;
	//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	Pin *tempPin;

//Búa til Signöl
	Pin::PinType myPinType = Pin::Signal;

	for (int i = 0; i < numberOfSignals; i++) {
		tempPin = new Pin(
				myWidth / 2 - 6 , spaceBetweenPins*i - (numberOfSignals-1)*spaceBetweenPins/2 - 6,
				12, 12, myPinType, this);

		mySignalPins << tempPin;
	}
	tempPin = 0;

//Búa til Slotts
	myPinType = Pin::Slot;

	for (int i = 0; i < numberOfSlots; i++) {
		tempPin = new Pin(
				- myWidth / 2 - 6 , spaceBetweenPins*i - (numberOfSlots-1)*spaceBetweenPins/2 - 6,
				12, 12, myPinType, this);

		mySlotPins << tempPin;
	}
	tempPin = 0;

//	QGraphicsEllipseItem *testEllipse = new QGraphicsEllipseItem(10,10,10,10,this);
//	testEllipse->setBrush(Qt::white);
//	testEllipse->setPen(pen);

// reikna hversu hár kassinn má vera


	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	int childItemsHeight = qMax(heightOfName, qMax(numberOfSignals*spaceBetweenPins,numberOfSlots*spaceBetweenPins));

	if (childItemsHeight + 40 < minDeviceHeight)
			myHeight = minDeviceHeight;
	else if (childItemsHeight + 40 > maxDeviceHeight)
		myHeight = maxDeviceHeight;
	else
		myHeight = childItemsHeight + 40;

	myTopLeft = QPointF(-(myWidth / 2), -myHeight / 2);
	myBottomRight = QPointF(myWidth / 2, myHeight / 2);

	QPainterPath path;
	path.addRoundRect(QRectF(myTopLeft, myBottomRight), 100, bewelOfDeviceEdges
			* 100 / myHeight);

	myPolygon = path.toFillPolygon();
	setPen(QPen(Qt::black, deviceEdgeThickness));
	setBrush(QColor(200, 200, 200, 255));
	setPolygon(myPolygon);

	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	//	QList<QGraphicsItem *> allTheItems;
	//	allTheItems << nameTag << testPin ;
	//	QGraphicsItemGroup *group = scene->createItemGroup(allTheItems);
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

}
QGraphicsTextItem * Component::pTailorTextItem(QString name,
		int maxItemWidth, int maxItemHeight, QGraphicsItem *parent) {

	QGraphicsTextItem *textItem = new QGraphicsTextItem(name, parent);
	//Athuga hvort nafnið í heild sé of stórt fyrir línuna.
	//Ef ef ekki þá er því skilað. Annars er smíðað nýtt textItem sem skiptist í línur.
	if (textItem->boundingRect().width() < maxItemWidth)
		return textItem;

	delete textItem;
	textItem = 0;
	QGraphicsTextItem *textItemTemp;
	QString lineTemp = "";
	QStringList lineTempList;
	QStringList myNameList = name.split(".", QString::SkipEmptyParts);

	//Skipta nafninu í QStringList array af QString línum sem eru passlega stórar
	for (int i = 0; i < myNameList.size(); i++) {
		textItemTemp = new QGraphicsTextItem(myNameList[i] + ".", parent);
		//athugar hvort stakt orð sé of stórt fyrir línuna
		if (textItemTemp->boundingRect().width() > maxItemWidth) {
			delete textItemTemp;
			textItemTemp = 0;
			QString wordTemp = lineTemp;//???
			QStringList wordTempList;
			QStringList letterList;

			//skipta orðinu í array þar sem er einn stafur í hverju hólfi
			for (int k = 0; k < myNameList[i].size(); k++) {
				letterList << myNameList[i].at(k);
			}

			//skipta orðinu í array af línum sem eru passlega stórar
			for (int k = 0; k < letterList.size(); k++) {
				textItemTemp = new QGraphicsTextItem(wordTemp + letterList[k]
						+ ".", parent);
				if (textItemTemp->boundingRect().width() < maxItemWidth) {
					wordTemp += letterList[k];
				} else {
					lineTempList << wordTemp;
					wordTemp = letterList[k];
				}
				//athuga hvort að við séum kominn á endann á orðinu
				if (letterList.size() == k + 1) {
					lineTemp = wordTemp;
				}
				delete textItemTemp;
				textItemTemp = 0;
			}
		}
		//Ef stakt orð er ekki of stórt þá bætum við því við línuna og athugum
		// hvort línan sé orðin of stór. Ef svo, þá er orðinu ekki bætt við línuna
		// heldur búin til ný lína og orðið sett fremst í hana.
		else {
			delete textItemTemp;
			textItemTemp = new QGraphicsTextItem(
					lineTemp + myNameList[i] + ".", parent);
			if (textItemTemp->boundingRect().width() < maxItemWidth) {
				lineTemp += myNameList[i];
			} else {
				lineTempList << lineTemp;
				lineTemp = myNameList[i];
			}
			delete textItemTemp;
			textItemTemp = 0;
		}
		//athuga hvort að við séum kominn á endann á nafninu
		if (myNameList.size() == i + 1)
			lineTempList << lineTemp;
		else
			lineTemp += ".";
	}
	delete textItemTemp;
	textItemTemp = 0;
	delete textItem;

	//sníðum nýtt textItem sem skiptist niður í línur, en er ekki of stórt m.v. maxItemHeight
	textItem = new QGraphicsTextItem(lineTempList.join("\n"), parent);
	while (textItem->boundingRect().height() > maxItemHeight
			&& lineTempList.size() > 1) {
		delete textItem;
		lineTempList.removeLast();
		int listSize = lineTempList.size();
		textItemTemp = new QGraphicsTextItem(lineTempList[listSize - 1]
				+ "....");
		while (textItemTemp->boundingRect().width() > maxItemWidth) {
			delete textItemTemp;
			int lineSize = lineTempList[lineTempList.size() - 1].size(); //count of letters in this line
			lineTempList[listSize - 1].remove(lineSize - 1, 1);
			textItemTemp = new QGraphicsTextItem(lineTempList[listSize - 1]
					+ "....");
		}
		delete textItemTemp;
		lineTempList[listSize - 1] += "....";
		textItem = new QGraphicsTextItem(lineTempList.join("\n"), parent);
	}
	return textItem;
}

void Component::removeConnection(Connection *connection) {
	int index = connections.indexOf(connection);
	if (index != -1)
		connections.removeAt(index);
}

void Component::removeConnections() {
	foreach (Connection *connection, connections)
		{
//			arrow->startItem()->removeArrow(arrow);
//			arrow->endItem()->removeArrow(arrow);
//			scene()->removeItem(arrow);
//			delete arrow;
		}
}

//void Component::addConnection(Connection *connection) {
//	connections.append(connection);
//}

QVariant Component::itemChange(GraphicsItemChange change,
		const QVariant &value) {
	if (change == ItemPositionChange && scene()) {
		int i = 0;


//		QList<Connection *> connectionlist = scene->getConnections();
//		qDebug() << "connections are " + QString::number(m);

//		foreach (Connection *connection, connections)
//			{
//				connection->updatePosition();
//				qDebug() << i++;
//			}
	}

	  if (change == ItemPositionChange && scene()) {
	         // value is the new position.
	         QPointF newPos = value.toPointF();
	         QRectF rect = scene()->sceneRect();
	         if (!rect.contains(newPos)) {
	             // Keep the item inside the scene rect.
	             newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
	             newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
	             return newPos;
	         }
	     }

	     return QGraphicsItem::itemChange(change, value);
}
