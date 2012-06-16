/**************************************************************************
**  suovaabstractquerymodel.cpp
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

#include "suovaabstractquerymodel.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusArgument>


SuovaAbstractQueryModel::SuovaAbstractQueryModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}


QVariant SuovaAbstractQueryModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid())
        return QVariant();

    if( role == Qt::DisplayRole)
    {
        return result( index.row(), index.column());
    }

    return QVariant();
}

bool SuovaAbstractQueryModel::execQuery(QString query)
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

        bool modified = rowCount() > 0; // If there is data, model must emit some signals
        if( modified)
            beginRemoveRows(QModelIndex(),0, rowCount()-1);
        clear();            // Clear old result set
        if(modified)
            endRemoveRows();

        query_ = query;     // Store query string

        QVariant firstArgument = message.arguments().first();
        QDBusArgument resultSet = firstArgument.value<QDBusArgument>();

        resultSet.beginArray();
        while( !resultSet.atEnd())
        {
            // Append every row to internal result storage
            // There is a virtual function for more hight level functions
            if( modified)
                beginInsertRows(QModelIndex(),rowCount(), rowCount()+1);
            appendRow(resultSet.asVariant().toStringList() );
            if( modified)
                endInsertRows();
        }
        emit layoutChanged();
        return true;
    }

    // Unsuccessed - no data in reply message
    return false;

}
