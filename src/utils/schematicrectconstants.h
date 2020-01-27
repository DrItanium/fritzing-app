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

#ifndef SCHEMATICRECTCONTANTS_H
#define SCHEMATICRECTCONTANTS_H

#include <QString>
#include <QList>
#include <QDomElement>

// all measurements in millimeters

class SchematicRectConstants {

public:
    static constexpr double PinWidth = 0.246944;  // millimeters
    static constexpr double PinSmallTextHeight = 0.881944444;
    static constexpr double PinBigTextHeight = 1.23472222;
    static constexpr double PinTextIndent = PinWidth * 2;   // was PinWidth * 3;
    static constexpr double PinTextVert = PinWidth * 1;
    static constexpr double PinSmallTextVert = -PinWidth / 2;
    static constexpr double LabelTextHeight = 1.49930556;
    static constexpr double LabelTextSpace = 0.1;
    static constexpr double RectStrokeWidth = 0.3175;
    static constexpr double NewUnit = 0.1 * 25.4;      // .1in in mm

	static const QString PinColor;
	static const QString PinTextColor;
	static const QString TitleColor;
	static const QString RectStrokeColor;
	static const QString RectFillColor;

	static const QString FontFamily;

public:
	static QString genSchematicDIP(QList<QDomElement> & powers, QList<QDomElement> & grounds, QList<QDomElement> & lefts,
	                               QList<QDomElement> & rights, QList<QDomElement> & vias, QStringList & busNames,
	                               QString & boardName, bool usingParam, bool genericSMD, QString (*getConnectorName)(const QDomElement &));
	static QString simpleGetConnectorName(const QDomElement & element);

};


#endif
