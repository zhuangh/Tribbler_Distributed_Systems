/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Tribbler_types.h"

#include <algorithm>

namespace Tribbler {

int _kTribbleStatusValues[] = {
  TribbleStatus::OK,
  TribbleStatus::EEXISTS,
  TribbleStatus::INVALID_USER,
  TribbleStatus::INVALID_SUBSCRIBETO,
  TribbleStatus::NOT_IMPLEMENTED
};
const char* _kTribbleStatusNames[] = {
  "OK",
  "EEXISTS",
  "INVALID_USER",
  "INVALID_SUBSCRIBETO",
  "NOT_IMPLEMENTED"
};
const std::map<int, const char*> _TribbleStatus_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(5, _kTribbleStatusValues, _kTribbleStatusNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

const char* Tribble::ascii_fingerprint = "FA35BEC6F4D26D79A7E0AD1366489BCC";
const uint8_t Tribble::binary_fingerprint[16] = {0xFA,0x35,0xBE,0xC6,0xF4,0xD2,0x6D,0x79,0xA7,0xE0,0xAD,0x13,0x66,0x48,0x9B,0xCC};

uint32_t Tribble::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->userid);
          this->__isset.userid = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->posted);
          this->__isset.posted = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->contents);
          this->__isset.contents = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Tribble::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Tribble");

  xfer += oprot->writeFieldBegin("userid", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->userid);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("posted", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->posted);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("contents", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->contents);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Tribble &a, Tribble &b) {
  using ::std::swap;
  swap(a.userid, b.userid);
  swap(a.posted, b.posted);
  swap(a.contents, b.contents);
  swap(a.__isset, b.__isset);
}

const char* TribbleResponse::ascii_fingerprint = "43BFF501D78BB9C8F03213B50B38B34D";
const uint8_t TribbleResponse::binary_fingerprint[16] = {0x43,0xBF,0xF5,0x01,0xD7,0x8B,0xB9,0xC8,0xF0,0x32,0x13,0xB5,0x0B,0x38,0xB3,0x4D};

uint32_t TribbleResponse::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->tribbles.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            xfer += iprot->readListBegin(_etype3, _size0);
            this->tribbles.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += this->tribbles[_i4].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.tribbles = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast5;
          xfer += iprot->readI32(ecast5);
          this->status = (TribbleStatus::type)ecast5;
          this->__isset.status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TribbleResponse::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("TribbleResponse");

  xfer += oprot->writeFieldBegin("tribbles", ::apache::thrift::protocol::T_LIST, 1);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->tribbles.size()));
    std::vector<Tribble> ::const_iterator _iter6;
    for (_iter6 = this->tribbles.begin(); _iter6 != this->tribbles.end(); ++_iter6)
    {
      xfer += (*_iter6).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32((int32_t)this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TribbleResponse &a, TribbleResponse &b) {
  using ::std::swap;
  swap(a.tribbles, b.tribbles);
  swap(a.status, b.status);
  swap(a.__isset, b.__isset);
}

const char* SubscriptionResponse::ascii_fingerprint = "86398F2299656EAB855B1FD290A7B0C1";
const uint8_t SubscriptionResponse::binary_fingerprint[16] = {0x86,0x39,0x8F,0x22,0x99,0x65,0x6E,0xAB,0x85,0x5B,0x1F,0xD2,0x90,0xA7,0xB0,0xC1};

uint32_t SubscriptionResponse::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->subscriptions.clear();
            uint32_t _size7;
            ::apache::thrift::protocol::TType _etype10;
            xfer += iprot->readListBegin(_etype10, _size7);
            this->subscriptions.resize(_size7);
            uint32_t _i11;
            for (_i11 = 0; _i11 < _size7; ++_i11)
            {
              xfer += iprot->readString(this->subscriptions[_i11]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.subscriptions = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast12;
          xfer += iprot->readI32(ecast12);
          this->status = (TribbleStatus::type)ecast12;
          this->__isset.status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t SubscriptionResponse::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("SubscriptionResponse");

  xfer += oprot->writeFieldBegin("subscriptions", ::apache::thrift::protocol::T_LIST, 1);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->subscriptions.size()));
    std::vector<std::string> ::const_iterator _iter13;
    for (_iter13 = this->subscriptions.begin(); _iter13 != this->subscriptions.end(); ++_iter13)
    {
      xfer += oprot->writeString((*_iter13));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32((int32_t)this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(SubscriptionResponse &a, SubscriptionResponse &b) {
  using ::std::swap;
  swap(a.subscriptions, b.subscriptions);
  swap(a.status, b.status);
  swap(a.__isset, b.__isset);
}

} // namespace