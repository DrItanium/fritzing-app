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

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QHash>
#include <QString>
#include <QList>
#include <QXmlStreamWriter>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QPointer>

#include "../viewlayer.h"
class ConnectorShared;
class ModelPart;
class SvgIdLayer;
class ConnectorItem;
class Bus;
class Connector : public QObject
{
	Q_OBJECT
public:
	enum ConnectorType {
		Male,
		Female,
		Wire,
		Pad,
		Unknown
	};

public:
	Connector(ConnectorShared *, ModelPart * modelPart);
	~Connector();

	Connector::ConnectorType connectorType() const;
	void addViewItem(ConnectorItem *);
	void removeViewItem(ConnectorItem *);
	class ConnectorShared * connectorShared();
	void connectTo(Connector *);
	void disconnectFrom(Connector *);
	void saveAsPart(QXmlStreamWriter & writer);
	const QList<Connector *> & toConnectors();
	ConnectorItem * connectorItemByViewLayerID(ViewLayer::ViewID, ViewLayer::ViewLayerID);
	ConnectorItem * connectorItem(ViewLayer::ViewID);
	bool connectionIsAllowed(Connector* that);
	const QString & connectorSharedID() const;
	const QString & connectorSharedName() const;
	const QString & connectorSharedDescription() const;
	const QString & connectorSharedReplacedby() const;
	class ErcData * connectorSharedErcData();
	const QString & busID();
	Bus * bus();
	void setBus(class Bus *);
	long modelIndex();
	ModelPart * modelPart();
	int connectorItemCount();
	void unprocess(ViewLayer::ViewID viewID, ViewLayer::ViewLayerID viewLayerID);
	SvgIdLayer * fullPinInfo(ViewLayer::ViewID viewId, ViewLayer::ViewLayerID viewLayerID);
	const QList<SvgIdLayer *> svgIdLayers() const;
	QList< QPointer<ConnectorItem> > viewItems();
	const QString & legID(ViewLayer::ViewID, ViewLayer::ViewLayerID);
	void setConnectorLocalName(const QString &);
	constexpr const QString & connectorLocalName() const noexcept { return m_connectorLocalName; }
	void addPin(ViewLayer::ViewID, const QString & svgId, ViewLayer::ViewLayerID, const QString & terminalId, const QString & legId, bool hybrid);

public:
	static void initNames();
	static const QString & connectorNameFromType(ConnectorType);
	static ConnectorType connectorTypeFromName(const QString & name);

protected:
	void writeLayerAttr(QXmlStreamWriter &writer, ViewLayer::ViewLayerID);
	void writeSvgIdAttr(QXmlStreamWriter &writer, ViewLayer::ViewID view, QString connId);
	void writeTerminalIdAttr(QXmlStreamWriter &writer, ViewLayer::ViewID view, QString terminalId);

protected:
	QPointer<ConnectorShared> m_connectorShared;
	QPointer<ModelPart> m_modelPart;
	QPointer<Bus> m_bus;
	QHash< int, QPointer<ConnectorItem> > m_connectorItems;
	QList<Connector *> m_toConnectors;
	QString m_connectorLocalName;

protected:
	static QHash<ConnectorType, QString> Names;
};

#endif
