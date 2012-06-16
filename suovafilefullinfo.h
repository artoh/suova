/**************************************************************************
**  suovafilefullinfo.h
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
**  SuovaFileFullInfo  15.6.2012
**************************************************************************/

#ifndef SUOVAFILEFULLINFO_H
#define SUOVAFILEFULLINFO_H

#include "suovaabstractquerymodel.h"
#include "suovaabstractfileinfo.h"

/** Stores full information about a single file (including tags)

  */
class SuovaFileFullInfo : public SuovaAbstractQueryModel, public SuovaAbstractFileInfo
{
    Q_OBJECT
public:
    SuovaFileFullInfo(QString urn, QObject *parent = 0);
    

    QVariant data(const QModelIndex &index, int role) const;
    virtual QString result(const int row, const int column) const;

    int rowCount(const QModelIndex& /* parent */ = QModelIndex()) const;
    int columnCount(const QModelIndex& /* &parent */ = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QVariant information(const QString& key) const;
    QList<QVariant> informations(const QString& key) const;
    QStringList allKeys() const;
    QList<QVariant> allInformation() const;

    QString urn() const { return urn_; }

signals:
    
public slots:

protected:
    virtual void appendRow(const QStringList &rowData);

private:
    QString urn_;
    QMap<QString,QVariant> information_; /** All information reached by tracker-info*/
    
};

#endif // SUOVAFILEFULLINFO_H
