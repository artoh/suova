/**************************************************************************
**  suovaabstractquerymodel.h
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
**  SuovaAbstractQueryModel  14.6.2012
**************************************************************************/

#ifndef SUOVAABSTRACTQUERYMODEL_H
#define SUOVAABSTRACTQUERYMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

/** Model fot SPARQL queries

    This is a most low lever query model

  */
class SuovaAbstractQueryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SuovaAbstractQueryModel(QObject *parent = 0);
    
    QVariant data(const QModelIndex &index, int role) const;

    /** Return single result item as string */
    virtual QString result(const int row, const int column) const = 0;

    /** SPARQL query */
    QString query() const { return query_; }

    /** Clear results

      It is possible to make models without function to reload results,
      so it can be empty funtion.
      */
    virtual void clear() {;}

signals:
    
public slots:
    
protected:
    /** Append a row from QStringList*/
    virtual void appendRow(const QStringList& rowData) = 0; /** Append a row from QStringList data*/

    /** Set and exec SPARQL query

      @arg query Query to execute
      @returns true is successed */
    bool execQuery( QString query );



private:
    QString query_; /** SPARQL query */
};

#endif // SUOVAABSTRACTQUERYMODEL_H
