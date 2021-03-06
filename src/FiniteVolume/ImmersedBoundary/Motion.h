#ifndef MOTION_H
#define MOTION_H

#include "Point2D.h"

class ImmersedBoundaryObject;

class Motion
{
public:

    Motion(const std::weak_ptr<ImmersedBoundaryObject> ibObj);

    virtual void update(Scalar timeStep) = 0;

    const Vector2D &acceleration() const
    { return acc_; }

    Vector2D acceleration(const Point2D &pt) const
    { return acc_ + alpha_ * (pt - pos_).tangentVec() + omega_ * omega_ * (pos_ - pt); }

    const Vector2D &velocity() const
    { return vel_; }

    Vector2D velocity(const Point2D &pt) const
    { return vel_ + omega_ * (pt - pos_).tangentVec(); }

    Scalar alpha() const
    { return alpha_; }

    Scalar omega() const
    { return omega_; }

    Scalar theta() const
    { return theta_; }

protected:

    Scalar alpha_, omega_, theta_;
    Vector2D acc_, vel_, pos_;

    std::weak_ptr<ImmersedBoundaryObject> ibObj_;
};

#endif