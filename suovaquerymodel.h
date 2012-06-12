/**************************************************************************
**  suovaquerymodel.h
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
**  SuovaQueryModel  12.6.2012
**************************************************************************/

#ifndef SUOVAQUERYMODEL_H
#define SUOVAQUERYMODEL_H

#include <QAbstractTableModel>

#include <QStringList>

/** Model for SPARQL query

  */
class SuovaQueryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SuovaQueryModel(QObject *parent = 0, QString query = QString());
    
    int rowCount(const QModelIndex& /* parent */ = QModelIndex()) const;
    int columnCount(const QModelIndex& /* parent */ = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    /** Return single result item as string*/
    QString result(const int row, const int column) const;

    /** SPARQL query */
    QString query() const { return query_; }


    /** Set and exec SPARQL query

      @arg query Query to execute
      @returns true is successed */
    bool setQuery( QString query );

signals:
    
public slots:

private:
    QList<QStringList> result_; /** Results for query */
    QString query_; /** SPARQL query */
};

#endif // SUOVAQUERYMODEL_H