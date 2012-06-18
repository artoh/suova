/**************************************************************************
**  suovasparqlwidget.h
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

#ifndef SUOVASPARQLWIDGET_H
#define SUOVASPARQLWIDGET_H

#include "suovaquerymodel.h"

#include <QWidget>

#include <QLineEdit>
#include <QListWidget>
#include <QTableView>
#include <QStringList>

/** Widget for custom SPARQL queries

    Supports history, saved queries, urn links and to open url

    Based on trackerlelu

  */
class SuovaSparqlWidget : public QWidget
{
    Q_OBJECT
public:
    /** Tool for custom queries

      @arg query Initial query
      */
    SuovaSparqlWidget(const QString& query=QString(), QWidget *parent = 0);

    ~SuovaSparqlWidget();
    
signals:
    
public slots:
    /** Execute current query */
    void execute();
    /** Save current query */
    void saveQuery();
    /** Back to previous query*/
    void historyBack();
    /** Open clicked url or urn */
    void cellClicked(const QModelIndex& index);
    /** Execute a saved query*/
    void execute(const QString& query);


private:
    QLineEdit* queryLine_;
    QListWidget* savedList_;
    QTableView* resultTable_;
    QStringList history_;

    SuovaQueryModel* suovaModel_;
};

#endif // SUOVASPARQLWIDGET_H
