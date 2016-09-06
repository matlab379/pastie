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

#include "threshold.h"

Threshold::Threshold(enum Threshold::Type t, double v, int sz, double d) :
	Filter(),
	type(t),
	method(THRESH_BINARY),
	size(sz),
	value(v),
	c(d)
{
	QMap<int, QString> typeMap;
	typeMap[ADAPTIVE_GAUSS] = "Adaptive Gauss";
	typeMap[ADAPTIVE_MEAN]  = "Adaptive Mean";
	typeMap[FIXED]          = "Fixed";
	typeMap[OTSU]			= "Otsu's method";
	typeMap[TRIANGLE]		= "Triangle";

	QMap<int, QString> methodMap;
	methodMap[THRESH_BINARY] = "Binary";
	methodMap[THRESH_TOZERO] = "To Zero";
	methodMap[THRESH_TRUNC]  = "Truncate";

	settings["Type"]		= new EnumSetting(this, (int&) type, typeMap);
	settings["Method"]		= new EnumSetting(this, (int&) method, methodMap);
    settings["Threshold"]	= new DoubleSetting(this, value, ps::Range<double>(0, 0xff));
    settings["C"]			= new DoubleSetting(this, c, ps::Range<double>(0, 0xff));
    settings["Size"]		= new IntegerSetting(this, size, ps::Range<int>(0, 100));
	settings["Inverted"]	= new BooleanSetting(this, invert);
}

Result * Threshold::applyInternal(Image *img)
{
	Mat &m = img->getMat();

	int threshMethod;
	switch (method) {
		case THRESH_BINARY:	threshMethod = invert ? THRESH_BINARY_INV : THRESH_BINARY; break;
		case THRESH_TOZERO: threshMethod = invert ? THRESH_TOZERO_INV : THRESH_TOZERO; break;
		default:			threshMethod = method;
	}

	if (type == ADAPTIVE_GAUSS)
			adaptiveThreshold(m, m, 0xff, ADAPTIVE_THRESH_GAUSSIAN_C, threshMethod, size, c);
	else if (type == ADAPTIVE_MEAN)
			adaptiveThreshold(m, m, 0xff, ADAPTIVE_THRESH_MEAN_C, threshMethod, size, c);
	else {
		int mode;
		switch (type) {
			case OTSU:		mode = THRESH_OTSU; break;
			case TRIANGLE:	mode = THRESH_TRIANGLE; break;
			default:		mode = 0;
		}

		double ret = threshold(m, m, value, 0xff, mode | threshMethod);
		return new DoubleResult("tresh", ret);
	}

	return NULL;
}
