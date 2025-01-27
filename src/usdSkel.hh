// SPDX-License-Identifier: MIT
// Copyright 2022 - Present, Syoyo Fujita.
//
// UsdSkel(includes BlendShapes)
#pragma once

#include "prim-types.hh"
#include "value-types.hh"
#include "xform.hh"

namespace tinyusdz {

constexpr auto kSkelRoot = "SkelRoot";
constexpr auto kSkeleton = "Skeleton";
constexpr auto kSkelAnimation = "SkelAnimation";
constexpr auto kBlendShape = "BlendShape";

// BlendShapes
struct BlendShape {
  std::string name;
  Specifier spec{Specifier::Def};

  TypedAttribute<std::vector<value::vector3f>>
      offsets;  // uniform vector3f[]. required property
  TypedAttribute<std::vector<value::vector3f>>
      normalOffsets;  // uniform vector3f[]. required property

  TypedAttribute<std::vector<int>>
      pointIndices;  // uniform int[]. optional. vertex indices to the original
                     // mesh for each values in `offsets` and `normalOffsets`.

  std::pair<ListEditQual, std::vector<Reference>> references;
  std::pair<ListEditQual, std::vector<Payload>> payload;
  std::map<std::string, VariantSet> variantSet;
  std::map<std::string, Property> props;
  PrimMeta meta;

  const std::vector<value::token> &primChildrenNames() const { return _primChildren; }
  const std::vector<value::token> &propertyNames() const { return _properties; }
  std::vector<value::token> &primChildrenNames() { return _primChildren; }
  std::vector<value::token> &propertyNames() { return _properties; }

 private:
  std::vector<value::token> _primChildren;
  std::vector<value::token> _properties;
};

// Skeleton
struct Skeleton : Xformable {
  std::string name;
  Specifier spec{Specifier::Def};

  TypedAttribute<std::vector<value::matrix4d>>
      bindTransforms;  // uniform matrix4d[]. bind-pose transform of each joint
                       // in world coordinate.

  TypedAttribute<std::vector<value::token>> jointNames;  // uniform token[]
  TypedAttribute<std::vector<value::token>> joints;      // uniform token[]

  TypedAttribute<std::vector<value::matrix4d>>
      restTransforms;  // uniform matrix4d[] rest-pose transforms of each
                       // joint in local coordinate.

  nonstd::optional<Relationship> proxyPrim;  // rel proxyPrim

  // SkelBindingAPI
  nonstd::optional<Relationship>
      animationSource;  // rel skel:animationSource = </path/...>

  TypedAttributeWithFallback<Animatable<Visibility>> visibility{
      Visibility::Inherited};  // "token visibility"
  TypedAttribute<Animatable<Extent>>
      extent;  // bounding extent. When authorized, the extent is the bounding
               // box of whole its children.
  TypedAttributeWithFallback<Purpose> purpose{
      Purpose::Default};  // "uniform token purpose"

  std::pair<ListEditQual, std::vector<Reference>> references;
  std::pair<ListEditQual, std::vector<Payload>> payload;
  std::map<std::string, VariantSet> variantSet;
  std::map<std::string, Property> props;
  //std::vector<value::token> xformOpOrder;

  PrimMeta meta;

  bool get_animationSource(Path *path, ListEditQual *qual = nullptr) {
    if (!path) {
      return false;
    }

    const Relationship &rel = animationSource.value();
    if (qual) {
      (*qual) = rel.get_listedit_qual();
    }

    if (rel.is_path()) {
      (*path) = rel.targetPath;
    } else if (rel.is_pathvector()) {
      if (rel.targetPathVector.size()) {
        (*path) = rel.targetPathVector[0];
      }
    } else {
      return false;
    }


    return false;
  }

  const std::vector<value::token> &primChildrenNames() const { return _primChildren; }
  const std::vector<value::token> &propertyNames() const { return _properties; }
  std::vector<value::token> &primChildrenNames() { return _primChildren; }
  std::vector<value::token> &propertyNames() { return _properties; }

 private:
  std::vector<value::token> _primChildren;
  std::vector<value::token> _properties;
};

// NOTE: SkelRoot itself does not have dedicated attributes in the schema.
struct SkelRoot : Xformable {
  std::string name;
  Specifier spec{Specifier::Def};
  int64_t parent_id{-1};

