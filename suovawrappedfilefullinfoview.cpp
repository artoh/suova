/**************************************************************************
**  suovawrappedfilefullinfoview.cpp (of Suova)
**  Copyright (c) 2012 Heli Hyvättinen
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  See <http://www.gnu.org/licenses/>
**
**  SuovaWrappedFileFullInfoView 7.8.2012
**************************************************************************/


/*
  Provides QML accessible QTableView that uses SuovaFileFullInfo as its model.
  */
#include "suovawrappedfilefullinfoview.h"




SuovaWrappedFileFullInfoView::SuovaWrappedFileFullInfoView(QGraphicsProxyWidget *parent) :
    QGraphicsProxyWidget(parent)
{
    pView_ = new QTableView();
    setWidget(pView_);

    pModel_ = NULL;
}

SuovaWrappedFileFullInfoView::~SuovaWrappedFileFullInfoView()
{
    delete pView_;
}

QString SuovaWrappedFileFullInfoView::getFileNameWithPath()
{
    return pModel_->information("url").toString();
}



void SuovaWrappedFileFullInfoView::setUrn(QString urn)
{
    if (!pModel_ )
        delete pModel_;
    pModel_ = new SuovaFileFullInfo(urn,this);
    pView_->setModel(pModel_);
}
