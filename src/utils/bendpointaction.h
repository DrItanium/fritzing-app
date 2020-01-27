/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2019 Fritzing

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************/

#ifndef BENDPOINTACTION_H
#define BENDPOINTACTION_H

#include <QAction>
#include <QPointF>
#include <QString>

class ConnectorItem;
class ItemBase;
class BendpointAction : public QAction
{
	Q_OBJECT
public:
	BendpointAction(const QString & text, QObject * parent);

	void setLastHoverEnterConnectorItem(ConnectorItem *);
	void setLastHoverEnterItem(ItemBase *);
	void setLastLocation(QPointF);
	ConnectorItem * lastHoverEnterConnectorItem();
	ItemBase * lastHoverEnterItem();
	constexpr const QPointF& lastLocation() const noexcept { return m_lastLocation; }

protected:
	ConnectorItem * m_lastHoverEnterConnectorItem = nullptr;
	ItemBase * m_lastHoverEnterItem = nullptr;
	QPointF m_lastLocation;

};

#endif
