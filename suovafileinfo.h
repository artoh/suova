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

#include <QStringList>
#include <QDateTime>
#include <QMap>


/** Stores information about a single file
  */
class SuovaFileInfo
{
public:
    /** Construct a file information

        @arg data QStringList containing data (heders) in right order:
        urn, url, file name, title, mimetype, time created, time modified, time accessed, bytes */
    SuovaFileInfo(QStringList data = QStringList());


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

    /** List of tags */
    QStringList tags() const;

    /** Information about specified key

        @arg Field name with full namespace */
    QString information(QString key) const;
    QStringList informations(QString key) const;
    QStringList keys() const { return information_.keys(); }
    QStringList information() const { return information_.values(); }

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

    QMap<QString,QString> information_; /** All information reached by tracker-info*/
    QStringList tags_;

    bool allInformationFetched_;    /** Have all the information, or only headers*/
    bool tagsFetched_;

    /** Fetch all information reached by tracker-info*/
    void fetchAllInformation();
    void fetchTags();
};

#endif // SUOVAFILEINFO_H
