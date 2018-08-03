// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: geometry.proto

#include "geometry.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace pbmldgeo {
class GeometryDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Geometry>
      _instance;
} _Geometry_default_instance_;
}  // namespace pbmldgeo
namespace protobuf_geometry_2eproto {
void InitDefaultsGeometryImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::pbmldgeo::_Geometry_default_instance_;
    new (ptr) ::pbmldgeo::Geometry();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pbmldgeo::Geometry::InitAsDefaultInstance();
}

void InitDefaultsGeometry() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsGeometryImpl);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldgeo::Geometry, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldgeo::Geometry, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldgeo::Geometry, index_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldgeo::Geometry, nodes_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldgeo::Geometry, fwd_weights_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldgeo::Geometry, rev_weights_),
  ~0u,
  ~0u,
  ~0u,
  ~0u,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, sizeof(::pbmldgeo::Geometry)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::pbmldgeo::_Geometry_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "geometry.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\016geometry.proto\022\010pbmldgeo\"R\n\010Geometry\022\r"
      "\n\005index\030\001 \003(\r\022\r\n\005nodes\030\002 \003(\r\022\023\n\013fwd_weig"
      "hts\030\003 \003(\r\022\023\n\013rev_weights\030\004 \003(\r"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 110);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "geometry.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_geometry_2eproto
namespace pbmldgeo {

// ===================================================================

void Geometry::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Geometry::kIndexFieldNumber;
const int Geometry::kNodesFieldNumber;
const int Geometry::kFwdWeightsFieldNumber;
const int Geometry::kRevWeightsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Geometry::Geometry()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_geometry_2eproto::InitDefaultsGeometry();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:pbmldgeo.Geometry)
}
Geometry::Geometry(const Geometry& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      index_(from.index_),
      nodes_(from.nodes_),
      fwd_weights_(from.fwd_weights_),
      rev_weights_(from.rev_weights_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:pbmldgeo.Geometry)
}

void Geometry::SharedCtor() {
  _cached_size_ = 0;
}

Geometry::~Geometry() {
  // @@protoc_insertion_point(destructor:pbmldgeo.Geometry)
  SharedDtor();
}

void Geometry::SharedDtor() {
}

void Geometry::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Geometry::descriptor() {
  ::protobuf_geometry_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_geometry_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Geometry& Geometry::default_instance() {
  ::protobuf_geometry_2eproto::InitDefaultsGeometry();
  return *internal_default_instance();
}

Geometry* Geometry::New(::google::protobuf::Arena* arena) const {
  Geometry* n = new Geometry;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Geometry::Clear() {
// @@protoc_insertion_point(message_clear_start:pbmldgeo.Geometry)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  index_.Clear();
  nodes_.Clear();
  fwd_weights_.Clear();
  rev_weights_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool Geometry::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pbmldgeo.Geometry)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 index = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8u, input, this->mutable_index())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_index())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated uint32 nodes = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16u, input, this->mutable_nodes())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_nodes())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated uint32 fwd_weights = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 24u, input, this->mutable_fwd_weights())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_fwd_weights())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated uint32 rev_weights = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 32u, input, this->mutable_rev_weights())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_rev_weights())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:pbmldgeo.Geometry)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pbmldgeo.Geometry)
  return false;
#undef DO_
}

void Geometry::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pbmldgeo.Geometry)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint32 index = 1;
  for (int i = 0, n = this->index_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->index(i), output);
  }

  // repeated uint32 nodes = 2;
  for (int i = 0, n = this->nodes_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->nodes(i), output);
  }

  // repeated uint32 fwd_weights = 3;
  for (int i = 0, n = this->fwd_weights_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      3, this->fwd_weights(i), output);
  }

  // repeated uint32 rev_weights = 4;
  for (int i = 0, n = this->rev_weights_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      4, this->rev_weights(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pbmldgeo.Geometry)
}

::google::protobuf::uint8* Geometry::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:pbmldgeo.Geometry)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint32 index = 1;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt32ToArray(1, this->index_, target);

  // repeated uint32 nodes = 2;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt32ToArray(2, this->nodes_, target);

  // repeated uint32 fwd_weights = 3;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt32ToArray(3, this->fwd_weights_, target);

  // repeated uint32 rev_weights = 4;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt32ToArray(4, this->rev_weights_, target);

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbmldgeo.Geometry)
  return target;
}

size_t Geometry::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbmldgeo.Geometry)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  // repeated uint32 index = 1;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt32Size(this->index_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->index_size());
    total_size += data_size;
  }

  // repeated uint32 nodes = 2;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt32Size(this->nodes_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->nodes_size());
    total_size += data_size;
  }

  // repeated uint32 fwd_weights = 3;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt32Size(this->fwd_weights_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->fwd_weights_size());
    total_size += data_size;
  }

  // repeated uint32 rev_weights = 4;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt32Size(this->rev_weights_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->rev_weights_size());
    total_size += data_size;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Geometry::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pbmldgeo.Geometry)
  GOOGLE_DCHECK_NE(&from, this);
  const Geometry* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Geometry>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pbmldgeo.Geometry)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pbmldgeo.Geometry)
    MergeFrom(*source);
  }
}

void Geometry::MergeFrom(const Geometry& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbmldgeo.Geometry)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  index_.MergeFrom(from.index_);
  nodes_.MergeFrom(from.nodes_);
  fwd_weights_.MergeFrom(from.fwd_weights_);
  rev_weights_.MergeFrom(from.rev_weights_);
}

void Geometry::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pbmldgeo.Geometry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Geometry::CopyFrom(const Geometry& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbmldgeo.Geometry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Geometry::IsInitialized() const {
  return true;
}

void Geometry::Swap(Geometry* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Geometry::InternalSwap(Geometry* other) {
  using std::swap;
  index_.InternalSwap(&other->index_);
  nodes_.InternalSwap(&other->nodes_);
  fwd_weights_.InternalSwap(&other->fwd_weights_);
  rev_weights_.InternalSwap(&other->rev_weights_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Geometry::GetMetadata() const {
  protobuf_geometry_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_geometry_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace pbmldgeo

// @@protoc_insertion_point(global_scope)
