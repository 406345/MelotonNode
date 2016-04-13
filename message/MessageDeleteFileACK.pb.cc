// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageDeleteFileACK.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MessageDeleteFileACK.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* MessageDeleteFileACK_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MessageDeleteFileACK_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_MessageDeleteFileACK_2eproto() {
  protobuf_AddDesc_MessageDeleteFileACK_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "MessageDeleteFileACK.proto");
  GOOGLE_CHECK(file != NULL);
  MessageDeleteFileACK_descriptor_ = file->message_type(0);
  static const int MessageDeleteFileACK_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageDeleteFileACK, code_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageDeleteFileACK, message_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageDeleteFileACK, path_),
  };
  MessageDeleteFileACK_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MessageDeleteFileACK_descriptor_,
      MessageDeleteFileACK::default_instance_,
      MessageDeleteFileACK_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageDeleteFileACK, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageDeleteFileACK, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MessageDeleteFileACK));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_MessageDeleteFileACK_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MessageDeleteFileACK_descriptor_, &MessageDeleteFileACK::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_MessageDeleteFileACK_2eproto() {
  delete MessageDeleteFileACK::default_instance_;
  delete MessageDeleteFileACK_reflection_;
}

void protobuf_AddDesc_MessageDeleteFileACK_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032MessageDeleteFileACK.proto\"C\n\024MessageD"
    "eleteFileACK\022\014\n\004Code\030\001 \002(\005\022\017\n\007Message\030\002 "
    "\002(\t\022\014\n\004Path\030\003 \002(\t", 97);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MessageDeleteFileACK.proto", &protobuf_RegisterTypes);
  MessageDeleteFileACK::default_instance_ = new MessageDeleteFileACK();
  MessageDeleteFileACK::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MessageDeleteFileACK_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MessageDeleteFileACK_2eproto {
  StaticDescriptorInitializer_MessageDeleteFileACK_2eproto() {
    protobuf_AddDesc_MessageDeleteFileACK_2eproto();
  }
} static_descriptor_initializer_MessageDeleteFileACK_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int MessageDeleteFileACK::kCodeFieldNumber;
const int MessageDeleteFileACK::kMessageFieldNumber;
const int MessageDeleteFileACK::kPathFieldNumber;
#endif  // !_MSC_VER

MessageDeleteFileACK::MessageDeleteFileACK()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MessageDeleteFileACK)
}

void MessageDeleteFileACK::InitAsDefaultInstance() {
}

MessageDeleteFileACK::MessageDeleteFileACK(const MessageDeleteFileACK& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MessageDeleteFileACK)
}

void MessageDeleteFileACK::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  code_ = 0;
  message_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  path_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MessageDeleteFileACK::~MessageDeleteFileACK() {
  // @@protoc_insertion_point(destructor:MessageDeleteFileACK)
  SharedDtor();
}

void MessageDeleteFileACK::SharedDtor() {
  if (message_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete message_;
  }
  if (path_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete path_;
  }
  if (this != default_instance_) {
  }
}

void MessageDeleteFileACK::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MessageDeleteFileACK::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageDeleteFileACK_descriptor_;
}

const MessageDeleteFileACK& MessageDeleteFileACK::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MessageDeleteFileACK_2eproto();
  return *default_instance_;
}

MessageDeleteFileACK* MessageDeleteFileACK::default_instance_ = NULL;

MessageDeleteFileACK* MessageDeleteFileACK::New() const {
  return new MessageDeleteFileACK;
}

void MessageDeleteFileACK::Clear() {
  if (_has_bits_[0 / 32] & 7) {
    code_ = 0;
    if (has_message()) {
      if (message_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        message_->clear();
      }
    }
    if (has_path()) {
      if (path_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        path_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MessageDeleteFileACK::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MessageDeleteFileACK)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 Code = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &code_)));
          set_has_code();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_Message;
        break;
      }

      // required string Message = 2;
      case 2: {
        if (tag == 18) {
         parse_Message:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_message()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->message().data(), this->message().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "message");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_Path;
        break;
      }

      // required string Path = 3;
      case 3: {
        if (tag == 26) {
         parse_Path:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_path()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->path().data(), this->path().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "path");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MessageDeleteFileACK)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MessageDeleteFileACK)
  return false;
#undef DO_
}

void MessageDeleteFileACK::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MessageDeleteFileACK)
  // required int32 Code = 1;
  if (has_code()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->code(), output);
  }

  // required string Message = 2;
  if (has_message()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "message");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->message(), output);
  }

  // required string Path = 3;
  if (has_path()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "path");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->path(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MessageDeleteFileACK)
}

::google::protobuf::uint8* MessageDeleteFileACK::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MessageDeleteFileACK)
  // required int32 Code = 1;
  if (has_code()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->code(), target);
  }

  // required string Message = 2;
  if (has_message()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "message");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->message(), target);
  }

  // required string Path = 3;
  if (has_path()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "path");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->path(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MessageDeleteFileACK)
  return target;
}

int MessageDeleteFileACK::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 Code = 1;
    if (has_code()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->code());
    }

    // required string Message = 2;
    if (has_message()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->message());
    }

    // required string Path = 3;
    if (has_path()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->path());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MessageDeleteFileACK::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MessageDeleteFileACK* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MessageDeleteFileACK*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MessageDeleteFileACK::MergeFrom(const MessageDeleteFileACK& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_code()) {
      set_code(from.code());
    }
    if (from.has_message()) {
      set_message(from.message());
    }
    if (from.has_path()) {
      set_path(from.path());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MessageDeleteFileACK::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MessageDeleteFileACK::CopyFrom(const MessageDeleteFileACK& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageDeleteFileACK::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void MessageDeleteFileACK::Swap(MessageDeleteFileACK* other) {
  if (other != this) {
    std::swap(code_, other->code_);
    std::swap(message_, other->message_);
    std::swap(path_, other->path_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MessageDeleteFileACK::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MessageDeleteFileACK_descriptor_;
  metadata.reflection = MessageDeleteFileACK_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
