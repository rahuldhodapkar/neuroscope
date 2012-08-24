/***************************************************************************
                          clusterproperties.cpp  -  description
                             -------------------
    begin                : Thu Jul 22 2004
    copyright            : (C) 2004 by Lynn Hazan
    email                : lynn.hazan.myrealbox.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "clusterproperties.h"

ClusterProperties::ClusterProperties(QWidget *parent, const char *name ) : ClusterPropertiesLayout(parent),
    intValidator(this){
    //Set a validator on the line edits, the values have to be integers.
    nbSamplesLineEdit->setValidator(&intValidator);
    peakIndexLineEdit->setValidator(&intValidator);
}


ClusterProperties::~ClusterProperties(){
}

#include "clusterproperties.moc"
