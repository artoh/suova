/**************************************************************************
**  suovaabstractfileinfo.h
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
**  SuovaAbstractFileInfo  15.6.2012
**************************************************************************/

#ifndef SUOVAABSTRACTFILEINFO_H
#define SUOVAABSTRACTFILEINFO_H

#include <QStringList>
#include <QList>
#include <QVariant>

/** Information about single file

  */
class SuovaAbstractFileInfo
{
public:
    SuovaAbstractFileInfo();

    virtual QString urn() const = 0;

    virtual QVariant information(const QString& key) const = 0;
    virtual QList<QVariant> informations(const QString& key) const = 0;
    /** List of all keys*/
    virtual QStringList allKeys() const = 0;
    /** List of all information values, in key order*/
    virtual QList<QVariant> allInformation() const = 0;

protected:
    /** Field name without any content
        nfo:fileName --> fileName */
    QString withoutContext(const QString& key) const;

};

#endif // SUOVAABSTRACTFILEINFO_H
