// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: scc.proto

#include "scc.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

extern PROTOBUF_INTERNAL_EXPORT_scc_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_Edges_scc_2eproto;
namespace pbscc {
class EdgesDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Edges> _instance;
} _Edges_default_instance_;
class SCCGraphDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<SCCGraph> _instance;
} _SCCGraph_default_instance_;
}  // namespace pbscc
static void InitDefaultsEdges_scc_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::pbscc::_Edges_default_instance_;
    new (ptr) ::pbscc::Edges();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pbscc::Edges::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_Edges_scc_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsEdges_scc_2eproto}, {}};

static void InitDefaultsSCCGraph_scc_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::pbscc::_SCCGraph_default_instance_;
    new (ptr) ::pbscc::SCCGraph();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::pbscc::SCCGraph::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<1> scc_info_SCCGraph_scc_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsSCCGraph_scc_2eproto}, {
      &scc_info_Edges_scc_2eproto.base,}};

void InitDefaults_scc_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_Edges_scc_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_SCCGraph_scc_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_scc_2eproto[2];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_scc_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_scc_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_scc_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::pbscc::Edges, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::pbscc::Edges, targets_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::pbscc::SCCGraph, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::pbscc::SCCGraph, v_),
  PROTOBUF_FIELD_OFFSET(::pbscc::SCCGraph, adj_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::pbscc::Edges)},
  { 6, -1, sizeof(::pbscc::SCCGraph)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::pbscc::_Edges_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::pbscc::_SCCGraph_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_scc_2eproto = {
  {}, AddDescriptors_scc_2eproto, "scc.proto", schemas,
  file_default_instances, TableStruct_scc_2eproto::offsets,
  file_level_metadata_scc_2eproto, 2, file_level_enum_descriptors_scc_2eproto, file_level_service_descriptors_scc_2eproto,
};

const char descriptor_table_protodef_scc_2eproto[] =
  "\n\tscc.proto\022\005pbscc\"\030\n\005Edges\022\017\n\007targets\030\003"
  " \003(\005\"0\n\010SCCGraph\022\t\n\001V\030\001 \001(\005\022\031\n\003adj\030\004 \003(\013"
  "2\014.pbscc.Edgesb\006proto3"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_scc_2eproto = {
  false, InitDefaults_scc_2eproto, 
  descriptor_table_protodef_scc_2eproto,
  "scc.proto", &assign_descriptors_table_scc_2eproto, 102,
};

void AddDescriptors_scc_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_scc_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_scc_2eproto = []() { AddDescriptors_scc_2eproto(); return true; }();
namespace pbscc {

// ===================================================================

void Edges::InitAsDefaultInstance() {
}
class Edges::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Edges::kTargetsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Edges::Edges()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pbscc.Edges)
}
Edges::Edges(const Edges& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      targets_(from.targets_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:pbscc.Edges)
}

void Edges::SharedCtor() {
}

Edges::~Edges() {
  // @@protoc_insertion_point(destructor:pbscc.Edges)
  SharedDtor();
}

void Edges::SharedDtor() {
}

void Edges::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Edges& Edges::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_Edges_scc_2eproto.base);
  return *internal_default_instance();
}


void Edges::Clear() {
// @@protoc_insertion_point(message_clear_start:pbscc.Edges)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  targets_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Edges::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<Edges*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // repeated int32 targets = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) == 26) {
          ptr = ::google::protobuf::io::ReadSize(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          parser_till_end = ::google::protobuf::internal::PackedInt32Parser;
          object = msg->mutable_targets();
          if (size > end - ptr) goto len_delim_till_end;
          auto newend = ptr + size;
          if (size) ptr = parser_till_end(ptr, newend, object, ctx);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr == newend);
          break;
        } else if (static_cast<::google::protobuf::uint8>(tag) != 24) goto handle_unusual;
        do {
          msg->add_targets(::google::protobuf::internal::ReadVarint(&ptr));
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 24 && (ptr += 1));
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool Edges::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pbscc.Edges)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated int32 targets = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (26 & 0xFF)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_targets())));
        } else if (static_cast< ::google::protobuf::uint8>(tag) == (24 & 0xFF)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 26u, input, this->mutable_targets())));
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
  // @@protoc_insertion_point(parse_success:pbscc.Edges)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pbscc.Edges)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Edges::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pbscc.Edges)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated int32 targets = 3;
  if (this->targets_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(3, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_targets_cached_byte_size_.load(
        std::memory_order_relaxed));
  }
  for (int i = 0, n = this->targets_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32NoTag(
      this->targets(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pbscc.Edges)
}

::google::protobuf::uint8* Edges::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pbscc.Edges)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated int32 targets = 3;
  if (this->targets_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      3,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
        _targets_cached_byte_size_.load(std::memory_order_relaxed),
         target);
    target = ::google::protobuf::internal::WireFormatLite::
      WriteInt32NoTagToArray(this->targets_, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbscc.Edges)
  return target;
}

