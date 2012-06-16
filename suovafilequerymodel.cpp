/**************************************************************************
**  suovafilequerymodel.cpp
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

#include "suovafilequerymodel.h"

#include <QIcon>
#include <QUrl>
#include <QFile>
#include <QDate>

SuovaFileQueryModel::SuovaFileQueryModel(QObject *parent, const QString &where) :
    SuovaAbstractQueryModel(parent)
{
    if( !where.isEmpty())
        setWhere(where);
}


bool SuovaFileQueryModel::setWhere(const QString &where)
{
    // query with file info headers and custom where
    QString query = QString("SELECT ?f WHERE  %2 ").arg(where);

    return execQuery(query);

}

SuovaFileFullInfo* SuovaFileQueryModel::fileInfo(const int row) const
{
    return files_.value(row,0);
}


void SuovaFileQueryModel::appendRow(const QStringList &rowData)
{
    // append SuovaFileInfo object
    SuovaFileFullInfo* info = new SuovaFileFullInfo(rowData.first(), this);
    files_.append( info );
}


void SuovaFileQueryModel::clear()
{
    SuovaFileFullInfo* info;
    foreach( info, files_)
        info->deleteLater();
    files_.clear();
}

int SuovaFileQueryModel::rowCount(const QModelIndex &) const
{
    return files_.count();
}

int SuovaFileQueryModel::columnCount(const QModelIndex &) const
{
    // File, Modified, Accessed and Size, tags
    return 5;
}

QVariant SuovaFileQueryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::TextAlignmentRole)
        return int( Qt::AlignCenter | Qt::AlignVCenter);
    else if( role == Qt::DisplayRole)
    {
        if( orientation == Qt::Vertical)
            return QVariant(section+1);   // row number
        else
        {
            switch(section)
            {
            case 0 : return tr("File");
            case 1: return tr("Modified");
            case 2: return tr("Accessed");
            case 3: return tr("Size");
            case 4: return tr("Tags");

            }
        }
    }

    return QVariant();
}


QVariant SuovaFileQueryModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid())
        return QVariant();

    if( role == Qt::TextAlignmentRole)
    {
        if( index.column()==0)
            return int( Qt::AlignLeft | Qt::AlignTop);
        else if( index.column() == 1)
            return int( Qt::AlignCenter | Qt::AlignTop);
        return int( Qt::AlignRight | Qt::AlignTop);
    }

    else if( role == Qt::DisplayRole)
    {       
        switch( index.column() )
        {
        case 0:
            return files_.at(index.row())->information("fileName");
        case 1:
            return files_.at(index.row())->information("fileLastModified").toDate();
        case 2:
            return files_.at(index.row())->information("fileLastAccessed").toDate();
        case 3:
        {
            int bytes = files_.at(index.row())->information("fileSize").toInt();
            if( bytes < 1024 )
                return tr("%1 B").arg(bytes);
            if( bytes < 1024 * 1024)
                return tr("%1 kB").arg(bytes / 1024);
            return tr("%1 MB").arg( bytes / (1024 * 1024));
        }
        case 4:
            return files_.at(index.row())->information("tag").toString();
        }

    }
    else if( role == Qt::UserRole)
    {
        switch( index.column() )
        {
        case 0:
            if( files_.at(index.row())->information("title").isNull())
                return files_.at(index.row())->information("fileName");
            else
                return files_.at(index.row())->information("title");
        case 1:
            return files_.at(index.row())->information("fileLastModified");
        case 2:
            return files_.at(index.row())->information("fileLastAccessed");
        case 3:
        {
            int bytes = files_.at(index.row())->information("fileSize").toInt();
            return bytes; // Disabled to sort!
            if( bytes < 1024 )
                return tr("%1 b").arg(bytes);
            if( bytes < 1024 * 1024)
                return tr("%1 k").arg(bytes / 1024);
            return tr("%1 MB").arg( bytes / (1024 * 1024));
        }
        case 4:
            return files_.at(index.row())->information("tag").toString();
        }

    }
    else if( role == Qt::DecorationRole && index.column() == 0)
    {
        // mimetype icons
        // testing - image for images
        QString iconFileName;
        QString mimetype = files_.at(index.row())->information("mimeType").toString();
        if( mimetype.startsWith("image"))
            iconFileName = QUrl(files_.at(index.row())->information("url").toString() ).toLocalFile() ;
        else
            iconFileName = QString(":/mime/pic/%1.png").arg( mimetype.replace('/','-'));
        if( QFile(iconFileName).exists())
                return QIcon(iconFileName);    // icon for mime type
        return QIcon(":/mime/pic/unknown.png");
    }

    return QVariant();
}

QString SuovaFileQueryModel::result(const int row, const int column) const
{
    return data( index(row,column), Qt::DisplayRole ).toString();
}
