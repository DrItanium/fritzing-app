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

#ifndef MODELPARTSHARED_H
#define MODELPARTSHARED_H

#include <QDomDocument>
#include <QDomElement>
#include <QList>
#include <QStringList>
#include <QHash>
#include <QDate>
#include <QPointer>

#include "../viewlayer.h"

#include <functional>

struct ViewImage {
	ViewLayer::ViewID viewID;
	qulonglong layers = 0;
	qulonglong sticky = 0;
	qulonglong flipped = 0;
	QString image;
	bool canFlipHorizontal = false;
	bool canFlipVertical = false;

	ViewImage(ViewLayer::ViewID) noexcept;
};

class ModelPartShared : public QObject
{
	Q_OBJECT
public:
	ModelPartShared() = default;
	ModelPartShared(QDomDocument &, const QString & path);
	~ModelPartShared();

	//QDomDocument * domDocument();

	void copy(ModelPartShared* other);

	const QString & uri() const noexcept { return m_uri; }
	void setUri(QString);
	const QString & moduleID() const noexcept { return m_moduleID; }
	void setModuleID(QString);
	const QString & version() const noexcept { return m_version; }
	void setVersion(QString);
	const QString & author() const noexcept { return m_author; }
	void setAuthor(QString);
	const QString & description() const noexcept { return m_description; }
	void setDescription(QString);
	const QString & spice() const noexcept { return m_spice; }
	void setSpice(QString);
	const QString & spiceModel() const noexcept { return m_spiceModel; }
	void setSpiceModel(QString);
	const QString & url() const noexcept { return m_url; }
	void setUrl(QString);
	const QString & title() const noexcept { return m_title; }
	void setTitle(QString);
	const QString & label() const noexcept { return m_label; }
	void setLabel(QString);
	const QDate & date();
	void setDate(QDate);
	const QString & dateAsStr() const noexcept { return m_date; }
	void setDate(QString);
	void setDBID(qulonglong);
	constexpr qulonglong dbid() const noexcept { return m_dbid; }
	const QString & fritzingVersion() const noexcept { return m_fritzingVersion; }
	void setFritzingVersion(const QString &);

	const QList<ViewImage *> viewImages();
	QString imageFileName(ViewLayer::ViewID, ViewLayer::ViewLayerID);
	void setImageFileName(ViewLayer::ViewID, const QString & filename);
	QString imageFileName(ViewLayer::ViewID);
	const QList< QPointer<ModelPartShared> > & subparts() const noexcept { return m_subparts; }
	void addSubpart(ModelPartShared * subpart);
	bool hasSubparts() const noexcept { return m_subparts.count() > 0; }
	void setSubpartID(const QString &);
	const QString & subpartID() const noexcept { return m_subpartID; }
	ModelPartShared * superpart();
	void setSuperpart(ModelPartShared *);
	bool anySticky(ViewLayer::ViewID);
	bool hasMultipleLayers(ViewLayer::ViewID);
	bool canFlipHorizontal(ViewLayer::ViewID);
	bool canFlipVertical(ViewLayer::ViewID);
	bool hasViewID(ViewLayer::ViewID viewID);
	LayerList viewLayers(ViewLayer::ViewID viewID);
	LayerList viewLayersFlipped(ViewLayer::ViewID viewID);

	const QString & path();
	void setPath(QString path);
	const QString & taxonomy();
	void setTaxonomy(QString taxonomy);

	const QList< QPointer<class ConnectorShared> > connectorsShared();
	void setConnectorsShared(QList< QPointer<class ConnectorShared> > connectors);
	void connectorIDs(ViewLayer::ViewID viewId, ViewLayer::ViewLayerID viewLayerID, QStringList & connectorIDs, QStringList & terminalIDs, QStringList & legIDs);

	const QStringList &tags() const noexcept { return m_tags; }
	void setTags(const QStringList &tags);
	void setTag(const QString &tag);

