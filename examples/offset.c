#include "clipper2c/clipper2c.h"
#include "clipper2c/types.h"
#include "malloc.h"
#include "stdio.h"

// define delta callback
double delta_calback(ClipperPath64 *path, ClipperPathD *path_normals,
                     size_t curr_idx, size_t prev_idx) {

  return 1.0 * (double)curr_idx;
}

int main() {
  ClipperPaths64 *solution = clipper_paths64(malloc(clipper_paths64_size()));
  ClipperPaths64 *subject = clipper_paths64(malloc(clipper_paths64_size()));

  // add path to subject
  ClipperPath64 *path = clipper_path64(malloc(clipper_path64_size()));
  const int64_t points[5][2] = {
      //      {100, 50}, {10, 79}, {65, 2}, {65, 98}, {10, 21}};
      {0, 0},
      {10, 0},
      {10, 10},
      {0, 10},
      {0, 0}};
  for (int i = 0; i < 5; i++) {
    ClipperPoint64 p = {points[i][0], points[i][1]};
    clipper_path64_add_point(path, p);
  }
  clipper_paths64_add_path(subject, path);

  ClipperClipperOffset *c = clipper_clipperoffset(
      malloc(clipper_clipperoffset_size()), 2.0, 0.25, 0, 0);
  clipper_clipperoffset_add_paths64(c, subject, MITER_JOIN, POLYGON_END);

  // example with constant delta
  //  clipper_clipperoffset_execute(solution, c, 10.0);

  // example with delta callback
  clipper_clipperoffset_execute_callback(solution, c, delta_calback);

  printf("Solution: %zu\n", clipper_paths64_length(solution));

  //  print result
  for (int i = 0; i < clipper_paths64_length(solution); i++) {
    size_t pathlen = clipper_paths64_path_length(solution, i);

    for (int pt_idx = 0; pt_idx < pathlen; pt_idx++) {
      ClipperPoint64 p = clipper_paths64_get_point(solution, i, pt_idx);
      printf("\t%ld %ld\n", p.x, p.y);
    }
  }

  return 0;
}