/** -*- mode: c-mode; tab-width: 4; indent-tabs-mode: t; -*-
 * @file notifier.cpp Base class implementations
 *
 * Copyright (C) 2004 Mike Hearn
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA  02111-1307  USA
 */

#include "notifier.h"
#include "logging.h"

Notification::Notification()
{
	summary = body = sound = NULL;
	images = NULL;
	primary_frame = -1;
	timeout = 0;
	use_timeout = true;
	id = 0;
}

Notification::~Notification()
{
	if (this->summary) free(this->summary);
	if (this->body) free(this->body);
	// FIXME: free images/sound data
}

/*************************************************************/

BaseNotifier::BaseNotifier()
{
	next_id = 0;
}

int
BaseNotifier::notify(Notification *n)
{
	/* add to the internal list using the next cookie, increment, return */
	n->id = next_id;
	
	next_id++;
	
	notifications[n->id] = n;
	
	return n->id;
}

bool
BaseNotifier::unnotify(uint id)
{
	validate( notifications.find(id) != notifications.end(), false,
			  "Given ID (%d) is not valid", id );
	
	delete notifications[id];
	notifications.erase(id);
	
	return true;
}

Notification*
BaseNotifier::create_notification()
{
	return new Notification();
}
