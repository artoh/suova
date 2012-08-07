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


#include "suovaabstractquerymodel.h"

#include <QStringList>
#include <QVector>

/** Model for SPARQL query

    Storing results in table
  */
class SuovaQueryModel : public SuovaAbstractQueryModel
{
    Q_OBJECT
public:
    SuovaQueryModel(QObject *parent = 0, QString query = QString());
    
    Q_INVOKABLE int rowCount(const QModelIndex& /* parent */ = QModelIndex()) const; //Q_INVOKABLE added by Heli Hyvättinen 2012 for use from QML in the Harmattan version
    int columnCount(const QModelIndex& /* parent */ = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /** Return single result item as string */
    Q_INVOKABLE virtual QString result(const int row, const int column) const; //Q_INVOKABLE added by Heli Hyvättinen 2012 for use from QML in the Harmattan version


    /** Set and exec SPARQL query

      @arg query Query to execute
      @returns true is successed */
    Q_INVOKABLE bool setQuery( const QString& query ); //Q_INVOKABLE added by Heli Hyvättinen 2012 for use from QML in the Harmattan version

    virtual void clear();


signals:
    
public slots:

protected:
    virtual void appendRow(const QStringList& rowData); /** Append a row from QStringList data*/

private:
    void storeQuery( const QString& query); /** Store query command*/

    QVector<QStringList> result_; /** Results for query */
    QStringList columnHeaders_;
};

#endif // SUOVAQUERYMODEL_H
