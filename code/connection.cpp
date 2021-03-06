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

#include "connection.h"
#include <math.h>
#include "pin.h"
const qreal Pi = 3.14;

//! [0]
Connection::Connection(Pin *startItem, Pin *endItem, QGraphicsItem *parent,
		QGraphicsScene *scene) :
	QGraphicsLineItem(parent, scene) {
	if(startItem->type() == Pin::Signal){
		mySignal = startItem;
		mySlot = endItem;
	}
	else{
		mySignal = endItem;
		mySlot = startItem;
	}

//	setFlag(QGraphicsItem::ItemIsSelectable, true);
	myColor = Qt::black;
	setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

}

QRectF Connection::boundingRect() const {
	qreal extra = 300;//(pen().width() + 20) / 2.0;
	//
	//	qDebug() << "line().p2().x() - line().p1().x() = " << line().p2().x()
	//			- line().p1().x();
	//	qDebug() << "line().p2().y() - line().p1().y() = " << line().p2().y()
	//			- line().p1().y();
	//	qDebug() << "-----------------------------------------";
	//
	//
	//	return QRectF(line().p1(),QSizeF(-350,-50))
	//			.normalized()
	//			.adjusted(-extra,-extra, extra, extra);

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
			line().p2().y() - line().p1().y())) .normalized() .adjusted(-extra,
			-extra, extra, extra);

}
//! [1]

//! [2]
QPainterPath Connection::shape() const {
	QPainterPath path = QGraphicsLineItem::shape();
//	path.addPolygon(arrowHead);
	return path;
}
void Connection::updatePosition() {
	QLineF line(mapFromItem(mySignal, 0, 0), mapFromItem(mySlot, 0, 0));
	setLine(line);
}
//! [3]

//! [4]
void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
		QWidget *) {
//		if (mySignal->parentItem()->collidesWithItem(mySlot->parentItem()))
//			return;

	QPen myPen = pen();
	myPen.setColor(myColor);
//	qreal arrowSize = 20;
	painter->setPen(myPen);
	painter->setBrush(myColor);
	//! [4] //! [5]

	//Kóði sem kannar hvar intersection á línunni við mySlot er:
	//	QLineF centerLine(mySignal->scenePos(), mySlot->scenePos());
	//	QPolygonF endPolygon = mySlot->polygon();
	//	QPointF p1 = endPolygon.first() + mySlot->pos();
	//	QPointF p2;
	//	QPointF intersectPoint;
	//	QLineF polyLine;
	//	for (int i = 1; i < endPolygon.count(); ++i) {
	//		p2 = endPolygon.at(i) + mySlot->pos();
	//		polyLine = QLineF(p1, p2);
	//		QLineF::IntersectType intersectType = polyLine.intersect(centerLine,
	//				&intersectPoint);
	//		if (intersectType == QLineF::BoundedIntersection)
	//			break;
	//		p1 = p2;
	//	}

	setLine(QLineF(mySlot->scenePos() + QPointF(6, 6),
				   mySignal->scenePos() + QPointF(6, 6)));

	//	QPointF parentPos(mySlot->parentItem()->pos());
	//	setLine(QLineF(mySlot->pos() + parentPos, mySignal->pos() + parentPos));
	//

	//! [5] //! [6]

	//Teiknar örvar hausinn
	//	double angle = ::acos(line().dx() / line().length());
	//	if (line().dy() >= 0)
	//		angle = (Pi * 2) - angle;
	//
	//	QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
	//			cos(angle + Pi / 3) * arrowSize);
	//	QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3)
	//			* arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
	//
	//	arrowHead.clear();
	//	arrowHead << line().p1() << arrowP1 << arrowP2;
	//! [6] //! [7]

	painter->drawLine(line());
	painter->drawEllipse(line().p1(), 2, 2);
	painter->drawEllipse(line().p2(), 2, 2);
	//	painter->drawPolygon(arrowHead);
	if (isSelected()) {
		painter->setPen(QPen(myColor, 1, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0, -8.0);
		painter->drawLine(myLine);
	}
}
//! [7]
