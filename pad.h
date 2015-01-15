#ifndef PAD_H
#define PAD_H

#include <QtGlobal>

#include <opencv2/core.hpp>

using namespace cv;

class Pad : public RotatedRect
{
	public:
		Pad(const Point &p);
		Pad(const RotatedRect &p);

		double getArea() const { return size.area(); }
		double getRatio() const { return qMax(size.width, size.height) / qMin(size.width, size.height); }
		Point2f getCenter() const { return center; }
		Point2f const * getVertexes() const { return vertexes; }

		operator Point2f() const { return center; }

	protected:
		Point2f vertexes[4];
};

#endif // PAD_H