	QString family();
	void setFamily(const QString &family);

	QHash<QString,QString> & properties();
	void setProperties(const QHash<QString,QString> &properties);
	const QStringList & displayKeys() const noexcept { return m_displayKeys; }


	void initConnectors();
	void setConnectorsInitialized(bool);
	ConnectorShared * getConnectorShared(const QString & id);
	constexpr bool ignoreTerminalPoints() const noexcept { return m_ignoreTerminalPoints; }

	void setProperty(const QString & key, const QString & value, bool showInLabel);
	bool showInLabel(const QString & key);
	const QString & replacedby() const noexcept { return m_replacedby; }
	void setReplacedby(const QString & replacedby);

	void flipSMDAnd();
	void setFlippedSMD(bool);
	constexpr bool flippedSMD() const noexcept { return m_flippedSMD; }
	constexpr bool needsCopper1() const noexcept { return m_needsCopper1; }
	bool hasViewFor(ViewLayer::ViewID);
	bool hasViewFor(ViewLayer::ViewID, ViewLayer::ViewLayerID);
	QString hasBaseNameFor(ViewLayer::ViewID);
	void setViewImage(ViewImage *);
	void addConnector(ConnectorShared *);
	void insertBus(class BusShared *);
	void lookForZeroConnector();
	constexpr bool hasZeroConnector() const noexcept { return m_hasZeroConnector; }
	void addOwner(QObject *);
	void setSubpartOffset(QPointF);
	QPointF subpartOffset() const noexcept { return m_subpartOffset; }

protected:
	void loadTagText(QDomElement parent, QString tagName, QString &field);
	// used to populate de StringList that contains both the <tags> and the <properties> values
	void populateTags(QDomElement parent, QStringList &list);
	void populateProperties(QDomElement parent, QHash<QString,QString> &hash, QStringList & displayKeys);
	void ensurePartNumberProperty();
	void copyPins(ViewLayer::ViewLayerID from, ViewLayer::ViewLayerID to);
	LayerList viewLayersAux(ViewLayer::ViewID viewID, std::function<qulonglong(ViewImage*)> accessor);
	void addSchematicText(ViewImage *);
	bool setDomDocument(QDomDocument &);

protected slots:
	void removeOwner();

public:
	static const QString PartNumberPropertyName;

protected:

	//QDomDocument* m_domDocument;

	QString m_uri;
	QString m_moduleID;
	QString m_fritzingVersion;
	QString m_version;
	QString m_author;
	QString m_title;
	QString m_label;
	QString m_description;
	QString m_spice;
	QString m_spiceModel;
	QString m_url;
	QString m_date;
	QString m_replacedby;

	QString m_path;
	QString m_taxonomy;

	QStringList m_tags;
	QStringList m_displayKeys;
	QHash<QString,QString> m_properties;

	QHash<QString, QPointer<class ConnectorShared> > m_connectorSharedHash;
	QHash<QString, class BusShared *> m_buses;
	QHash<ViewLayer::ViewID, ViewImage *> m_viewImages;

	bool m_connectorsInitialized = false;
	bool m_ignoreTerminalPoints = false;

	bool m_flippedSMD = false;
	bool m_needsCopper1 = false;				// for converting pre-two-layer parts
	qulonglong m_dbid = 0;
	bool m_hasZeroConnector = false;
	int m_ownerCount = 0;
	QList< QPointer<ModelPartShared> > m_subparts;
	QPointer<ModelPartShared> m_superpart;
	QString m_subpartID;
	QPointF m_subpartOffset;
};

class ModelPartSharedRoot : public ModelPartShared
{
	Q_OBJECT
public:
	const QString & icon() const noexcept ;
	void setIcon(const QString & filename);
	const QString & searchTerm() const noexcept;
	void setSearchTerm(const QString & searchTerm);

protected:
	QString m_icon;
	QString m_searchTerm;

};


#endif
