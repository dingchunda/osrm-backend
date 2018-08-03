// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cells.proto

#include "cells.pb.h"

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
namespace pbmldc {
class CellDataDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<CellData>
      _instance;
} _CellData_default_instance_;
class CellsDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Cells>
      _instance;
} _Cells_default_instance_;
}  // namespace pbmldc
namespace protobuf_cells_2eproto {
void InitDefaultsCellDataImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::pbmldc::_CellData_default_instance_;
    new (ptr) ::pbmldc::CellData();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pbmldc::CellData::InitAsDefaultInstance();
}

void InitDefaultsCellData() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsCellDataImpl);
}

void InitDefaultsCellsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  protobuf_cells_2eproto::InitDefaultsCellData();
  {
    void* ptr = &::pbmldc::_Cells_default_instance_;
    new (ptr) ::pbmldc::Cells();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pbmldc::Cells::InitAsDefaultInstance();
}

void InitDefaultsCells() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsCellsImpl);
}

::google::protobuf::Metadata file_level_metadata[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::CellData, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::CellData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::CellData, valueoffset_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::CellData, sourceboundaryoffset_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::CellData, destinationboundaryoffset_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::CellData, sourcenodesnumber_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::CellData, destinationnodesnumber_),
  0,
  1,
  2,
  3,
  4,
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::Cells, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::Cells, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::Cells, sourceboundary_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::Cells, destinationboundary_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::Cells, cells_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbmldc::Cells, leveloffset_),
  ~0u,
  ~0u,
  ~0u,
  ~0u,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, sizeof(::pbmldc::CellData)},
  { 15, 24, sizeof(::pbmldc::Cells)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::pbmldc::_CellData_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::pbmldc::_Cells_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "cells.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\013cells.proto\022\006pbmldc\"\233\001\n\010CellData\022\023\n\013va"
      "lueOffset\030\001 \001(\r\022\034\n\024sourceBoundaryOffset\030"
      "\002 \001(\r\022!\n\031destinationBoundaryOffset\030\003 \001(\r"
      "\022\031\n\021sourceNodesNumber\030\004 \001(\r\022\036\n\026destinati"
      "onNodesNumber\030\005 \001(\r\"r\n\005Cells\022\026\n\016sourceBo"
      "undary\030\001 \003(\r\022\033\n\023destinationBoundary\030\002 \003("
      "\r\022\037\n\005cells\030\003 \003(\0132\020.pbmldc.CellData\022\023\n\013le"
      "velOffset\030\004 \003(\004"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 295);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "cells.proto", &protobuf_RegisterTypes);
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
}  // namespace protobuf_cells_2eproto
namespace pbmldc {

// ===================================================================

void CellData::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int CellData::kValueOffsetFieldNumber;
const int CellData::kSourceBoundaryOffsetFieldNumber;
const int CellData::kDestinationBoundaryOffsetFieldNumber;
const int CellData::kSourceNodesNumberFieldNumber;
const int CellData::kDestinationNodesNumberFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

CellData::CellData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_cells_2eproto::InitDefaultsCellData();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:pbmldc.CellData)
}
CellData::CellData(const CellData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&valueoffset_, &from.valueoffset_,
    static_cast<size_t>(reinterpret_cast<char*>(&destinationnodesnumber_) -
    reinterpret_cast<char*>(&valueoffset_)) + sizeof(destinationnodesnumber_));
  // @@protoc_insertion_point(copy_constructor:pbmldc.CellData)
}

void CellData::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&valueoffset_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&destinationnodesnumber_) -
      reinterpret_cast<char*>(&valueoffset_)) + sizeof(destinationnodesnumber_));
}

CellData::~CellData() {
  // @@protoc_insertion_point(destructor:pbmldc.CellData)
  SharedDtor();
}

void CellData::SharedDtor() {
}

