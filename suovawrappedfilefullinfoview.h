/**************************************************************************
**  suovawrappedfilefullinfoview.h (of Suova)
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
**  SuovaWrappedFileFullInfoView 7.8.2012
**************************************************************************/

#ifndef SUOVAWRAPPEDFILEFULLINFOVIEW_H
#define SUOVAWRAPPEDFILEFULLINFOVIEW_H

#include <QGraphicsProxyWidget>
#include "suovafilefullinfo.h"
#include <QTableView>
/*
  Provides QML accessible QTableView that uses SuovaFileFullInfo as its model.
  */

class SuovaWrappedFileFullInfoView : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit SuovaWrappedFileFullInfoView(QGraphicsProxyWidget *parent = 0);
    
    ~SuovaWrappedFileFullInfoView();

signals:
    
public slots:

    void setUrn(QString urn);

private:

    QTableView*  pView_;
    SuovaFileFullInfo* pModel_;
    
};

#endif // SUOVAWRAPPEDFILEFULLINFOVIEW_H
