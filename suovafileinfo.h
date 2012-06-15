/**************************************************************************
**  suovafileinfo.h
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
**  SuovaFileInfo  12.6.2012
**************************************************************************/

#ifndef SUOVAFILEINFO_H
#define SUOVAFILEINFO_H

#include "suovaabstractfileinfo.h"

#include <QDateTime>

/** Stores information about a single file
  */
class SuovaFileInfo : public SuovaAbstractFileInfo
{
public:
    /** Construct a file information

        @arg data QStringList containing data (heders) in right order:
        urn, url, file name, title, mimetype, time created, time modified, time accessed, bytes */
    SuovaFileInfo(QStringList data);


public:
    QString urn() const { return urn_; }
    QString url() const { return url_; }
    QString fileName() const { return filename_; }
    QString title() const { return title_; }
    QString mimetype() const { return mimetype_; }
    QDateTime created() const { return created_; }
    QDateTime modified() const { return modified_; }
    QDateTime accessed() const { return accessed_; }
    int bytes() const { return bytes_; }

    /** Information about specified key

        @arg Field name shortly */
    QVariant information(const QString& key) const;
    QList<QVariant> informations(const QString& key) const;
    /** List of all keys*/
    QStringList allKeys() const;
    /** List of all information values, in key order*/
    QList<QVariant> allInformation() const;

    static const QString SelectFields;

private:
    QString urn_;
    QString url_;
    QString filename_;
    QString title_;
    QString mimetype_;
    QDateTime created_;
    QDateTime modified_;
    QDateTime accessed_;
    int bytes_;
};

#endif // SUOVAFILEINFO_H
