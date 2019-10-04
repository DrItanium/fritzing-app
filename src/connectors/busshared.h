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

#ifndef BUSSHARED_H
#define BUSSHARED_H

#include <QString>
#include <QDomElement>
#include <QHash>
#include <QList>
#include <QXmlStreamWriter>
#include <QPointer>

class ConnectorShared;
class BusShared {

public:
	BusShared(const QDomElement & busElement, const QHash<QString, QPointer<ConnectorShared> > & connectorHash);
	BusShared(const QString & id);

	constexpr const QString & id() const noexcept { return m_id; }
	const QList<class ConnectorShared *> & connectors() const noexcept;
	void addConnectorShared(ConnectorShared *);

protected:
	void initConnector(QDomElement & connector, const QHash<QString, QPointer<ConnectorShared> > & connectorHash);

protected:
	QString m_id;
	QList<ConnectorShared *> m_connectors;
};

#endif
