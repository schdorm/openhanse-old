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

#include "optionwindow.h"
#include "datamanager.h"
#include "settings.h"
#include "debugqueue.h"

#include <libs/oqstring.h>

#ifdef enable_sound
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#endif

#include <QtDebug>
#include <QtCore/QFile>
#include <QtCore/QDir>

#include <QtXml/QXmlStreamWriter>

#include <QtGui/QHBoxLayout>
#include <QtGui/QGridLayout>

#include <QtGui/QLabel>
#include <QtGui/QMessageBox>

OptionWindow::OptionWindow(QWidget *parent) : QWidget(parent)
{
  QLabel *label;
  
  setAutoFillBackground(true);
  // FullScreenCheck.setParent(this);
  // FullScreenCheck.setChecked(SETTINGS->fullscreen());
  layout.addWidget(&FullScreenCheck, 2, 5, 1, 1);
  // OpenGLCheck.setParent(this);
  // OpenGLCheck.setChecked(SETTINGS->opengl());
  layout.addWidget(&OpenGLCheck, 2, 8, 1, 1);
  
  label = new QLabel(tr("Fullscreen"), this);
  layout.addWidget(label, 2, 4, 1, 1);
  label = new QLabel(tr("Use OpenGL"), this);
  layout.addWidget(label, 2, 7, 1, 1);
  
  
  // FPSSlider.setParent(this);
  label = new QLabel(tr("FPS"), this);
  /*FPSSlider.setValue(SETTINGS->fps());*/
  FPSSlider.setRange(5,50);
  FPSSlider.setOrientation(Qt::Horizontal);
  FPSSlider.setTickPosition(QSlider::TicksBelow);
  FPSSlider.setTickInterval((FPSSlider.maximum() - FPSSlider.minimum())/2 + (FPSSlider.maximum() - FPSSlider.minimum())%2);
  layout.addWidget(label, 3, 0, 1, 1);
  layout.addWidget(&FPSSlider, 3, 1, 1, 7);
  
  // XResolutionBox.setParent(this);
  label = new QLabel(tr("Resolution"),this);
  layout.addWidget(label, 2, 0, 1, 1);
  layout.addWidget(&XResolutionBox, 2, 1, 1, 1);
  XResolutionBox.setRange(800, 4096);
  // XResolutionBox.setValue(SETTINGS->resolution().width());
  
  
  // YResolutionBox.setParent(this);
  layout.addWidget(&YResolutionBox, 2, 2, 1, 1);
  YResolutionBox.setRange(600, 3072);
  // YResolutionBox.setValue(SETTINGS->resolution().height());
  
  #ifdef enable_sound
  // MusicVolumeSlider.setParent(this);
  label = new QLabel(tr("Music Volume"),this);
  MusicVolumeSlider.setRange(0, 100);
  layout.addWidget(label, 4, 0, 1, 1);
  MusicVolumeSlider.setOrientation(Qt::Horizontal);
  MusicVolumeSlider.setTickPosition(QSlider::TicksBelow);
  MusicVolumeSlider.setTickInterval((MusicVolumeSlider.maximum() - MusicVolumeSlider.minimum())/2 + (MusicVolumeSlider.maximum() - MusicVolumeSlider.minimum())%2);
  /*MusicVolumeSlider.setValue(SETTINGS->musicVolume());*/
  layout.addWidget(&MusicVolumeSlider, 4, 1, 1, 7);
  
  // MiscVolumeSlider.setParent(this);
  MiscVolumeSlider.setRange(0, 100);
  label = new QLabel(tr("Misc Volume"),this);
  layout.addWidget(label, 5, 0, 1, 1);
  MiscVolumeSlider.setTickPosition(QSlider::TicksBelow);
  MiscVolumeSlider.setTickInterval((MiscVolumeSlider.maximum() - MiscVolumeSlider.minimum())/2 + (MiscVolumeSlider.maximum() - MiscVolumeSlider.minimum())%2);
  MiscVolumeSlider.setOrientation(Qt::Horizontal);
  /*MiscVolumeSlider.setValue(SETTINGS->miscVolume());*/
  layout.addWidget(&MiscVolumeSlider, 5, 1, 1, 7);
  #endif
  
  label = new QLabel(tr("Cache Maps"), this);
  layout.addWidget(label, 6, 0, 1, 2, Qt::AlignHCenter);
  
  layout.addWidget(&CacheMapsCheck, 6, 3, 1, 2);
  
  
  AcceptButton.setText(tr("Accept"));
  // layout.addWidget(&AcceptButton, 6, 0, 1, 1);
  
  AbortButton.setText(tr("Abort"));
  // layout.addWidget(&AbortButton, 6, 1, 1, 1);
  HBoxLayout.addWidget(&AcceptButton);
  HBoxLayout.addWidget(&AbortButton);
  layout.addLayout(&HBoxLayout, 7, 0, 1, 8, Qt::AlignHCenter);
  
  
  setLayout(&layout);
  
  /*connect(&AcceptButton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(&AbortButton, SIGNAL(clicked()), this, SLOT(reject()));
  
  connect(this, SIGNAL(rejected()), this, SLOT(takeSettings()));
  connect(this, SIGNAL(accepted()), this, SLOT(writeSettings()));
  
  // connect(this, SIGNAL(accepted()), this, SLOT(writeSettings()));
  connect(this, SIGNAL(finished(int)), this, SLOT(hide()));*/
  
  #ifdef enable_sound
  m_testMediaObject = new Phonon::MediaObject(this);
  m_testAudioOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
  Phonon::createPath(m_testMediaObject, m_testAudioOutput);
  #endif
  
  takeSettings();
  
  #ifdef enable_sound
  connect(&MiscVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(testSound(int)));
  connect(&MusicVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(testSound(int)));
  #endif
  
  connect(&OpenGLCheck, SIGNAL(stateChanged(int)), this, SLOT(openglHint()));
  
  connect(&AcceptButton, SIGNAL(clicked()), this, SLOT(writeSettings()));
  connect(&AbortButton, SIGNAL(clicked()),  this, SIGNAL(aborted()));
}

