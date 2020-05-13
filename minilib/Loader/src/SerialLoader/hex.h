#ifndef HEX_H
#define HEX_H

#include <bytearray.h>
#include <QIODevice>

class Hex {
 public:
  enum RecordType {
    DataType,
    EofType,
    ExtSegAdr,
    StartSegAdr,
    ExtLinAdr,
    StartLinAdr
  };

  Hex() : _start(0), _base(0), _stringNum(0) {}

  static bool toFile(QString fileName,
                     const ByteArray& data,
                     quint32 baseAdr = 0,
                     quint32 startAdr = 0);
  static bool fromHex(QIODevice* src,
                      QIODevice* dest,
                      quint32* baseAdr,
                      quint32* startAdr,
                      quint32* stringNumber);
  static bool toHex(QIODevice* dest,
                    const ByteArray& data,
                    quint32 baseAdr = 0,
                    quint32 startAdr = 0);

  quint32 startAdr() const { return _start; }
  quint32 baseAdr() const { return _base; }
  quint32 stringNumber() const { return _stringNum; }
  const ByteArray& data() const { return _data; }
  int sizeData() const { return _data.size(); }
  void setData(const ByteArray& bin, const quint32 base, quint32 start) {
    _data = bin;
    _base = base;
    _start = start;
  }
  bool fromFile(QString fileName);
  bool toFile(QString fileName) {
    return toFile(fileName, _data, _base, _start);
  }

 private:
  static ByteArray hexString(quint16 adr,
                             quint8 recordType,
                             const ByteArray& data);

  quint32 _start;
  quint32 _base;
  quint32 _stringNum;
  ByteArray _data;
};

#endif  // HEX_H
