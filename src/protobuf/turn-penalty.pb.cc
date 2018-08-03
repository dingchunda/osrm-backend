// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: turn-penalty.proto

#include "turn-penalty.pb.h"

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
namespace pbtp {
class TurnPenaltyDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<TurnPenalty>
      _instance;
} _TurnPenalty_default_instance_;
}  // namespace pbtp
namespace protobuf_turn_2dpenalty_2eproto {
void InitDefaultsTurnPenaltyImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::pbtp::_TurnPenalty_default_instance_;
    new (ptr) ::pbtp::TurnPenalty();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pbtp::TurnPenalty::InitAsDefaultInstance();
}

void InitDefaultsTurnPenalty() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsTurnPenaltyImpl);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbtp::TurnPenalty, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbtp::TurnPenalty, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::pbtp::TurnPenalty, penalty_),
  ~0u,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 6, sizeof(::pbtp::TurnPenalty)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::pbtp::_TurnPenalty_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "turn-penalty.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
      "\n\022turn-penalty.proto\022\004pbtp\"\036\n\013TurnPenalt"
      "y\022\017\n\007penalty\030\001 \003(\005"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 58);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "turn-penalty.proto", &protobuf_RegisterTypes);
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
}  // namespace protobuf_turn_2dpenalty_2eproto
namespace pbtp {

// ===================================================================

void TurnPenalty::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TurnPenalty::kPenaltyFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TurnPenalty::TurnPenalty()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_turn_2dpenalty_2eproto::InitDefaultsTurnPenalty();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:pbtp.TurnPenalty)
}
TurnPenalty::TurnPenalty(const TurnPenalty& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      penalty_(from.penalty_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:pbtp.TurnPenalty)
}

void TurnPenalty::SharedCtor() {
  _cached_size_ = 0;
}

TurnPenalty::~TurnPenalty() {
  // @@protoc_insertion_point(destructor:pbtp.TurnPenalty)
  SharedDtor();
}

void TurnPenalty::SharedDtor() {
}

void TurnPenalty::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TurnPenalty::descriptor() {
  ::protobuf_turn_2dpenalty_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_turn_2dpenalty_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const TurnPenalty& TurnPenalty::default_instance() {
  ::protobuf_turn_2dpenalty_2eproto::InitDefaultsTurnPenalty();
  return *internal_default_instance();
}

TurnPenalty* TurnPenalty::New(::google::protobuf::Arena* arena) const {
  TurnPenalty* n = new TurnPenalty;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void TurnPenalty::Clear() {
// @@protoc_insertion_point(message_clear_start:pbtp.TurnPenalty)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  penalty_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool TurnPenalty::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pbtp.TurnPenalty)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated int32 penalty = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 8u, input, this->mutable_penalty())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_penalty())));
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
  // @@protoc_insertion_point(parse_success:pbtp.TurnPenalty)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pbtp.TurnPenalty)
  return false;
#undef DO_
}

void TurnPenalty::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pbtp.TurnPenalty)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated int32 penalty = 1;
  for (int i = 0, n = this->penalty_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      1, this->penalty(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pbtp.TurnPenalty)
}

::google::protobuf::uint8* TurnPenalty::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:pbtp.TurnPenalty)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated int32 penalty = 1;
  target = ::google::protobuf::internal::WireFormatLite::
    WriteInt32ToArray(1, this->penalty_, target);

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbtp.TurnPenalty)
  return target;
}

size_t TurnPenalty::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbtp.TurnPenalty)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  // repeated int32 penalty = 1;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      Int32Size(this->penalty_);
    total_size += 1 *
                  ::google::protobuf::internal::FromIntSize(this->penalty_size());
    total_size += data_size;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TurnPenalty::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pbtp.TurnPenalty)
  GOOGLE_DCHECK_NE(&from, this);
  const TurnPenalty* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const TurnPenalty>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pbtp.TurnPenalty)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pbtp.TurnPenalty)
    MergeFrom(*source);
  }
}

void TurnPenalty::MergeFrom(const TurnPenalty& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbtp.TurnPenalty)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  penalty_.MergeFrom(from.penalty_);
}

void TurnPenalty::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pbtp.TurnPenalty)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TurnPenalty::CopyFrom(const TurnPenalty& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbtp.TurnPenalty)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TurnPenalty::IsInitialized() const {
  return true;
}

void TurnPenalty::Swap(TurnPenalty* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TurnPenalty::InternalSwap(TurnPenalty* other) {
  using std::swap;
  penalty_.InternalSwap(&other->penalty_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata TurnPenalty::GetMetadata() const {
  protobuf_turn_2dpenalty_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_turn_2dpenalty_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace pbtp

// @@protoc_insertion_point(global_scope)
