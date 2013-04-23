#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm.h>

class MyArea : public Gtk::DrawingArea
{
	public:
		MyArea();
		virtual ~MyArea();

	protected:
		//Override default signal handler:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
};

#endif // GTKMM_EXAMPLE_MYAREA_H
