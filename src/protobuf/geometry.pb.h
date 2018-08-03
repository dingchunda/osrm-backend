// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: geometry.proto

#ifndef PROTOBUF_geometry_2eproto__INCLUDED
#define PROTOBUF_geometry_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_geometry_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsGeometryImpl();
void InitDefaultsGeometry();
inline void InitDefaults() {
  InitDefaultsGeometry();
}
}  // namespace protobuf_geometry_2eproto
namespace pbmldgeo {
class Geometry;
class GeometryDefaultTypeInternal;
extern GeometryDefaultTypeInternal _Geometry_default_instance_;
}  // namespace pbmldgeo
namespace pbmldgeo {

// ===================================================================

class Geometry : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:pbmldgeo.Geometry) */ {
 public:
  Geometry();
  virtual ~Geometry();

  Geometry(const Geometry& from);

  inline Geometry& operator=(const Geometry& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Geometry(Geometry&& from) noexcept
    : Geometry() {
    *this = ::std::move(from);
  }

  inline Geometry& operator=(Geometry&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Geometry& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Geometry* internal_default_instance() {
    return reinterpret_cast<const Geometry*>(
               &_Geometry_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Geometry* other);
  friend void swap(Geometry& a, Geometry& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Geometry* New() const PROTOBUF_FINAL { return New(NULL); }

  Geometry* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Geometry& from);
  void MergeFrom(const Geometry& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Geometry* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated uint32 index = 1;
  int index_size() const;
  void clear_index();
  static const int kIndexFieldNumber = 1;
  ::google::protobuf::uint32 index(int index) const;
  void set_index(int index, ::google::protobuf::uint32 value);
  void add_index(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      index() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_index();

  // repeated uint32 nodes = 2;
  int nodes_size() const;
  void clear_nodes();
  static const int kNodesFieldNumber = 2;
  ::google::protobuf::uint32 nodes(int index) const;
  void set_nodes(int index, ::google::protobuf::uint32 value);
  void add_nodes(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      nodes() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_nodes();

  // repeated uint32 fwd_weights = 3;
  int fwd_weights_size() const;
  void clear_fwd_weights();
  static const int kFwdWeightsFieldNumber = 3;
  ::google::protobuf::uint32 fwd_weights(int index) const;
  void set_fwd_weights(int index, ::google::protobuf::uint32 value);
  void add_fwd_weights(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      fwd_weights() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_fwd_weights();

  // repeated uint32 rev_weights = 4;
  int rev_weights_size() const;
  void clear_rev_weights();
  static const int kRevWeightsFieldNumber = 4;
  ::google::protobuf::uint32 rev_weights(int index) const;
  void set_rev_weights(int index, ::google::protobuf::uint32 value);
  void add_rev_weights(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      rev_weights() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_rev_weights();

  // @@protoc_insertion_point(class_scope:pbmldgeo.Geometry)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > index_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > nodes_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > fwd_weights_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > rev_weights_;
  friend struct ::protobuf_geometry_2eproto::TableStruct;
  friend void ::protobuf_geometry_2eproto::InitDefaultsGeometryImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Geometry

// repeated uint32 index = 1;
inline int Geometry::index_size() const {
  return index_.size();
}
inline void Geometry::clear_index() {
  index_.Clear();
}
inline ::google::protobuf::uint32 Geometry::index(int index) const {
  // @@protoc_insertion_point(field_get:pbmldgeo.Geometry.index)
  return index_.Get(index);
}
inline void Geometry::set_index(int index, ::google::protobuf::uint32 value) {
  index_.Set(index, value);
  // @@protoc_insertion_point(field_set:pbmldgeo.Geometry.index)
}
inline void Geometry::add_index(::google::protobuf::uint32 value) {
  index_.Add(value);
  // @@protoc_insertion_point(field_add:pbmldgeo.Geometry.index)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Geometry::index() const {
  // @@protoc_insertion_point(field_list:pbmldgeo.Geometry.index)
  return index_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Geometry::mutable_index() {
  // @@protoc_insertion_point(field_mutable_list:pbmldgeo.Geometry.index)
  return &index_;
}

// repeated uint32 nodes = 2;
inline int Geometry::nodes_size() const {
  return nodes_.size();
}
inline void Geometry::clear_nodes() {
  nodes_.Clear();
}
inline ::google::protobuf::uint32 Geometry::nodes(int index) const {
  // @@protoc_insertion_point(field_get:pbmldgeo.Geometry.nodes)
  return nodes_.Get(index);
}
inline void Geometry::set_nodes(int index, ::google::protobuf::uint32 value) {
  nodes_.Set(index, value);
  // @@protoc_insertion_point(field_set:pbmldgeo.Geometry.nodes)
}
inline void Geometry::add_nodes(::google::protobuf::uint32 value) {
  nodes_.Add(value);
  // @@protoc_insertion_point(field_add:pbmldgeo.Geometry.nodes)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Geometry::nodes() const {
  // @@protoc_insertion_point(field_list:pbmldgeo.Geometry.nodes)
  return nodes_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Geometry::mutable_nodes() {
  // @@protoc_insertion_point(field_mutable_list:pbmldgeo.Geometry.nodes)
  return &nodes_;
}

// repeated uint32 fwd_weights = 3;
inline int Geometry::fwd_weights_size() const {
  return fwd_weights_.size();
}
inline void Geometry::clear_fwd_weights() {
  fwd_weights_.Clear();
}
inline ::google::protobuf::uint32 Geometry::fwd_weights(int index) const {
  // @@protoc_insertion_point(field_get:pbmldgeo.Geometry.fwd_weights)
  return fwd_weights_.Get(index);
}
inline void Geometry::set_fwd_weights(int index, ::google::protobuf::uint32 value) {
  fwd_weights_.Set(index, value);
  // @@protoc_insertion_point(field_set:pbmldgeo.Geometry.fwd_weights)
}
inline void Geometry::add_fwd_weights(::google::protobuf::uint32 value) {
  fwd_weights_.Add(value);
  // @@protoc_insertion_point(field_add:pbmldgeo.Geometry.fwd_weights)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Geometry::fwd_weights() const {
  // @@protoc_insertion_point(field_list:pbmldgeo.Geometry.fwd_weights)
  return fwd_weights_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Geometry::mutable_fwd_weights() {
  // @@protoc_insertion_point(field_mutable_list:pbmldgeo.Geometry.fwd_weights)
  return &fwd_weights_;
}

// repeated uint32 rev_weights = 4;
inline int Geometry::rev_weights_size() const {
  return rev_weights_.size();
}
inline void Geometry::clear_rev_weights() {
  rev_weights_.Clear();
}
inline ::google::protobuf::uint32 Geometry::rev_weights(int index) const {
  // @@protoc_insertion_point(field_get:pbmldgeo.Geometry.rev_weights)
  return rev_weights_.Get(index);
}
inline void Geometry::set_rev_weights(int index, ::google::protobuf::uint32 value) {
  rev_weights_.Set(index, value);
  // @@protoc_insertion_point(field_set:pbmldgeo.Geometry.rev_weights)
}
inline void Geometry::add_rev_weights(::google::protobuf::uint32 value) {
  rev_weights_.Add(value);
  // @@protoc_insertion_point(field_add:pbmldgeo.Geometry.rev_weights)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Geometry::rev_weights() const {
  // @@protoc_insertion_point(field_list:pbmldgeo.Geometry.rev_weights)
  return rev_weights_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Geometry::mutable_rev_weights() {
  // @@protoc_insertion_point(field_mutable_list:pbmldgeo.Geometry.rev_weights)
  return &rev_weights_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace pbmldgeo

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_geometry_2eproto__INCLUDED
