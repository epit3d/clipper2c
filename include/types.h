#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct ClipperClipper64 ClipperClipper64;
typedef struct ClipperClipperD ClipperClipperD;
typedef struct ClipperPath64 ClipperPath64;
typedef struct ClipperPathD ClipperPathD;
typedef struct ClipperPaths64 ClipperPaths64;
typedef struct ClipperPathsD ClipperPathsD;

typedef struct ClipperPointD {
  double x;
  double y;
} ClipperPointD;

typedef struct ClipperPoint64 {
  int64_t x;
  int64_t y;
} ClipperPoint64;

typedef enum ClipperFillRule {
  EVEN_ODD,
  NON_ZERO,
  POSITIVE,
  NEGATIVE
} ClipperFillRule;

typedef enum ClipperClipType {
  NONE,
  INTERSECTION,
  UNION,
  DIFFERENCE,
  XOR
} ClipperClipType;

typedef enum ClipperPathType { SUBJECT, CLIP } ClipperPathType;
