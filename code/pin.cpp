/*
 * pin.cpp
 *
 *  Created on: Aug 18, 2009
 *      Author: frimann
 */

#include "pin.h"
#include <QMessageBox>

Pin::Pin(qreal x, qreal y, qreal width, qreal height, PinType pinType,
		QGraphicsItem * parent) :
	QGraphicsEllipseItem(0, 0, width, height, parent) {

	myConnection = 0;
	myPinType = pinType;

	QPen pen;
	pen.setWidth(2);
	pen.setBrush(Qt::black);
	setPen(pen);
	setBrush(Qt::white);
	setFlag(QGraphicsItem::ItemIsSelectable, true);

	setPos(x, y);
}

void Pin::setConnectedTo(Pin *pin, Connection *connection) {

	if (pin->pinType() == Pin::Signal && 		//pinna típa mín er signal &&
			connectedTo.indexOf(pin) == -1) { 	// pin er ekki nú þegar tengdur)
		connectedTo << pin; 					//bæta pin við connectedTo array
	}
	if (pin->pinType() == Pin::Slot && 			//pinna týpa mín er slot)
			connectedTo.indexOf(pin) == -1) { 	//pin er ekki nú þegar tengdur
		connectedTo.clear(); 					//hreinsa arrayið
		connectedTo << pin; 					//setja pin í fyrsta item í connectedTo
		myConnection = connection;
	}

}

