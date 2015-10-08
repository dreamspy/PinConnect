/*
 * pin.h
 *
 *  Created on: Aug 18, 2009
 *      Author: frimann
 */

#ifndef PIN_H_
#define PIN_H_

#include <QGraphicsLineItem>

#include "component.h"

QT_BEGIN_NAMESPACE
class QGraphicsEllipseItem;
QT_END_NAMESPACE

class Pin : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 20 };
    enum PinType{ Signal, Slot};

    Pin(qreal x, qreal y, qreal width, qreal height, PinType pinType, QGraphicsItem * parent = 0 );

    int type() const
        { return Type; }
    int pinType() const
        { return myPinType; }
    void setConnectedTo(Pin *pin, Connection *connection);
    QList<Pin *> myConnections()
		{return connectedTo; }

private:
    PinType myPinType;
    Connection *myConnection;
    QList<Pin *> connectedTo;

};

#endif /* PIN_H_ */

