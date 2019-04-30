/*
 * Copyright (C) 2016-2019 Fanout, Inc.
 *
 * This file is part of Pushpin.
 *
 * $FANOUT_BEGIN_LICENSE:AGPL$
 *
 * Pushpin is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Pushpin is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Alternatively, Pushpin may be used under the terms of a commercial license,
 * where the commercial license agreement is provided with the software or
 * contained in a written agreement between you and Fanout. For further
 * information use the contact form at <https://fanout.io/enterprise/>.
 *
 * $FANOUT_END_LICENSE$
 */

#ifndef INSTRUCT_H
#define INSTRUCT_H

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QList>
#include <QHash>
#include <QUrl>
#include "packet/httpresponsedata.h"

class Instruct
{
public:
	enum HoldMode
	{
		NoHold,
		ResponseHold,
		StreamHold
	};

	enum KeepAliveMode
	{
		NoKeepAlive,
		Idle,
		Interval
	};

	class Channel
	{
	public:
		QString name;
		QString prevId;
		QStringList filters;
	};

	HoldMode holdMode;
	QList<Channel> channels;
	int timeout;
	QList<QByteArray> exposeHeaders;
	KeepAliveMode keepAliveMode;
	QByteArray keepAliveData;
	int keepAliveTimeout;
	QHash<QString, QString> meta;
	HttpResponseData response;
	QUrl nextLink;
	int nextLinkTimeout;

	Instruct() :
		holdMode(NoHold),
		timeout(-1),
		keepAliveMode(NoKeepAlive),
		keepAliveTimeout(-1),
		nextLinkTimeout(-1)
	{
	}

	static Instruct fromResponse(const HttpResponseData &response, bool *ok = 0, QString *errorMessage = 0);
};

#endif
