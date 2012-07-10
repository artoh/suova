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
#include "suovaquerymodel.h"

#include "suovasparqlwidget.h"

#include <QTableView>
#include <QSortFilterProxyModel>

#include <QDockWidget>
#include <QToolBar>

#include <QIcon>

#include <QSettings>
#include <QPushButton>
#include <QItemSelectionModel>

SuovaWindow::SuovaWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowIcon( QIcon(":/icon/pic/suova.png"));

    // Testing code: view 100 last modified files
    // SuovaQueryModel* model = new SuovaQueryModel(this,"SELECT ?f nie:url(?f) ?pvm WHERE { ?f nfo:fileLastAccessed ?pvm  } ORDER BY DESC(?pvm) LIMIT 100");
    model_ = new SuovaFileQueryModel(this, "{ ?f nfo:fileLastAccessed ?pvm  } ORDER BY DESC(?pvm) LIMIT 100");
    view_ = new QTableView(this);
    filter_ = new QSortFilterProxyModel(this);
    filter_->setSourceModel(model_);
    filter_->setSortRole(Qt::UserRole);
    view_->setModel(filter_);
    view_->sortByColumn(2, Qt::DescendingOrder);
    view_->setSortingEnabled(true);
    view_->resizeColumnsToContents();
    setCentralWidget(view_);

    infoTable_ = new QTableView(this);
    QDockWidget *dock = new QDockWidget( tr("Information"));
    dock->setWidget(infoTable_);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    textBrowser_ = new QTextBrowser(this);
    textBrowser_->setReadOnly(true);
    textBrowser_->setHtml(QString("<img src=:/icon/pic/suova.svg width=240>%1").arg(tr("<h2> Welcome to Suova Tracker Search Tool </h2><p> &copy; Arto Hyv&auml;ttinen 2012. This program is a free software, licensed under GPL 3")));

    QDockWidget *textDock = new QDockWidget( tr("Preview"));
    textDock->setWidget( textBrowser_);
    addDockWidget(Qt::RightDockWidgetArea, textDock);

    connect( view_, SIGNAL(clicked(QModelIndex)), this, SLOT(fileSelected(QModelIndex)));

    QToolBar* quickSearchBar = new QToolBar( tr("Quick search"));
    QToolBar* filterBar = new QToolBar( tr("Filter"));

    typeCombo_ = new QComboBox;
    typeCombo_->addItem(tr("All files"),QVariant());
    typeCombo_->addItem(QIcon(":/mime/pic/text-plain.png"), tr("Text documents"), QVariant("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#TextDocument"));
    typeCombo_->addItem(tr("Image files"), QVariant("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Image"));
    filterBar->addWidget(typeCombo_);

    searchTypeCombo_ = new QComboBox;
    searchTypeCombo_->addItem( tr("File name"), QVariant("nfo:fileName"));
    searchTypeCombo_->addItem( tr("Contents"), QVariant("fts:match"));
    searchTypeCombo_->addItem( tr("Title"), QVariant("nie:title"));
    quickSearchBar->addWidget(searchTypeCombo_);


    searchTextEdit_ = new QLineEdit();
    quickSearchBar->addWidget(searchTextEdit_);

    keywordCombo_ = new QComboBox;
    SuovaQueryModel keywordQuestion(this,"SELECT DISTINCT ?k where {?f nie:keyword ?k . } ORDER BY ?k");
    keywordCombo_->addItem(tr("Keyword"), QVariant());
    for( int i=0; i < keywordQuestion.rowCount(); i++ )
    {
        keywordCombo_->addItem(keywordQuestion.result(i,0), QVariant(keywordQuestion.result(i,0)));
    }
    filterBar->addWidget(keywordCombo_);


    tagCombo_ = new QComboBox;
    keywordQuestion.setQuery("SELECT  ?labels WHERE {   ?tags a nao:Tag ;     nao:prefLabel ?labels . } ORDER BY ASC(?labels)");
    tagCombo_->addItem( tr("Tag"),QVariant());
    for( int i=0; i < keywordQuestion.rowCount(); i++ )
    {
        tagCombo_->addItem(keywordQuestion.result(i,0), QVariant(keywordQuestion.result(i,0)));
    }
    filterBar->addWidget(tagCombo_);

    QPushButton* sparqlButton = new QPushButton( tr("Custom query"));
    filterBar->addSeparator();
    filterBar->addWidget(sparqlButton);


    addToolBar( quickSearchBar);
    addToolBar( filterBar);
    connect( searchTextEdit_, SIGNAL(editingFinished()), this, SLOT(doSeach()));
    connect( typeCombo_, SIGNAL(currentIndexChanged(int)), this, SLOT(doSeach()));
    connect( searchTypeCombo_, SIGNAL(currentIndexChanged(int)), this, SLOT(doSeach()));
    connect( keywordCombo_, SIGNAL(currentIndexChanged(int)), this, SLOT(doSeach()));
    connect( tagCombo_, SIGNAL(currentIndexChanged(int)), this, SLOT(doSeach()));
    connect( sparqlButton, SIGNAL(clicked()), this, SLOT(sparql()));

    quickSearchBar->setObjectName("Quick Search Bar");
    filterBar->setObjectName("Filter Bar");
    dock->setObjectName("Dock");
    textDock->setObjectName("Text Dock");


    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
}

