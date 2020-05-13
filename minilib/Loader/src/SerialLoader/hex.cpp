#include "hex.h"

#include <QBuffer>
#include <QDebug>
#include <QFile>
#include "bytearray.h"

bool Hex::toFile(QString fileName,
                 const ByteArray& data,
                 quint32 baseAdr,
                 quint32 startAdr) {
  QFile file(fileName);
  if (fileName.endsWith(".hex", Qt::CaseInsensitive)) {
    return toHex(&file, data, baseAdr, startAdr);
  }
  if (fileName.endsWith(".bin", Qt::CaseInsensitive)) {
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << file.fileName() << file.errorString();
      return false;
    }
    file.write(data);
    file.close();
    return true;
  }
  qDebug() << "unsupoered file format" << fileName;
  return false;
}

bool Hex::fromHex(QIODevice* src,
                  QIODevice* dest,
                  quint32* baseAdr,
                  quint32* startAdr,
                  quint32* stringNumber) {
  quint32 dataType = 0;
  quint32 offset = 0;
  quint32 newBase;
  quint32 newStart;
  quint32 currOffset;
  quint32 adrPtr = 0;
  quint32 dataSize = 0;

  *baseAdr = 0;
  *startAdr = 0;
  *stringNumber = 0;

  if (!src->isOpen()) {
    if (!src->open(QIODevice::ReadOnly)) {
      QFile* file(qobject_cast<QFile*>(src));
      if (file)
        qDebug() << file->fileName() << file->errorString();
      return false;
    }
  }

  if (!dest->isOpen()) {
    if (!dest->open(QIODevice::WriteOnly)) {
      src->close();
      QFile* file(qobject_cast<QFile*>(dest));
      if (file)
        qDebug() << file->fileName() << file->errorString();
      return false;
    }
  }

  bool error = false;
  while (!src->atEnd() && !error) {
    // read and check line
    ByteArray line = static_cast<ByteArray>(src->readLine());
    stringNumber++;
    if (line.isEmpty()) {
      qDebug() << "empty line is read";
      error = true;
      break;
    }
    if (line.length() < 11) {
      qDebug() << "too short string";
      error = true;
      break;
    }
    if (line.at(0) != ':') {
      qDebug() << "start code missing";
      error = true;
      break;
    }
    quint8 dataLen = ByteArray::fromHex(line.mid(1, 2)).at(0);
    if (line.length() < int(11 + dataLen * 2)) {
      qDebug() << "string lenght mismatch";
      error = true;
      break;
    }

    // Разбор полей параграфа и проверка КС
    QByteArray raw = ByteArray::fromHex(line.mid(1, 10 + dataLen * 2));
    offset = static_cast<quint8>(raw.at(1));
    offset = offset * 256 + static_cast<quint8>(raw.at(2));
    dataType = static_cast<quint8>(raw.at(3));
    uchar ccs = 0;
    for (int i = 0; i < raw.size() - 1; i++) {
      ccs += raw.at(i);
    }
    ccs = 1 + ~ccs;
    if (ccs != static_cast<quint8>(raw.at(raw.size() - 1))) {
      qDebug() << "checksum mismatch";
      qDebug() << "ccs =" << ccs
               << " cs =" << static_cast<quint8>(raw.at(raw.size() - 1));
      error = true;
      break;
    }

    // qDebug() << "strLen =" << strLen << "offset =" << offset << "dataType ="
    // << dataType << line;
    // Разбор данных
    switch (dataType) {
      case DataType:  // запись содержит данные двоичного файла.
        currOffset = adrPtr & 0xFFFFU;
        if (dataSize == 0) {
          adrPtr += offset;
        } else if (currOffset != offset) {
          qDebug() << "next offset isnt continue current data";
          qDebug() << "currOffset =" << QString::number(currOffset, 16)
                   << " offset =" << offset;
          error = true;
          break;
        }
        dest->write(raw.mid(4, dataLen));
        dataSize += dataLen;
        adrPtr += dataLen;
        break;
      case EofType:  // запись является концом файла.
        qDebug() << "EOF detected";
        break;
      case ExtSegAdr:  // запись адреса сегмента (подробнее см. ниже).
        newBase = static_cast<quint8>(raw.at(4));
        newBase = newBase * 256 + static_cast<quint8>(raw.at(5));
        newBase <<= 4;
        if (dataSize != 0) {        // если есть данные
          if (newBase != adrPtr) {  // и не продолжение данных
            qDebug() << "next ESA isnt continue current data";
            error = true;
            break;
          }
        } else {  // если данных нет
          adrPtr = newBase;
          qDebug() << "newBase ESA =" << newBase << "offset =" << offset;
        }
        break;
      case StartSegAdr:  // Start Segment Address Record
        qDebug() << "unsuported i16hex type";
        error = true;
        break;
      case ExtLinAdr:  // запись расширенного адреса
        newBase = static_cast<quint8>(raw.at(4));
        newBase = newBase * 256 + static_cast<quint8>(raw.at(5));
        newBase <<= 16;
        if (dataSize != 0) {        // если есть данные
          if (newBase != adrPtr) {  // и не продолжение данных
            qDebug() << "next ESA isnt continue current data";
            error = true;
            break;
          }
        } else {  // если данных нет
          adrPtr = newBase;
          // qDebug()<<"newBase ELA ="<<newBase<<"offset ="<<offset;
          qDebug("newBase ELA = %#010X, offset = %#010X", newBase, offset);
        }
        break;
      case StartLinAdr:  // Start Linear Address Record.
        newStart = static_cast<quint8>(raw.at(4));
        newStart = newStart * 256 + static_cast<quint8>(raw.at(5));
        newStart = newStart * 256 + static_cast<quint8>(raw.at(6));
        newStart = newStart * 256 + static_cast<quint8>(raw.at(7));
        (*startAdr) = newStart;
        break;
      default:  // не известный тип...
        qDebug() << "unknown record type";
        error = true;
        break;
    }
  }
  *baseAdr = adrPtr - dataSize;
  src->close();
  dest->close();
  return !error;
}

