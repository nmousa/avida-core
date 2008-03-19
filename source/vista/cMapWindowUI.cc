//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1993 - 2000 California Institute of Technology             //
//                                                                          //
// Read the COPYING and README files, or contact 'avida@alife.org',         //
// before continuing.  SOME RESTRICTIONS MAY APPLY TO USE OF THIS FILE.     //
//////////////////////////////////////////////////////////////////////////////
// generated by Fast Light User Interface Designer (fluid) version 1.00

#include "cMapWindowUI.hh"
#include <iostream.h>
#include <Fl/fl_ask.h>
#include "vista_main.hh"
#include "map_mode_enum.hh"

inline void cMapWindowUI::cb_map_window_i(Fl_Double_Window*, void*) {
  vista_main->CloseMapWindow();
}
void cMapWindowUI::cb_map_window(Fl_Double_Window* o, void* v) {
  ((cMapWindowUI*)(o->user_data()))->cb_map_window_i(o,v);
}

inline void cMapWindowUI::cb_Close_i(Fl_Button*, void*) {
  vista_main->CloseMapWindow();
}
void cMapWindowUI::cb_Close(Fl_Button* o, void* v) {
  ((cMapWindowUI*)(o->parent()->user_data()))->cb_Close_i(o,v);
}

inline void cMapWindowUI::cb_zoom_slider_i(Fl_Value_Slider* o, void*) {
  legend->SetCellSize(((Fl_Slider*)o)->value() );
}
void cMapWindowUI::cb_zoom_slider(Fl_Value_Slider* o, void* v) {
  ((cMapWindowUI*)(o->parent()->user_data()))->cb_zoom_slider_i(o,v);
}

inline void cMapWindowUI::cb_Y_i(Fl_Roller* o, void*) {
  if(  ((Fl_Roller*)o)->value() >= 1 )
 ((Fl_Roller*)o)->value( ((Fl_Roller*)o)->value()-1 );
if(  ((Fl_Roller*)o)->value() < 0 )
 ((Fl_Roller*)o)->value( ((Fl_Roller*)o)->value()+1 );
grid->SetY0( ((Fl_Roller*)o)->value() *grid->GetRows() );
center_label->value(grid->GetOriginString());
}
void cMapWindowUI::cb_Y(Fl_Roller* o, void* v) {
  ((cMapWindowUI*)(o->parent()->parent()->user_data()))->cb_Y_i(o,v);
}

inline void cMapWindowUI::cb_X_i(Fl_Roller* o, void*) {
  if(  ((Fl_Roller*)o)->value() >= 1 )
 ((Fl_Roller*)o)->value( ((Fl_Roller*)o)->value()-1 );
if(  ((Fl_Roller*)o)->value() < 0 )
 ((Fl_Roller*)o)->value( ((Fl_Roller*)o)->value()+1 );
grid->SetX0( ((Fl_Roller*)o)->value() *grid->GetRows() );
center_label->value(grid->GetOriginString());
}
void cMapWindowUI::cb_X(Fl_Roller* o, void* v) {
  ((cMapWindowUI*)(o->parent()->parent()->user_data()))->cb_X_i(o,v);
}

inline void cMapWindowUI::cb_Threshold_i(Fl_Light_Button*, void*) {
  mode = MAP_MODE_THRESHOLD;
vista_main->SetupMap(MAP_MODE_THRESHOLD);
}
void cMapWindowUI::cb_Threshold(Fl_Light_Button* o, void* v) {
  ((cMapWindowUI*)(o->parent()->parent()->user_data()))->cb_Threshold_i(o,v);
}

inline void cMapWindowUI::cb_Birth_i(Fl_Light_Button*, void*) {
  mode = MAP_MODE_BIRTH;
vista_main->SetupMap(MAP_MODE_BIRTH);
}
void cMapWindowUI::cb_Birth(Fl_Light_Button* o, void* v) {
  ((cMapWindowUI*)(o->parent()->parent()->user_data()))->cb_Birth_i(o,v);
}

inline void cMapWindowUI::cb_Genotype_i(Fl_Light_Button*, void*) {
  mode = MAP_MODE_GENOTYPE;
vista_main->SetupMap(MAP_MODE_GENOTYPE);
}
void cMapWindowUI::cb_Genotype(Fl_Light_Button* o, void* v) {
  ((cMapWindowUI*)(o->parent()->parent()->user_data()))->cb_Genotype_i(o,v);
}