SuovaWindow::~SuovaWindow()
{
     QSettings settings;
     settings.setValue("geometry", saveGeometry());
     settings.setValue("state",saveState());
    
}


void SuovaWindow::sparql()
{
    // Open SPARQL widget
    QString query;
    QModelIndexList selected = view_->selectionModel()->selectedIndexes();
    if( !selected.isEmpty() )
        query = QString("SELECT ?predicate ?object WHERE { <%1> ?predicate ?object }")
                .arg( model_->fileInfo( filter_->mapToSource(selected.first()).row())->urn() );

    SuovaSparqlWidget* sparWidget = new SuovaSparqlWidget(query);
    sparWidget->setAttribute(Qt::WA_DeleteOnClose);
    sparWidget->show();
}

void SuovaWindow::fileSelected(const QModelIndex &index)
{

    QModelIndex sourceIndex = filter_->mapToSource(index);
    SuovaFileFullInfo* info = model_->fileInfo( sourceIndex.row());
    infoTable_->setModel( info );

    // Preview!

    QString mime = info->information("mimeType").toString();
    if( mime.startsWith("image") && info->information("fileSize").toInt() < 1024 * 1024 * 2)
        textBrowser_->setHtml( QString("<img src=\"%1\" width=%2>").arg(info->information("url").toString()).arg(textBrowser_->width()-20) );
    else if((mime.startsWith("text/html") || mime.startsWith("text/plain")) && info->information("fileSize").toInt() < 1024 * 32)
        textBrowser_->setSource( info->information("url").toString() );
    else
        textBrowser_->setText( info->information("plainTextContent").toString());
}


void SuovaWindow::doSeach()
{
    // DIRTY test code to make searches!

    QString typeWhere;
    QString keyWhere;
    QString type = typeCombo_->itemData(typeCombo_->currentIndex()).toString();
    if( !type.isEmpty())
        typeWhere= QString("rdf:type '%1';").arg(type);
    QString keyword = keywordCombo_->itemData( keywordCombo_->currentIndex()).toString();
    if( !keyword.isEmpty())
        keyWhere = QString("nie:keyword '%1' ;").arg(keyword);

    QString tag = tagCombo_->itemData( tagCombo_->currentIndex()).toString();
    if( !tag.isEmpty())
        keyWhere += QString("nao:hasTag [nao:prefLabel '%1'] ; ").arg(tag);

    // Test code: full text search
    if( !searchTextEdit_->text().isEmpty())
    {
        QString where;
        // do full text seach
        if( searchTypeCombo_->currentIndex()==1)
            where = QString("{ ?f %2 %3 fts:match '%1*' } ").arg(searchTextEdit_->text()).arg(typeWhere).arg(keyWhere);
        else
            where = QString("{ ?f %1  %4 %2 ?name . FILTER regex(?name, '%3')  }").arg(typeWhere).arg( searchTypeCombo_->itemData(searchTypeCombo_->currentIndex()).toString()).arg(searchTextEdit_->text()).arg(keyWhere) ;
        model_->setWhere(where);
    }
    else
        // do last accessedseach
    {
        keyWhere.clear();
        if( !keyword.isEmpty())
            keyWhere = QString("; nie:keyword '%1' ").arg(keyword);
        if( !tag.isEmpty())
            keyWhere += QString(" ; nao:hasTag [nao:prefLabel '%1'] ").arg(tag);
        if( type.isEmpty())
            model_->setWhere(QString("{ ?f nfo:fileLastAccessed ?pvm %1} ORDER BY DESC(?pvm) LIMIT 100 ").arg(keyWhere));
        else
            model_->setWhere(QString("{ ?f nfo:fileLastAccessed ?pvm ; rdf:type '%1' %2} ORDER BY DESC(?pvm) LIMIT 100 ").arg(type).arg(keyWhere));
    }

}
