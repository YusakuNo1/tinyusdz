// SPDX-License-Identifier: Apache 2.0
// Copyright 2022-Present Light Transport Entertainment Inc.

#include "c-tinyusd.h"

#include "tinyusdz.hh"
#include "tydra/scene-access.hh"
#include "usdLux.hh"
#include "prim-pprint.hh"
#include "value-pprint.hh"
#include "common-macros.inc"

// TODO:
// - [ ] Implement our own `strlen`

const char *c_tinyusd_value_type_name(CTinyUSDValueType value_type) {
  // 32 should be enough length to support all C_TINYUSD_VALUE_* type name +
  // '[]'
  static thread_local char buf[32];

  bool is_array = value_type & C_TINYUSD_VALUE_1D_BIT;

  // drop array bit.
  uint32_t basety = value_type & (~C_TINYUSD_VALUE_1D_BIT);

  const char *tyname = "[invalid]";

  switch (static_cast<CTinyUSDValueType>(basety)) {
    case C_TINYUSD_VALUE_BOOL: {
      tyname = "bool";
      break;
    }
    case C_TINYUSD_VALUE_TOKEN: {
      tyname = "token";
      break;
    }
    case C_TINYUSD_VALUE_STRING: {
      tyname = "string";
      break;
    }
    case C_TINYUSD_VALUE_HALF: {
      tyname = "half";
      break;
    }
    case C_TINYUSD_VALUE_HALF2: {
      tyname = "half2";
      break;
    }
    case C_TINYUSD_VALUE_HALF3: {
      tyname = "half3";
      break;
    }
    case C_TINYUSD_VALUE_HALF4: {
      tyname = "half4";
      break;
    }
    case C_TINYUSD_VALUE_INT: {
      tyname = "int";
      break;
    }
    case C_TINYUSD_VALUE_INT2: {
      tyname = "int2";
      break;
    }
    case C_TINYUSD_VALUE_INT3: {
      tyname = "int3";
      break;
    }
    case C_TINYUSD_VALUE_INT4: {
      tyname = "int4";
      break;
    }
    case C_TINYUSD_VALUE_UINT: {
      tyname = "uint";
      break;
    }
    case C_TINYUSD_VALUE_UINT2: {
      tyname = "uint2";
      break;
    }
    case C_TINYUSD_VALUE_UINT3: {
      tyname = "uint3";
      break;
    }
    case C_TINYUSD_VALUE_UINT4: {
      tyname = "uint4";
      break;
    }
    case C_TINYUSD_VALUE_INT64: {
      tyname = "int64";
      break;
    }
    case C_TINYUSD_VALUE_UINT64: {
      tyname = "uint64";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT: {
      tyname = "float";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT2: {
      tyname = "float2";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT3: {
      tyname = "float3";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT4: {
      tyname = "float4";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE: {
      tyname = "double";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE2: {
      tyname = "double2";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE3: {
      tyname = "double3";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE4: {
      tyname = "double4";
      break;
    }
    case C_TINYUSD_VALUE_QUATH: {
      tyname = "quath";
      break;
    }
    case C_TINYUSD_VALUE_QUATF: {
      tyname = "quatf";
      break;
    }
    case C_TINYUSD_VALUE_QUATD: {
      tyname = "quatd";
      break;
    }
    case C_TINYUSD_VALUE_NORMAL3H: {
      tyname = "normal3h";
      break;
    }
    case C_TINYUSD_VALUE_NORMAL3F: {
      tyname = "normal3f";
      break;
    }
    case C_TINYUSD_VALUE_NORMAL3D: {
      tyname = "normal3d";
      break;
    }
    case C_TINYUSD_VALUE_VECTOR3H: {
      tyname = "vector3h";
      break;
    }
    case C_TINYUSD_VALUE_VECTOR3F: {
      tyname = "vector3f";
      break;
    }
    case C_TINYUSD_VALUE_VECTOR3D: {
      tyname = "vector3d";
      break;
    }
    case C_TINYUSD_VALUE_POINT3H: {
      tyname = "point3h";
      break;
    }
    case C_TINYUSD_VALUE_POINT3F: {
      tyname = "point3f";
      break;
    }
    case C_TINYUSD_VALUE_POINT3D: {
      tyname = "point3d";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD2H: {
      tyname = "texCoord2h";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD2F: {
      tyname = "texCoord2f";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD2D: {
      tyname = "texCoord2d";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD3H: {
      tyname = "texCoord3h";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD3F: {
      tyname = "texCoord3f";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD3D: {
      tyname = "texCoord3d";
      break;
    }
    case C_TINYUSD_VALUE_COLOR3H: {
      tyname = "color3h";
      break;
    }
    case C_TINYUSD_VALUE_COLOR3F: {
      tyname = "color3f";
      break;
    }
    case C_TINYUSD_VALUE_COLOR3D: {
      tyname = "color3d";
      break;
    }
    case C_TINYUSD_VALUE_COLOR4H: {
      tyname = "color4h";
      break;
    }
    case C_TINYUSD_VALUE_COLOR4F: {
      tyname = "color4f";
      break;
    }
    case C_TINYUSD_VALUE_COLOR4D: {
      tyname = "color4d";
      break;
    }
    case C_TINYUSD_VALUE_MATRIX2D: {
      tyname = "matrix2d";
      break;
    }
    case C_TINYUSD_VALUE_MATRIX3D: {
      tyname = "matrix2d";
      break;
    }
    case C_TINYUSD_VALUE_MATRIX4D: {
      tyname = "matrix2d";
      break;
    }
    case C_TINYUSD_VALUE_FRAME4D: {
      tyname = "frame4d";
      break;
    }
    case C_TINYUSD_VALUE_END: {
      tyname = "[invalid]";
      break;
    }  // invalid
       // default: { return 0; }
  }

  uint32_t sz = static_cast<uint32_t>(strlen(tyname));

  if (sz > 31) {
    // Just in case: this should not happen though.
    sz = 31;
  }

  strncpy(buf, tyname, sz);

  if (is_array) {
    if (sz > 29) {
      // Just in case: this should not happen though.
      sz = 29;
    }

    buf[sz] = '[';
    buf[sz + 1] = ']';
    buf[sz + 2] = '\0';
  } else {
    buf[sz] = '\0';
  }

  return buf;
}

uint32_t c_tinyusd_value_type_components(CTinyUSDValueType value_type) {
  // drop array bit.
  uint32_t basety = value_type & (~C_TINYUSD_VALUE_1D_BIT);

  switch (static_cast<CTinyUSDValueType>(basety)) {
    case C_TINYUSD_VALUE_BOOL: {
      return 1;
    }
    case C_TINYUSD_VALUE_TOKEN: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_STRING: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_HALF: {
      return 1;
    }
    case C_TINYUSD_VALUE_HALF2: {
      return 2;
    }
    case C_TINYUSD_VALUE_HALF3: {
      return 3;
    }
    case C_TINYUSD_VALUE_HALF4: {
      return 4;
    }
    case C_TINYUSD_VALUE_INT: {
      return 1;
    }
    case C_TINYUSD_VALUE_INT2: {
      return 2;
    }
    case C_TINYUSD_VALUE_INT3: {
      return 3;
    }
    case C_TINYUSD_VALUE_INT4: {
      return 4;
    }
    case C_TINYUSD_VALUE_UINT: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT2: {
      return 2;
    }
    case C_TINYUSD_VALUE_UINT3: {
      return 3;
    }
    case C_TINYUSD_VALUE_UINT4: {
      return 4;
    }
    case C_TINYUSD_VALUE_INT64: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT64: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT2: {
      return 2;
    }
    case C_TINYUSD_VALUE_FLOAT3: {
      return 3;
    }
    case C_TINYUSD_VALUE_FLOAT4: {
      return 4;
    }
    case C_TINYUSD_VALUE_DOUBLE: {
      return 1;
    }
    case C_TINYUSD_VALUE_DOUBLE2: {
      return 2;
    }
    case C_TINYUSD_VALUE_DOUBLE3: {
      return 3;
    }
    case C_TINYUSD_VALUE_DOUBLE4: {
      return 4;
    }
    case C_TINYUSD_VALUE_QUATH: {
      return 4;
    }
    case C_TINYUSD_VALUE_QUATF: {
      return 4;
    }
    case C_TINYUSD_VALUE_QUATD: {
      return 4;
    }
    case C_TINYUSD_VALUE_NORMAL3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_NORMAL3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_NORMAL3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_VECTOR3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_VECTOR3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_VECTOR3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_POINT3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_POINT3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_POINT3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD2H: {
      return 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2F: {
      return 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2D: {
      return 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR4H: {
      return 4;
    }
    case C_TINYUSD_VALUE_COLOR4F: {
      return 4;
    }
    case C_TINYUSD_VALUE_COLOR4D: {
      return 4;
    }
    case C_TINYUSD_VALUE_MATRIX2D: {
      return 2 * 2;
    }
    case C_TINYUSD_VALUE_MATRIX3D: {
      return 3 * 3;
    }
    case C_TINYUSD_VALUE_MATRIX4D: {
      return 4 * 4;
    }
    case C_TINYUSD_VALUE_FRAME4D: {
      return 4 * 4;
    }
    case C_TINYUSD_VALUE_END: {
      return 0;
    }  // invalid
       // default: { return 0; }
  }

  return 0;
}

uint32_t c_tinyusd_value_type_sizeof(CTinyUSDValueType value_type) {
  // drop array bit.
  uint32_t basety = value_type & (~C_TINYUSD_VALUE_1D_BIT);

  switch (static_cast<CTinyUSDValueType>(basety)) {
    case C_TINYUSD_VALUE_BOOL: {
      return 1;
    }
    case C_TINYUSD_VALUE_TOKEN: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_STRING: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_HALF: {
      return sizeof(uint16_t);
    }
    case C_TINYUSD_VALUE_HALF2: {
      return sizeof(uint16_t) * 2;
    }
    case C_TINYUSD_VALUE_HALF3: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_HALF4: {
      return sizeof(uint16_t) * 4;
    }
    case C_TINYUSD_VALUE_INT: {
      return sizeof(int);
    }
    case C_TINYUSD_VALUE_INT2: {
      return sizeof(int) * 2;
    }
    case C_TINYUSD_VALUE_INT3: {
      return sizeof(int) * 3;
    }
    case C_TINYUSD_VALUE_INT4: {
      return sizeof(int) * 4;
    }
    case C_TINYUSD_VALUE_UINT: {
      return sizeof(uint32_t);
    }
    case C_TINYUSD_VALUE_UINT2: {
      return sizeof(uint32_t) * 2;
    }
    case C_TINYUSD_VALUE_UINT3: {
      return sizeof(uint32_t) * 3;
    }
    case C_TINYUSD_VALUE_UINT4: {
      return sizeof(uint32_t) * 4;
    }
    case C_TINYUSD_VALUE_INT64: {
      return sizeof(int64_t);
    }
    case C_TINYUSD_VALUE_UINT64: {
      return sizeof(uint64_t);
    }
    case C_TINYUSD_VALUE_FLOAT: {
      return sizeof(float);
    }
    case C_TINYUSD_VALUE_FLOAT2: {
      return sizeof(float) * 2;
    }
    case C_TINYUSD_VALUE_FLOAT3: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_FLOAT4: {
      return sizeof(float) * 4;
    }
    case C_TINYUSD_VALUE_DOUBLE: {
      return sizeof(double);
    }
    case C_TINYUSD_VALUE_DOUBLE2: {
      return sizeof(double) * 2;
    }
    case C_TINYUSD_VALUE_DOUBLE3: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_DOUBLE4: {
      return sizeof(double) * 4;
    }
    case C_TINYUSD_VALUE_QUATH: {
      return sizeof(uint16_t) * 4;
    }
    case C_TINYUSD_VALUE_QUATF: {
      return sizeof(float) * 4;
    }
    case C_TINYUSD_VALUE_QUATD: {
      return sizeof(double) * 4;
    }
    case C_TINYUSD_VALUE_NORMAL3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_NORMAL3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_NORMAL3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_VECTOR3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_VECTOR3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_VECTOR3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_POINT3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_POINT3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_POINT3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD2H: {
      return sizeof(uint16_t) * 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2F: {
      return sizeof(float) * 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2D: {
      return sizeof(double) * 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_COLOR3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_COLOR3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_COLOR3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_COLOR4H: {
      return sizeof(uint16_t) * 4;
    }
    case C_TINYUSD_VALUE_COLOR4F: {
      return sizeof(float) * 4;
    }
    case C_TINYUSD_VALUE_COLOR4D: {
      return sizeof(double) * 4;
    }
    case C_TINYUSD_VALUE_MATRIX2D: {
      return sizeof(double) * 2 * 2;
    }
    case C_TINYUSD_VALUE_MATRIX3D: {
      return sizeof(double) * 3 * 3;
    }
    case C_TINYUSD_VALUE_MATRIX4D: {
      return sizeof(double) * 4 * 4;
    }
    case C_TINYUSD_VALUE_FRAME4D: {
      return sizeof(double) * 4 * 4;
    }
    case C_TINYUSD_VALUE_END: {
      return 0;
    }  // invalid
       // default: { return 0; }
  }

  return 0;
}

CTinyUSDFormat c_tinyusd_detect_format(const char *filename) {
  if (tinyusdz::IsUSDA(filename)) {
    return C_TINYUSD_FORMAT_USDA;
  }

  if (tinyusdz::IsUSDC(filename)) {
    return C_TINYUSD_FORMAT_USDC;
  }

  if (tinyusdz::IsUSDZ(filename)) {
    return C_TINYUSD_FORMAT_USDZ;
  }

  return C_TINYUSD_FORMAT_UNKNOWN;
}

const char *c_tinyusd_prim_type_name(CTinyUSDPrimType prim_type) {
  // 32 should be enough length to support all C_TINYUSD_PRIM_*** type
  static thread_local char buf[32];

  const char *tyname = "";

  switch (prim_type) {
    case C_TINYUSD_PRIM_UNKNOWN: {
      return nullptr;
    }
    case C_TINYUSD_PRIM_MODEL: {
      tyname = "";
      break;
    }  // empty string for Model
    case C_TINYUSD_PRIM_XFORM: {
      tyname = tinyusdz::kGeomXform;
      break;
    }
    case C_TINYUSD_PRIM_MESH: {
      tyname = tinyusdz::kGeomMesh;
      break;
    }
    case C_TINYUSD_PRIM_GEOMSUBSET: {
      tyname = tinyusdz::kGeomSubset;
      break;
    }
    case C_TINYUSD_PRIM_MATERIAL: {
      tyname = tinyusdz::kMaterial;
      break;
    }
    case C_TINYUSD_PRIM_SHADER: {
      tyname = tinyusdz::kShader;
      break;
    }
    case C_TINYUSD_PRIM_CAMERA: {
      tyname = tinyusdz::kGeomCamera;
      break;
    }
    case C_TINYUSD_PRIM_SPHERE_LIGHT: {
      tyname = tinyusdz::kSphereLight;
      break;
    }
    case C_TINYUSD_PRIM_DISTANT_LIGHT: {
      tyname = tinyusdz::kDistantLight;
      break;
    }
    case C_TINYUSD_PRIM_RECT_LIGHT: {
      tyname = tinyusdz::kRectLight;
      break;
    }
    case C_TINYUSD_PRIM_END: {
      return nullptr;
    }
  }

  size_t sz = strlen(tyname);
  if (sz > 31) {
    // Just in case: this should not happen though.
    sz = 31;
  }
  strncpy(buf, tyname, sz);
  buf[sz] = '\0';

  return buf;
}

CTinyUSDPrimType c_tinyusd_prim_type_from_string(const char *c_type_name) {
  std::string type_name(c_type_name);

  if (type_name == "Model") {
    return C_TINYUSD_PRIM_MODEL;
  } else if (type_name == tinyusdz::kGeomXform) {
    return C_TINYUSD_PRIM_XFORM;
  } else if (type_name == tinyusdz::kGeomMesh) {
    return C_TINYUSD_PRIM_MESH;
  } else if (type_name == tinyusdz::kGeomSubset) {
    return C_TINYUSD_PRIM_GEOMSUBSET;
  } else if (type_name == tinyusdz::kGeomCamera) {
    return C_TINYUSD_PRIM_CAMERA;
  } else if (type_name == tinyusdz::kMaterial) {
    return C_TINYUSD_PRIM_MATERIAL;
  } else if (type_name == tinyusdz::kShader) {
    return C_TINYUSD_PRIM_SHADER;
  } else if (type_name == tinyusdz::kSphereLight) {
    return C_TINYUSD_PRIM_SPHERE_LIGHT;
  } else if (type_name == tinyusdz::kDistantLight) {
    return C_TINYUSD_PRIM_DISTANT_LIGHT;
  } else if (type_name == tinyusdz::kRectLight) {
    return C_TINYUSD_PRIM_RECT_LIGHT;
  } else {
    return C_TINYUSD_PRIM_UNKNOWN;
  }
}

int c_tinyusd_token_new(c_tinyusd_token *tok, const char *str) {
  if (!tok) {
    return 0;
  }

  auto *value = new tinyusdz::value::token(str);

  tok->data = reinterpret_cast<void *>(value);

  return 1;  // ok
}

int c_tinyusd_token_free(c_tinyusd_token *tok) {
  if (!tok) {
    return 0;
  }

  if (tok->data) {
    auto *p = reinterpret_cast<tinyusdz::value::token *>(tok->data);
    delete p;
    tok->data = nullptr;
  }

  return 1;  // ok
}

const char *c_tinyusd_token_str(const c_tinyusd_token *tok) {
  if (!tok) {
    return nullptr;
  }

  if (tok->data) {
    auto *p = reinterpret_cast<tinyusdz::value::token *>(tok->data);
    return p->str().c_str();
  }

  return nullptr;
}

size_t c_tinyusd_token_size(const c_tinyusd_token *tok) {
  if (!tok) {
    return 0;
  }

  if (!tok->data) {
    return 0;
  }

  auto *p = reinterpret_cast<tinyusdz::value::token *>(tok->data);

  return p->str().size();
}

int c_tinyusd_string_new_empty(c_tinyusd_string *s) {
  if (!s) {
    return 0;
  }

  auto *value = new std::string();
  s->data = reinterpret_cast<void *>(value);

  return 1;  // ok
}

int c_tinyusd_string_new(c_tinyusd_string *s, const char *str) {
  if (!s) {
    return 0;
  }

  if (str) {
    auto *value = new std::string(str);
    s->data = reinterpret_cast<void *>(value);
  } else {
    auto *value = new std::string();
    s->data = reinterpret_cast<void *>(value);
  }

  return 1;  // ok
}

size_t c_tinyusd_string_size(const c_tinyusd_string *s) {
  if (!s) {
    return 0;
  }

  if (!s->data) {
    return 0;
  }

  auto *p = reinterpret_cast<const std::string *>(s->data);

  return p->size();
}

int c_tinyusd_string_replace(c_tinyusd_string *s, const char *str) {
  if (!s) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  if (!s->data) {
    return 0;
  }

  std::string *p = reinterpret_cast<std::string *>(s->data);
  (*p) = std::string(str);

  return 1;  // ok
}

int c_tinyusd_string_free(c_tinyusd_string *s) {
  if (!s) {
    return 0;
  }

  if (s->data) {
    auto *p = reinterpret_cast<std::string *>(s->data);
    delete p;
    s->data = nullptr;
  }

  return 1;  // ok
}

const char *c_tinyusd_string_str(const c_tinyusd_string *s) {
  if (!s) {
    return nullptr;
  }

  if (s->data) {
    auto *p = reinterpret_cast<const std::string *>(s->data);
    return p->c_str();
  }

  return nullptr;
}

int c_tinyusd_buffer_new(CTinyUSDBuffer *buf, CTinyUSDValueType value_type) {
  if (!buf) {
    return 0;
  }

  uint32_t sz = c_tinyusd_value_type_sizeof(value_type);
  if (sz == 0) {
    return 0;
  }

  buf->value_type = value_type;
  buf->ndim = 0;

  //uint8_t *m = new uint8_t[sz];
  //buf->data = reinterpret_cast<void *>(m);
  tinyusdz::value::Value *vp = new tinyusdz::value::Value(); // new `null` Value at the moment 
  buf->data = reinterpret_cast<void *>(vp);

  return 1;  // ok
}

int c_tinyusd_buffer_new_and_copy_token(CTinyUSDBuffer *buf, const c_tinyusd_token *tok) {
  if (!buf) {
    return 0;
  }

  if (!tok) {
    return 0;
  }

  size_t sz = c_tinyusd_token_size(tok);

  buf->value_type = C_TINYUSD_VALUE_TOKEN;
  buf->ndim = 0;

  if (sz == 0) {
    // Allow null string 
    buf->data = nullptr;
  } else {

    const char *str = c_tinyusd_token_str(tok);
    if (strlen(str) != sz) {
      // ???
      return false;
    }

    if (str) {
      uint8_t *m = new uint8_t[sz];

      memcpy(m, str, sz);
      buf->data = reinterpret_cast<void *>(m);
    } else {
      // ???
      return 0;
    }
  }

  return 1;  // ok
}

int c_tinyusd_buffer_new_and_copy_string(CTinyUSDBuffer *buf, const c_tinyusd_string *str) {
  if (!buf) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  size_t sz = c_tinyusd_string_size(str);

  buf->value_type = C_TINYUSD_VALUE_STRING;
  buf->ndim = 0;

  if (sz == 0) {
    // Allow null string 
    buf->data = nullptr;
  } else {

    const char *s = c_tinyusd_string_str(str);
    if (strlen(s) != sz) {
      // ???
      return false;
    }

    if (s) {
      uint8_t *m = new uint8_t[sz];

      memcpy(m, s, sz);
      buf->data = reinterpret_cast<void *>(m);
    } else {
      // ???
      return 0;
    }
  }

  return 1;  // ok
}

int c_tinyusd_buffer_new_array(CTinyUSDBuffer *buf,
                               CTinyUSDValueType value_type, uint64_t n) {
  if (!buf) {
    return 0;
  }

  uint32_t sz = c_tinyusd_value_type_sizeof(value_type);
  if (sz == 0) {
    return 0;
  }

  buf->value_type = value_type;
  buf->ndim = 1;
  buf->shape[0] = n;

  if (n == 0) {
    // empty array
    buf->data = nullptr;
  } else {
    uint8_t *m = new uint8_t[n * sz];
    buf->data = reinterpret_cast<void *>(m);
  }

  return 1;  // ok
}

int c_tinyusd_buffer_free(CTinyUSDBuffer *buf) {
  if (!buf) {
    return 0;
  }

  if (!buf->data) {
    return 0;
  }

  uint8_t *p = reinterpret_cast<uint8_t *>(buf->data);
  delete[] p;

  buf->data = nullptr;

  return 1;
}

int c_tinyusd_is_usda_file(const char *filename) {
  if (tinyusdz::IsUSDA(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_is_usdc_file(const char *filename) {
  if (tinyusdz::IsUSDC(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_is_usdz_file(const char *filename) {
  if (tinyusdz::IsUSDZ(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_is_usd_file(const char *filename) {
  if (tinyusdz::IsUSD(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_load_usd_from_file(const char *filename, CTinyUSDStage *stage,
                                 c_tinyusd_string *warn,
                                 c_tinyusd_string *err) {
  // tinyusdz::Stage *p = new tinyusdz::Stage();

  if (!stage) {
    if (err) {
      c_tinyusd_string_replace(err, "`stage` argument is null.\n");
    }
    return 0;
  }

  if (!stage->data) {
    if (err) {
      c_tinyusd_string_replace(
          err, "`stage` object is not initialized or new'ed.\n");
    }
    return 0;
  }

  std::string _warn;
  std::string _err;

  bool ret = tinyusdz::LoadUSDFromFile(
      filename, reinterpret_cast<tinyusdz::Stage *>(stage->data), &_warn,
      &_err);

  if (_warn.size() && warn) {
    c_tinyusd_string_replace(warn, _warn.c_str());
  }

  if (!ret) {
    if (err) {
      c_tinyusd_string_replace(err, _err.c_str());
    }

    return 0;
  }

  return 1;
}

namespace {

using namespace tinyusdz;

bool CVisitPrimFunction(const Path &abs_path, const Prim &prim,
                        const int32_t tree_depth, void *userdata,
                        std::string *err) {
  (void)tree_depth;

  if (!userdata) {
    if (err) {
      (*err) += "`userdata` is nullptr.\n";
    }
    return false;
  }

  CTinyUSDPrim cprim;
  cprim.data = reinterpret_cast<void *>(const_cast<Prim *>(&prim));

  CTinyUSDPath cpath;
  cpath.data = reinterpret_cast<void *>(const_cast<Path *>(&abs_path));

  CTinyUSDTraversalFunction callback_fun =
      reinterpret_cast<CTinyUSDTraversalFunction>(userdata);

  int ret = callback_fun(&cprim, &cpath);

  if (ret) {
    return true;
  }

  return false;
}

}  // namespace

int c_tinyusd_prim_new(const char *_prim_type, CTinyUSDPrim *prim) {
  if (!prim) {
    return 0;
  }

  if (!_prim_type) {
    return 0;
  }

  bool non_builtin_prim_type{false};

  CTinyUSDPrimType prim_type = c_tinyusd_prim_type_from_string(_prim_type);
  if (prim_type == C_TINYUSD_PRIM_UNKNOWN) {
    // Use `Model`
    prim_type = C_TINYUSD_PRIM_MODEL;
    non_builtin_prim_type = true;
  }

  Prim *p{nullptr};

#define NEW_PRIM(__cty, __ty) \
  if (prim_type == __cty) {   \
    __ty content;             \
    p = new Prim(content);    \
  } else

  if (non_builtin_prim_type) {
    p->prim_type_name() = _prim_type;
  }

  NEW_PRIM(C_TINYUSD_PRIM_XFORM, Xform)
  NEW_PRIM(C_TINYUSD_PRIM_MESH, GeomMesh)
  NEW_PRIM(C_TINYUSD_PRIM_GEOMSUBSET, GeomSubset)
  NEW_PRIM(C_TINYUSD_PRIM_MATERIAL, Material)
  NEW_PRIM(C_TINYUSD_PRIM_SHADER, Shader)
  // TODO: More types.
  {
    // ???
    return 0;
  }

#undef NEW_PRIM

  prim->data = reinterpret_cast<void *>(p);

  return 1;
}

int c_tinyusd_prim_new_builtin(CTinyUSDPrimType prim_type, CTinyUSDPrim *prim) {
  if (!prim) {
    return 0;
  }

  const char *prim_type_name = c_tinyusd_prim_type_name(prim_type);
  if (!prim_type_name) {
    return 0;
  }

  return c_tinyusd_prim_new(prim_type_name, prim);
}

int c_tinyusd_prim_free(CTinyUSDPrim *prim) {
  if (!prim) {
    return 0;
  }

  if (!prim->data) {
    return 0;
  }

  Prim *p = reinterpret_cast<Prim *>(prim->data);
  delete p;
  prim->data = nullptr;

  return 1;
}

uint64_t c_tinyusd_prim_num_children(const CTinyUSDPrim *prim) {
  if (!prim) {
    return 0;
  }

  if (!prim->data) {
    return 0;
  }

  const Prim *p = reinterpret_cast<const Prim *>(prim->data);
  return uint64_t(p->children().size());
}

int c_tinyusd_prim_get_child(const CTinyUSDPrim *prim, uint32_t child_idx,
                             CTinyUSDPrim **child) {
  if (!prim) {
    return 0;
  }

  if (!prim->data) {
    return 0;
  }

  if (!child) {
    return 0;
  }

  const Prim *p = reinterpret_cast<const Prim *>(prim->data);
  if (child_idx >= p->children().size()) {
    return 0;
  }

  // Use pointer address.
  const Prim *child_ptr = &(p->children()[child_idx]);

  (*child)->data = reinterpret_cast<void *>(const_cast<Prim *>(child_ptr));

  return 0;
}

int c_tinyusd_prim_to_string(const CTinyUSDPrim *prim, c_tinyusd_string *str) {
  if (!prim) {
    return 0;
  }

  if (!prim->data) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  if (!str->data) {
    return 0;
  }

  const Prim *p = reinterpret_cast<const Prim *>(prim->data);

  std::string s = tinyusdz::to_string(*p);

  if (!c_tinyusd_string_replace(str, s.c_str())) {
    return 0;
  }

  return 1;
}

int c_tinyusd_stage_new(CTinyUSDStage *stage) {
  if (!stage) {
    return 0;
  }

  auto *buf = new tinyusdz::Stage();
  stage->data = reinterpret_cast<void *>(buf);

  return 1;
}

int c_tinyusd_stage_to_string(const CTinyUSDStage *stage,
                              c_tinyusd_string *str) {
  if (!stage) {
    return 0;
  }

  if (!stage->data) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  if (!str->data) {
    return 0;
  }

  const auto *p = reinterpret_cast<const tinyusdz::Stage *>(stage->data);
  std::string s = p->ExportToString();

  return c_tinyusd_string_replace(str, s.c_str());
}

int c_tinyusd_stage_free(CTinyUSDStage *stage) {
  if (!stage) {
    return 0;
  }

  tinyusdz::Stage *ptr = reinterpret_cast<tinyusdz::Stage *>(stage->data);
  delete ptr;

  return 1;
}

int c_tinyusd_stage_traverse(const CTinyUSDStage *_stage,
                             CTinyUSDTraversalFunction callback_fun,
                             c_tinyusd_string *_err) {
  if (!_stage) {
    if (_err) {
      c_tinyusd_string_replace(_err, "`stage` argument is null.\n");
    }
    return 0;
  }

  if (!_stage->data) {
    if (_err) {
      c_tinyusd_string_replace(_err, "`stage.data` is null.\n");
    }
    return 0;
  }

  const tinyusdz::Stage *pstage =
      reinterpret_cast<const tinyusdz::Stage *>(_stage);

  std::string err;
  if (!tinyusdz::tydra::VisitPrims(*pstage, CVisitPrimFunction,
                                   reinterpret_cast<void *>(callback_fun),
                                   &err)) {
    if (_err) {
      c_tinyusd_string_replace(_err, err.c_str());
    }
  }

  return 1;
}

int c_tinyusd_attribute_value_new_token(CTinyUSDAttributeValue *aval, const c_tinyusd_token *tok) {
  if (!aval) { 
    return 0;
  }

  CTinyUSDBuffer buf;
  if (!c_tinyusd_buffer_new_and_copy_token(&buf, tok)) {
    return 0;
  }

  return 1;
}

int c_tinyusd_attribute_value_new_string(CTinyUSDAttributeValue *aval, const c_tinyusd_string *str) {
  if (!aval) { 
    return 0;
  }

  CTinyUSDBuffer buf;
  if (!c_tinyusd_buffer_new_and_copy_string(&buf, str)) {
    return 0;
  }

  return 1;
}

#define ATTRIB_VALUE_IMPL(__tyname, __cppty, __cty, __tyenum) \
int c_tinyusd_attribute_value_new_##__tyname(CTinyUSDAttributeValue *aval, __cty val) { \
  /* ensure C++ and C types has same size. */ \
  static_assert(sizeof(__cppty) == sizeof(__cty), ""); \
  if (!aval) { \
    return 0; \
  } \
  CTinyUSDBuffer buf; \
  if (!c_tinyusd_buffer_new(&buf, __tyenum)) { \
    return 0; \
  } \
  tinyusdz::value::Value *vp = reinterpret_cast<tinyusdz::value::Value *>(buf.data); \
  __cppty cppval; \
  memcpy(&cppval, &val, sizeof(__cty)); \
  (*vp) = cppval; \
  aval->buffer = buf; \
  return 1; \
}

ATTRIB_VALUE_IMPL(int, int, int, C_TINYUSD_VALUE_INT)
ATTRIB_VALUE_IMPL(int2, value::int2, c_tinyusd_int2, C_TINYUSD_VALUE_INT2)
ATTRIB_VALUE_IMPL(int3, value::int3, c_tinyusd_int3, C_TINYUSD_VALUE_INT3)
ATTRIB_VALUE_IMPL(int4, value::int4, c_tinyusd_int4, C_TINYUSD_VALUE_INT4)

ATTRIB_VALUE_IMPL(float, float, float, C_TINYUSD_VALUE_FLOAT)
ATTRIB_VALUE_IMPL(float2, value::float2, c_tinyusd_float2, C_TINYUSD_VALUE_FLOAT2)
ATTRIB_VALUE_IMPL(float3, value::float3, c_tinyusd_float3, C_TINYUSD_VALUE_FLOAT3)
ATTRIB_VALUE_IMPL(float4, value::float4, c_tinyusd_float4, C_TINYUSD_VALUE_FLOAT4)

#undef ATTRIB_VALUE_IMPL

int c_tinyusd_attribute_value_to_string(const CTinyUSDAttributeValue *aval, c_tinyusd_string *str) {
  if (!aval) {
    return 0;
  }

  if (!aval->buffer.data) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  if (!str->data) {
    return 0;
  }

  // TODO: Check if Value's type == buffer.value_type 
  const tinyusdz::value::Value *cp = reinterpret_cast<const tinyusdz::value::Value *>(aval->buffer.data);
  
  std::string s = tinyusdz::value::pprint_value(*cp, /* indent */0, /* closing_brace */false);

  if (!c_tinyusd_string_replace(str, s.c_str())) {
    return 0;
  }
  
  return 1;
}

int c_tinyusd_prim_get_property_names(const CTinyUSDPrim *prim, uint32_t *n_out, char ***prop_names_out) {
  if (!prim) {
    return 0;
  }

  if (!prim->data) {
    return 0;
  }

  if (!n_out) {
    return 0;
  }

  if (!prop_names_out) {
    return 0;
  }

  const Prim *p = reinterpret_cast<const Prim *>(prim->data);
  std::vector<std::string> ps;
  std::string err;
  if (!tydra::GetPropertyNames(*p, &ps, &err)) {
    // err is suppressed.
    return 0;
  }

  char **cp = reinterpret_cast<char **>(malloc(sizeof(char *) * ps.size()));
  if (!cp) {
    return 0;
  }

  if (ps.size() == 0) {
    (*n_out) = 0;
    (*prop_names_out) = nullptr;
    return 1;
  } 

  (*n_out) = uint32_t(ps.size());

  for (size_t i = 0; i < ps.size(); i++) {
    const std::string &s = ps[i];

    cp[i] = reinterpret_cast<char *>(malloc(s.size() + 1));
    // TODO: malloc null check.
    strncpy(cp[i], s.c_str(), s.size());
    cp[i][s.size()] = '\0';
  }

  (*prop_names_out) = cp;

  return 1;
}


