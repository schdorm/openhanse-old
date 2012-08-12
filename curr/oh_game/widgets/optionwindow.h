/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   oh.devs@googlemail.com                                                *
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

#ifndef _OptionWindow_H
#define _OptionWindow_H

#include <QtGui/QDialog>
#include <QtGui/QCheckBox>
#include <QtGui/QSpinBox>
#include <QtGui/QSlider>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
// class QPushButton;
// class QCheckBox;
// class QSpinBox;
// class QSlider;
// class QGridLayout;

#include "sound_pre.h"

// #ifdef enable_sound
// namespace Phonon{
// class AudioOutput;
// class MediaObject;
// }
// #endif


class OptionWindow : public QWidget
{
Q_OBJECT
public:
  // OptionWindow();
  
  OptionWindow(QWidget *parent = 0);
//   ~OptionWindow();

public slots:
  void writeSettings();
  void takeSettings();
  void openglHint();
  
  #ifdef enable_sound
  void testSound(int);
  #endif
  
signals:
  void aborted();
  void modAssumed();			// modifications assumed ..

private:
  
protected:
  QGridLayout layout;
  QHBoxLayout HBoxLayout;


  QCheckBox FullScreenCheck;
  QCheckBox OpenGLCheck;
  QCheckBox CacheMapsCheck;

  QSlider FPSSlider;

  QSpinBox XResolutionBox;
  QSpinBox YResolutionBox;
  
  #ifdef enable_sound
  QSlider MusicVolumeSlider;
  QSlider MiscVolumeSlider;
  #endif

  QPushButton AcceptButton;
  QPushButton AbortButton;
  
  #ifdef enable_sound
  Phonon::AudioOutput *m_testAudioOutput;
  Phonon::MediaObject *m_testMediaObject;
  #endif

// void writeSettings();
// void takeSettings();

};

#endif
