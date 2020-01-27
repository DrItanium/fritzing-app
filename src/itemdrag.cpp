/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2019 Fritzing

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************/


#include "itemdrag.h"
#include "debugdialog.h"

void ItemDrag::__dragIsDone() {
	m_cache.clear();
	emit dragIsDoneSignal(this);
}

void ItemDrag::cleanup() { }

QHash<QObject *, QObject *> & ItemDrag::cache() {
	return singleton().m_cache;
}

ItemDrag& ItemDrag::singleton() noexcept {
    static ItemDrag _singleton;
	return _singleton;
}

void ItemDrag::dragIsDone() {
	singleton().__dragIsDone();
}

void ItemDrag::setOriginator(QWidget * originator) {
	singleton().m_originator = originator;
}

QWidget* ItemDrag::originator() {
	return singleton().m_originator;
}

void ItemDrag::setOriginatorIsTempBin(bool itb) {
    singleton().m_originatorIsTempBin = itb;
}

bool ItemDrag::originatorIsTempBin() {
    return singleton().m_originatorIsTempBin;
}