inline void cMapWindowUI::cb_pause_button_i(Fl_Light_Button*, void*) {
  vista_main->TogglePauseState();
}
void cMapWindowUI::cb_pause_button(Fl_Light_Button* o, void* v) {
  ((cMapWindowUI*)(o->parent()->user_data()))->cb_pause_button_i(o,v);
}

cMapWindowUI::cMapWindowUI(int x_size, int y_size) {
  Fl_Double_Window* w;
  mode = MAP_MODE_THRESHOLD;
  { Fl_Double_Window* o = map_window = new Fl_Double_Window(701, 498, "Map");
    w = o;
    o->callback((Fl_Callback*)cb_map_window, (void*)(this));
    { Fl_Button* o = new Fl_Button(525, 470, 70, 25, "&Close");
      o->callback((Fl_Callback*)cb_Close);
    }
    { Fl_Value_Slider* o = zoom_slider = new Fl_Value_Slider(150, 470, 230, 20, "Zoom");
      o->type(1);
      o->minimum(1);
      o->maximum(20);
      o->step(1);
      o->value(5);
      o->callback((Fl_Callback*)cb_zoom_slider);
      o->align(FL_ALIGN_LEFT);
    }
    { Fl_Group* o = pan_group = new Fl_Group(0, 220, 245, 225);
      o->align(FL_ALIGN_BOTTOM_LEFT|FL_ALIGN_INSIDE);
      { Fl_Roller* o = new Fl_Roller(10, 220, 20, 170, "Y");
        o->minimum(-0.9);
        o->maximum(1.9);
        o->step(0.005);
        o->callback((Fl_Callback*)cb_Y);
      }
      { Fl_Roller* o = new Fl_Roller(65, 415, 180, 20, "X");
        o->type(1);
        o->minimum(-0.9);
        o->maximum(1.9);
        o->step(0.005);
        o->callback((Fl_Callback*)cb_X);
        o->align(FL_ALIGN_LEFT);
      }
      { Fl_Output* o = center_label = new Fl_Output(5, 415, 40, 20);
        o->box(FL_FLAT_BOX);
        o->color(49);
        o->labeltype(FL_NO_LABEL);
      }
      o->end();
    }
    { Fl_Group* o = new Fl_Group(490, 20, 100, 100, "Mode");
      { Fl_Light_Button* o = new Fl_Light_Button(490, 20, 95, 25, "&Threshold");
        o->type(102);
        o->value(1);
        o->callback((Fl_Callback*)cb_Threshold);
      }
      { Fl_Light_Button* o = new Fl_Light_Button(490, 45, 95, 25, "&Birth");
        o->type(102);
        o->callback((Fl_Callback*)cb_Birth);
      }
      { Fl_Light_Button* o = new Fl_Light_Button(490, 70, 95, 25, "&Genotype");
        o->type(102);
        o->callback((Fl_Callback*)cb_Genotype);
      }
      o->end();
    }
    { Fl_Scroll* o = new Fl_Scroll(465, 130, 200, 280, "Legend");
      o->box(FL_ENGRAVED_BOX);
      { cLegend* o = legend = new cLegend(470, 135, 160, 270);
        o->labeltype(FL_NO_LABEL);
        o->align(FL_ALIGN_TOP);
      }
      o->end();
    }
    { Fl_Light_Button* o = pause_button = new Fl_Light_Button(5, 470, 70, 25, "&Pause");
      o->selection_color(1);
      o->callback((Fl_Callback*)cb_pause_button);
    }
    { Fl_Box* o = new Fl_Box(40, 5, 415, 405);
      o->box(FL_ENGRAVED_FRAME);
    }
    grid = new cGrid(40, 5, 415, 405);
    o->end();
  }
  grid->SetupSize(x_size, y_size, legend);
  pause_button->value(vista_main->GetPauseState());
  show();
}

void cMapWindowUI::show() {
  map_window->show();
  grid->show();
  legend->show();
}

cMapWindowUI::~cMapWindowUI() {
  map_window->hide();
  Fl::wait(0.025);
}
