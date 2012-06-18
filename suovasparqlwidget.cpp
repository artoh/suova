/**************************************************************************
**  suovasparqlwidget.cpp
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
**  SuovaSparqlWidget  18.6.2012
**************************************************************************/

#include "suovasparqlwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QSettings>

#include <QUrl>
#include <QDesktopServices>
#include <QIcon>

SuovaSparqlWidget::SuovaSparqlWidget(const QString& query, QWidget *parent) :
    QWidget(parent)
{

    // Set up widget
    setWindowIcon( QIcon(":/icon/pic/suova.png"));
    setWindowTitle( tr("Suova SPARQL Custom Query Tool"));

    QPushButton* backButton = new QPushButton(tr("<"));
    queryLine_ = new QLineEdit;
    queryLine_->setPlaceholderText(tr("Write SPARQL query here"));

    if( !query.isEmpty())
    {
        // Fist query. Update to history and line edit
        queryLine_->setText(query);
        history_.append(query);
    }

    QPushButton* executeButton = new QPushButton(tr("Execute"));
    QPushButton* saveButton = new QPushButton( tr("Save"));

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(backButton);
    topLayout->addWidget(queryLine_);
    topLayout->addWidget(executeButton);
    topLayout->addWidget(saveButton);

    savedList_ = new QListWidget;
    resultTable_ = new QTableView;

    suovaModel_ = new SuovaQueryModel(this, query);
    resultTable_->setModel(suovaModel_);
    resultTable_->resizeColumnsToContents();

    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(savedList_);
    splitter->addWidget(resultTable_);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,3);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(splitter);

    setLayout(mainLayout);

    connect( executeButton, SIGNAL(clicked()), this, SLOT(execute()));
    connect(queryLine_, SIGNAL(returnPressed()), this, SLOT(execute()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveQuery()));
    connect( backButton, SIGNAL(clicked()), this, SLOT(historyBack()));
    connect( resultTable_, SIGNAL(clicked(QModelIndex)), this, SLOT(cellClicked(QModelIndex)));
    connect( savedList_, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(executeSaved(QListWidgetItem*)));

    // Load settings
    QSettings settings;
    QStringList savedQueries = settings.value("savedQueries").toStringList();
    savedList_->insertItems(0, savedQueries);
    restoreGeometry( settings.value("sparqlWidget").toByteArray());

}


SuovaSparqlWidget::~SuovaSparqlWidget()
{
    // Save settings
    QSettings settings;

    QStringList savedQueries;
    for(int i=0; i<savedList_->count();i++)
        savedQueries.append( savedList_->item(i)->text() );

    settings.setValue("savedQueries", savedQueries);
    settings.setValue("sparqlWidget", saveGeometry());

}

void SuovaSparqlWidget::saveQuery()
{
    // Add query to saved list
    new QListWidgetItem( queryLine_->text(), savedList_);
}

void SuovaSparqlWidget::execute()
{
    // execute current query
    suovaModel_->setQuery(queryLine_->text());
    history_.append(queryLine_->text());
    resultTable_->resizeColumnsToContents();
}

void SuovaSparqlWidget::historyBack()
{
    if( !history_.empty())
    {
        history_.removeLast();
        if( !history_.empty())
        {
            // Execute last query in history
            queryLine_->setText( history_.takeLast());
            execute();
        }
    }
}

void SuovaSparqlWidget::executeSaved(QListWidgetItem *item)
{
    // Execute query
    queryLine_->setText( item->text() );
    execute();
}

void SuovaSparqlWidget::cellClicked(const QModelIndex &index)
{
    QString cellText = suovaModel_->result(index.row(), index.column());
    // If is it urn, selet information of urn
    if( cellText.startsWith("urn:"))
    {
        queryLine_->setText( QString("SELECT ?predicate ?object WHERE { <%1> ?predicate ?object }").arg(cellText) );
        execute();
    }
    else
    {
        // If it is a url, open it
        QUrl url( cellText );
        if( url.isValid())
            QDesktopServices::openUrl(url);
    }

}
