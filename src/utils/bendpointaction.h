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
    using QAction::QAction;

	void setLastHoverEnterConnectorItem(class ConnectorItem *) noexcept;
	void setLastHoverEnterItem(class ItemBase *) noexcept;
	void setLastLocation(QPointF) noexcept;
	ConnectorItem * lastHoverEnterConnectorItem() noexcept;
	ItemBase * lastHoverEnterItem() noexcept;
	QPointF lastLocation() noexcept;

protected:
	ConnectorItem * m_lastHoverEnterConnectorItem = nullptr;
	ItemBase * m_lastHoverEnterItem = nullptr;
	QPointF m_lastLocation;

};

#endif