  TypedAttribute<Animatable<Extent>>
      extent;  // bounding extent. When authorized, the extent is the bounding
               // box of whole its children.
  TypedAttributeWithFallback<Purpose> purpose{
      Purpose::Default};  // "uniform token purpose"
  TypedAttributeWithFallback<Animatable<Visibility>> visibility{
      Visibility::Inherited};  // "token visibility"

  nonstd::optional<Relationship> proxyPrim;  // rel proxyPrim
  //std::vector<XformOp> xformOps;

  // TODO: Add function to check if SkelRoot contains `Skeleton` and `GeomMesh`
  // node?;

  
  std::pair<ListEditQual, std::vector<Reference>> references;
  std::pair<ListEditQual, std::vector<Payload>> payload;
  std::map<std::string, VariantSet> variantSet;
  std::map<std::string, Property> props;
  PrimMeta meta;

  const std::vector<value::token> &primChildrenNames() const { return _primChildren; }
  const std::vector<value::token> &propertyNames() const { return _properties; }
  std::vector<value::token> &primChildrenNames() { return _primChildren; }
  std::vector<value::token> &propertyNames() { return _properties; }

 private:
  std::vector<value::token> _primChildren;
  std::vector<value::token> _properties;

};

struct SkelAnimation {
  std::string name;
  Specifier spec{Specifier::Def};

  TypedAttribute<std::vector<value::token>> blendShapes;  // uniform token[]
  TypedAttribute<Animatable<std::vector<float>>> blendShapeWeights;  // float[]
  TypedAttribute<std::vector<value::token>> joints;  // uniform token[]
  TypedAttribute<Animatable<std::vector<value::quatf>>>
      rotations;  // quatf[] Joint-local unit quaternion rotations
  TypedAttribute<Animatable<std::vector<value::half3>>>
      scales;  // half3[] Joint-local scaling in 16bit half float. TODO: Use
               // float3 for TinyUSDZ for convenience?
  TypedAttribute<Animatable<std::vector<value::float3>>>
      translations;  // float3[] Joint-local translation.

  bool get_blendShapes(std::vector<value::token> *toks);
  bool get_blendShapeWeights(std::vector<float> *vals,
                             const double t = value::TimeCode::Default(),
                             const value::TimeSampleInterpolationType tinterp =
                                 value::TimeSampleInterpolationType::Held);
  bool get_joints(std::vector<value::token> *toks);
  bool get_rotations(std::vector<value::quatf> *vals,
                     const double t = value::TimeCode::Default(),
                     const value::TimeSampleInterpolationType tinterp =
                         value::TimeSampleInterpolationType::Held);
  bool get_scales(std::vector<value::half3> *vals,
                  const double t = value::TimeCode::Default(),
                  const value::TimeSampleInterpolationType tinterp =
                      value::TimeSampleInterpolationType::Held);
  bool get_translations(std::vector<value::float3> *vals,
                        const double t = value::TimeCode::Default(),
                        const value::TimeSampleInterpolationType tinterp =
                            value::TimeSampleInterpolationType::Held);

  std::pair<ListEditQual, std::vector<Reference>> references;
  std::pair<ListEditQual, std::vector<Payload>> payload;
  std::map<std::string, VariantSet> variantSet;
  std::map<std::string, Property> props;
  PrimMeta meta;

  const std::vector<value::token> &primChildrenNames() const { return _primChildren; }
  const std::vector<value::token> &propertyNames() const { return _properties; }
  std::vector<value::token> &primChildrenNames() { return _primChildren; }
  std::vector<value::token> &propertyNames() { return _properties; }

 private:
  std::vector<value::token> _primChildren;
  std::vector<value::token> _properties;
};

// PackedJointAnimation is deprecated(Convert to SkelAnimation)
// struct PackedJointAnimation {
// };

// import DEFINE_TYPE_TRAIT and DEFINE_ROLE_TYPE_TRAIT
#include "define-type-trait.inc"

namespace value {

// Geom
DEFINE_TYPE_TRAIT(SkelRoot, kSkelRoot, TYPE_ID_SKEL_ROOT, 1);
DEFINE_TYPE_TRAIT(Skeleton, kSkeleton, TYPE_ID_SKELETON, 1);
DEFINE_TYPE_TRAIT(SkelAnimation, kSkelAnimation, TYPE_ID_SKELANIMATION, 1);
DEFINE_TYPE_TRAIT(BlendShape, kBlendShape, TYPE_ID_BLENDSHAPE, 1);

#undef DEFINE_TYPE_TRAIT
#undef DEFINE_ROLE_TYPE_TRAIT

}  // namespace value

}  // namespace tinyusdz
