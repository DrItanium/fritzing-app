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

#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

#include <QPointF>
#include <QRectF>
#include <QTransform>
#include <QXmlStreamWriter>
#include <QDomElement>
#include <QPixmap>
#include <QPainterPath>
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPixmap>
#include <tuple>

class GraphicsUtils
{

public:
	static void distanceFromLine(double cx, double cy, double ax, double ay, double bx, double by,
	                             double & dx, double & dy, double &distanceSegment, bool & atEndpoint);
	static QPointF calcConstraint(QPointF initial, QPointF current);

	static constexpr double pixels2mils(double p, double dpi) noexcept {
        return p * 1000.0 / dpi;
    }
	static constexpr double pixels2ins(double p, double dpi) noexcept {
        return p / dpi;
    }
	static constexpr double distanceSqd(QPointF p1, QPointF p2) noexcept {
        return ((p1.x() - p2.x()) * (p1.x() - p2.x())) + ((p1.y() - p2.y()) * (p1.y() - p2.y()));
    }
	static constexpr double distanceSqd(QPoint p1, QPoint p2) noexcept {
        double dpx = p1.x() - p2.x();
        double dpy = p1.y() - p2.y();
        return (dpx * dpx) + (dpy * dpy);
    }
	static double getNearestOrdinate(double ordinate, double units);

	static constexpr double mm2mils(double mm) noexcept {
        return (mm / 25.4 * 1000);
    }
	static constexpr double pixels2mm(double p, double dpi) noexcept {
	    return (p / dpi * 25.4);
    }
	static constexpr double mm2pixels(double mm) noexcept {
        return (90 * mm / 25.4);
    }
	static constexpr double mils2pixels(double m, double dpi) noexcept {
        return (dpi * m / 1000);
    }
	static void saveTransform(QXmlStreamWriter & streamWriter, const QTransform & transform);
	static bool loadTransform(const QDomElement & transformElement, QTransform & transform);
	static bool isRect(const QPolygonF & poly);
	static QRectF getRect(const QPolygonF & poly);
	static void shortenLine(QPointF & p1, QPointF & p2, double d1, double d2);
    using LiangBarskyLineClipResults = std::tuple<bool, double, double, double, double>;
	static bool liangBarskyLineClip(double x1, double y1, double x2, double y2,
	                                double wxmin, double wxmax, double wymin, double wymax,
	                                double & x11, double & y11, double & x22, double & y22);
    /**
     * Non destructive version of the liang-barskey line clip algorithm
     */
    static constexpr LiangBarskyLineClipResults liangBarskyLineClip(double x1, double y1, double x2, double y2,
	                                double wxmin, double wxmax, double wymin, double wymax) noexcept {
        double p1 = -(x2 - x1 );
        double q1 = x1 - wxmin;
        double p2 = ( x2 - x1 );
        double q2 = wxmax - x1;
        double p3 = - ( y2 - y1 );
        double q3 = y1 - wymin;
        double p4 = ( y2 - y1 );
        double q4 = wymax - y1;

        double x11 = x1;
        double y11 = y1;
        double x22 = x2;
        double y22 = y2;

        if( ( ( p1 == 0.0 ) && ( q1 < 0.0 ) ) ||
                ( ( p2 == 0.0 ) && ( q2 < 0.0 ) ) ||
                ( ( p3 == 0.0 ) && ( q3 < 0.0 ) ) ||
                ( ( p4 == 0.0 ) && ( q4 < 0.0 ) ) )
        {
            return std::make_tuple(false, x11, y11, x22, y22);
        }

        double u1 = 0.0, u2 = 1.0;

        if( p1 != 0.0 )
        {
            double r1 = q1 /p1 ;
            if( p1 < 0 )
                u1 = qMax(r1, u1 );
            else
                u2 = qMin(r1, u2 );
        }
        if( p2 != 0.0 )
        {
            double r2 = q2 /p2 ;
            if( p2 < 0 )
                u1 = qMax(r2, u1 );
            else
                u2 = qMin(r2, u2 );

        }
        if( p3 != 0.0 )
        {
            double r3 = q3 /p3 ;
            if( p3 < 0 )
                u1 = qMax(r3, u1 );
            else
                u2 = qMin(r3, u2 );
        }
        if( p4 != 0.0 )
        {
            double r4 = q4 /p4 ;
            if( p4 < 0 )
                u1 = qMax(r4, u1 );
            else
                u2 = qMin(r4, u2 );
        }

        if( u1 > u2 ) {
            return std::make_tuple(false, x11, y11, x22, y22);
        }

        x11 = x1 + u1 * ( x2 - x1 ) ;
        y11 = y1 + u1 * ( y2 - y1 ) ;

        x22 = x1 + u2 * ( x2 - x1 );
        y22 = y1 + u2 * ( y2 - y1 );

        return std::make_tuple(true, x11, y11, x22, y22);
    }
	static QString toHtmlImage(QPixmap *pixmap, const char* format = "PNG");
	static QPainterPath shapeFromPath(const QPainterPath &path, const QPen &pen, double shapeStrokeWidth, bool includeOriginalPath);
	static void qt_graphicsItem_highlightSelected(QPainter *painter, const QStyleOptionGraphicsItem *option, const QRectF & boundingRect, const QPainterPath & path);
	static QPointF calcRotation(QTransform & rotation, QPointF rCenter, QPointF p, QPointF pCenter);
	static void drawBorder(QImage * image, int border);
	static bool isFlipped(const QMatrix & matrix, double & rotation);

public:
	static constexpr double IllustratorDPI = 72;
	static constexpr double StandardFritzingDPI = 1000;
	static constexpr double SVGDPI = 90;
	static constexpr double InchesPerMeter = 39.370078;
	static constexpr double StandardSchematicSeparationMils = 295.275591; // 7.5mm
	static constexpr double StandardSchematicSeparation10thinMils = 100;  // 0.1 inches
public:
    // make sure that instances of this class cannot be constructed
    GraphicsUtils() = delete;
    ~GraphicsUtils() = delete;
    GraphicsUtils(const GraphicsUtils&) = delete;
    GraphicsUtils(GraphicsUtils&&) = delete;
    GraphicsUtils& operator=(GraphicsUtils&&) = delete;
    GraphicsUtils& operator=(const GraphicsUtils&) = delete;

};

#endif
