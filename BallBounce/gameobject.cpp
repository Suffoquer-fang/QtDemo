#include "gameobject.h"

GameObject::GameObject()
{
    randomInit();
}

void GameObject::move(float deltaTime)
{
    QPointF des;

    if(useGravity())
    {
        QVector2D gravity;
        gravity.setX(0);
        gravity.setY(10);
        m_velocity.setY(m_velocity.y() + 1);
    }

    des.setX(m_velocity.x() * deltaTime * m_radius / 5000);
    des.setY(m_velocity.y() * deltaTime * m_radius / 5000);

    m_center.operator +=(des);
    //m_rotation += 0.1;
    m_rotation += m_velocity.x() * deltaTime * 0.7 / 50;

    if(m_rotation >= 360)   m_rotation -= 360;
}

void GameObject::bounce()
{
    if(m_center.y() + m_radius >= m_boundary.bottom() && m_velocity.y() > 0)
    {
        m_velocity.setY(-m_velocity.y() * m_bounceE);
    }
    if(m_center.y() - m_radius <= m_boundary.top() && m_velocity.y() < 0)
    {
        m_velocity.setY(-m_velocity.y() * m_bounceE);
    }

    if(m_center.x() - m_radius <= m_boundary.left() && m_velocity.x() < 0)
    {
        m_velocity.setX(-m_velocity.x() * m_bounceE * 0.5);
    }

    if(m_center.x() + m_radius > m_boundary.right() && m_velocity.x() > 0)
    {
        m_velocity.setX(-m_velocity.x() * m_bounceE * 0.5);
    }
}

void GameObject::activate()
{
    if(m_velocity.lengthSquared() <= 20 && m_center.y() >= 640)
    {
        m_velocity.setX(m_velocity.x() * 5);
        m_velocity.setY(-50);
    }
}

void GameObject::randomInit()
{
    m_rotation = 0;
    m_radius = qrand() % 125 + 25;
    m_velocity.setX(qrand() % 80 - 40);
    m_velocity.setY(10);

    m_center.setX(qrand() % 2000);
    m_center.setY(qrand() % 1000);

    m_useGravity = true;
    m_bounceE = (qrand() % 3) * 0.1 + 0.7;

}
