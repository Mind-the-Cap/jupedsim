/// Copyright © 2012-2022 Forschungszentrum Jülich GmbH
/// SPDX-License-Identifier: LGPL-3.0-or-later
#include "LineSegment.hpp"

#include "AABB.hpp"
#include "GeometricFunctions.hpp"
#include "Logger.hpp"
#include "Macros.hpp"
#include "Mathematics.hpp"
#include "Point.hpp"

#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <boost/variant.hpp>

LineSegment::LineSegment(Point _p1, Point _p2) : p1(std::move(_p1)), p2(std::move(_p2))
{
}

bool LineSegment::operator==(const LineSegment& other) const
{
    return p1 == other.p1 && p2 == other.p2;
}

bool LineSegment::operator!=(const LineSegment& other) const
{
    return !(*this == other);
}

bool LineSegment::operator<(const LineSegment& other) const
{
    return p1 < other.p1 || p2 < other.p2;
}

Point LineSegment::NormalVec() const
{
    const Point r = (p2 - p1);
    return Point(-r.y, r.x).Normalized();
}

double LineSegment::NormalComp(const Point& v) const
{
    // Normierte Vectoren
    Point l = (p2 - p1).Normalized();
    const Point& n = NormalVec();

    double alpha;

    if(fabs(l.x) < J_EPS) {
        alpha = v.x / n.x;
    } else if(fabs(l.y) < J_EPS) {
        alpha = v.y / n.y;
    } else {
        alpha = l.CrossProduct(v) / n.CrossProduct(l);
    }

    return fabs(alpha);
}

/* Punkt auf der Linie mit kürzestem Abstand zu p
 * In der Regel Lotfußpunkt, Ist der Lotfußpunkt nicht im Segment
 * wird der entsprechende Eckpunkt der Line genommen
 * */
Point LineSegment::ShortestPoint(const Point& p) const
{
    if(p1 == p2)
        return p1;

    const Point& t = p1 - p2;
    double lambda = (p - p2).ScalarProduct(t) / t.ScalarProduct(t);
    if(lambda < 0)
        return p2;
    else if(lambda > 1)
        return p1;
    else
        return p2 + t * lambda;
}

/* Berechnet direkt den Abstand von p zum Segment l
 * dazu wird die Funktion Line::ShortestPoint()
 * benuzt
 * */
double LineSegment::DistTo(const Point& p) const
{
    return (p - ShortestPoint(p)).Norm();
}

double LineSegment::LengthSquare() const
{
    return (p1 - p2).NormSquare();
}