/**************************************************************************
**  suovaeasyfilequerymodel.h (of Suova)
**  Copyright (c) 2012 Heli Hyvättinen
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
**  SuovaEasyFileQueryModel 10.7.2012
**************************************************************************/

#ifndef SUOVAEASYFILEQUERYMODEL_H
#define SUOVAEASYFILEQUERYMODEL_H

#include "suovafilequerymodel.h"


class SuovaEasyFileQueryModel : public SuovaFileQueryModel
{
    Q_OBJECT
public:
    explicit SuovaEasyFileQueryModel(QObject *parent = 0);


    
signals:
    
public slots:

    void setSearchType(QString type);
    void setFileType(QString type);
    void setSearchString(QString search);
    void setTag(QString tag);
    void setKeyword(QString keyword);
    void doQuery();

protected:

    QString searchType_;
    QString fileType_;
    QString searchString_;
    QString tag_;
    QString keyword_;


    
};

#endif // SUOVAEASYFILEQUERYMODEL_H
