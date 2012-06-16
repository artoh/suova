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
#include <QToolBar>

SuovaWindow::SuovaWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Testing code: view 100 last modified files
    // SuovaQueryModel* model = new SuovaQueryModel(this,"SELECT ?f nie:url(?f) ?pvm WHERE { ?f nfo:fileLastAccessed ?pvm  } ORDER BY DESC(?pvm) LIMIT 100");
    model_ = new SuovaFileQueryModel(this, "{ ?f nfo:fileLastAccessed ?pvm  } ORDER BY DESC(?pvm) LIMIT 100");
    QTableView* view = new QTableView(this);
    filter_ = new QSortFilterProxyModel(this);
    filter_->setSourceModel(model_);
    filter_->setSortRole(Qt::UserRole);
    view->setModel(filter_);
    view->sortByColumn(2, Qt::DescendingOrder);
    view->setSortingEnabled(true);
    view->resizeColumnsToContents();
    setCentralWidget(view);

    infoTable_ = new QTableView(this);
    QDockWidget *dock = new QDockWidget( tr("Information"));
    dock->setWidget(infoTable_);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    textBrowser_ = new QTextBrowser(this);
    textBrowser_->setReadOnly(true);
    QDockWidget *textDock = new QDockWidget( tr("Preview"));
    textDock->setWidget( textBrowser_);
    addDockWidget(Qt::RightDockWidgetArea, textDock);

    connect( view, SIGNAL(clicked(QModelIndex)), this, SLOT(fileSelected(QModelIndex)));

    QToolBar* quickSearchBar = new QToolBar( tr("Quick search"));
    searchTextEdit_ = new QLineEdit();
    quickSearchBar->addWidget(searchTextEdit_);
    addToolBar(quickSearchBar);

    connect( searchTextEdit_, SIGNAL(editingFinished()), this, SLOT(doSeach()));
}

SuovaWindow::~SuovaWindow()
{
    
}


void SuovaWindow::fileSelected(const QModelIndex &index)
{

    QModelIndex sourceIndex = filter_->mapToSource(index);
    infoTable_->setModel( model_->fileInfo( sourceIndex.row()) );
    textBrowser_->setText( model_->fileInfo( sourceIndex.row())->information("plainTextContent").toString());
}


void SuovaWindow::doSeach()
{
    // Test code: full text search
    if( !searchTextEdit_->text().isEmpty())
    {
        // do full text seach
        QString where = QString("{ ?f  fts:match '%1*'  } ").arg(searchTextEdit_->text());
        model_->setWhere(where);
    }

}
