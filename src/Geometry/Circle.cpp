#include "Circle.h"

Circle::Circle(Point2D center, Scalar radius)
    :
      center_(center),
      radius_(radius)
{
    area_ = M_PI*radius_*radius_;
}

void Circle::init(const Point2D &center, Scalar radius)
{
    center_ = center;
    radius_ = radius;
    area_ = M_PI*radius_*radius_;
}

//- Tests
bool Circle::isInside(const Point2D &testPoint) const
{
    return (testPoint - center_).magSqr() < radius_*radius_;
}

bool Circle::isOnEdge(const Point2D &testPoint) const
{
    return (testPoint - center_).magSqr() - radius_*radius_ <= Point2D::epsilon();
}

//- Intersections
std::vector<Point2D> Circle::intersections(const Line2D &line) const
{
    Vector2D origin = line.r0() - center_;

    const Scalar dx = line.d().x, dy = line.d().y;
    const Scalar a = dx*dx + dy*dy;
    const Scalar b = 2.*(origin.x*dx + origin.y*dy);
    const Scalar c = origin.x*origin.x + origin.y*origin.y - radius_*radius_;

    const Scalar disc = b*b - 4.*a*c;

    origin += center_;

    if(disc < 0.)
        return std::vector<Point2D>();
    else if (disc < Point2D::epsilon())
    {
        return std::vector<Point2D>({
                                        origin - b/(2.*a)*line.n()
                                    });
    }
    else
    {
        const Scalar tmp = sqrt(disc);
        const Scalar t1 = (-b + tmp)/(2.*a), t2 = (-b + tmp)/(2.*a);

        return std::vector<Point2D>({
                                        line(t1),
                                        line(t2)
                                    });
    }
}

Point2D Circle::nearestIntersect(const Point2D &point) const
{
    return (point - center_).unitVec()*radius_ + center_;
}

std::pair<Point2D, Point2D> Circle::nearestEdge(const Point2D &point) const
{
    const Point2D xc = nearestIntersect(point);
    const Vector2D utan = (center_ -  xc).tangentVec().unitVec();

    return std::make_pair(
                xc + 0.5*utan,
                xc - 0.5*utan
                );
}

//- Transformations
void Circle::scale(Scalar factor)
{
    radius_ *= factor;
    area_ *= factor*factor;
}

//- Translations
void Circle::operator +=(const Vector2D& translationVec)
{
    center_ += translationVec;
}

void Circle::operator -=(const Vector2D& translationVec)
{
    center_ -= translationVec;
}

boost::geometry::model::box<Point2D> Circle::boundingBox() const
{
    return boost::geometry::model::box<Point2D>(Point2D(center_.x - radius_,
                                                        center_.y - radius_),
                                                Point2D(center_.x + radius_,
                                                        center_.y + radius_));
}

//- External functions
