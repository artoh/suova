/**************************************************************************
**  suovawrappedquerytableview.cpp (of Suova)
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
**  SuovaWrappedQueryTableView 7.8.2012
**************************************************************************/

#include "suovawrappedquerytableview.h"

SuovaWrappedQueryTableView::SuovaWrappedQueryTableView(QGraphicsProxyWidget *parent) :
    QGraphicsProxyWidget(parent)
{
    view_.setModel(&model_);
    setWidget(&view_);
    connect(&view_,SIGNAL(clicked(QModelIndex)),this,SLOT(fileSelected(QModelIndex)));
}

void SuovaWrappedQueryTableView::setSearchType(QString type)
{
    model_.setSearchType(type);
}

void SuovaWrappedQueryTableView::setFileType(QString type)
{
    model_.setFileType(type);
}

void SuovaWrappedQueryTableView::setSearchString(QString search)
{
    model_.setSearchString(search);
}

void SuovaWrappedQueryTableView::setTag(QString tag)
{
    model_.setTag(tag);
}

void SuovaWrappedQueryTableView::setKeyword(QString keyword)
{
    model_.setKeyword(keyword);
}

void SuovaWrappedQueryTableView::doQuery()
{
    model_.doQuery();
}

void SuovaWrappedQueryTableView::fileSelected(QModelIndex index)
{
}
