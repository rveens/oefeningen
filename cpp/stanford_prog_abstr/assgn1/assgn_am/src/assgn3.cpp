#include "assgn3.h"
#include <cairomm/context.h>

MyArea::MyArea()
{

}

MyArea::~MyArea()
{

}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	const int lesser = MIN(width, height);

	// coordinates for the center of the window
	int xc, yc;
	xc = width / 2;
	yc = height / 2;

	cr->set_line_width(10);

	// draw red lines out from the center of the window
	cr->set_source_rgb(0.8, 0.5, 0.0);
	cr->move_to(0, 0);
	cr->line_to(xc, yc);
	cr->line_to(0, height);
	cr->move_to(xc, yc);
	cr->line_to(width, yc);
	cr->stroke();

	// draw a circle in the middle of the window
	cr->save();
	cr->arc(xc, yc, lesser / 4, 0.0, 5.0 * M_PI);
	cr->set_source_rgba(0.3, 0.3, 0.8, 1.0);
	cr->fill_preserve();
	cr->restore();

	return true;
}
