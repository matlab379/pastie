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

#ifndef SETTING_H
#define SETTING_H

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QComboBox>
#include <QCheckBox>
#include <QMap>

#include <opencv2/core.hpp>
#include "rangeslider.h"
#include "range.h"

using namespace cv;

class Filter;

class Setting : public QObject
{
	Q_OBJECT

	public:
		Setting(Filter *f, QString tip);
		QWidget * getWidget(QWidget *parent);

	signals:
		void valueChanged();

	protected:
		virtual QWidget * createWidget(QWidget *parent) = 0;

		Filter *filter;
		QWidget *widget = NULL;
		QString toolTip;
};

class BooleanSetting : public Setting
{
	Q_OBJECT

	public:
		BooleanSetting(Filter *f, bool &v, QString tip = "") :
			Setting(f, tip), value(v) { }

	protected:
		QWidget *createWidget(QWidget *parent);

		bool &value;
		QCheckBox *box;
};

class IntegerSetting : public Setting
{
	Q_OBJECT

	public:
        IntegerSetting(Filter *f, int &v, ps::Range<int> l = ps::Range<int>(0, 100), QString tip = "") :
			Setting(f, tip), value(v), limits(l) { }

	protected:
		QWidget * createWidget(QWidget *parent = 0);

		int &value;
        ps::Range<int> limits;
		QSpinBox *spinner;
		QSlider *slider;
};

class DoubleSetting : public Setting
{
	Q_OBJECT

	public:
        DoubleSetting(Filter *f, double &v, ps::Range<double> l = ps::Range<double>(0, 100), QString tip = "") :
			Setting(f, tip), value(v), limits(l) { }

	protected:
		static const int SCALE = 1000;

		QWidget * createWidget(QWidget *parent = 0);

		double &value;
        ps::Range<double> limits;
		QDoubleSpinBox *spinner;
		QSlider *slider;

		double getSliderValue(int v);
		void setSliderValue(double value);
};

class RangeSetting : public Setting
{
		Q_OBJECT

	public:
        RangeSetting(Filter *f, ps::Range<int> &r, ps::Range<int> l = ps::Range<int>(0, 100), QString tip = "") :
			Setting(f, tip), range(r), limits(l) { }

	protected:
		QWidget * createWidget(QWidget *parent);

        ps::Range<int> &range;
        ps::Range<int> limits;

		QSpinBox *spinnerL, *spinnerU;
		RangeSlider *slider;
};

class DoubleRangeSetting : public Setting
{
		Q_OBJECT

	public:
        DoubleRangeSetting(Filter *f, ps::Range<double> &r, ps::Range<double> l = ps::Range<double>(0, 100), QString tip = "") :
			Setting(f, tip), range(r), limits(l) { }

	protected:
		static const int SCALE = 1000;

		QWidget * createWidget(QWidget *parent);

        ps::Range<double> &range;
        ps::Range<double> limits;

		QDoubleSpinBox *spinnerL, *spinnerU;
		RangeSlider *slider;

        ps::Range<double> getSliderRange(ps::Range<int> range);
        void setSliderRange(ps::Range<double> value);
};

class EnumSetting : public Setting
{
		Q_OBJECT

	public:
		EnumSetting(Filter *f, int &v, QMap<int, QString> m, QString tip = "") :
			Setting(f, tip), value(v), map(m) { }

	protected:
		QWidget * createWidget(QWidget *parent);

		int &value;
		QMap<int, QString> map;
		QComboBox *combo;
};

class SizeSetting : public Setting
{
		Q_OBJECT

	public:
        SizeSetting(Filter *f, Size &v, ps::Range<int> l = ps::Range<int>(1, 100), QString tip = "") :
			Setting(f, tip), value(v), limits(l) { }

	protected:
		QWidget * createWidget(QWidget *parent);

		Size &value;
        ps::Range<int> limits;

		QSpinBox *spinnerH, *spinnerW;
};

#endif // SETTING_H