// OptionWindow::OptionWindow(QWidget *parentObj)
// {
// setParent(parentObj);
// OptionWindow();
// }

// OptionWindow::~OptionWindow()
// {
//   #ifdef enable_sound
//   delete m_testAudioOutput;
//   delete m_testMediaObject;
//   #endif
//   ~QWidget();
// }

#ifdef enable_sound
void OptionWindow::testSound(int volume)
{
//   double nvol = volume;
  m_testAudioOutput->setVolume(((qreal) volume)/100);

  m_testMediaObject->setCurrentSource(Phonon::MediaSource(":/audio/sounds/dong.ogg"));
  m_testMediaObject->play();
  qWarning() << "Volume" << ((qreal) volume)/100;
}
#endif

void OptionWindow::takeSettings()
{
FullScreenCheck.setChecked(SETTINGS->fullscreen());
OpenGLCheck.setChecked(SETTINGS->opengl());

FPSSlider.setValue(SETTINGS->fps());
XResolutionBox.setValue(SETTINGS->resolution().width());
YResolutionBox.setValue(SETTINGS->resolution().height());

#ifdef enable_sound
MusicVolumeSlider.setValue(SETTINGS->musicVolume());
MiscVolumeSlider.setValue(SETTINGS->miscVolume());
#endif

CacheMapsCheck.setChecked(SETTINGS->cacheMaps());
}

void OptionWindow::openglHint()
{
  disconnect(&OpenGLCheck, SIGNAL(stateChanged(int)), this, SLOT(openglHint()));
  
  QMessageBox *hint = new QMessageBox(this);
  
  hint->setText(tr("Please notice, that changes on OpenGL-Settings not take effect until restarting the application."));
  hint->exec();
  connect(hint, SIGNAL(buttonClicked()), hint, SLOT(deleteLater()));
}

void OptionWindow::writeSettings()
{
OHDEBUG("Apply Configs ...");
qWarning() << "\nResolution: " << XResolutionBox.value() << " x " << YResolutionBox.value();
qWarning() << "FPS: " << FPSSlider.value();
qWarning() << "OpenGL: " << OpenGLCheck.isChecked() << " \t Fullscreen: " << FullScreenCheck.isChecked();
qWarning() << "Music-Volume: " << MusicVolumeSlider.value() << "\t Misc-Volume: " << MiscVolumeSlider.value();
qWarning() << "Chaching Maps: " << CacheMapsCheck.isChecked();
qWarning() << "End of Written Confs ...\n";

SETTINGS->applySettings(QSize(XResolutionBox.value(), YResolutionBox.value()), FullScreenCheck.isChecked(), OpenGLCheck.isChecked(), FPSSlider.value(), MusicVolumeSlider.value(), MiscVolumeSlider.value(), CacheMapsCheck.isChecked());
SETTINGS->writeConfigFile();
emit modAssumed();

}