void CellData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CellData::descriptor() {
  ::protobuf_cells_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_cells_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const CellData& CellData::default_instance() {
  ::protobuf_cells_2eproto::InitDefaultsCellData();
  return *internal_default_instance();
}

CellData* CellData::New(::google::protobuf::Arena* arena) const {
  CellData* n = new CellData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void CellData::Clear() {
// @@protoc_insertion_point(message_clear_start:pbmldc.CellData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 31u) {
    ::memset(&valueoffset_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&destinationnodesnumber_) -
        reinterpret_cast<char*>(&valueoffset_)) + sizeof(destinationnodesnumber_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool CellData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pbmldc.CellData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 valueOffset = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          set_has_valueoffset();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &valueoffset_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 sourceBoundaryOffset = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          set_has_sourceboundaryoffset();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &sourceboundaryoffset_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 destinationBoundaryOffset = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {
          set_has_destinationboundaryoffset();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &destinationboundaryoffset_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 sourceNodesNumber = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {
          set_has_sourcenodesnumber();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &sourcenodesnumber_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 destinationNodesNumber = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {
          set_has_destinationnodesnumber();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &destinationnodesnumber_)));
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
  // @@protoc_insertion_point(parse_success:pbmldc.CellData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pbmldc.CellData)
  return false;
#undef DO_
}

void CellData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pbmldc.CellData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 valueOffset = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->valueoffset(), output);
  }

  // optional uint32 sourceBoundaryOffset = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->sourceboundaryoffset(), output);
  }

  // optional uint32 destinationBoundaryOffset = 3;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->destinationboundaryoffset(), output);
  }

  // optional uint32 sourceNodesNumber = 4;
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->sourcenodesnumber(), output);
  }

  // optional uint32 destinationNodesNumber = 5;
  if (cached_has_bits & 0x00000010u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->destinationnodesnumber(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pbmldc.CellData)
}

::google::protobuf::uint8* CellData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:pbmldc.CellData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 valueOffset = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->valueoffset(), target);
  }

  // optional uint32 sourceBoundaryOffset = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->sourceboundaryoffset(), target);
  }

  // optional uint32 destinationBoundaryOffset = 3;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->destinationboundaryoffset(), target);
  }

  // optional uint32 sourceNodesNumber = 4;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->sourcenodesnumber(), target);
  }

  // optional uint32 destinationNodesNumber = 5;
  if (cached_has_bits & 0x00000010u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->destinationnodesnumber(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbmldc.CellData)
  return target;
}

size_t CellData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbmldc.CellData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (_has_bits_[0 / 32] & 31u) {
    // optional uint32 valueOffset = 1;
    if (has_valueoffset()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->valueoffset());
    }

    // optional uint32 sourceBoundaryOffset = 2;
    if (has_sourceboundaryoffset()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->sourceboundaryoffset());
    }

    // optional uint32 destinationBoundaryOffset = 3;
    if (has_destinationboundaryoffset()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->destinationboundaryoffset());
    }

    // optional uint32 sourceNodesNumber = 4;
    if (has_sourcenodesnumber()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->sourcenodesnumber());
    }

    // optional uint32 destinationNodesNumber = 5;
    if (has_destinationnodesnumber()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->destinationnodesnumber());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CellData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pbmldc.CellData)
  GOOGLE_DCHECK_NE(&from, this);
  const CellData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const CellData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pbmldc.CellData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pbmldc.CellData)
    MergeFrom(*source);
  }
}

void CellData::MergeFrom(const CellData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbmldc.CellData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 31u) {
    if (cached_has_bits & 0x00000001u) {
      valueoffset_ = from.valueoffset_;
    }
    if (cached_has_bits & 0x00000002u) {
      sourceboundaryoffset_ = from.sourceboundaryoffset_;
    }
    if (cached_has_bits & 0x00000004u) {
      destinationboundaryoffset_ = from.destinationboundaryoffset_;
    }
    if (cached_has_bits & 0x00000008u) {
      sourcenodesnumber_ = from.sourcenodesnumber_;
    }
    if (cached_has_bits & 0x00000010u) {
      destinationnodesnumber_ = from.destinationnodesnumber_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void CellData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pbmldc.CellData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CellData::CopyFrom(const CellData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbmldc.CellData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CellData::IsInitialized() const {
  return true;
}

void CellData::Swap(CellData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void CellData::InternalSwap(CellData* other) {
  using std::swap;
  swap(valueoffset_, other->valueoffset_);
  swap(sourceboundaryoffset_, other->sourceboundaryoffset_);
  swap(destinationboundaryoffset_, other->destinationboundaryoffset_);
  swap(sourcenodesnumber_, other->sourcenodesnumber_);
  swap(destinationnodesnumber_, other->destinationnodesnumber_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata CellData::GetMetadata() const {
  protobuf_cells_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_cells_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void Cells::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Cells::kSourceBoundaryFieldNumber;
const int Cells::kDestinationBoundaryFieldNumber;
const int Cells::kCellsFieldNumber;
const int Cells::kLevelOffsetFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Cells::Cells()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_cells_2eproto::InitDefaultsCells();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:pbmldc.Cells)
}
Cells::Cells(const Cells& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      sourceboundary_(from.sourceboundary_),
      destinationboundary_(from.destinationboundary_),
      cells_(from.cells_),
      leveloffset_(from.leveloffset_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:pbmldc.Cells)
}

void Cells::SharedCtor() {
  _cached_size_ = 0;
}

Cells::~Cells() {
  // @@protoc_insertion_point(destructor:pbmldc.Cells)
  SharedDtor();
}

void Cells::SharedDtor() {
}

void Cells::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Cells::descriptor() {
  ::protobuf_cells_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_cells_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Cells& Cells::default_instance() {
  ::protobuf_cells_2eproto::InitDefaultsCells();
  return *internal_default_instance();
}

Cells* Cells::New(::google::protobuf::Arena* arena) const {
  Cells* n = new Cells;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Cells::Clear() {
// @@protoc_insertion_point(message_clear_start:pbmldc.Cells)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  sourceboundary_.Clear();
  destinationboundary_.Clear();
  cells_.Clear();
  leveloffset_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool Cells::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pbmldc.Cells)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 sourceBoundary = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8u, input, this->mutable_sourceboundary())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_sourceboundary())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated uint32 destinationBoundary = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16u, input, this->mutable_destinationboundary())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_destinationboundary())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .pbmldc.CellData cells = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(input, add_cells()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated uint64 levelOffset = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 1, 32u, input, this->mutable_leveloffset())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, this->mutable_leveloffset())));
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
  // @@protoc_insertion_point(parse_success:pbmldc.Cells)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pbmldc.Cells)
  return false;
