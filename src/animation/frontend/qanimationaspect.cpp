/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qanimationaspect.h"
#include "qanimationaspect_p.h"
#include <Qt3DAnimation/qanimationclip.h>
#include <Qt3DAnimation/private/handler_p.h>
#include <Qt3DAnimation/private/managers_p.h>
#include <Qt3DAnimation/private/nodefunctor_p.h>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DAnimation {

QAnimationAspectPrivate::QAnimationAspectPrivate()
    : QAbstractAspectPrivate()
    , m_handler(new Animation::Handler)
{
}

/*!
    \class Qt3DAnimation::QAnimationAspect
    \inherits Qt3DCore::QAbstractAspect
    \inmodule Qt3DAnimation
    \brief Provides key-frame animation capabilities to Qt 3D.
    \since 5.9

    QAnimationAspect provides key-frame animation to Qt 3D.
*/

/*!
 * Constructs a new QAnimationAspect with \a parent.
 */
QAnimationAspect::QAnimationAspect(QObject *parent)
    : QAnimationAspect(*new QAnimationAspectPrivate, parent)
{
}

/*! \internal */
QAnimationAspect::QAnimationAspect(QAnimationAspectPrivate &dd, QObject *parent)
    : QAbstractAspect(dd, parent)
{
    setObjectName(QStringLiteral("Animation Aspect"));
    Q_D(QAnimationAspect);
    registerBackendType<QAnimationClip>(
        QSharedPointer<Animation::NodeFunctor<Animation::AnimationClip, Animation::AnimationClipManager>>::create(d->m_handler.data(),
                                                                                                                  d->m_handler->animationClipManager()));
}

/*! \internal */
QAnimationAspect::~QAnimationAspect()
{
}

/*!
    \internal
 */
QVector<QAspectJobPtr> QAnimationAspect::jobsToExecute(qint64 time)
{
    Q_D(QAnimationAspect);
    Q_ASSERT(d->m_handler);
    return d->m_handler->jobsToExecute(time);
}

} // namespace Qt3DAnimation

QT_END_NAMESPACE

QT3D_REGISTER_NAMESPACED_ASPECT("animation", QT_PREPEND_NAMESPACE(Qt3DAnimation), QAnimationAspect)