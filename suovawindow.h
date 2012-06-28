/**************************************************************************
**  suovawindow.h
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
**    12.6.2012
**************************************************************************/

#ifndef SUOVAWINDOW_H
#define SUOVAWINDOW_H

#include "suovafilequerymodel.h"

#include <QtGui/QMainWindow>

#include <QTableView>
#include <QTextBrowser>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QComboBox>


class SuovaWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    SuovaWindow(QWidget *parent = 0);
    ~SuovaWindow();

public slots:
    void fileSelected( const QModelIndex& index);
    void doSeach();
    void sparql();

protected:
    QTableView* infoTable_;
    QTextBrowser* textBrowser_;
    QSortFilterProxyModel* filter_;


    SuovaFileQueryModel* model_;
    QLineEdit* searchTextEdit_;
    QComboBox* typeCombo_;
    QComboBox* searchTypeCombo_;
    QComboBox* keywordCombo_;
    QComboBox* tagCombo_;
    QTableView* view_;

};

#endif // SUOVAWINDOW_H
