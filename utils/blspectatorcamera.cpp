#include "blspectatorcamera.h"

#include <cmath>
#include <bllogger.h>
#include <iostream>

#include <QCursor>

namespace black {

SpectatorCamera::SpectatorCamera()
    : Camera(), m_lastMousePos(), m_firstMouseEvent(true),
      m_speed(1.0f), m_smoothness(0.5f)
{
    this->setPosition({400.0f, 600.0f, 400.0f});

    this->setPitchConstraint(-56.5f);
    this->setYawConstraint(-229.0f);
    this->setRoll(1.0f);

    this->setRotate({-56.5f, -229.0f, 1.0f});
}

void SpectatorCamera::handleKeyboard(QKeyEvent *e)
{
    switch ( e->key() ) {
    case Qt::Key_Left:
    case Qt::Key_A:
        this->moveLeft(m_speed);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        this->moveRight(m_speed);
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        this->moveForward(m_speed);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        this->moveBack(m_speed);
        break;
    default:
        break;
    }
}

void SpectatorCamera::handleMouse(QMouseEvent *e)
{
    float dMax = 100.0f;
    if ( !m_firstMouseEvent ) {
        float dx = e->localPos().x() - m_lastMousePos.x();
        float dy = m_lastMousePos.y() - e->localPos().y();

        if ( std::abs(dx) > dMax || std::abs(dy) > dMax ) {
            m_lastMousePos = e->localPos();
            return;
        }

        dx *= 1.0f - m_smoothness;
        dy *= 1.0f - m_smoothness;

        this->setRotate({m_pitch + dy, m_yaw + dx, m_roll});
        std::cout << "\nrotating pitch: " << m_pitch << " yaw: " << m_yaw << " roll: " << m_roll << endl;
    } else {
        m_firstMouseEvent = false;
    }

    m_lastMousePos = e->localPos();
}

void SpectatorCamera::handleWheel(QWheelEvent *e)
{

}

} // end of black namespace
