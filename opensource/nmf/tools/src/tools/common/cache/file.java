/*
 * Copyright (C) ST-Ericsson SA 2010. All rights reserved.
 *
 * This code is part of the NMF Toolset.
 *
 * The NMF Toolset is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * The NMF Toolset is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the NMF Toolset. If not, see <http://www.gnu.org/licenses/>.
 *
 */
package tools.common.cache;

import java.io.File;
import java.util.Hashtable;

public class file {
	protected static Hashtable<String, Long> files = new Hashtable<String, Long>();
	
	public static long getModifiedDate(String filename) {
		Long date = files.get(filename.replace('\\', '/'));
		if(date == null) {
			File file = new File(filename);
			date = new Long(file.lastModified());
			files.put(file.getPath().replace('\\', '/'), date);
		};
		return date.longValue();
	}
}