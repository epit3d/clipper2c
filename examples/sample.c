#include "clipper2c/clipper2c.h"
#include "clipper2c/types.h"
#include "malloc.h"
#include "stdio.h"

#ifndef USINGZ
#define USINGZ
#endif

// define custom z callback 64
ClipperPoint64 myZCB(ClipperPoint64 bot1, ClipperPoint64 top1,
                     ClipperPoint64 bot2, ClipperPoint64 top2,
                     ClipperPoint64 pt) {
  printf("myZCB: %ld %ld %ld %ld %ld\n", bot1.z, top1.z, bot2.z, top2.z, pt.z);

  pt.z = 1;

  return pt;
}

int main() {
  /*
   Paths64 subject, solution;
  MyClass mc;
  Clipper64 c64;

  subject.push_back(MakePath({ 100, 50, 10, 79, 65, 2, 65, 98, 10, 21 }));
  c64.AddSubject(subject);
  c64.SetZCallback(
   std::bind(&MyClass::myZCB, mc, std::placeholders::_1,
             std::placeholders::_2, std::placeholders::_3,
             std::placeholders::_4, std::placeholders::_5));
  c64.Execute(ClipType::Union, FillRule::NonZero, solution);
   */

  ClipperPaths64 *solution = clipper_paths64(malloc(clipper_paths64_size()));
  ClipperPaths64 *subject = clipper_paths64(malloc(clipper_paths64_size()));
  ClipperPaths64 *open = clipper_paths64(malloc(clipper_paths64_size()));

  // add path to subject
  ClipperPath64 *path = clipper_path64(malloc(clipper_path64_size()));
  const int64_t points[5][2] = {
      {100, 50}, {10, 79}, {65, 2}, {65, 98}, {10, 21}};
  for (int i = 0; i < 5; i++) {
    ClipperPoint64 p = {points[i][0], points[i][1]};
    clipper_path64_add_point(path, p);
  }
  clipper_paths64_add_path(subject, path);

  ClipperClipper64 *c64 = clipper_clipper64(malloc(clipper_clipper64_size()));
  clipper_clipper64_add_subject(c64, subject);
  clipper_clipper64_set_zcallback(c64, (ClipperZCallback64)myZCB);

  clipper_clipper64_execute(c64, UNION, NON_ZERO, solution, open);

  printf("Solution: %zu\n", clipper_paths64_length(solution));
  printf("Open: %zu\n", clipper_paths64_length(open));

  //  print result
  for (int i = 0; i < clipper_paths64_length(solution); i++) {
    size_t pathlen = clipper_paths64_path_length(solution, i);

    for (int pt_idx = 0; pt_idx < pathlen; pt_idx++) {
      ClipperPoint64 p = clipper_paths64_get_point(solution, i, pt_idx);
      printf("\t%ld %ld %ld\n", p.x, p.y, p.z);
    }
  }

  return 0;
}