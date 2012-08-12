/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   schdorm@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "debugqueue.h"


DebugQueue::DebugQueue()
{
  
}

DebugQueue::~DebugQueue()
{
  
}

void DebugQueue::debug(const QString &a_newMessage)
{
  enqueue(a_newMessage);
}

// DebugQueue *DebugQueue::instance()
// {
//   if(m_instance == 0)
//   {
//     m_instance = new DebugQueue();
//   }
//   return m_instance;
// }

QString DebugQueue::dequeue()
{
  m_dequeued = true;
  if(!m_messages.isEmpty())
    return m_messages.dequeue();
  else
    return QString();
}

void DebugQueue::enqueue(const QString &a_newMessage)
{
  m_messages.enqueue(a_newMessage);
  if(m_dequeued)
  {
    emit dataAvailabled();
    m_dequeued = false;
  }
}

bool DebugQueue::dataAvailable() const
{
  return (!m_messages.isEmpty());
}