bool Hex::toHex(QIODevice* dest,
                const ByteArray& data,
                quint32 baseAdr,
                quint32 startAdr) {
  if (baseAdr & 0xF) {
    qDebug() << "align base error";
    return false;
  }

  if (data.size() < 0) {
    qDebug() << "zero size data error";
    return false;
  }

  if (!dest->isOpen()) {
    if (!dest->open(QIODevice::WriteOnly)) {
      QFile* file(qobject_cast<QFile*>(dest));
      if (file)
        qDebug() << file->fileName() << file->errorString();
      return false;
    }  // не забываать закрывать файл
  }

  quint16 offset = baseAdr >> 16;
  quint16 adr = baseAdr & 0xFFFF;
  ByteArray array;

  // guaranted by ALIGN_BASE_ERROR
  for (int i = 0; i < data.size(); i += 16, adr += 16) {
    if ((adr == 0) || (i == 0)) {  // в начале файла и при переполнении adr
      array.clear();
      array.append(offset).reverse();
      dest->write(hexString(0, ExtLinAdr, array));
      offset++;  // указывает на СЛЕДУЮЩИЙ сегмент
    }

    auto dataStr = static_cast<ByteArray>(data.mid(i, 16));
    auto str = hexString(adr, DataType, dataStr);
    dest->write(str);
  }

  array.clear();
  array.append(startAdr).reverse();
  dest->write(hexString(0, StartLinAdr, array));
  dest->write(":00000001FF\r\n");
  dest->close();
  qDebug("ok!");
  return true;
}

bool Hex::fromFile(QString fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << file.fileName() << file.errorString();
    return false;
  }
  _data.clear();
  if (fileName.endsWith(".hex", Qt::CaseInsensitive)) {
    _data.reserve(file.size() / 2);
    QBuffer buffer(&_data);
    return fromHex(&file, &buffer, &_base, &_start, &_stringNum);
  } else if (fileName.endsWith(".bin", Qt::CaseInsensitive)) {
    _data = file.readAll();
    file.close();
    _base = 0xFFFFFFFF;
    _start = 0xFFFFFFFF;
    _stringNum = _data.size();
    return true;
  }
  qDebug() << "unsupoered file format" << fileName;
  return false;
}

ByteArray Hex::hexString(quint16 adr,
                         quint8 recordType,
                         const ByteArray& data) {
  ByteArray d, r;
  d.append((quint8)data.size());
  r.append((quint16)adr);
  d.append(r.reverse());
  d.append((quint8)recordType);
  d.append(data);
  unsigned char ccs = 0;
  for (int i = 0; i < d.size(); i++) {
    ccs += d.at(i);
  }
  ccs = 1 + ~ccs;
  d.append((quint8)ccs);
  ByteArray s(":");
  s.append(d.toHex().toUpper());
  s.append("\r\n");
  return s;
}
