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

#ifndef SVGIDLAYER_H
#define SVGIDLAYER_H

#include <QString>

#include "../viewlayer.h"


struct PointRect {
	QRectF rect;
	QPointF point;
	bool processed = false;
	bool svgVisible = false;
};

class SvgIdLayer
{
public:
	SvgIdLayer(ViewLayer::ViewID);
	SvgIdLayer * copyLayer();

	QPointF point(ViewLayer::ViewLayerPlacement);
	QRectF rect(ViewLayer::ViewLayerPlacement);
	bool processed(ViewLayer::ViewLayerPlacement);
	bool svgVisible(ViewLayer::ViewLayerPlacement);
	void unprocess();
	void setInvisible(ViewLayer::ViewLayerPlacement);
	void setPointRect(ViewLayer::ViewLayerPlacement, QPointF, QRectF, bool svgVisible);

public:
	ViewLayer::ViewID m_viewID;
	bool m_hybrid = false;
	double m_radius = 0.0;
	double m_strokeWidth = 0.0;
	double m_legStrokeWidth = 0.0;
	bool m_path = false;
	QString m_legId;
	QString m_legColor;
	QString m_svgId;
	QString m_terminalId;
	ViewLayer::ViewLayerID m_svgViewLayerID;
	QLineF m_legLine;


protected:
	PointRect m_pointRectBottom;
	PointRect m_pointRectTop;

protected:
};


#endif
