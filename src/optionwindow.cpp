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

#include "optionwindow.h"
#include "datamanager.h"
#include "settings.h"

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtXml/QXmlStreamWriter>

#include <QtGui/QCheckBox>
#include <QtGui/QSpinBox>
#include <QtGui/QSlider>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>

#include <QtGui/QHBoxLayout>

#include "konsole.h"


OptionWindow::OptionWindow(QWidget *parentwidget) : QDialog(parentwidget)
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
label = new QLabel(tr("Music Volume"),this);
layout.addWidget(label, 5, 0, 1, 1);
MiscVolumeSlider.setTickPosition(QSlider::TicksBelow);
MiscVolumeSlider.setTickInterval((MiscVolumeSlider.maximum() - MiscVolumeSlider.minimum())/2 + (MiscVolumeSlider.maximum() - MiscVolumeSlider.minimum())%2);
MiscVolumeSlider.setOrientation(Qt::Horizontal);
/*MiscVolumeSlider.setValue(SETTINGS->miscVolume());*/
layout.addWidget(&MiscVolumeSlider, 5, 1, 1, 7);

takeSettings();

AcceptButton.setText(tr("Accept"));
// layout.addWidget(&AcceptButton, 6, 0, 1, 1);

AbortButton.setText(tr("Abort"));
// layout.addWidget(&AbortButton, 6, 1, 1, 1);

HBoxLayout.addWidget(&AcceptButton);
HBoxLayout.addWidget(&AbortButton);

layout.addLayout(&HBoxLayout, 6, 0, 1, 8, Qt::AlignHCenter);


setLayout(&layout);

connect(&AcceptButton, SIGNAL(clicked()), this, SLOT(accept()));
connect(&AbortButton, SIGNAL(clicked()), this, SLOT(reject()));

connect(this, SIGNAL(rejected()), this, SLOT(takeSettings()));
connect(this, SIGNAL(accepted()), this, SLOT(writeSettings()));

// connect(this, SIGNAL(accepted()), this, SLOT(writeSettings()));
connect(this, SIGNAL(finished(int)), this, SLOT(hide()));
}

// OptionWindow::OptionWindow(QWidget *parentObj)
// {
// setParent(parentObj);
// OptionWindow();
// }

OptionWindow::~OptionWindow()
{
}

void OptionWindow::takeSettings()
{
FullScreenCheck.setChecked(SETTINGS->fullscreen());
OpenGLCheck.setChecked(SETTINGS->openGL());

FPSSlider.setValue(SETTINGS->fps());
XResolutionBox.setValue(SETTINGS->resolution().width());
YResolutionBox.setValue(SETTINGS->resolution().height());

MusicVolumeSlider.setValue(SETTINGS->musicVolume());
MiscVolumeSlider.setValue(SETTINGS->miscVolume());

}

void OptionWindow::writeSettings()
{
OHDebug("Writing Configs ...");
QFile Cfg(QString(QDir().home().absolutePath()).append("/.OpenHanse/cfg.ohc"));
Cfg.open(QIODevice::WriteOnly);
QXmlStreamWriter writer(&Cfg);
writer.setAutoFormatting(true);
writer.writeStartElement("conf");
writer.writeEmptyElement("resolution");
// writer.writeStartElement("height");
writer.writeAttribute(QXmlStreamAttribute("width", QString("%1").arg(XResolutionBox.value())));
writer.writeAttribute(QXmlStreamAttribute("height", QString("%1").arg(YResolutionBox.value())));
writer.writeStartElement("fullscreen");
if(FullScreenCheck.isChecked())
	writer.writeCharacters("true");
else
	writer.writeCharacters("false");

writer.writeEndElement();

writer.writeStartElement("fps");
writer.writeCharacters(QString("%1").arg(FPSSlider.value()));
writer.writeEndElement();

writer.writeStartElement("opengl");
if(OpenGLCheck.isChecked())
	writer.writeCharacters("true");
else
	writer.writeCharacters("false");
writer.writeEndElement();

float miscvolume = MiscVolumeSlider.value()/100;
float musicvolume = MusicVolumeSlider.value()/100;

writer.writeStartElement("misc-volume");
writer.writeCharacters(QString("%1").arg(miscvolume));
writer.writeEndElement();

writer.writeStartElement("music-volume");
writer.writeCharacters(QString("%1").arg(musicvolume));
writer.writeEndElement();


writer.writeEndDocument();
Cfg.close();
// QFile(QString(QDir().home().absolutePath()).append("/.OpenHanse/cfg_old.ohc")).remove();
// QFile(QString(QDir().home().absolutePath()).append("/.OpenHanse/cfg.ohc")).rename("cfg_old.ohc");
// Cfg.rename("cfg.ohc");
OHDebug("End of Writing Configs");
SETTINGS->readConfigs(QFileInfo(Cfg).absoluteFilePath());
}
