#include <clipper2/clipper.h>

#include "../include/clipper2c/clipper2c.h"
#include "../include/clipper2c/types.h"
#include "clipper2/clipper.core.h"
#include "conv.h"
#include <stdint.h>

using namespace Clipper2Lib;

#ifdef __cplusplus
extern "C" {
#endif

// Constructors

ClipperClipperOffset *clipper_clipperoffset(void *mem, double miter_limit,
                                            double arc_tolerance,
                                            int preserve_collinear,
                                            int reverse_solution) {
  return to_c(new (mem) ClipperOffset(miter_limit, arc_tolerance,
                                      preserve_collinear, reverse_solution));
}

// Setters / Getters

void clipper_clipperoffset_set_miter_limit(ClipperClipperOffset *c, double l) {
  from_c(c)->MiterLimit(l);
}

void clipper_clipperoffset_set_arc_tolerance(ClipperClipperOffset *c,
                                             double t) {
  from_c(c)->ArcTolerance(t);
}

void clipper_clipperoffset_set_preserve_collinear(ClipperClipperOffset *c,
                                                  int t) {
  from_c(c)->PreserveCollinear(t);
}

void clipper_clipperoffset_set_reverse_solution(ClipperClipperOffset *c,
                                                int t) {
  from_c(c)->ReverseSolution(t);
}

double clipper_clipperoffset_get_miter_limit(ClipperClipperOffset *c) {
  return from_c(c)->MiterLimit();
}

double clipper_clipperoffset_get_arc_tolerance(ClipperClipperOffset *c) {
  return from_c(c)->ArcTolerance();
}

int clipper_clipperoffset_get_preserve_collinear(ClipperClipperOffset *c) {
  return from_c(c)->PreserveCollinear();
}

int clipper_clipperoffset_get_reverse_solution(ClipperClipperOffset *c) {
  return from_c(c)->ReverseSolution();
}

int clipper_clipperoffset_error_code(ClipperClipperOffset *c) {
  return from_c(c)->ErrorCode();
}

void clipper_clipperoffset_clear(ClipperClipperOffset *c) {
  from_c(c)->Clear();
}

// Methods

void clipper_clipperoffset_add_path64(ClipperClipperOffset *c, ClipperPath64 *p,
                                      ClipperJoinType jt, ClipperEndType et) {
  from_c(c)->AddPath(*from_c(p), from_c(jt), from_c(et));
}

void clipper_clipperoffset_add_paths64(ClipperClipperOffset *c,
                                       ClipperPaths64 *p, ClipperJoinType jt,
                                       ClipperEndType et) {
  from_c(c)->AddPaths(*from_c(p), from_c(jt), from_c(et));
}

ClipperPaths64 *clipper_clipperoffset_execute(void *mem,
                                              ClipperClipperOffset *c,
                                              double delta) {
  auto result = new (mem) Paths64();
  from_c(c)->Execute(delta, *result);
  return to_c(result);
}

ClipperPaths64 *
clipper_clipperoffset_execute_callback(void *mem, ClipperClipperOffset *c,
                                       ClipperDeltaCallback64 cb) {
  auto result = new (mem) Paths64();
  from_c(c)->Execute(from_c(cb), *result);
  return to_c(result);
}

#ifdef GO_BINDINGS

ClipperPaths64 *
clipper_clipperoffset_execute_gocallback(void *mem, ClipperClipperOffset *c,
                                         ClipperDeltaGoCallback64 cb) {

  auto result = new (mem) Paths64();
  from_c(c)->Execute(from_c(c->handle, cb), *result);
  return to_c(result);
}

#endif

#ifdef __cplusplus
}
#endif