#undef DO_
}

void Cells::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pbmldc.Cells)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint32 sourceBoundary = 1;
  for (int i = 0, n = this->sourceboundary_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->sourceboundary(i), output);
  }

  // repeated uint32 destinationBoundary = 2;
  for (int i = 0, n = this->destinationboundary_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->destinationboundary(i), output);
  }

  // repeated .pbmldc.CellData cells = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->cells_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->cells(static_cast<int>(i)), output);
  }

  // repeated uint64 levelOffset = 4;
  for (int i = 0, n = this->leveloffset_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(
      4, this->leveloffset(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pbmldc.Cells)
}

::google::protobuf::uint8* Cells::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:pbmldc.Cells)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint32 sourceBoundary = 1;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt32ToArray(1, this->sourceboundary_, target);

  // repeated uint32 destinationBoundary = 2;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt32ToArray(2, this->destinationboundary_, target);

  // repeated .pbmldc.CellData cells = 3;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->cells_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        3, this->cells(static_cast<int>(i)), deterministic, target);
  }

  // repeated uint64 levelOffset = 4;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteUInt64ToArray(4, this->leveloffset_, target);

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbmldc.Cells)
  return target;
}

size_t Cells::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbmldc.Cells)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  // repeated uint32 sourceBoundary = 1;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt32Size(this->sourceboundary_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->sourceboundary_size());
    total_size += data_size;
  }

  // repeated uint32 destinationBoundary = 2;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt32Size(this->destinationboundary_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->destinationboundary_size());
    total_size += data_size;
  }

  // repeated .pbmldc.CellData cells = 3;
  {
    unsigned int count = static_cast<unsigned int>(this->cells_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->cells(static_cast<int>(i)));
    }
  }

  // repeated uint64 levelOffset = 4;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt64Size(this->leveloffset_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->leveloffset_size());
    total_size += data_size;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Cells::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pbmldc.Cells)
  GOOGLE_DCHECK_NE(&from, this);
  const Cells* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Cells>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pbmldc.Cells)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pbmldc.Cells)
    MergeFrom(*source);
  }
}

void Cells::MergeFrom(const Cells& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbmldc.Cells)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  sourceboundary_.MergeFrom(from.sourceboundary_);
  destinationboundary_.MergeFrom(from.destinationboundary_);
  cells_.MergeFrom(from.cells_);
  leveloffset_.MergeFrom(from.leveloffset_);
}

void Cells::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pbmldc.Cells)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Cells::CopyFrom(const Cells& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbmldc.Cells)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Cells::IsInitialized() const {
  return true;
}

void Cells::Swap(Cells* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Cells::InternalSwap(Cells* other) {
  using std::swap;
  sourceboundary_.InternalSwap(&other->sourceboundary_);
  destinationboundary_.InternalSwap(&other->destinationboundary_);
  cells_.InternalSwap(&other->cells_);
  leveloffset_.InternalSwap(&other->leveloffset_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Cells::GetMetadata() const {
  protobuf_cells_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_cells_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace pbmldc

// @@protoc_insertion_point(global_scope)
