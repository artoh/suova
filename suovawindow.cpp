/**************************************************************************
**  suovawindow.cpp
**  Copyright (c) 2012 Arto Hyvättinen 
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
**    12.6.2012
**************************************************************************/

#include "suovawindow.h"

#include "suovafilequerymodel.h"

#include <QTableView>
#include <QSortFilterProxyModel>

#include <QDockWidget>


SuovaWindow::SuovaWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Testing code: view 100 last modified files
    // SuovaQueryModel* model = new SuovaQueryModel(this,"SELECT ?f nie:url(?f) ?pvm WHERE { ?f nfo:fileLastAccessed ?pvm  } ORDER BY DESC(?pvm) LIMIT 100");
    model_ = new SuovaFileQueryModel(this, "{ ?f nfo:fileLastAccessed ?pvm  } ORDER BY DESC(?pvm) LIMIT 100");
    QTableView* view = new QTableView(this);
    QSortFilterProxyModel* filter = new QSortFilterProxyModel(this);
    filter->setSourceModel(model_);
    filter->setSortRole(Qt::UserRole);
    view->setModel(filter);
    view->sortByColumn(2, Qt::DescendingOrder);
    view->setSortingEnabled(true);
    view->resizeColumnsToContents();
    setCentralWidget(view);

    infoTable_ = new QTableView(this);
    QDockWidget *dock = new QDockWidget( tr("Information"));
    dock->setWidget(infoTable_);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect( view, SIGNAL(clicked(QModelIndex)), this, SLOT(fileSelected(QModelIndex)));
}

SuovaWindow::~SuovaWindow()
{
    
}


void SuovaWindow::fileSelected(const QModelIndex &index)
{
    infoTable_->setModel( model_->fileInfo( index.row()) );
}