size_t Edges::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbscc.Edges)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 targets = 3;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      Int32Size(this->targets_);
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
            static_cast<::google::protobuf::int32>(data_size));
    }
    int cached_size = ::google::protobuf::internal::ToCachedSize(data_size);
    _targets_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Edges::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pbscc.Edges)
  GOOGLE_DCHECK_NE(&from, this);
  const Edges* source =
      ::google::protobuf::DynamicCastToGenerated<Edges>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pbscc.Edges)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pbscc.Edges)
    MergeFrom(*source);
  }
}

void Edges::MergeFrom(const Edges& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbscc.Edges)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  targets_.MergeFrom(from.targets_);
}

void Edges::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pbscc.Edges)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Edges::CopyFrom(const Edges& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbscc.Edges)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Edges::IsInitialized() const {
  return true;
}

void Edges::Swap(Edges* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Edges::InternalSwap(Edges* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  targets_.InternalSwap(&other->targets_);
}

::google::protobuf::Metadata Edges::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_scc_2eproto);
  return ::file_level_metadata_scc_2eproto[kIndexInFileMessages];
}


// ===================================================================

void SCCGraph::InitAsDefaultInstance() {
}
class SCCGraph::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SCCGraph::kVFieldNumber;
const int SCCGraph::kAdjFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SCCGraph::SCCGraph()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pbscc.SCCGraph)
}
SCCGraph::SCCGraph(const SCCGraph& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      adj_(from.adj_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  v_ = from.v_;
  // @@protoc_insertion_point(copy_constructor:pbscc.SCCGraph)
}

void SCCGraph::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_SCCGraph_scc_2eproto.base);
  v_ = 0;
}

SCCGraph::~SCCGraph() {
  // @@protoc_insertion_point(destructor:pbscc.SCCGraph)
  SharedDtor();
}

void SCCGraph::SharedDtor() {
}

void SCCGraph::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const SCCGraph& SCCGraph::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_SCCGraph_scc_2eproto.base);
  return *internal_default_instance();
}


void SCCGraph::Clear() {
// @@protoc_insertion_point(message_clear_start:pbscc.SCCGraph)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  adj_.Clear();
  v_ = 0;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* SCCGraph::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<SCCGraph*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int32 V = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_v(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // repeated .pbscc.Edges adj = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 34) goto handle_unusual;
        do {
          ptr = ::google::protobuf::io::ReadSize(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          parser_till_end = ::pbscc::Edges::_InternalParse;
          object = msg->add_adj();
          if (size > end - ptr) goto len_delim_till_end;
          ptr += size;
          GOOGLE_PROTOBUF_PARSER_ASSERT(ctx->ParseExactRange(
              {parser_till_end, object}, ptr - size, ptr));
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 34 && (ptr += 1));
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool SCCGraph::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pbscc.SCCGraph)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 V = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &v_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .pbscc.Edges adj = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (34 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_adj()));
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
  // @@protoc_insertion_point(parse_success:pbscc.SCCGraph)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pbscc.SCCGraph)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void SCCGraph::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pbscc.SCCGraph)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 V = 1;
  if (this->v() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->v(), output);
  }

  // repeated .pbscc.Edges adj = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->adj_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4,
      this->adj(static_cast<int>(i)),
      output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pbscc.SCCGraph)
}

::google::protobuf::uint8* SCCGraph::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pbscc.SCCGraph)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 V = 1;
  if (this->v() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->v(), target);
  }

  // repeated .pbscc.Edges adj = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->adj_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        4, this->adj(static_cast<int>(i)), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbscc.SCCGraph)
  return target;
}

size_t SCCGraph::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbscc.SCCGraph)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .pbscc.Edges adj = 4;
  {
    unsigned int count = static_cast<unsigned int>(this->adj_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->adj(static_cast<int>(i)));
    }
  }

  // int32 V = 1;
  if (this->v() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->v());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SCCGraph::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pbscc.SCCGraph)
  GOOGLE_DCHECK_NE(&from, this);
  const SCCGraph* source =
      ::google::protobuf::DynamicCastToGenerated<SCCGraph>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pbscc.SCCGraph)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pbscc.SCCGraph)
    MergeFrom(*source);
  }
}

void SCCGraph::MergeFrom(const SCCGraph& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbscc.SCCGraph)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  adj_.MergeFrom(from.adj_);
  if (from.v() != 0) {
    set_v(from.v());
  }
}

void SCCGraph::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pbscc.SCCGraph)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SCCGraph::CopyFrom(const SCCGraph& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbscc.SCCGraph)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SCCGraph::IsInitialized() const {
  return true;
}

void SCCGraph::Swap(SCCGraph* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SCCGraph::InternalSwap(SCCGraph* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  CastToBase(&adj_)->InternalSwap(CastToBase(&other->adj_));
  swap(v_, other->v_);
}

::google::protobuf::Metadata SCCGraph::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_scc_2eproto);
  return ::file_level_metadata_scc_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace pbscc
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::pbscc::Edges* Arena::CreateMaybeMessage< ::pbscc::Edges >(Arena* arena) {
  return Arena::CreateInternal< ::pbscc::Edges >(arena);
}
template<> PROTOBUF_NOINLINE ::pbscc::SCCGraph* Arena::CreateMaybeMessage< ::pbscc::SCCGraph >(Arena* arena) {
  return Arena::CreateInternal< ::pbscc::SCCGraph >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>