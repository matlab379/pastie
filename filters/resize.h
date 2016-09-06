/*
 * This file is part of Pastie
 *
 * Pastie is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Pastie is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Pastie. If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @copyright  2015 Steffen Vogel
 * @license	   http://www.gnu.org/licenses/gpl.txt GNU Public License
 * @author     Steffen Vogel <steffen.vogel@rwth-aachen.de>
 * @link       http://www.steffenvogel.de
 */

#ifndef RESIZE_H
#define RESIZE_H

#include "filter.h"

class Resize : public Filter
{
	public:
        Resize(ps::Range<int> r = ps::Range<int>(320, 1024), int inter = INTER_LINEAR);

		QString getName() const { return "Resize"; }

	protected:
        ps::Range<int> range;
		int interpolation;

		Result * applyInternal(Image *img);
};

#endif // RESIZE_H
