/**************************************************************************
**  suovaquerymodel.cpp
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

#include "suovaquerymodel.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusArgument>

SuovaQueryModel::SuovaQueryModel(QObject *parent, QString query) :
    QAbstractTableModel(parent)
{
    if( !query.isEmpty())
        setQuery(query);
}

int SuovaQueryModel::rowCount(const QModelIndex& /* parent */) const
{
    return result_.count();
}

int SuovaQueryModel::columnCount(const QModelIndex& /* parent */) const
{
    if( result_.count())
        return result_.first().count();
    return 0;
}

QString SuovaQueryModel::result(const int row, const int column) const
{
    if( row >= 0 && row < rowCount() && column >= 0 && column < columnCount())
    {
        return result_.at(row).at(column);
    }

    return QString();   // Out of result set
}


QVariant SuovaQueryModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid())
        return QVariant();

    if( role == Qt::TextAlignmentRole)
        return int( Qt::AlignLeft | Qt::AlignTop);
    else if( role == Qt::DisplayRole)
    {
        return result( index.row(), index.column());
    }

    return QVariant();
}

bool SuovaQueryModel::setQuery(QString query)
{
    // dbus message connecting to Meta Tracker server
    QDBusMessage message = QDBusMessage::createMethodCall("org.freedesktop.Tracker1","/org/freedesktop/Tracker1/Resources",
                                                              "org.freedesktop.Tracker1.Resources","SparqlQuery");
    QList<QVariant> arguments;
    arguments.append( query );
    message.setArguments(arguments);

    // call Meta Tracker
    message = QDBusConnection::sessionBus().call(message);

    if( message.type() == QDBusMessage::ErrorMessage)
        return false;

    // dbus reply message contains results as first argument
    // first argument is a table containing the results

    if( message.arguments().count())
    {
        QVariant firstArgument = message.arguments().first();
        QDBusArgument resultSet = firstArgument.value<QDBusArgument>();

        resultSet.beginArray();
        while( !resultSet.atEnd())
        {
            // Append every row to internal result storage
            result_.append( resultSet.asVariant().toStringList() );
        }

        return true;
    }

    // Unsuccessed - no data in reply message
    return false;

}

