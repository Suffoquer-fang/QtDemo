#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPointF>
#include <QVector2D>
#include <QRectF>
#include <random>

class GameObject
{
public:
    GameObject();

private:
    float m_radius;
    float m_rotation;
    QPointF m_center;
    QVector2D m_velocity;

    float m_bounceE;

    bool m_useGravity;
    bool m_useBounce;

    QRectF m_boundary;

public:
    void setRadius(float r) { m_radius = r;}
    void setRotation(float r) { m_rotation = r;}
    void setCenter(QPointF c) { m_center = c;}
    void setCenter(float x, float y) { m_center.setX(x), m_center.setY(y);}
    void setVelocity(QVector2D v) { m_velocity = v;}
    void setVelocity(float x, float y) { m_velocity.setX(x), m_velocity.setY(y);}
    void setBounceE(float e) { m_bounceE = e;}

    void setGravity(bool t) { m_useGravity = t;}
    void setBounce(bool t) { m_useBounce = t;}

    void setBoundary(float left, float top, float right, float bottom)
    {
        m_boundary.setBottom(bottom);
        m_boundary.setLeft(left);
        m_boundary.setRight(right);
        m_boundary.setTop(top);
    }

    void setBoundary(QRect r) {m_boundary = r;}

    float radius() {return m_radius;}
    float rotation() {return m_rotation;}
    QPointF center() {return m_center;}
    QPointF lefttop() {return QPointF(m_center.x() - m_radius, m_center.y() - m_radius);}
    QVector2D velocity() {return m_velocity;}

    bool useGravity() {return m_useGravity;}
    bool useBounce() {return m_useBounce;}

    void move(float deltaTime);
    void bounce();
    void activate();

    void randomInit();

};

#endif // GAMEOBJECT_H
