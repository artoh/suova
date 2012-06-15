/**************************************************************************
**  suovafilequerymodel.h
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
**  SuovaFileQueryModel  13.6.2012
**************************************************************************/

#ifndef SUOVAFILEQUERYMODEL_H
#define SUOVAFILEQUERYMODEL_H

#include "suovafilefullinfo.h"

#include <QList>

/** Model for quering files

    This is advanced (table) model for getting file list

  */
class SuovaFileQueryModel : public SuovaAbstractQueryModel
{
    Q_OBJECT
public:
    explicit SuovaFileQueryModel(QObject *parent = 0, const QString& where = QString());

    int rowCount(const QModelIndex & = QModelIndex()) const;
    int columnCount(const QModelIndex & = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

    virtual QString result(const int row, const int column) const;

    SuovaFileFullInfo* fileInfo(const int row) const;

    /** Query with where clause*/
    bool setWhere(const QString& where);

    void clear();

signals:
    
public slots:
    
protected:
    virtual void appendRow(const QStringList &rowData);

    QList<SuovaFileFullInfo*> files_;
};

#endif // SUOVAFILEQUERYMODEL_H
