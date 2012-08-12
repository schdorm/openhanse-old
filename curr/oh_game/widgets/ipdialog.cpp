/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Christian Doerffel                       *
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

#include "ipdialog.h"

IPDialog::IPDialog(QString *hn, int *pn, QWidget *parent) : QDialog(parent), m_hostName(hn), m_portNumber(pn)
{
  ui.setupUi(this);
  /*if(*pn > 0)
  {
    ui.PortSpinBox->setValue(*pn);
  }*/
  if(hn->size() > 0)
    ui.HostLineEdit->setText(*hn);
  connect(ui.PortSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setData()));
  connect(ui.HostLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setData()));
  setData();
}


void IPDialog::setData()
{
  *m_portNumber = ui.PortSpinBox->value();
  *m_hostName = ui.HostLineEdit->text();
}