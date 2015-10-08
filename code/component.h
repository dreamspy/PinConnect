/*
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

#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QPen>

class Connection;
class Pin;

class Component : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };
    //UserType = 65536    unique identifier of this class, used for the qgraphicsitem_cast

    Component(QString name, QStringList inputs, QStringList outputs, QMenu *contextMenu,
        QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void removeConnection(Connection *connection);
    void removeConnections();
    QPolygonF polygon() const
        { return myPolygon; }
//    void addConnection(Connection *connection);
    int type() const
        { return Type;}

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QGraphicsTextItem * pTailorTextItem(QString name,int maxLineWidth, int maxItemHeight,  QGraphicsItem *parent = 0);

private:
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Connection *> connections;
    QPointF myTopLeft;
    QPointF myBottomRight;
	QString myName;
	QStringList mySlots;
	QStringList mySignals;
    int widthOfName;
    int heightOfName;
    int minDeviceWidth;
    int maxDeviceWidth;
    int minDeviceHeight;
	int maxDeviceHeight;
    int myWidth;
    int myHeight;
    int deviceEdgeThickness;
    int bewelOfDeviceEdges;
    int spaceBetweenPins;
	int numberOfSlots;
	int numberOfSignals;
	QList<Pin *> mySignalPins;
	QList<Pin *> mySlotPins;


};
#endif
