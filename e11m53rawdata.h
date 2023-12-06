#ifndef E11m53RAWDATA_H
#define E11m53RAWDATA_H

#include<QObject>
#include<mpfr.h>

class E11m53RawData : public QObject
{
  Q_OBJECT

  Q_PROPERTY(uint64_t m_Raw READ getRaw WRITE setRaw NOTIFY RawChanged)
  Q_PROPERTY(QString m_u64Str READ getu64Str WRITE setu64Str NOTIFY u64StrChanged)
  Q_PROPERTY(QString m_s64Str READ gets64Str WRITE sets64Str NOTIFY s64StrChanged)
  Q_PROPERTY(QString m_f64Str READ getf64Str WRITE setf64Str NOTIFY f64StrChanged)
  Q_PROPERTY(QString m_Hex READ getHex WRITE setHex NOTIFY HexChanged)
  //Q_PROPERTY(QString m_Bits READ getBits WRITE setBits NOTIFY BitsChanged)
public:
  explicit E11m53RawData(QObject *parent = nullptr)
      :m_Raw(0),m_u64Str("0"),m_s64Str("0"),m_f64Str("0"),m_Hex("0x0")
  {}
  ~E11m53RawData(){}

 Q_INVOKABLE bool getBitsbyIdx(size_t idx){
   if( ((1ULL << idx) & this->m_Raw) )
    return true;
   else
    return false;
  }

void setRaw(const uint64_t& Raw){
  this->m_Raw = Raw;
  emit RawChanged(m_Raw);
}

uint64_t getRaw() const {return m_Raw;}

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

void setf64Str(const QString& Str){
  this->m_f64Str = Str;
  emit f64StrChanged(m_f64Str);
}

QString getf64Str() const {return m_f64Str;}

void setHex(const QString& Hex){
  this->m_Hex = Hex;
  emit HexChanged(m_Hex);
}

QString getHex() const {return m_Hex;}

//void setBits(const QString& Bits){
//  this->m_Bits = Bits;
//  emit HexChanged(m_Bits);
//}

//QString getBits() const {return m_Bits;}

signals:
  void updateUi(QString &m_u64Str, QString &m_s64Str, QString &m_f64Str);
  void RawChanged(uint64_t Raw);
  void u64StrChanged(QString &u64Str);
  void s64StrChanged(QString &s64Str);
  void f64StrChanged(QString &Str);
  void HexChanged(QString &Hex);
  void BitsChanged(QString &Bits);


public slots:

  void setRawbyBit(bool predictor, size_t idx){
    if(predictor){
      uint64_t mask = 1ULL << idx;
      m_Raw = m_Raw | mask;
    }else{
      uint64_t mask = ~(1ULL << idx);
      m_Raw = m_Raw & mask;
    }
    updateRawData();
    emit updateUi(m_u64Str,m_s64Str,m_f64Str);
  }

  void setRawbyU64Str(const QString &u64Str){

    this->m_Raw = u64Str.toULongLong();
    updateRawData();
    emit updateUi(m_u64Str,m_s64Str,m_f64Str);
  }

  void setRawbyS64Str(const QString &s64Str){

    int64_t tmp = s64Str.toLongLong();
    this->m_Raw = *(uint64_t*)&tmp;
    updateRawData();
    emit updateUi(m_u64Str,m_s64Str,m_f64Str);
  }

private:
  uint64_t m_Raw;
  QString m_u64Str;
  QString m_s64Str;
  QString m_f64Str;
  QString m_Hex;
  //QString m_Bits;
  void updateRawData(){
    this->m_Hex = QString::asprintf("0x%llx", m_Raw);
    this->m_u64Str = QString::asprintf("%llu", m_Raw);
    this->m_s64Str = QString::asprintf("%lld", m_Raw);
    this->m_f64Str = QString::asprintf("%lf", *(double*)&m_Raw);

    this->m_f64Str.clear();
    mpfr_t tmp_mpfr;
    mpfr_init2(tmp_mpfr,54);
    mpfr_set_d(tmp_mpfr, *(double*)&this->m_Raw,MPFR_RNDZ);
    mpfr_exp_t tmp_exp_mpfr;
    char* tmp_chars = mpfr_get_str (nullptr, &tmp_exp_mpfr, 10, 0, tmp_mpfr, MPFR_RNDZ);
  }
};

#endif // E11m53RAWDATA_H
