/**************************************************************************
**  suovafileinfo.cpp
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

#include "suovafileinfo.h"
#include "suovaquerymodel.h"

SuovaFileInfo::SuovaFileInfo(QStringList data)
{
    if( data.count() > 8)
    {
        // Data MUST be in correct order!!!
        QStringListIterator iter(data);

        urn_ = iter.next(); // 1. field: urn
        url_ = iter.next(); // 2. field: url
        filename_ = iter.next(); // 3. field: file name
        title_ = iter.next(); // 4. field: file title
        mimetype_ = iter.next(); // 5. field: mime type
        created_ = QDateTime::fromString(iter.next(), Qt::ISODate); // 6. created
        modified_ = QDateTime::fromString(iter.next(), Qt::ISODate); // 7. modified
        accessed_ = QDateTime::fromString(iter.next(), Qt::ISODate); // 8. accessed
        bytes_ = iter.next().toInt(); // 9. file size in bytes
    }
}


QVariant SuovaFileInfo::information(const QString &key) const
{
    QString shortKey = withoutContext(key); // nie:title --> title

    if( shortKey == "fileLastAccessed")
        return accessed();
    else if( shortKey == "fileLastModified")
        return modified();
    else if( shortKey == "fileName")
        return fileName();
    else if( shortKey == "fileSize")
        return bytes();
    else if( shortKey == "contentCreated")
        return created();
    else if( shortKey == "isStoredAs")
        return urn();
    else if( shortKey == "mimeType")
        return mimetype();
    else if( shortKey == "title")
        return title();
    else if( shortKey == "url")
        return url();

    return QVariant();
}

QList<QVariant> SuovaFileInfo::informations(const QString &key) const
{
    // Return single item as list.
    QList<QVariant> list;
    list.append(information(key));
    return list;
}

QStringList SuovaFileInfo::allKeys() const
{
    QStringList keys;
    keys << "fileAccessed" << "fileLastModified" << "fileName"
         << "fileSize" << "contentCreated" << "isStoredAs"
         << "mimeType" << "title" << "url";
    return keys;
}

QList<QVariant> SuovaFileInfo::allInformation() const
{
    QList<QVariant> information;
    information << accessed() << modified() << fileName()
                << bytes() << created() << urn()
                << mimetype() << title() << url();
    return information;
}





const QString SuovaFileInfo::SelectFields = "?f nie:url(?f) nfo:fileName(?f) nie:title(?f) nie:mimeType(?f) "
        "nie:contentCreated(?f) nfo:fileLastModified(?f) nfo:fileLastAccessed(?f) nfo:fileSize(?f)";
