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

#include "ingamemenu.h"

// IngameMenu::IngameMenu()
// {
// ResumeButton.setText(tr("Resume"));
// SaveButton.setText(tr("Save Game"));
// LoadButton.setText(tr("Load Game"));
// OptionsButton.setText(tr("Options"));
// QuitButton.setText(tr("Quit/Exit"));
// 
// ResumeButton.setToolTip(tr("Resume"));
// SaveButton.setToolTip(tr("Save Game"));
// LoadButton.setToolTip(tr("Load Game"));
// OptionsButton.setToolTip(tr("Options"));
// QuitButton.setToolTip(tr("Quit/Exit"));
// 
// MenuLayout.addWidget(&ResumeButton);
// MenuLayout.addWidget(&SaveButton);
// MenuLayout.addWidget(&LoadButton);
// MenuLayout.addWidget(&OptionsButton);
// MenuLayout.addWidget(&QuitButton);
// 
// connect(&ResumeButton, SIGNAL(clicked()), this, SIGNAL(resume()));
// connect(&SaveButton, SIGNAL(clicked()), this, SIGNAL(save()));
// connect(&LoadButton, SIGNAL(clicked()), this, SIGNAL(load()));
// connect(&OptionsButton, SIGNAL(clicked()), this, SIGNAL(options()));
// connect(&QuitButton, SIGNAL(clicked()), this, SIGNAL(exit()));
// 
// 
// show();
// raise();
// }

IngameMenu::IngameMenu(QWidget *parentwidget): QWidget( parentwidget )
{
// if(parentwidget != 0 )
// 	setParent(parentwidget);

ResumeButton.setText(tr("Resume"));
SaveButton.setText(tr("Save Game"));
LoadButton.setText(tr("Load Game"));
OptionsButton.setText(tr("Options"));
QuitButton.setText(tr("Quit/Exit"));

ResumeButton.setToolTip(tr("Resume"));
SaveButton.setToolTip(tr("Save Game"));
LoadButton.setToolTip(tr("Load Game"));
OptionsButton.setToolTip(tr("Options"));
QuitButton.setToolTip(tr("Quit/Exit"));

MenuLayout.addWidget(&ResumeButton);
MenuLayout.addWidget(&SaveButton);
MenuLayout.addWidget(&LoadButton);
MenuLayout.addWidget(&OptionsButton);
MenuLayout.addWidget(&QuitButton);

connect(&ResumeButton, SIGNAL(clicked()), this, SIGNAL(resume()));
connect(&SaveButton, SIGNAL(clicked()), this, SIGNAL(save()));
connect(&LoadButton, SIGNAL(clicked()), this, SIGNAL(load()));
connect(&OptionsButton, SIGNAL(clicked()), this, SIGNAL(options()));
connect(&QuitButton, SIGNAL(clicked()), this, SIGNAL(exit()));

GroupBox.setParent(this);
GroupBox.setLayout(&MenuLayout);
// setAutoFillBackground(true);

show();
raise();
}
