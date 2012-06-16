/**************************************************************************
**  suovaabstractfileinfo.cpp
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

#include "suovaabstractfileinfo.h"

SuovaAbstractFileInfo::SuovaAbstractFileInfo()
{
}


QString SuovaAbstractFileInfo::withoutContext(const QString &key) const
{
    // Remove anything before / or : or #
    QString result = key;
    result.remove(0, key.lastIndexOf('/')+1);
    result.remove(0, result.lastIndexOf(":")+1);
    result.remove(0, result.lastIndexOf("#")+1);
    return result;
}
