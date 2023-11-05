#ifndef F64RAWDATA_H
#define F64RAWDATA_H

#include<QObject>

class F64RawData : public QObject
{
  Q_OBJECT

  Q_PROPERTY(uint64_t m_f64Raw READ getf64Raw WRITE setf64Raw NOTIFY f64RawChanged)
  Q_PROPERTY(QString m_u64Str READ getu64Str WRITE setu64Str NOTIFY u64StrChanged)
  Q_PROPERTY(QString m_s64Str READ gets64Str WRITE sets64Str NOTIFY s64StrChanged)
  Q_PROPERTY(QString m_f64Str READ getf64Str WRITE setf64Str NOTIFY f64StrChanged)
  Q_PROPERTY(QString m_f64Hex READ getf64Hex WRITE setf64Hex NOTIFY f64HexChanged)
  Q_PROPERTY(QString m_f64Bits READ getf64Bits WRITE setf64Bits NOTIFY f64BitsChanged)
public:
  explicit F64RawData(QObject *parent = nullptr)
      :m_f64Raw(0),m_u64Str("0"),m_s64Str("0"),m_f64Str("0"),m_f64Hex("0.0")
  {}
  ~F64RawData(){}

 Q_INVOKABLE bool getf64BitsbyIdx(size_t idx){
   if( ((1ULL << idx) & this->m_f64Raw) )
    return true;
   else
    return false;
  }

void setf64Raw(const uint64_t& f64Raw){
  this->m_f64Raw = f64Raw;
  emit f64RawChanged(m_f64Raw);
}

uint64_t getf64Raw() const {return m_f64Raw;}

void setu64Str(const QString& u64Str){
  this->m_u64Str = u64Str;
  emit u64StrChanged(m_u64Str);
}

QString getu64Str() const {return m_u64Str;}

void sets64Str(const QString& s64Str){
  this->m_s64Str = s64Str;
  emit s64StrChanged(m_s64Str);
}

QString gets64Str() const {return m_s64Str;}

void setf64Str(const QString& f64Str){
  this->m_f64Str = f64Str;
  emit f64StrChanged(m_f64Str);
}

QString getf64Str() const {return m_f64Str;}

void setf64Hex(const QString& f64Hex){
  this->m_f64Hex = f64Hex;
  emit f64HexChanged(m_f64Hex);
}

QString getf64Hex() const {return m_f64Hex;}

void setf64Bits(const QString& f64Bits){
  this->m_f64Bits = f64Bits;
  emit f64HexChanged(m_f64Bits);
}

QString getf64Bits() const {return m_f64Bits;}

signals:
  void updateUi(QString &m_u64Str, QString &m_s64Str, QString &m_f64Str);
  void f64RawChanged(uint64_t f64Raw);
  void u64StrChanged(QString &u64Str);
  void s64StrChanged(QString &s64Str);
  void f64StrChanged(QString &f64Str);
  void f64HexChanged(QString &f64Hex);
  void f64BitsChanged(QString &f64Bits);


public slots:

  void setF64RawbyBit(bool predictor, size_t idx){
    if(predictor){
      uint64_t mask = 1ULL << idx;
      m_f64Raw = m_f64Raw | mask;
    }else{
      uint64_t mask = ~(1ULL << idx);
      m_f64Raw = m_f64Raw & mask;
    }
    updateRawData();
    emit updateUi(m_u64Str,m_s64Str,m_f64Str);
  }

  void setF64RawbyU64Str(const QString &u64Str){

    this->m_f64Raw = u64Str.toULongLong();
    updateRawData();
    emit updateUi(m_u64Str,m_s64Str,m_f64Str);
  }

  void setF64RawbyS64Str(const QString &s64Str){

    int64_t tmp = s64Str.toLongLong();
    this->m_f64Raw = *(uint64_t*)&tmp;
    updateRawData();
    emit updateUi(m_u64Str,m_s64Str,m_f64Str);
  }

private:
  uint64_t m_f64Raw;
  QString m_u64Str;
  QString m_s64Str;
  QString m_f64Str;
  QString m_f64Hex;
  QString m_f64Bits;
  void updateRawData(){
    this->m_f64Hex = QString::asprintf("0x%llx", m_f64Raw);
    this->m_u64Str = QString::asprintf("%llu", m_f64Raw);
    this->m_s64Str = QString::asprintf("%lld", m_f64Raw);
    this->m_f64Str = QString::asprintf("%lf", *(double*)&m_f64Raw);
    this->m_f64Bits = QString::number(m_f64Raw,2);
  }
};

#endif // F64RAWDATA_H
